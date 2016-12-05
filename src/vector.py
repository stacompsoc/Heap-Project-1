class Vector:
    def __init__(self, components):
        self._components = components

    def getComponents(self):
        return self._components

    def addVector(self, secondVector):
        for elements in secondVector:
            self._components += elements

    def mutlipleByConstant(self, constant):
        for index in range(len(self._components)):
            self._components[index] *= constant

    def substractVector(self, secondVector):
        secondVector.multipleByScalar(-1)
        self.addVector(secondVector)

    def divideByScalar(self, scalar):
        scalar = 1/scalar
        self.multipleByScalar(scalar)

    def multipleVectors(self, vector):
        numOfIteration = len(vector) if len(vector) < len(self._components) else len(self._components)
        for index in range(numOfIteration):
            self._components[index] *= vector[index]

    def workOutDotProduct(self, secondVector):
        dotProduct = 0
        for element1, element2 in zip(self._components, secondVector):
            dotProduct += element1 * element2

        return dotProduct

    def workOutVectorProduct(self, secondVector):
        if(len(self._components) == len(secondVector)):
            pass
