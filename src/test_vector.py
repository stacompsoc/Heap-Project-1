#!/usr/bin/env python3
from vector import *
import unittest
import types

empty, ints = None, None

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

    def test_set_item(self):
        v1 = create_vector()
        v1[0] = 13
        self.assertEqual(v1[0], 13)
        v1[2] = -1
        self.assertEqual(v1[2], -1)

def clear():
    global empty, ints
    empty = Vector()
    ints = Vector(1, 3, 5, 6, 7)

def test_str():
    clear()
    assert str(empty) == "()"
    print(str(ints))
    assert str(ints) == "(1,3,5,6,7)"

def test_getitem():
    clear()
    try: empty[0]
    except IndexError: pass
    try: ints[5]
    except IndexError: pass
    assert ints[0] == 1
    assert ints[0] == 1
    assert ints[4] == 7

def test_setitem():
    clear()
    try: empty[0] = 1
    except IndexError: pass
    try: ints[5] = 1
    except IndexError: pass
    ints[0] = -13
    assert ints[0] == -13
    ints[4] = 1e9
    assert ints[4] == 1e9

def test_len():
    assert len(empty) == 0
    assert len(ints) == 5

def test_pos():
    assert +empty == empty
    assert +ints == ints

if __name__ == '__main__':
    unittest.main()
