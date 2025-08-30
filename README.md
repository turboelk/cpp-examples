A selection of self-contained `lessons learned` type of tests, showcasing usage of distinct C++ features - for those of us more inclined to read actual code.

# Goals
* Self-contained; Each unit should be constrained to a single feature, or, where it makes sense, a *small* collection of features.
* Compileable; Each unit should compile to a single artifact
* Legible; Each artifact should produce output clearly traceable to where it was output and why

# Requirements
* [GNU Make](https://www.gnu.org/software/make/)
* [CMake](https://cmake.org/)

# Build
1. `mkdir build && cd build && cmake ..`
2. `make`
