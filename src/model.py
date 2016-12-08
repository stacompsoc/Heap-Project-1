from time import sleep
from random import randint

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
        for i in range(50):
            self.phy.push(PhysicalObject(
                float(randint(1e9, 1e12)),
                float(randint(0, s.display.width) * SCALE_FACTOR),
                float(randint(0, s.display.height) * SCALE_FACTOR)))
        while True:
            if not self.tick():
                break
            # sleep(.001)
        self.display.stop()

    def tick(self):
        """Run the idle function of the model."""
        print("tick")
        return self.display.tick()
