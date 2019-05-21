#!/usr/bin/env python

"""
"""

# import os
import sys
import logging
import argparse
# import pprint
try:
    import colorer
    colorer.__name__
except ImportError:
    pass
try:
    import ROOT
    ROOT.PyConfig.IgnoreCommandLineOptions = True
except ImportError:
    pass


def main(argv):
    parser = argparse.ArgumentParser(
        description='template for generic python script',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("-d", '--debug',
                        default=False, action='store_true',
                        help='print in debug output')
    parser.add_argument("-N", '--Ntimes',
                        default=1, type=int,
                        help='print multiple times')
    parser.add_argument("inputs", nargs="*",
                        help="further input")
    args = parser.parse_args(argv)

    if args.debug:
        logging.basicConfig(level=logging.DEBUG)
        logging.debug("Set log level to DEBUG")
    else:
        logging.basicConfig(level=logging.INFO)
        logging.debug("Set log level to INFO")


if __name__ == "__main__":
    main(sys.argv[1:])
