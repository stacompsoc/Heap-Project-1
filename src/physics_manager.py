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

        def _volume(r):
            return 4./3*PI*(r**3)

        def _partial_radius(p1, p2):
            # Works out the distance between points
            range = sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2) * SCALE_FACTOR

            #Checks whether the objects are touching one another surface or not
            if range >= p1.radius + p2.radius:
                return Vector([1., 1.])


            d, r1, r2 = range, p1.radius, p2.radius

            # Gets the distance between the two objects
            r = r1 + r2 - d

            v = r*r*(PI/(12.*d))*(d*d + 2*d*(r1 + r2) - 3*((r1 - r2)**2))

            first = 0. if range <= p1.radius else 1. - v/_volume(r1)
            second = 0. if range <= p2.radius else 1. - v/_volume(r2)

            return [first, second]

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

    def tick(self):
        """Recomputing the forces and ticking all its elements."""
        for p in self.phyobjs:
            p.forces['gravity'] = self.calc_gravity_vector(p)
        for p in self.phyobjs:
            p.tick()
