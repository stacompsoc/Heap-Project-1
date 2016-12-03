#!/usr/bin/env python3

from model import Model


def main():
    print("starting simulation")
    model = Model()
    model.run()
    print("stopping simulation")

if __name__ == '__main__':
    main()
