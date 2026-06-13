### Build and Run

Ensure  Microsoft's `vcpkg` package manager is installed and added `sfml` through it:

```
# 1. Configure the build directory with the vcpkg toolchain
cmake -B build -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake

# 2. Compile the source code
cmake --build build

# 3. Run the executable
./build/b

```
