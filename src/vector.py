import math
import copy

class Vector:
    def __init__(self, components):
        s = self;
        s._components = components

    def __str__(s):
        string = ""
        for index in range(len(s._components)):
            string += str(s._components[index])
            string += " "

        return string

    def getComponents(s):
        return s._components

    """
        Adds a vector to the current vector
        object
    """
    def addVector(s, vector):
        compSecondVector = vector.getComponents()
        for index in range(len(compSecondVector)):
            s._components[index] += compSecondVector[index]

    """
        Multiples the current vector by a
        given constant
    """
    def mutlipleByConstant(s, constant):
        for index in range(len(s._components)):
            s._components[index] *= constant

    """
        substracts antoher vector from the current
        vector object
    """
    def substractVector(s, secondVector):
        secondVector.multipleByScalar(-1)
        s.addVector(secondVector)

    """
        Divides the current vector by a given scalar
    """
    def divideByScalar(s, scalar):
        scalar = 1/scalar
        s.multipleByScalar(scalar)

    """
        Multiples the current vector object by another
        vector
    """
    def multipleVectors(s, vector, returnNewVector = False):
        numOfIteration = len(vector) if len(vector) < len(s._components) else len(s._components)
        secondVectorComponents = vector.getComponents()
        for index in range(numOfIteration):
            s._components[index] *= secondVectorComponents[index]

    """
        Works out the dot product of the current vector and another
        vector.

        Return: the dot product
    """
    def workOutDotProduct(s, secondVector):
        dotProduct = 0
        for element1, element2 in zip(s._components, secondVector):
            dotProduct += element1 * element2
        return dotProduct




    """
        Works out the magnitude of the current vector object

        Return: the magnitude of the vector
    """
    def workOutMagnitude(s):
        magnitude = 0
        for currentElement in s._components:
            magnitude += currentElement^2

        magnitude = math.sqrt(magnitude)

        return magnitude


    def workOutVectorProduct(s, secondVector):
        if(len(s._components) == len(secondVector)):
            pass

def main():
    v1 = Vector([1,2,3,4])
    print(v1)
    v1.mutlipleByConstant(5)
    print(v1)

    v2 = Vector([5,6,7,8])
    v1.addVector(v2)
    print(v1)

if __name__ == '__main__':
    main()
