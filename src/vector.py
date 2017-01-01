from math import sqrt


class Vector:
    def __init__(self, *components):
        self._components = list(components)
        self._index = 0

    def __str__(self):
        string = '(' + ','.join(str(e) for e in self._components) + ')'
        return string

    def __iter__(self):
        for i in self._components:
            yield i

    def __len__(self):
        return len(self._components)

    def __next__(self):
        if self._index < len(self):
            value = self._index
            self._index += 1
            return self._components[value]
        else:
            raise StopIteration

    def __getitem__(self, index):
        return self._components[index]

    def __setitem__(self, index, value):
        self._components[index] = value

    def __pos__(self):
        return self

    def __neg__(self):
        return self * -1

    def _checkDim(self, v2):
        if len(self) != len(v2):
            raise Exception("Error vectors don't have matching dimensions")

    def __add__(self, v2):
        """
        Overload '+' operator for vectors.

        Returns: the resultant vector of the operation
        """
        self._checkDim(v2)
        components = [i+j for i, j in zip(self, v2)]
        return Vector(*components)

    def __sub__(self, v2):
        """
        Overload '-' operator for vectors.

        Returns: the resultant vector of the operation
        """
        self._checkDim(v2)
        v2 = -v2
        return self + v2

    def __mul__(self, v2):
        """
        Overload '*' operator for vector on the lhs.

        :v2: rhs
        :returns: self + v2
        """
        if isinstance(v2, Vector):
            self._checkDim(v2)
            return sum([i*j for i, j in zip(self, v2)])
        else:
            components = [i*v2 for i in self]
            return Vector(*components)

    def __truediv__(self, num):
        """
        Overload '/' operator for vector.

        :num: rhs
        :returns: vector divided by num
        """
        if isinstance(num, Vector):
            raise Exception("Error cannot divide two vectors")
        components = [i/num for i in self]
        return Vector(*components)

    def __floordiv__(self, num):
        """
        Overload '//' operator (floor division).

        :num: rhs
        :returns: vector divided by num
        """
        if isinstance(num, Vector):
            raise Exception("Error cannot divide two vectors")
        components = [int(i/num) for i in self]
        return Vector(*components)

    def __abs__(self):
        """
        Calculate vectors magnitude.

        :returns: length of vector
        """
        return sqrt(sum(i*i for i in self))
