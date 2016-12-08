from math import sqrt

from constants import *
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

        def _volume(r):
            return 4./3*PI*(r**3)

        def _partial_radius(p1, p2):
            range = sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)
            if range >= p1.radius + p2.radius:
                return [1., 1.]
            d, r1, r2 = range, p1.radius, p2.radius
            r = r1 + r2 - d
            v = r*r*(PI/(12.*d))*(d*d + 2*d*(r1 + r2) - 3*((r1 - r2)**2))
            first = 0. if range <= p1.radius else 1. - v/_volume(r1)
            second = 0. if range <= p2.radius else 1. - v/_volume(r2)
            return [first, second]

        for p in self.phyobjs:
            if p == pp:
                continue
            r = [p.x - pp.x, p.y - pp.y]
            r_len = sqrt(r[0]*r[0] + r[1]*r[1])
            decr = _partial_radius(p, pp)
            coeff = G * decr[0]*p.mass * decr[1]*pp.mass / (r_len ** 3)
            force[0] += coeff * r[0]
            force[1] += coeff * r[1]
        return force

    def remove_small_objects(self, startidx=0):
        """
        Remove undisplayable objects.

        :startidx: starting index (constant optimization)
        """
        ppp = self.phyobjs
        for i in range(startidx, len(ppp)):
            if ppp[i].mass < MIN_MASS:
                del(ppp[i])
                self.remove_small_objects(i)
                return

    def tick(self):
        """Recomputing the forces and ticking all its elements."""
        ppp = self.phyobjs
        for p in ppp:
            p.forces['gravity'] = self.calc_gravity_vector(p)
        self.remove_small_objects()
        for p in ppp:
            p.tick()
        for i in range(len(ppp)):
            for j in range(i):
                t = PhysicalObject.collide(self.phyobjs[i], self.phyobjs[j])
                if t is not None:
                    self.push(t)
