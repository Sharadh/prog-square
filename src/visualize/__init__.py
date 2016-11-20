import os
import sys


P2_SRC_DIR = os.path.realpath(os.path.dirname(os.path.dirname(__file__)))
if P2_SRC_DIR not in sys.path:
    sys.path.insert(0, P2_SRC_DIR)
