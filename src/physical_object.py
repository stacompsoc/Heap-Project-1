from math import pi as PI
from vector import Vector
from constants import *

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

        s = self
        s.density = density
        s.set_mass(mass)

        # creates zero vectors
        s.speed = Vector(0, 0)
        s.accel = Vector(0, 0)
        s.position =Vector(0, 0)

        # empty list, to be filled with force vectors
        s.forces = []


    def set_mass(self, new_mass):
        """
        Change attributes of the object when the mass changes.

        :new_mass: new mass
        """
        s = self
        s.mass = new_mass
        s.volume = s.mass / s.density
        s.radius = (s.volume / (PI * 4./3)) ** (1./3)

    def get_forces_composition(self):
        """
        Calculate the sum of force vectors for the object.

        :returns: force vector
        """
        force = Vector([0, 0])
        for f in self.forces:
            force.add(f)

        return force

    def reset_forces(self):
        for f in self.forces:
            self.forces[f] = [0., 0.]

    def add_force(self, label, force):
        if label not in self.forces:
            self.forces[label] = [0., 0.]
        f = self.forces[label]
        f[0] += force[0]
        f[1] += force[1]

    @staticmethod
    def distance(p1, p2):
        """
        Calculate the distance between two objects.

        :p1: first object
        :p2: second object

        :returns: distance
        """
        return sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)

    @staticmethod
    def calc_gravity(p1, p2):
        """
        Calculate the gravity force vector between two objects.

        :p1: first object
        :p2: second object
        """
        static = PhysicalObject
        d = static.distance(p1, p2)
        m1, m2 = p1.mass, p2.mass
        r1, r2 = p1.radius, p2.radius

        def _intersection_coefficient():
            if d >= r1 + r2:
                return [1., 1.]
            r = r1 + r2 - d
            v = r*r*(PI/12.)*(d*d + 2*d*(r1+r2) - 3*((r1-r2)**2))/d
            v1, v2 = p1.volume, p2.volume
            return [
                0. if d <= r1 else 1. - v / v1,
                0. if d <= r2 else 1. - v / v2
            ]
        decr = _intersection_coefficient()
        coeff = G * decr[0]*m1 * decr[1]*m2 / (d ** 3)
        force = [
            coeff * (p2.x - p1.x),
            coeff * (p2.y - p1.y)
        ]
        p1.add_force('gravity', force)
        p2.add_force('gravity', [-force[0], -force[1]])

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

        d = static.distance(p1, p2)
        r1, r2 = p1.radius, p2.radius

        if d >= r1 + r2:
            return None
        static.set_speeds_after_collision(p1, p2)
        return static.set_masses_after_collision(p1, p2)

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

        p.speed = Vector(_get_new_speed(u1, u2, m1, m2))
        q.speed = Vector(_get_new_speed(u2, u1, m2, m1))

    def tick(self):
        """Tick the physical object: update its physical properties."""
        s = self
        force = s.get_forces_composition()

        s.position.add(s.speed)
        s.speed.add(s.accel)

        force.divideByConstant(s.mass)
        s.accel.add(force)


    def __str__(self):
        """
        Convert to string.

        :returns: str(PhysicalObject)
        """
        return "point: mass=" + str(self.mass) \
            + ", coordinates=" + str(self.position) \
            + ", velocity = " + str(self.speed) \
            + ", acceleration = " + str(self.accel)
