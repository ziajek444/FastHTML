# FastHTML
FastHTML library filter out wanted tag's data.
------------------------------------------------------------------------------------------------
FastHTML detect if html string is bigger than 3MB. Threading is better for response bigger than 3MB.
------------------------------------------------------------------------------------------------
25.01.2034
https://stackoverflow.com/a/64719718/9473237

# Configure the build
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Debug

# Actually build the binaries
cmake --build build/

# Configure a release build
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release

# Build release binaries
cmake --build build/


For multi-configuration generators it's slightly different (Ninja Multi-Config, Visual Studio)

# Configure the build
cmake -S . -B build

# Build debug binaries
cmake --build build --config Debug

# Build release binaries
cmake --build build --config Release
------------------------------------------------------------------------------------------------