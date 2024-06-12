# ScoreBoard Challenge
This solution provides only necessary minimum provided with requirements of the challenge. Therefore does not cover requirements which was not clearly requested, like starting 2 games where one team already is in progress in other game or any restrictions on scores updates etc.

# Directory structure
`include` and `src` folders contains ScoreBoard implementation
`tests` contains tests
mocks can be found under `tests\mocks`

# Build
## Requirements

Solution is provided with C++20, it was tested with Clang/LLVM and OS X.

## Build
CMake was used for build system, so it follows standard build procedure

enter workdir
```
mkdir build
cd build
cmake ..
make
```

`ScoreBoardTests` and `libScoreBoardLib.a` are created as a result.

To execute tests run `./ScoreBoardTests` from `build` directory