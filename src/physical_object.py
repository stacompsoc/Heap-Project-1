class PhysicalObject:
    def __init__(self, mass, x, y):
        s = self
        s.mass, s.x, s.y = mass, x, y
        # all tuples are to be replaced with vectors
        s.speed, s.accel, s.forces = [0., 0.], [0., 0.], {}

    def get_forces_composition(self):
        force = [0., 0.]
        for f in self.forces:
            force[f][0] += f[0]
            force[f][1] += f[1]
        return force

    def tick(self):
        force = self.get_forces_composition()
        self.x += self.speed[0]
        self.y += self.speed[1]
        self.speed[0] += self.accel[0]
        self.speed[1] += self.accel[1]
        self.accel = [f / self.mass for f in force]

    def __str__(self):
        return "point: mass=" + str(self.mass) \
            + ", coordinates=(" + str(self.x) \
            + ", " + str(self.y) + ")"
