#! /usr/bin/env python

""" Several handy mathematical functions 
"""

def AddInQuadrature(list,positions = None):
	""" Adds elements in list in quadrature"""
	import math
	try:
		result = math.sqrt(sum([x*x for x in list]))
	except TypeError as e:
		print "input: ", list
		raise TypeError("input: ", list)
	if positions:
		result = round(result,positions)
	return result