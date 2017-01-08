from math import sqrt

from constants import *
from physical_object import *


"""
This entity contains and manages physical objects.
"""


class PhysicsManager:
    def __init__(self):
        """Initialize physics manager."""
        self.objects = []
        self.counter = 0

    def push(self, p):
        """
        Add a physical object to the model.

        :p: physical object
        """
        self.objects.append(p)

    def reset_forces(self):
        """Reset all forces."""
        for p in self.objects:
            p.reset_forces()

    def set_forces(self):
        """Set gravity forces for the objects."""
        s = self
        ppp = s.objects
        for i in range(len(ppp)):
            for j in range(i):
                PhysicalObject.calc_gravity(ppp[i], ppp[j])

    def remove(self, p):
        """
        Find and remove object.

        :p: physical object
        """
        s = self
        for i in range(len(s.objects)):
            if p is s.objects[i]:
                print("removed object")
                del(s.objects[i])
                return

    def remove_small_objects(self, startidx=0):
        """
        Remove undisplayable objects.

        :startidx: starting index (constant optimization)
        """
        s = self
        ppp = s.objects
        for i in range(startidx, len(ppp)):
            if ppp[i].mass < MIN_MASS:
                del(ppp[i])
                s.remove_small_objects(i)
                return

    def deal_with_collisions(self):
        """Perform all collisions."""
        s = self
        ppp = s.objects
        for i in range(len(ppp)):
            for j in range(i):
                t = PhysicalObject.collide(ppp[i], ppp[j])
                if t is not None:
                    s.push(t)

    def tick(self):
        """Recomputing the forces and ticking all its elements."""
        s = self
        s.counter += 1
        s.reset_forces()
        if s.counter % 9 == 0:
            s.set_forces()
        s.remove_small_objects()
        for p in s.objects:
            p.tick()
        if s.counter % 15 == 0:
            s.deal_with_collisions()
