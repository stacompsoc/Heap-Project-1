from time import sleep
from random import random

from physics_manager import *
from physical_object import *
from display_manager import *


class Model:

    """
    Model class.

    Binds display, physics and everything together.
    """

    def __init__(self):
        """Initialize a model."""
        s = self
        print("initializing model")
        s.phy = PhysicsManager()
        s.display = DisplayManager(self.phy)

    def run(self):
        """Run the model."""
        s = self
        s.display.start()
        w, h = s.display.width, s.display.height
        for i in range(500):
            self.phy.push(PhysicalObject(
                1e23 * (random() * 1e7),
                1. + random() * 10,
                (random() * (w * 5) - 2 * w) * SCALE_FACTOR,
                (random() * (h * 5) - 2 * h) * SCALE_FACTOR,
            ))
            print(self.phy.phyobjs[-1])
        while True:
            if not self.tick():
                break
            # sleep(.001)
        self.display.stop()

    def tick(self):
        """Run the idle function of the model."""
        print("tick")
        return self.display.tick()
