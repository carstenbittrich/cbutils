#!/usr/bin/env python

""" handy functions for parsing / writing tables
"""

# input
def ReadLine(filename = None, string = None, seperator = '|', offsetPositions = 0, ignorelast = 0, startLine = 0, endLine = None):
	""" parses table given as string and returns dictionary of lines, where key is entry of first column
	"""
	lines = []
	dContent = {}
	if filename:
		file = open(filename,"r")
		for line in file:
			lines.append(line)
	if string:
		lines += string.split('\n')
	cLines = 0
	for line in lines:
		cLines += 1
		if cLines < startLine:
			continue
		if endLine and cLines > endLine:
			continue

		entries = [entry.strip() for entry in line.split(seperator)]
		if len(entries) > offsetPositions:
			dContent[entries[offsetPositions]] = entries[offsetPositions+1:-ignorelast]
	return dContent

# processing
def LineDict2Table(dLines, order,allowSkip=False):
	""" turns a dict as returned by ReadLines to encapsulated lists
	argument order defines order
	"""
	if order == None:
		order = dLines.keys()
	outputList = []
	for key in order:
		if key == 'midrule':
			outputList.append(key)
			continue
		if allowSkip and not key in dLines.keys():
			continue
		line = [key]
		line += dLines[key]
		outputList.append(line)
	return outputList

def combineLines(lineDict, inputDict, fCombine):
	""" combines entries of the input dict according to definition in lineDict.
	key in lineDict is new key, value is list of keys of inputDict to combine.
	fCombine is function to combine entries of cells, has to take a list as input argument
	"""
	outputDict = {}
	for newKey in lineDict.keys():
		keysToCombine = lineDict[newKey]
		if len(keysToCombine) == 1: # nothing ot combine, just return line
			outputDict[newKey] = inputDict[keysToCombine[0]]
		else:
			outputDict[newKey] = []
			Ncells = len(inputDict[keysToCombine[0]])
			for iCell in range(Ncells):
				# build lists o combine later on
				valuesToCombine = []
				for key in keysToCombine:
					entry = inputDict[key][iCell]
					valuesToCombine.append(entry)

				combination = fCombine(valuesToCombine)
				outputDict[newKey].append(combination)
	return outputDict

# output
def PrintLatex(content, positions=2,midrule=r"\midrule"):
	""" takes list of lists (outer list: lines, inner list: cells) and returns string for latex output 
	"""
	if not type(content) == type([]):
		raise Exception

	Ncells = max([len(line) for line in content if type(line) == type([])])
	columntag = "c" + (Ncells-1)*" r "

	output  = "\\begin{tabular}{%s} \n" %columntag
	output += " \\toprule\n"

	for line in content:
		if line == 'midrule':
			output += '      %s \n' %midrule
			continue
		cells = []
		for cell in line:
			if type(cell) == str:
				cells.append(cell)
			elif type(cell) == float or type(cell) == int:
				cells.append("{:0.{n}f}".format(cell,n=positions))
			else:
				cells.append(str(cell))
		output += "    " + " & ".join(cells) + "\\\\ \n"
	output += "  \\bottomrule\n"
	output += "\\end{tabular}\n"
	return output


# testing
def testrun():
	inputfile = "testtable.txt"
	Lines = ReadLine(filename = inputfile, seperator = '|', startLine = 4, endLine = 9)
	for line in Lines:
		print line
	print "done printing"
	Lines = combineLines(Lines,)
	PrintLatex(Lines)



def main(argv):
	from optparse import OptionParser
	parser = OptionParser(usage="usage: %prog sample",description="Determines uncertainty of JES from output of EWUnfolding package." )
	parser.add_option('-v','--verbose',default=None, action='store_true', help='verbose output.')
	# parser.add_option("-o","--outfile",default='VaryEcm.pdf',help="output directory (default: \"VaryEcm.pdf\")")

	(options,args) = parser.parse_args()

	testrun()


if __name__ == '__main__':
	import os
	main(os.sys.argv[1:])

# class Table:
# 	def __init__(self):
# 		self.rows		= []
# 		self.columns	= []
# 		self.cells		= []


# class Line:
# 	def __init__(self):
# 		self.isDivider	= False
# 		self.title		= None
# 		self.cells		= []

# class Row(Line):
# 	pass

# class Column(Line):
# 	pass

# class Cell:
# 	defaultValue		= None
# 	def __init__(self, row, column, value = Cell.defaultValue):
# 		self.row 		= row
# 		self.column 	= column
# 		self.value 		= value






