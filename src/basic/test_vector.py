from vector import *
import unittest
import types
from math import sqrt

def create_vector():
    return Vector(1,2,3)


class testVector(unittest.TestCase):
    def test_creation(self):
        with self.assertRaises(NoComponents):
            Vector()
        self.assertIsInstance(create_vector(), Vector)
        components = [1,2,3,4,5]
        self.assertIsInstance(Vector(*components), Vector)

    def test_to_string(self):
        v1 = create_vector()
        self.assertEqual(str(v1), "(1,2,3)")

    def test_get_length(self):
        v1 = create_vector()
        self.assertEqual(len(v1), 3)

    def test_iterable(self):
        v1 = create_vector()
        iterable = v1.__iter__()
        self.assertIsInstance(iterable, types.GeneratorType)

    def test_get_item(self):
        v1 = create_vector()
        self.assertEqual(v1[0], 1)
        self.assertEqual(v1[1], 2)
        self.assertEqual(v1[2], 3)

        with self.assertRaises(IndexError):
            item = v1[10]

    def test_set_item(self):
        v1 = create_vector()
        v1[0] = 13
        self.assertEqual(v1[0], 13)
        v1[2] = -1
        self.assertEqual(v1[2], -1)

    def test_eqaulity(self):
        v1 = create_vector()
        self.assertEqual(v1, v1)
        v2 = Vector(5,6,7,8)
        self.assertFalse(v1 == v2)

    def test_ne(self):
        v1 = create_vector()
        v2 = Vector(5,6,7)
        self.assertTrue(v1 != v2)
        self.assertFalse(v1 != v1)

    def test_neg(self):
        v1 = create_vector()
        self.assertEqual(-v1, Vector(-1,-2,-3))

    def test_check_dim(self):
        v1 = create_vector()
        v2 = Vector(1,2,3,4)

        with self.assertRaises(Exception):
            v1._checkDim(v2)

    def test_add(self):
        v1 = create_vector()
        v2 = Vector(5,6,7)
        v3 = v1 + v2
        self.assertEqual(v3, Vector(6,8,10))

    def test_sub(self):
        v1 = create_vector()
        v2 = Vector(2,3,4)
        v3 = v1 - v2
        self.assertEqual(v3, Vector(-1, -1, -1))

    def test_pos(self):
        v1 = create_vector()
        self.assertEqual(+v1, create_vector())

    def test_mul(self):
        v1 = create_vector()
        v2 = Vector(4,5,6)
        self.assertEqual(v1*v2, 32)
        self.assertEqual(v1*5, Vector(5,10,15))

    def test_div(self):
        v1 = create_vector()
        self.assertAlmostEqual(v1/2, Vector(0.5, 1.0, 1.5))
        self.assertAlmostEqual(v1//2, Vector(0,1,1))

    def test_abs(self):
        v1 = create_vector()
        self.assertAlmostEqual(abs(v1), sqrt(14))
