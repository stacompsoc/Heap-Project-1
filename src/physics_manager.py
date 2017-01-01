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
        self.counter = 0

    def push(self, p):
        """
        Add a physical object to the model.
        :p: physical object
        """
        self.phyobjs.append(p)

    def reset_forces(self):
        """Reset all forces."""
        for p in self.phyobjs:
            p.reset_forces()

    def set_forces(self):
        """
        Set gravity forces for the objects.
        Separated for more distinct profiling.
        """
        ppp = self.phyobjs
        for i in range(len(ppp)):
            for j in range(i):
                PhysicalObject.calc_gravity(ppp[i], ppp[j])

    def remove(self, p):
        """
        Find and remove object.
        :p: physical object
        """
        for i in range(len(self.phyobjs)):
            if p is self.phyobjs[i]:
                print("removed object")
                del(self.phyobjs[i])
                return

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
        """Perform all collisions."""
        ppp = self.phyobjs
        for i in range(len(ppp)):
            for j in range(i):
                t = PhysicalObject.collide(ppp[i], ppp[j])
                if t is not None:
                    self.push(t)

    def tick(self):
        """Recomputing the forces and ticking all its elements."""
        self.counter += 1
        if self.counter % 5 == 0:
            self.reset_forces()
        self.set_forces()
        self.remove_small_objects()
        for p in self.phyobjs:
            p.tick()
        if self.counter % 3 == 0:
            self.deal_with_collisions()
