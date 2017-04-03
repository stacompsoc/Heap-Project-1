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
        print("initializing model")
        self.phy = PhysicsManager()
        self.display = DisplayManager(self.phy)

    def run(self):
        """Run the model."""
        self.display.start()
        w, h = self.display.width, self.display.height
        for i in range(50):
            self.phy.push(PhysicalObject(
                MIN_MASS * (random() * SCALE_FACTOR) / 1e3,
                MIN_DENSITY + random() * (MAX_DENSITY - MAX_DENSITY),
                (random() * (w * 1) - 0 * w) * SCALE_FACTOR,
                (random() * (h * 1) - 0 * h) * SCALE_FACTOR,
            ))
        while True:
            if not self.tick():
                break
            # sleep(.001)
        self.display.stop()

    def tick(self):
        """Run the idle function of the model."""
        print("tick")
        return self.display.tick()
