# CS163-DataVisualization
**Data Structure Visualization**, a solo project for CS163 - Data Structures course.

<!-- This project uses **C++**, **CMake**, and the **raylib** graphics library. -->
This project uses **C++**, **CMake**, the **SFML** graphics library, and the **Dear ImGui/ImGui-SFML** GUI libraries.

This project contains visualizations for these data structures and algorithms:

- Singly linked list
- Hash table *(linear probing)*
- **Trees:** AVL Tree, Trie *(26-ary tree)*
- **Graphs:** Minimum Spanning Tree *(Kruskal's algorithm)*, Shortest Path *(Dijkstra's algorithm)*

## Building

This project uses **CMake** as its build system.

### 1. Get the prerequisites
Download and make sure you have:
- git (version 2.50.1 or higher)
- [CMake](https://cmake.org/download/) (version 3.20 or higher)
- A C++ compiler (GCC, Clang, MinGW-w64, or MSVC) that ***MUST*** support **C++17**

Make sure all of them are available in **PATH** in order to be used in the Terminal, and make sure you have Internet connection while following these building steps.

Clone this repository using *git*:
```bash
git clone --single-branch --branch main https://github.com/khanhf-ng820/CS163-DataVisualization.git
```
Enter the repository folder:
```bash
cd CS163-DataVisualization
```

If you use **Linux**, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions, you can use the following commands:
```bash
sudo apt update
sudo apt install \
	libxrandr-dev \
	libxcursor-dev \
	libxi-dev \
	libudev-dev \
	libfreetype-dev \
	libflac-dev \
	libvorbis-dev \
	libgl1-mesa-dev \
	libegl1-mesa-dev \
	libfreetype-dev
```

### 2. Build the project

**macOS** and **Linux:**
```bash
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

### 3. Running the application
You can run the application by double-clicking the application in the ```build/``` folder inside the project's directory in File Explorer/Finder, or you can open the Terminal in the **project root folder** and run:

**macOS** and **Linux:**
```bash
./build/src/DSVisualizer
```

**Windows:**
```powershell
.\build\src\DSVisualizer.exe
```
