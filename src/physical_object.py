from math import pi as PI


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
        s = self
        s.mass, s.x, s.y = mass, x, y
        s.radius = (s.mass * (PI * 4./3)) ** (1./3)
        # all tuples are to be replaced with vectors
        s.speed, s.accel, s.forces = [0., 0.], [0., 0.], {}

    def get_forces_composition(self):
        """
        Calculate the sum of force vectors for the object.

        :returns: force vector
        """
        force = [0., 0.]
        for f in self.forces:
            force[0] += self.forces[f][0]
            force[1] += self.forces[f][1]
        return force

    def tick(self):
        """Tick the physical object: update its physical properties."""
        # print(str(self))
        force = self.get_forces_composition()
        # print("force == " + str(force))
        self.x += self.speed[0]
        self.y += self.speed[1]
        self.speed[0] += self.accel[0]
        self.speed[1] += self.accel[1]
        self.accel = [f / self.mass for f in force]

    def __str__(self):
        """
        Convert to string.

        :returns: str(PhysicalObject)
        """
        return "point: mass=" + str(self.mass) \
            + ", coordinates=(" + str(self.x) \
            + ", " + str(self.y) + ")" \
            + ", velocity = (" + str(self.speed[0]) \
            + ", " + str(self.speed[1]) + ")" \
            + " acceleration = (" + str(self.accel[0]) \
            + ", " + str(self.accel[1]) + ")"
