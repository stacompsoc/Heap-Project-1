from time import sleep
from random import randint

from physics_manager import *
from physical_object import *
from display_manager import *


w, h = 1280, 960


class Model:

    """
    Model class.

    Binds display, physics and everything together.
    """

    def __init__(self):
        """Initialize a model."""
        print("initializing model")
        self.phy = PhysicsManager()
        for i in range(50):
            self.phy.push(PhysicalObject(
                randint(1e9, 1e12),
                randint(0, w),
                randint(0, h)))
        self.display = DisplayManager(self.phy)

    def run(self):
        """Run the model."""
        self.display.start(w, h)
        while True:
            if not self.tick():
                break
            # sleep(.001)
        self.display.stop()

    def tick(self):
        """Run the idle function of the model."""
        print("tick")
        return self.display.tick()
