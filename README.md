# Betfair Trading

Automated trading on Betfair Exchange.

## Installation

This project requires CMake and C++17.

```
mkdir build
cd build
cmake ..
make
./app
```

This generates an executable **app** located in build.

This can also be compiled with tests:
```
mkdir build
cd build
cmake -DBUILD_TESTS=ON ..
make
ctest
```

**ctest** executes the test suite.