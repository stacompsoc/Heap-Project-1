from constants import *
from vector import Vector
from operator import __mul__
"""
This entity represents a physical object, i.e. which has physical matter.
"""


class PhysicalObject:
    def __init__(self, mass, density, x, y):
        """
        Initialize physical object.

        :mass: mass
        :x: x coordinate
        :y: y coordinate
        """
        self.density = density
        self.set_mass(mass)
        self.position = Vector(x, y)
        # all tuples are to be replaced with vectors
        self.speed = Vector(0, 0)
        self.accel = Vector(0, 0)
        self.forces = {}

    def set_mass(self, new_mass):
        """
        Change attributes of the object when the mass changes.

        :new_mass: new mass
        """
        self.mass = new_mass
        self.volume = self.mass / self.density
        self.radius = (self.volume / (PI * 4./3)) ** (1./3)

    def get_forces_composition(self):
        """
        Calculate the sum of force vectors for the object.

        :returns: force vector
        """
        force = Vector(0, 0)
        for key, f in self.forces.items():
            force += f
        return force

    def reset_forces(self):
        """Reset all forces affecting the object's dynamics."""
        for f in self.forces:
            self.forces[f] = Vector(0, 0)

    def add_force(self, label, force):
        """Add the force associated with the label to all forces."""
        if label not in self.forces:
            self.forces[label] = Vector(0, 0)
        self.forces[label] += force

    @staticmethod
    def calc_gravity(p1, p2):
        """
        Calculate the gravity force vector between two objects.

        :p1: first object
        :p2: second object
        """
        static = PhysicalObject
        d = abs(p1.position - p2.position)
        m1, m2 = p1.mass, p2.mass
        r1, r2 = p1.radius, p2.radius

        def _intersection_coefficient():
            if d >= r1 + r2:
                return [1., 1.]
            r = r1 + r2 - d
            v = r*r*(PI/12.)*(d*d + 2*d*(r1+r2) - 3*((r1-r2)**2))/d
            v1, v2 = p1.volume, p2.volume
            return Vector(
                0. if d <= r1 else 1. - v / v1,
                0. if d <= r2 else 1. - v / v2
            )
        decr = _intersection_coefficient()
        coeff = G * decr[0]*m1 * decr[1]*m2 / (d ** 3)
        force = (p2.position - p1.position) * coeff
        p1.add_force('gravity', force)
        p2.add_force('gravity', -force)

    @staticmethod
    def collide(p1, p2):
        """
        Collide two objects.

        :p1: first object
        :p2: second object
        :returns: an asteroid or None
        """
        static = PhysicalObject
        if p1 is p2:
            return None
        if abs(p1.position - p2.position) >= p1.radius + p2.radius:
            return None
        static.set_speeds_after_collision(p1, p2)
        static.set_masses_after_collision(p1, p2)
        return None

    @staticmethod
    def set_speeds_after_collision(p1, p2):
        """
        Set speeds after collision.

        :p1: first object
        :p2: second object
        """
        u1, m1, u2, m2 = p1.speed, p1.mass, p2.speed, p2.mass
        p1.speed = (u1*(m1-m2) + u2*2.*m2) / (m1 + m2)
        p2.speed = (u1*2.*m1 - u2*(m1-m2)) / (m1 + m2)

    @staticmethod
    def set_masses_after_collision(p, q):
        """
        Set masses after collision.

        :p: first object
        :q: second object
        :returns: an object (asteroid) spawned after collision
        """
        static = PhysicalObject
        m1, m2 = p.mass, q.mass
        if m1 < m2:
            return static.set_masses_after_collision(q, p)
        m3 = m1 - m2
        if m3 > m2:
            m3 = m2
        m3 *= COLLISION_TRANSFER
        p.set_mass(m1 + m3)
        q.set_mass(m2 - m3)
        return None

    def tick(self):
        """Tick the physical object: update its physical properties."""
        force = self.get_forces_composition()
        self.position += self.speed
        self.speed += self.accel
        self.accel = force / self.mass

    def __str__(self):
        """
        Convert to string.

        :returns: str(PhysicalObject)
        """
        return "point: mass=" + str(self.mass) \
            + ", coordinates=" + str(self.position) \
            + ", velocity = " + str(self.speed) \
            + ", acceleration = " + str(self.accel) \
            + ", radius = " + str(self.radius)
