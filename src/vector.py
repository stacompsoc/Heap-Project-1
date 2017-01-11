from math import sqrt
from operator import __neg__, __pos__, __and__
from functools import reduce

class NoComponents(Exception):
    pass

class Vector:
    def __init__(self, *components):
        """
        Initialize a vector.

        :compoents: values
        """
        self.__div__ = self.__truediv__
        if not components:
            raise NoComponents("Error vector must components!")
        else:
            self._components = list(components)
        self._index = 0

    def __str__(self):
        """
        Get string representation.

        :returns: str(self)
        """
        return '(' + ','.join(str(e) for e in self._components) + ')'

    def __iter__(self):
        """Iterate itself."""
        for i in self._components:
            yield i

    def __len__(self):
        """
        Compute length.

        :returns: len(self)
        """
        return len(self._components)

    def __next__(self):
        """
        Get next element.

        :returns: next value in iteration
        """
        if self._index < len(self):
            value = self._index
            self._index += 1
            return self._components[value]
        else:
            raise StopIteration

    def __getitem__(self, index):
        """
        Get value by index.

        :index: index
        :returns: self[index]
        """
        return self._components[index]

    def __setitem__(self, index, value):
        """
        Set value by index.

        :index: index
        :value: value
        """
        self._components[index] = value

    def __eq__(self, other):
        """
        Determine whether two objects are equal.

        :other: other object
        :returns: boolean
        """
        return type(self) == type(other) and len(self) == len(other) and \
            reduce(__and__, map(lambda z: z[0] == z[1], zip(self, other)), True)

    def __ne__(self, other):
        """
        Determine whether two objects are not equal.

        :other: other object
        :returns: boolean
        """
        return not (self == other)

    def __pos__(self):
        """
        Compute + unary operator of self.

        :returns: +self
        """
        return Vector(*map(__pos__, self))

    def __neg__(self):
        """
        Compute - unary operator of self.

        :returns: -self
        """
        return Vector(*map(__neg__, self))

    def _checkDim(self, other):
        """
        Check that two vectors are of the same dimension.

        :other: other object
        """
        if len(self) != len(other):
            raise Exception("Error vectors don't have matching dimensions")

    def __add__(self, other):
        """
        Overload '+' operator for vectors.

        :returns: the resultant vector of the operation
        """
        self._checkDim(other)
        return Vector(*[i + j for i, j in zip(self, other)])

    def __sub__(self, other):
        """
        Overload '-' operator for vectors.

        :returns: the resultant vector of the operation
        """
        self._checkDim(other)
        return self + (-other)

    def __mul__(self, other):
        """
        Overload '*' operator for vector on the lhs.

        :other: rhs
        :returns: self + other
        """
        if type(other) == Vector:
            self._checkDim(other)
            return sum(i*j for i, j in zip(self, other))
        else:
            return Vector(*map(lambda x: x * other, self))

    def __truediv__(self, other):
        """
        Overload '/' operator for vector.

        :other: rhs
        :returns: vector divided by other
        """
        if type(other) == Vector:
            raise Exception("Error cannot divide two vectors")
        return Vector(*map(lambda x : x / other, self._components))

    def __floordiv__(self, other):
        """
        Overload '//' operator (floor division).

        :other: rhs
        :returns: vector divided by other
        """
        if isinstance(other, Vector):
            raise Exception("Error cannot divide two vectors")
        return Vector(*map(lambda x: int(x / other), self))

    def __abs__(self):
        """
        Calculate vectors magnitude.

        :returns: length of vector
        """
        return sqrt(sum(i * i for i in self))
