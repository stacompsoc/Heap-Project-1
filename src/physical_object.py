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
        s.density = 1./1.
        s.set_mass(mass)
        s.x, s.y = x, y
        # all tuples are to be replaced with vectors
        s.speed, s.accel, s.forces = [0., 0.], [0., 0.], {}

    def set_mass(self, new_mass):
        """
        Change attributes of the object when the mass changes.

        :new_mass: new mass
        """
        s = self
        s.mass = new_mass
        s.volume = s.mass * s.density
        s.radius = (s.volume * (PI * 4./3)) ** (1./3)

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

    @staticmethod
    def collide(p, q):
        if p is q:
            return None
        d = sqrt((p.x - q.x)**2 + (p.y - q.y)**2) * SCALE_FACTOR
        r1, r2 = p.radius, q.radius
        if d >= r1 + r2:
            return None
        PhysicalObject.set_speeds_after_collision(p, q)
        return PhysicalObject.set_masses_after_collision(p, q)

    @staticmethod
    def set_masses_after_collision(p, q):
        """
        Set masses after collision.

        :p: first object
        :q: second object

        :returns: an object spawned after collision
        """
        m1, m2 = p.mass, q.mass
        if m1 < m2:
            return PhysicalObject.set_masses_after_collision(q, p)
        m3 = m1 - m2
        if m3 > m2:
            m3 = m2
        m3 *= COLLISION_TRANSFER
        p.set_mass(m1 + m3)
        q.set_mass(m2 - m3)
        return None

    @staticmethod
    def set_speeds_after_collision(p, q):
        """
        Set speeds after collision.

        :p: first object
        :q: second object
        """
        u1, m1, u2, m2 = p.speed, p.mass, q.speed, q.mass

        def _get_new_speed(u1, u2, m1, m2):
            return [
                (u1[0] * (m1 - m2) + 2 * m2 * u2[0]) / (m1 + m2),
                (u1[1] * (m1 - m2) + 2 * m2 * u2[1]) / (m1 + m2)
            ]
        p.speed = _get_new_speed(u1, u2, m1, m2)
        q.speed = _get_new_speed(u2, u1, m2, m1)

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
