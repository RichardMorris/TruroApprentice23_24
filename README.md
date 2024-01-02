From https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

```
function Dijkstra(Graph, source):
      
      for each vertex v in Graph.Vertices:
          dist[v] ← INFINITY
          prev[v] ← UNDEFINED
          add v to Q
      dist[source] ← 0
      
      while Q is not empty:
          u ← vertex in Q with min dist[u]
          remove u from Q
          
          for each neighbor v of u still in Q:
              alt ← dist[u] + Graph.Edges(u, v)
              if alt < dist[v]:
                  dist[v] ← alt
                  prev[v] ← u

      return dist[], prev[]
```

# Testing with Catch2 via the CMake system

CMake set up and runs the system needed to compile projects, and link dependent libraries.

First edit the `CMakeLists.txt` file that defines the build option and defines files needed for each executable. 

## Running from linux command line 

```
mkdir build
cd build
cmake ..
cmake --build .
```
Files will be compiled in a separate `build` folder.
The `cmake ..` command configures the build system depending in the `CMakeList.txt` file.
The `cmake --build .` command runs the build process, creating an executable in the build directory.

# Running from VSCode

Ensure the CMake tools are installed. 

Bring up the pallet Ctrl-Shift-P

Type `CMake: build` or `CMake: run tests`

# Red-Black Trees

This follows the left-leaning Red-Black tree from https://opendatastructures.org/versions/edition-0.1e/ods-java/9_2_RedBlackTree_Simulated_.html