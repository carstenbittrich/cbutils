#!/usr/bin/env python

"""
"""
import os
import yaml

from optparse import OptionParser

def ReadFromFile(filename, default = None):
    """ returns object stores in file 'filename'.
    If default not None and Exception accures, default is returned 
    """
    try:
        file = open(filename,'r')
        object = yaml.load(file.read())
        file.close()
        return object
    except Exception, e:
        if default == None:
            raise IOError("Could not read file %(file)s with default %(default)s" % {'file': filename, 'default': default})
        return default

def WriteToFile(object, filename):
    """ helper function to write object to file 'filename'
    """
    file = open(filename,'w')
    file.write(yaml.dump(object, default_flow_style=False))
    file.close()

def main(argv):
	parser = OptionParser(usage="usage: %prog sample",description="Determines uncertainty of JES from output of EWUnfolding package." )
	parser.add_option('-v','--verbose',default=None, action='store_true', help='verbose output.')
	# parser.add_option("-o","--outfile",default='VaryEcm.pdf',help="output directory (default: \"VaryEcm.pdf\")")

	(options,args) = parser.parse_args()


if __name__ == '__main__':
	main(os.sys.argv[1:])