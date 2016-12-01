class MassObject:
    def __init__(self, mass, x, y):
        self.mass = mass
        self.x = x
        self.y = y

    def __str__(self):
        return "point: mass=" + str(mass) \
            + ", coordinates=(" + str(x) \
            + ", " + str(y) + ")"
