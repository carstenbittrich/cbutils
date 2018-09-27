#!/usr/bin/env python

""" handy functions for parsing / writing tables
"""
import numpy
import math
import logging

def GetRandom(pdf, min = 0, max = 1, amount = 1, seed = None):
	""" returns list of random numbers distributed according to pdf
	random numbers are generated using hit-and-miss approach
	pdf - probability density function
	min, max - allowed range for random number (default = (0 - 1))
	threshold - maximal value of pdf (default = 1)
	amount - number of random numbers (default = 1)
	if amount == 1 returns number, if > 1 returns list
	seed - no seed set if == None
	"""
	randoms = []
	if (seed != None):
		numpy.random.seed(seed)

	threshold = pdf.threshold

	for i in range(amount):
		found = False
		while not found:
			guess = numpy.random.uniform(min, max)
			keep  = numpy.random.uniform(0,threshold)
			if keep < pdf(guess):
				found = True
		randoms.append(guess)

	if len(randoms) == 1:
		return randoms[0]
	return randoms

def pdf(x):
	return x



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

class PDF:
	""" base class for PDF functions
	must also provide a threshold value
	"""
	def __init__(self):
		pass

	def __call__(self, value):
		pass

class BreitWigner(PDF):
	""" PDF for Breit-Wigner distribution
	by default in relativistic form, non-relativistic is available via rel in constructor
	"""
	def __init__ (self, mass, width, rel = True):
		self.mass = mass
		self.width = width
		self.rel = rel
		if rel:
			self.threshold = 1./(mass*mass * width*width)
		else:
			self.threshold = 2./(math.pi * self.width)

	def __call__(self, value):
		m = self.mass
		w = self.width
		if self.rel:
			diff = (value*value - m*m)
			return 1./(diff*diff + value*value*w*w)
		else:
			diff = (value - m)
			return 1./(2*math.pi) * w/(diff*diff + 0.25*w*w)

class Gaussian(PDF):
	""" PDF for Gaussian distribution
	"""
	def __init__(self, mean, width):
		self.mean = mean
		self.width = width
		self.threshold = 1./(math.sqrt(2. * math.pi * self.width * self.width))

	def __call__(self, value):
		return 1./(math.sqrt(2. * math.pi * self.width * self.width)) * math.exp(-((value - self.mean)*1.0*(value - self.mean)) / (2. * self.width * self.width))

