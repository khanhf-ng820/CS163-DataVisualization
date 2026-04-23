mkdir build
cd build
# (Don't do Debug build type)
# cmake ..
cmake -DCMAKE_BUILD_TYPE=Release .. # (Do Release build type)
cmake --build .
./src/DSVisualizer # .\src\Release\DSVisualizer.exe if using Windows
