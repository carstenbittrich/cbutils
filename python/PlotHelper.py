#! /usr/bin/env python

""" Several handy methods for plotting
"""

import ROOT

def ListToTH1D(list, name = "list", minRange=None, maxRange=None, Nbins = 10):
	if not minRange:
		minRange = min(list)
	if not maxRange:
		maxRange = max(list)

	histo = ROOT.TH1D(name, name, Nbins, float(minRange), float(maxRange))
	[histo.Fill(x) for x in list]
	return histo


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

