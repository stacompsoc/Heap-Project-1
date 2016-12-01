""" TODO: module docstring
"""
from time import sleep


class Model:
    """ TODO: class docstring
    """

    def __init__(self):
        print("initializing model")

    def run(self):
        """ TODO: run docstring
        """
        print("running model")
        while True:
            if not self.tick():
                break
            sleep(1)

    def tick(self):
        """ TODO: tick docstring
        """
        print("ticked")
        return False
