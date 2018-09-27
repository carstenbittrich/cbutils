#!/usr/bin/env python

"""
"""

import math
import os, copy
from optparse import OptionParser
import logging
# logging = logging.getLogger( 'mylogging' ) 
# hdl = logging.StreamHandler()
# form = logging.Formatter( '%(levelname)s: %(message)s [function: %(funcName)s, line: %(lineno)s]' )
# hdl.setFormatter( form )
# logging.addHandler( hdl )
# logging.propagate = 0
# logging.setLevel( logging.INFO )
import tabulate

def main(argv):
	parser = OptionParser(usage="usage: %prog sample",description="Determines uncertainty of JES from output of EWUnfolding package." )

	# parser.add_option('-d','--debug',default=None, action='store_true', help='use logging level DEBUG.')
	parser.add_option('-d','--download',default=False, action='store_true', help='download joboption to current directory.')

	# parser.add_option("-o","--outfile",default='VaryEcm.pdf',help="output directory (default: \"VaryEcm.pdf\")")

	(options,files) = parser.parse_args()

	# if options.debug:
	# 	logging.basicConfig(level=logging.DEBUG)
	# 	logging.info("Set log level to DEBUG")
	# else:
	# 	logging.basicConfig(level=logging.INFO)
	# 	logging.info("Set log level to INFO")

	# if options.input is None:
	# 	logging.error("pease specify input file with '-i'.")
	# 	return

	logging.debug("Done initializing")

	for f in files:
		name  = f.split("/")[-1]
		name  = name.split(":")[-1]
		infos = name.split(".")
		if (len(infos) < 5):
			raise Exception("Couldn't parse all information from filename. Is it valid?")
		(campeign, sqrts) = infos[0].split("_")
		campeign = campeign.strip("mc")
		dsid = infos[1]
		physicsName = infos[2]
		fileType = infos[-2]
		tags = infos[-1]

		svnUser = "cbittric"

		urlPrefix = "https://svnweb.cern.ch/trac/atlasoff/browser/"
		svnPrefix = "svn+ssh://" + svnUser + "@svn.cern.ch/reps/atlasoff/"
		suffix = "Generators/MC"+campeign+"JobOptions/trunk/share/DSID"+dsid[:3]+"xxx/MC"+campeign+"."+dsid+"."+physicsName+".py"

		url = urlPrefix + suffix
		svn = svnPrefix + suffix

		if options.download:
			import subprocess
			subprocess.call("svn export "+svn+" .", shell=True)
		else:
			logging.info(name + ":")
			print url
			print svn

		

#	for store in stores:
#		print store['name'], ": ", store['acceptance'], " +- ", store['statuncertainty']


if __name__ == '__main__':
	main(os.sys.argv[1:])
