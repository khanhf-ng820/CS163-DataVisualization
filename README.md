# CS163-DataVisualization
Data Structure Visualization project for CS163 - Data Structures.

<!-- This project uses **C++**, **CMake**, and the **raylib** graphics library. -->
This project uses **C++**, **CMake**, the **SFML** graphics library, and the **Dear ImGui** and **ImGui-SFML** GUI libraries.

## Building

This project uses **CMake** as its build system.

### 1. Get the prerequisites
Download and make sure you have:
- git (version 2.50.1 or higher)
- [CMake](https://cmake.org/download/) (version 3.20 or higher)
- A C++ compiler (GCC, Clang, MinGW-w64, or MSVC) that supports **C++17**

Make sure all of them are available in **PATH** in order to be used in the Terminal, and make sure you have Internet connection while following these building steps.

Clone this repository using git:
```bash
git clone --single-branch --branch main https://github.com/khanhf-ng820/CS163-DataVisualization.git
```

### 2. Build the project
Open the Terminal in the **project root folder** and run:

**macOS** and **Linux:**
```bash
#!/bin/bash

# Create a build folder
mkdir build
cd build

# Generate build files
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

# Build the project
cmake --build .
```


**Windows:**
```bash
#!/bin/bash

# Create a build folder
mkdir build
cd build

# Generate build files
# If you use the MinGW C++ compiler, do this:
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -S .. -B .
# Else, do this:
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

# Build the project
cmake --build .
```

### 3. Running the program
You can run the program by double-clicking the application in the ```build/``` folder inside the project's directory in File Explorer/Finder, or by open the Terminal in the **project root folder** and run:

**macOS** and **Linux:**
```bash
./build/DSVisualizer
```

**Windows:**
```bash
.\build\DSVisualizer.exe
```
