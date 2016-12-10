from math import sqrt
from copy import deepcopy
from constants import *
from physical_object import *
from vector import Vector
"""
This entity contains and manages physical objects.
"""


class PhysicsManager:
    def __init__(self):
        """Initialize physics manager."""
        self.phyobjs = []
        self.counter = 0

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
        force = Vector([0,0])

        def _partial_radius(p1, p2):
            """
            Calculate the coefficients of the gravity force.

            :p1: physical object 1
            :p2: physical object 2

            :returns: [x coeff, y coeff]
            """
            d = sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)
            r1, r2 = p1.radius, p2.radius
            if d >= r1 + r2:
                return [1., 1.]
            r = r1 + r2 - d
            v = r*r*(PI/12.)*(d*d + 2*d*(r1+r2) - 3*((r1-r2)**2))/d
            v1, v2 = p1.volume, p2.volume
            return [
                0. if d <= r1 else 1. - v / v1,
                0. if d <= r2 else 1. - v / v2
            ]

        for p in self.phyobjs:
            # Skips over itself
            if p == pp:
                continue

            # Copies the position vector and then works out the distance between the two points
            pos = copy.deepcopy(p.position)
            pos.substract(pp.position)
            distance = pos.magnitude()

            decr = _partial_radius(p, pp)
            coeff = G * decr[0]*p.mass * decr[1]*pp.mass / (distance ** 3)
            force.add([coeff * r[0], coeff * r[1]])
        return force

    def set_gravity_forces(self):
        """
        Set gravity forces for the objects.

        Separated for more distinct profiling.
        """
        for p in self.phyobjs:
            p.forces['gravity'] = self.calc_gravity_vector(p)

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

    def deal_with_collisions(self):
        ppp = self.phyobjs
        for i in range(len(ppp)):
            for j in range(i):
                t = PhysicalObject.collide(ppp[i], ppp[j])
                if t is not None:
                    self.push(t)

    def tick(self):
        """Recomputing the forces and ticking all its elements."""
        self.counter += 1
        if self.counter % 25 == 0:
            self.set_gravity_forces()
        self.remove_small_objects()
        for p in self.phyobjs:
            p.tick()
        if self.counter % 15 == 3:
            self.deal_with_collisions()
