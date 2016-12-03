from math import sqrt
from scipy.constants import gravitational_constant as G
from physical_object import *


"""
This entity contains and manages physical objects.
"""


class PhysicsManager:
    def __init__(self):
        """Initialize physics manager."""
        self.phyobjs = []

    def push(self, p):
        """
        Add a physical object to the model.

        :p: physical object
        """
        self.phyobjs.append(p)

    def calc_gravity_vector(self, pp):
        """
        Calculate the vector of gravity force for a particular physical object.

        :pp: physical object.

        :returns: force vector
        """
        force = [0., 0.]
        for p in self.phyobjs:
            if p == pp:
                continue
            r = [p.x - pp.x, p.y - pp.y]
            r_len = sqrt(r[0]*r[0] + r[1]*r[1])
            coeff = G * p.mass * pp.mass / (r_len ** 3)
            force[0] += coeff * r[0]
            force[1] += coeff * r[1]
        return force

    def tick(self):
        """Recomputing the forces and ticking all its elements."""
        for p in self.phyobjs:
            p.forces['gravity'] = self.calc_gravity_vector(p)
        for p in self.phyobjs:
            p.tick()
