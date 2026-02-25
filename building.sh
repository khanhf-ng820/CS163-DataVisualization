mkdir build
cd build
# cmake .. (Don't do Debug build type)
cmake -DCMAKE_BUILD_TYPE=Release .. # Do Release build type
cmake --build .
./src/DSVisualizer # or ./src/Debug/DSVisualizer if using Visual Studio
