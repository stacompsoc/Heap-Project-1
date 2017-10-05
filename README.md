# STACS Open Source Project 2016

## Authors

Delivered by University of St Andrews Computing Society.

## Program

The project consists of two parts: a basic physics engine, simulating 3d pseudophysics in 2d graphics, and a frontend, which has no physics, but does it in 3d.

## Built with

### Basic

* Python 3
* PyGame
* Unittest

### Frontend

* c++14
* opengl4, glsl
* glew, glfw3, glm, openal-soft
* libpng, libjpeg, libtiff, libsndfile, freetype
* opencl, openmp
* cmake, make, pkg-config

## Usage

### Basic

    cd src/basic
    ./main.py

## frontend

    cd src/frontend
    mkdir build/
    cd build/
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make
    cd ..
    ./build/planetarium

## Contributing

Please, read [CONTRIBUTING.md](CONTRIBUTING.md) file for details on how to contribute to our project.

## License

The project is licensed under [MIT License](LICENSE).

## Acknowledgements

The section is here to keep the readme structure.
