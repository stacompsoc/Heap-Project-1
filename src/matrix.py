class Matrix:
    self._ROW = 0
    self._COLUMN = 1

    def __init__(self, components, columns, row):

        if(columns < 1):
            raise Exception("Please eneter a valid number of columns")
        if(row <= 1):
            raise Exception("Please eneter a valid number of rows")

        try:
            components[coumns][row]
        except Exception as e:
            raise Exception("The number of rows or columns does match the components passed")

        self._components = components
        self._dimensions = [row, columns]

    def getDimensions(self):
        return self._dimensions;

    def getComponents(self):
        return self._components

    """
        Mutliples every element in the matrix by a
        scalar.
    """
    def multipleByScalar(self, scalar):
        # Goes through each element multiplying them by the scalar
        for row in range(self._dimensions[self._ROW]):
            for column in range(self._dimensions[self._COLUMN]):
                self._components[row][column] *= scalar



    """
        Adds another matrix onto the current matrix, providing
        this a valid thing to do
    """
    def addMatrices(self, secondMatric):
        dimensions = secondMatric.getDimensions()
        # Adds all the elements together for a multi-dimensional matrix
        for row in range(self._dimensions[self._ROW]):
            for column in range(self._dimensions[self._COLUMN]):
                self._components[row][column] += secondVectorsComponents[row][column]

    """
        Substracts another matrix from itself
    """

    def substractMatrices(self, secondMatric):
        secondMatric.multipleByScalar(-1)
        self.addMatrices(secondMatric)

    """
        Divides each element in the current matrix by
        a given scalar
    """
    def divideByScalar(self, scalar):
        scalar = 1/scalar
        self.multipleByScalar(scalar)

    def workDetermint(self):
        pass;

    def printMatrix(self):
        print(self._components)



def main():
    element = [[1,2,3,4],[1,2,3,4]]
    element2 = [[5,6,7,8],[9,10,11,12]]
    matrice = Matrix(element, 4, 2)
    matrice2 = Matrix(element2, 4,2)
    matrice.addMatrices(matrice2)
    matrice.printMatrix()

if __name__ == '__main__':
    mai
