# quadtree
Implementation of quadtree for collision detection in C++ using SFML

Requirements: 1) C++14, 2) SFML 2.6.1, 3) CMake 3.22.1

The program was tested on Ubuntu 22.04 LTS Jammy, gcc 11.4.0.

Instructions for an out-or-place build:
1) Go to the directory containing the CMakeLists.txt file.
2) Run `cmake -S . -B build`. This will create a `build` directory and put CMake files there.
3) Go to the `build` directory.
4) Build the project (e.g. for Unix makefiles it is achieved by running `make` command in the terminal).
5) Launch the executable file "quadtree".
