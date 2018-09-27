#!/usr/bin/env python

"""
FileHandler

Module for retrieving histograms and graphs saved to ROOT files.
Also has methods from inspecting ROOT files like getting a list
of existing histograms or TTrees.
"""

#------------------------------------------------------------------------------

import ROOT,os
import copy

#------------------------------------------------------------------------------
# FileHandler Class
#------------------------------------------------------------------------------
class FileHandler(object):
#______________________________________________________________________________
    def __init__(self,filename=None,state='READ'):
        """
        Initializes an instance of HistGetter with some input files given
        by files.  files can be a single file or a list.
        """
        self.file = None
        self.filename = filename
        self.sample = None
        self._hasFile = False
        if filename:
            self.file = ROOT.TFile.Open(filename,state)
            if self.file:
                self._hasFile = True

#______________________________________________________________________________
    def make_copy(self,obj): 
        """
        A helper function to create copy of an object
        """
        try:
            newobj = obj.__class__(obj) # bug?: doesn't have unique name
        except:
            newobj = obj.Clone()
        return newobj

#______________________________________________________________________________
    def get(self,name):
        """
        Returns a copy of the ROOT object with name
        """
        obj = None
        if not self._hasFile:
            print "no file associated"
            return None
        
        self.file.cd()
        temp = self.file.Get(name)
        if not temp:
            print "did not find object with name '%s' in file '%s'" %(name,self.file.GetName())
            return None
        
        obj = self.make_copy(temp)            
        return obj

#_______________________________________________________________________________
    def writeToFile(self,obj,name=""):
        """
        stores the given object in a root file
        """
        if not name:
            name = obj.GetName()
            
        if self._hasFile:
            dir = os.path.dirname(name)
            name = os.path.basename(name)
            d = self.file.GetDirectory(dir)
            if not d:
                d = self.makeDirectory(self.file,dir)
            d.cd()
            obj.Write(name)

#_______________________________________________________________________________
    def makeDirectory(self,curDir,dirName):
        """
        (recursively) creates (sub)directories in a rootfile
        """
        dirName.rstrip('/')
        dir_split = dirName.split('/')
        lead_dir = dir_split[0]
        sub_dirs = dir_split[1:]

        d = curDir.GetDirectory(lead_dir)
        if not d:
            d = curDir.mkdir(lead_dir)
    
        if sub_dirs:
            return self.makeDirectory(d,'/'.join(sub_dirs))
        else:
            return d     
#______________________________________________________________________________
    def getObjectNames(self,type,strict=False):
        obj_names = {}
        if not self._hasFile:
            print "no file associated"
            return obj_names
        #----------------------------------------------------------------------
        def traverseDir(directory,objects):
            # check objects corresponding to the keys for their type
            for key in directory.GetListOfKeys():
                #print "looking for key '%s'" % key.GetName()
                obj = directory.Get(key.GetName())
                if (strict and obj.Class().GetName() == type) or (not strict and obj.Class().InheritsFrom(type)):
                    #print "found object of type '%s' at '%s'" % (obj.Class().GetName(),obj.GetName())
                    objects[directory.GetPath().rstrip('/') + '/' + obj.GetName()] = obj
                    ROOT.SetOwnership(obj,False)
                # if object is a directory -> scan this as well
                elif isinstance(obj,ROOT.TDirectory):
                    traverseDir(obj,objects)
            return objects
        #----------------------------------------------------------------------
        basedir = self.file.GetPath().rstrip('/') + '/'
        objects = traverseDir(self.file,obj_names)
        result = {k.replace(basedir,""):copy.deepcopy(v) for k,v in objects.items()}
        for value in result.values():
            ROOT.SetOwnership(value,False)
        return result
    
#______________________________________________________________________________
    def getTreeEntries(self,trees = []):
        if not self._hasFile:
            print "no file associated"
            return None
        if not trees:
            trees = self.get_obj_names("TTree").keys()
        if not isinstance(trees,list):
            trees = [trees]
        t_entries = {}
        if trees:
            for treename in trees:
                t = self.get(treename)
                if t:
                    t_entries[t.GetName()] = t.GetEntries()
                else:
                    print "tree '%s' not found in file '%s'" % (treename,self.file.GetName())
        return t_entries

#______________________________________________________________________________
    def close(self):
        if self._hasFile:
            self.file.Close()
            self.file = None
        self._hasFile = False


#----------------------------------------
def __GetObjectsOfTypeWrapper(argv):
    getter = FileHandler(argv.filename)
    obj = getter.getObjectNames(argv.type,argv.strict)
    for t,o in obj.items():
        print "found object of type (%s) at: %s" %(o.Class().GetName(),t)
    getter.close()

#---------------------------------------
def __PrintTreeEntriesWrapper(argv):
    tree_entries = {}
    for file in argv.filelist:
        getter = FileHandler(file)
        t = getter.getTreeEntries(argv.trees)
        getter.close()
        for tname, tentries in t.items():
            if tname in tree_entries:
                tree_entries[tname] += tentries
            else:
                tree_entries[tname] = tentries
    for tname,tentries in tree_entries.items():
        print "found tree '%s' with %.0f entries" % (tname,tentries)

#-------------------------------------------------------------------------------
def __FileSizeWrapper(argv):
    import re
    # initialisation
    nFiles = len(argv.filelist)
    totalSize = 0
    totalEntries = 0
    blockSize={}
    for block in argv.blockList:
        blockSize[block]=0

    # loop over given files
    for file in argv.filelist:
        getter = FileHandler(file)
        tree = getter.get(argv.tree)
        totalEntries += tree.GetEntriesFast()
        totalSize += getter.file.GetSize()
        # loop over block patterns
        for block in argv.blockList:
            for branch in tree.GetListOfBranches():
                if re.search(block,branch.GetName()):
                    blockSize[block] = blockSize[block] + branch.GetZipBytes()
        getter.close()

    # print summary
    eventSize = (totalSize/(totalEntries*1024.))
    print "****************************************"
    print "ROOT FILE SUMMARY"
    print "Found ",nFiles," ROOT Files"
    print "Found ",totalEntries," ROOT Entries"
    print "Total Size of root files: %.2f MB" % (totalSize/(1024.0*1024.0))
    print "Size per Event: %.2f kB " % eventSize
    print "****************************************"

    print "****************************************"
    print "BLOCK BY BLOCK SUMMARY"
    totalBlockSize = sum(blockSize.values())/(totalEntries * 1024.)
    for block in argv.blockList:
        print "Block %20s uses %5.2f kB/evt (%4.1f%%)" % (block,blockSize[block]/(totalEntries*1024.),blockSize[block]/(totalEntries*1024.)/eventSize * 100)
    print "Total Block Size is (with double-counting): %.2f kB (%4.1f%%)" % (totalBlockSize,totalBlockSize*100.0/eventSize)
    print "****************************************"


def MergeFiles(files, output='output.root'):
    content = []
    allKeys = {}
    ToWrite = []
    for f in files:
        dic = {}
        f = FileHandler(f)
        dic['TH1'] = f.getObjectNames("TH1")
        dic['TTree'] = f.getObjectNames("TTree")
        content.append(dic)

    for key in ['TH1', 'TTree']:
        allKeys[key] = [ h for h in content[0][key].keys() if h in content[1][key].keys()]

    output = ROOT.TFile(output,"RECREATE")

    for obj in allKeys.keys():
        if obj == 'TTree':
            continue
        for key in allKeys[obj]:
            objs = [f[obj][key] for f in content]
            if obj == 'TH1':
                obj1 = objs[0]
                objs = objs[1:]
            Tlist = ROOT.TList()
            [Tlist.Add(o) for o in objs]
            print Tlist.GetEntries()
            if obj == 'TH1':
                obj1.Merge(Tlist)
            else:
                obj1 = ROOT.TTree.MergeTrees(Tlist)

            ToWrite.append(obj1)
    output.cd()
    [o.Write() for o in ToWrite]

    for treeName in allKeys['TTree']:
        chain = ROOT.TChain(treeName)
        [chain.Add(f) for f in files]
        chain.Merge(output,10000)

def parsePathString(string):
    split = string.split(":")
    return split[0], split[1]

def getObject(string):
    filename, name = parsePathString(string)
    fh = FileHandler(filename)
    obj = fh.get(name)
    return fh, obj

def Extract(files, outdir, replace = True):
    import os

    def getOutName(outdir, string):
        filename = string + ".pdf"
        if "/" in string:
            relpath = "/".join(string.split("/")[:-1])
            outdir = SaveDir(os.path.join(outdir,relpath))
            filename = string.split("/")[-1] + ".pdf"
        outfile = os.path.join(outdir,filename)
        return outfile

    for file in files:
        if not outdir: # use default outdir name
            outdir = file.replace(".root","")
        outdir = SaveDir(outdir)
        fh = FileHandler(file)
        tcanvas = fh.getObjectNames("TCanvas")
        print tcanvas
        for key in tcanvas.keys():
            obj = tcanvas[key]
            obj.SaveAs(getOutName(outdir, key))
            obj.Print(getOutName(outdir, key).replace(".pdf","print.pdf"))

        drawable = {}

        trooplot = fh.getObjectNames("RooPlot")
        drawable.update(trooplot)
        th1 = fh.getObjectNames("TH1")
        drawable.update(th1)
        for key in drawable.keys():
            outputname = getOutName(outdir, key)
            if os.path.isfile(outputname) and not replace:
                continue
            obj = drawable[key]
            name = obj.GetTitle()
            c1 = ROOT.TCanvas("c1"+name,name,1200,900)
            c1.cd()
            c1.SetTitle(obj.GetTitle())
            obj.Draw()
            c1.SaveAs(outputname)


def SaveDir(path):
    if os.path.isfile(path):
        raise Exception("invalid output dir name")
    if not os.path.isdir(path):
        os.makedirs(path)
    path = os.path.abspath(path)
    return path

#===============================================================================
def main(argv):
    from optparse import OptionParser
    parser = OptionParser(usage="usage: %prog sample",description="""Module for retrieving histograms and graphs saved to ROOT files.
Also has methods from inspecting ROOT files like getting a list
of existing histograms or TTrees.""" )
    parser.add_option('-v','--verbose',default=None, action='store_true', help='verbose output.')
    parser.add_option('--merge',default=None, action='store_true', help='merge files.')
    parser.add_option("--extract", default=None, action='store_true', help='extract histograms and save as pdf.')
    parser.add_option("--no-replace", default=None, action='store_true', help="don't replace old files (faster)")

    parser.add_option('--output',default="output.root", help='output file name (default: output.root).')
    parser.add_option('--outdir',default=None, help='output folder name (default: input file name without ".root").')
    parser.add_option("-b",'--batch',default=None, action='store_true', help='starts root in batch mode (faster).')

    # parser.add_option("-o","--outfile",default='VaryEcm.pdf',help="output directory (default: \"VaryEcm.pdf\")")

    (options,files) = parser.parse_args()

    if options.batch:
        ROOT.gROOT.SetBatch(True)

    if options.merge:
        MergeFiles(files, options.output, replace=not options.no-replace)


    if options.extract:
        Extract(files, options.outdir)

if __name__ == "__main__":
    import sys
    main(sys.argv[1:])