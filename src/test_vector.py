#!/usr/bin/env python3

from vector import *

empty, ints = None, None


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
