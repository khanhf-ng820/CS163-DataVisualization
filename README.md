# CS163-DataVisualization
**Data Structure Visualization**, a solo project for CS163 - Data Structures course.

<!-- This project uses **C++**, **CMake**, and the **raylib** graphics library. -->
This project uses **C++17**, **CMake**, the **SFML** graphics library, and the **ImGui-SFML** GUI library.

## Overview

The data structure visualization application provides an intuitive and user-friendly interface for the display and understanding of data stored in basic data structures.

The application displays the existing data within the structure in a clear and easy-to-read format with animations, step-by-step playback, and highlighting pseudocode. Users can perform various operations on the data structures.

This project contains visualizations and operations for these data structures and algorithms:

- **Singly linked list**
	- Searching a value
	- Inserting a value at a specific index
	- Deleting a value at a specific index
	- Updating a value at a specific index

- **Hash table *(Linear probing)***
	- Searching a key
	- Inserting a key
	- Deleting a key
	- Updating a key (deleting old key & inserting new key)

- **Trees: AVL Tree, Trie *(26-ary trie)***
	- Searching a key/word
	- Inserting a key/word
	- Deleting a key/word
	- Updating a key/word (deleting old key/word & inserting new key/word)

- **Graphs: Minimum Spanning Tree *(Prim's algorithm)*, Shortest Path *(Dijkstra's algorithm)***
	- *Prim's algorithm:* Single source vertex and finding the minimum spanning tree in an *undirected weighted* graph
	- *Dijkstra's algorithm:* Single source vertex and finding shortest paths (if exist) to all other vertices in an *undirected weighted* graph

### Technology stack:
- **C++17, CMake**
- 2D Graphics: **[SFML v3.0.2](https://github.com/SFML/SFML)**
- GUI: **[Dear ImGui v1.91.1](https://github.com/ocornut/imgui)**, **[ImGui-SFML v3.0](https://github.com/SFML/imgui-sfml)**
- File dialog box: **[tinyfiledialogs](https://github.com/native-toolkit/libtinyfiledialogs)**

## Main features

The main features of this application include:

- Interactive graphical user interface
- Support for both step-by-step and run-at-once visualization
- Animations for transitions between different states of the data structure
- Highlighting data nodes in the data structure
- Zooming and panning the visualization canvas
- Highlighting the corresponding pseudocode when visualizing operations
- Initializing the data structure with external data files using a file dialog box
- Different themes and font size for customization

## Building

This project uses **CMake** as its build system.

### 1. Get the prerequisites
Download and make sure you have:
- git (version 2.50.1 or higher)
- [CMake](https://cmake.org/download/) (version 3.20 or higher)
- A C++ compiler (GCC, Clang, MinGW-w64, or MSVC) that ***MUST*** support **C++17**

Make sure all of them are available in **PATH** in order to be used in the Terminal, and make sure you have Internet connection while following these building steps.

#### Clone the repository:
Open the Terminal (Command Prompt), and navigate to the directory where you want the repository to be in, using the `cd` command. (Example: `cd path/to/directory/`).

Clone this repository using *git*:
```bash
git clone --single-branch --branch Release https://github.com/khanhf-ng820/CS163-DataVisualization.git
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

### 2. Build the application

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

# Generate build files and build the project
### If using MinGW:
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -S .. -B .
cmake --build .

### If using Visual Studio (default on Windows):
cmake -S .. -B .
cmake --build . --config Release
```

### 3. Running the application
You can run the application by double-clicking the application in the ```build/src/``` folder inside the project's directory in File Explorer/Finder, or you can open the Terminal in the **project root folder** and run:

**macOS** and **Linux:**
```bash
./build/src/DSVisualizer
```

**Windows:**
```powershell
.\build\src\DSVisualizer.exe
```
