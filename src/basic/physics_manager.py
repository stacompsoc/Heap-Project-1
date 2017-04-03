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
        for i in range(len(self.objects)):
            for j in range(i):
                PhysicalObject.calc_gravity(self.objects[i], self.objects[j])

    def remove(self, p):
        """
        Find and remove object.

        :p: physical object
        """
        for i in range(len(self.objects)):
            if p is self.objects[i]:
                print("removed object")
                del(self.objects[i])
                return

    def remove_small_objects(self, startidx=0):
        """
        Remove undisplayable objects.

        :startidx: starting index (constant optimization)
        """
        for i in range(startidx, len(self.objects)):
            if self.objects[i].mass < MIN_MASS:
                del(self.objects[i])
                self.remove_small_objects(i)
                return

    def deal_with_collisions(self):
        """Perform all collisions."""
        for i in range(len(self.objects)):
            for j in range(i):
                t = PhysicalObject.collide(self.objects[i], self.objects[j])
                if t is not None:
                    self.push(t)

    def tick(self):
        """Recomputing the forces and ticking all its elements."""
        self.counter += 1
        self.reset_forces()
        # if self.counter % 9 == 0:
        self.set_forces()
        self.remove_small_objects()
        for p in self.objects:
            p.tick()
        # if self.counter % 15 == 0:
        self.deal_with_collisions()
