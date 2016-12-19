from math import sqrt

try:
    from scipy.constants import *
    G = gravitational_constant * 1e7
    LY = light_year
except ImportError:
    from math import pi
    G = 6.67408e-11 * 1e7
    LY = 9.4607e15

SCALE_FACTOR = 1e8
COLLISION_TRANSFER = 1./4
MIN_MASS = SCALE_FACTOR**3

PI = pi
