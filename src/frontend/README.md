# Frontend

## Compiling

    cmake . -DCMAKE_BUILD_TYPE=Debug # recommended for first run
    make -j$(getconf _NPROCESSORS_ONLN)

## Running

    ./planetarium

## Documentation

    Doxygen doc/Doxyfile
    cd latex && make -j$(getconf _NPROCESSORS_ONLN)
