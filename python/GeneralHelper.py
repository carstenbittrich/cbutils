#!/usr/bin/env python

"""
"""

import os
from optparse import OptionParser

def entryInString(sParts, string):
	""" Takes list of strings and tests which is included in string.
	returns None if not included
	"""
	for entry in sParts:
		if entry in string:
			return entry
	return None


def main(argv):
	parser = OptionParser(usage="usage: %prog sample",description="Determines uncertainty of JES from output of EWUnfolding package." )
	parser.add_option('-v','--verbose',default=None, action='store_true', help='verbose output.')
	# parser.add_option("-o","--outfile",default='VaryEcm.pdf',help="output directory (default: \"VaryEcm.pdf\")")

	(options,args) = parser.parse_args()


if __name__ == '__main__':
	main(os.sys.argv[1:])