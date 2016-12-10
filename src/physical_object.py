from math import pi as PI
from vector import Vector

"""
This entity represents a physical object, i.e. an object, which has physical matter in the context of the model.
"""


class PhysicalObject:
    def __init__(self, mass, x, y):
        """
        Initialize physical object.

        :mass: mass
        :x: x coordinate
        :y: y coordinate
        """


        self.mass = mass
        self.position = vector([x,y])


        self.radius = (s.mass * (PI * 4./3)) ** (1./3)

        # creates zero vectors
        self.speed = vectors([0, 0])
        self.accel = vectors([0, 0])

        # empty list, to be filled with force vectors
        self.forces = []


    def get_forces_composition(self):
        """
        Calculate the sum of force vectors for the object.

        :returns: force vector
        """
        force = vector([0, 0])
        for f in self.forces:
            force.add(f)

        return force

    def tick(self):
        """Tick the physical object: update its physical properties."""
        # print(str(self))
        force = self.get_forces_composition()
        # print("force == " + str(force))

        self.position.add(self.speed)
        self.speed.add(self.accel)

        self.accel.add(force.divideByConstant(self.mass))

    def __str__(self):
        """
        Convert to string.

        :returns: str(PhysicalObject)
        """
        return "point: mass=" + str(self.mass) \
            + ", coordinates=" + str(self.position) \
            + ", velocity = " + str(self.speed) \
            + ", acceleration = " + str(self.accel)
