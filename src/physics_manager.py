from math import sqrt
from physical_object import *


G = 6.67300E-11


class PhysicsManager:
    def __init__(self):
        self.phyobjs = []

    def push(phyobj):
        self.phyobjs += phyobj

    def calc_gravity_vector(self, pp):
        force = (0., 0.)
        for p in self.phyobjs:
            if p == pp:
                continue
            rdiff = (p.x - pp.x, p.y - pp.y)
            rdabs = sqrt(rdiff[0] ** 2 + rdiff[1] ** 2)
            runit = (r / rdabs for r in rdiff)
            coeff = G * p.mass * pp.mass / (rdabs ** 2)
            force[0] += -coeff * runit[0]
            force[1] += -coeff * runit[1]

    def __tick__(self):
        for p in self.phyobjs:
            p.forces['gravity'] = self.calc_gravity_vector(p)
        for p in self.phyobjs:
            tick(p)
