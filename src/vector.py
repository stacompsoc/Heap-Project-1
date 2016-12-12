import math
from copy import deepcopy

class Vector:
    """
        Parameters: Takes in a list of numeric components
    """
    def __init__(self, components):
        self._components = components
        self._index = 0
        self._max = len(components)

    # Returns string representation to print
    def __str__(self):
        string = "("
        for i, part in enumerate(self):
            if i != self._max - 1:
                string += str(part) + ", "
            else:
                string += str(part)
        string += ")"
        return string

    # Returns the length of the object
    def __len__(self):
        return (self._max - 1)

    # Makes the object an iterable (like a list or string)
    def __iter__(self):
        return self

    # Allows the object to be indexed into and changed
    def __setitem__(self, index, value):
        self._components[index] = value

    # Allows user to get a value at a certain index in the object
    def __getitem__(self, index):
        return self._components[index]

    # Allows the object to be iterated over
    def __next__(self):
        if self._index == self._max:
            self._index = 0
            raise StopIteration
        else:
            value = self._components[self._index]
            self._index += 1
            return value
    """
        Returns a copy of the vector
    """
    def clone(self):
        clone = deepcopy(self)
        return clone

    """
        Checks whether the vectors have the same number of components.
        For internal use only
    """
    def _checkMistmatchingVector(self, vector):
        if self._max - 1 != len(vector):
            raise Exception("Mismatching number of components")

    """
        Adds the vector passed to the current object (vector)
    """
    def add(self, vector):
        self._checkMistmatchingVector(vector)
        for i, element in enumerate(vector):
            self[i] += element

    """
        Substracts the vector passed from the current object (vector)
    """
    def substract(self, vector):
        self._checkMistmatchingVector(vector)
        for i, element in enumerate(vector):
            self[i] -= element

    """
        Mutliples the current object (vector) by the vector passed
    """
    def mutliple(self, vector):
        self._checkMistmatchingVector(vector)
        for i, component in enumerate(vector):
            self[i] *= component

    """
        Mutliples the current object (vector) by a constant
    """
    def mutlipleByConstant(self, constant):
        for i in range(self._max):
            self[i] *= 5

    """
        Divides the current object (vector) by a constant
    """
    def divideByConstant(self, constant):
        constant = 1/constant
        self.mutlipleByConstant(constant)

    """
        Works out the dot product for the current vector
        and the vector passed

        Returns: the dot product
    """
    def dotProduct(self, vector):
        dotProduct = 0
        self._checkMistmatchingVector(vector)

        for index, element1 in enumerate(self):
            dotProduct += element1 * vector[index]
        return dotProduct

    """
        Calculates the magnitude of the current vector

        Returns: the magnitude
    """
    def magnitude(self):
      magnitude = 0
      for currentElement in self:
          magnitude += currentElement**2

      magnitude = math.sqrt(magnitude)
      return magnitude

    """
        Calculates the angle between two vector

        Returns: the angle in radians
    """
    def angleBetween(self, vector):
        mag1 = self.magnitude()
        print(mag1)
        mag2 = vector.magnitude()
        print(mag2)
        dotProduct = self.dotProduct(vector)
        return math.acos(dotProduct/(mag1*mag2))

    """
        Returns the unit vector of the current
        vector
    """
    def getUnitVector(self):
        vector = self.clone()
        magnitude = vector.magnitude()
        vector.divideByConstant(magnitude)
        return magnitude
