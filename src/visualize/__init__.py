import os
import sys

# Add this top-level module to sys.path so it can be accessed by submodules
P2_SRC_DIR = os.path.realpath(os.path.dirname(os.path.dirname(__file__)))
if P2_SRC_DIR not in sys.path:
    sys.path.insert(0, P2_SRC_DIR)
