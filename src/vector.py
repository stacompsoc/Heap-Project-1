from math import sqrt

class Vector:
    def __init__(self, *args):
        self._components = list(args)
        self._max = len(self._components)
        self._index = 0;

    def __str__(self):
        string = '(' + ','.join(str(e) for e in self._components) + ')'
        return string

    def __iter__(self):
        return self;

    def __len__(self):
        return self._max

    def __next__(self):
        if self._index < self._max:
            value = self._index
            self._index += 1
            return self._components[value]
        else:
            raise StopIteration

    def __getitem__(self, index):
        return self._components[index]

    def __setitem__(self, index, value):
        self._components[index] = value

    def _checkDimension(self, v2):
        if not(self._max == len(v2)):
            raise Exception("Error vectors don't have matching dimensions")

    def _createEmptyVector(self, size):
        emptyVector = Vector(0,0,0)
        return emptyVector


    def __add__(self, v2):
        """
            Method allows vectors to be added
            like normal numeric value (i.e. a + b).
            Well throw an excption if the vectors don't
            have the same dimensions.
            Returns: the resultant vector of the operation
        """
        self._checkDimension(v2)
        v3 = self._createEmptyVector(self._max)
        for element in range(self._max):
            v3[element] = self[element] + v2[element]
        return v3

    def __sub__(self, v2):
        """
            Methods allows vector to be substracted
            like normal numeric values (i.e. a - b).
            Again throw an exception if dimensions and
            will return resultant vector
        """
        self._checkDimension(v2)
        v3 = self._createEmptyVector(self._max)
        for element in range(self._max):
            v3[element] = self[element] - v2[element]
        return v3


    def __mul__(self, v2):
        """
            Allows the vector to be multiplied like
            a normal numeric value (a*b). Will return
            the dot-product of two vectors or the vector
            multiplied by the constant
        """
        if(isinstance(v2, Vector)):
            self._checkDimension(v2)
            dotProduct = 0
            for index in range(self._max):
                dotProduct += self[index] * v2[index]
            return dotProduct
        else:
            v3 = self._createEmptyVector(self._max)
            for element in range(self._max):
                v3[element] = self[element] * v2
            return v3

    def __truediv__(self, num):
        """
            Allows vectors to be divided like normal numeric
            values (though not integer division) (a/b).
        """
        v2 = self._createEmptyVector(self._max)
        for index in range(self._max):
            v2[index] = float(self[index]/num)
        return v2

    def calMagnitude(self):
        """
            Works out the magnitude of the
            current vector and returns it
        """
        magnitude = 0.0
        for element in self:
            magnitude += element**2
        magnitude = sqrt(magnitude)
        return magnitude
