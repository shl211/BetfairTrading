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

## Examples

Some examples of the BetfairAPI library can be seen in examples/, which contain some basic lightweight examples. These are very basic, with more advanced functionalities possible. Examples use live server so if you do not want bets to be matched, the recommendation is to use pricing on events that will not be picked up during pre-market.