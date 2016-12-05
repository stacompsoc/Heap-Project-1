from constants import *


"""
This entity represents a physical object, i.e. which has physical matter.
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

    def collide(self, q):
        """
        Dirtily calculates collisions.

        :q: other object

        :returns: new speed
        """
        s = self
        if s is q:
            return [0., 0.]
        d = sqrt((s.x - q.x)**2 + (s.y - q.y)**2) * SCALE_FACTOR
        r1, r2 = s.radius, q.radius
        if d >= r1 + r2:
            return [0., 0.]
        u1, m1, u2, m2 = s.speed, s.mass, q.speed, q.mass
        ret = [
            (u1[0] * (m1 - m2) + 2 * m2 * u2[0]) / (m1 + m2),
            (u1[1] * (m1 - m2) + 2 * m2 * u2[1]) / (m1 + m2)
        ]
        return [ret[0] - s.speed[0], ret[1] - s.speed[1]]

    def tick(self):
        """Tick the physical object: update its physical properties."""
        s = self
        force = s.get_forces_composition()
        s.x += s.speed[0]
        s.y += s.speed[1]
        s.speed[0] += s.accel[0]
        s.speed[1] += s.accel[1]
        s.accel = [f / s.mass for f in force]

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
