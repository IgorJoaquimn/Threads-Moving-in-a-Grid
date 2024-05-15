# Threads Moving in a Grid

Author: Igor Joaquim da Silva Costa

## Introduction

This project aims to simulate multiple threads moving in a grid, where each thread follows a predefined path while accessing grid positions in a synchronized manner.
Each thread, after creation and obtaining its identification and path data, executes the following sequence of operations:

1. Extracts the first position P from the path.
2. Enters the grid position identified by P (always possible as all threads start in different positions).
3. Executes the passa_tempo function with the time associated with position P.
4. For the rest of the path:
    - Obtains the next position P' from the path.
    - When the rules permit:
        - Enters the next position.
        - Releases the previous position (Note: it only exits a position when it can enter the next one).
        - Executes the passa_tempo function with the time associated with position P'.
  
## How the syncronization works
### Path Traversal
The thread_t::run function represents the main loop of a thread, where it traverses a predefined path through the grid. Synchronization mechanisms ensure that threads can safely navigate the grid without conflicts, coordinating their movements to prevent collisions and ensure efficient execution.

By employing mutexes, condition variables, and occupancy tracking, the synchronization mechanisms in this project enable effective coordination and safe concurrent access within the grid-based environment.

### Thread Operations and Grid Interaction
Threads executing within the system adhere to a strict protocol when interacting with the grid. Before entering a cell, a thread acquires the mutex associated with that cell, ensuring exclusive access. It then checks the cell's occupancy status and waits, if necessary, by utilizing the corresponding condition variable. Once the cell becomes available, the thread proceeds with its operation, marking the cell as occupied. Upon completing its task within the cell, the thread releases the mutex, signaling its departure.


## Usage

To use this project, follow these steps:

1. Compile the source files using a C++ compiler.
2. Run the executable with appropriate input.

## Example

In this input: 
```
4 3
11 98 4
    0 0 50 
    1 0 60 
    2 0 90 
    3 0 60
12 99 4
    0 2 10
    1 2 20 
    2 2 60 
    3 2 180
13 99 4
    2 3 40 
    2 2 60 
    2 1 10 
    2 0 120
```

Gives the result
```
  0 [ 11 @( 0, 0) z  50
  0 [ 12 @( 0, 2) z  10
  0 [ 13 @( 2, 3) z  40
 10 ) 12 @( 0, 2) z  10
 10 [ 12 @( 1, 2) z  20
 30 ) 12 @( 1, 2) z  20
 30 [ 12 @( 2, 2) z  60
 40 ) 13 @( 2, 3) z  40
 50 ) 11 @( 0, 0) z  50
 50 [ 11 @( 1, 0) z  60
 90 ) 12 @( 2, 2) z  60
 90 [ 12 @( 3, 2) z 180
 90 [ 13 @( 2, 2) z  60
110 ) 11 @( 1, 0) z  60
110 [ 11 @( 2, 0) z  90
150 ) 13 @( 2, 2) z  60
150 [ 13 @( 2, 1) z  10
160 ) 13 @( 2, 1) z  10
200 ) 11 @( 2, 0) z  90
200 [ 11 @( 3, 0) z  60
200 [ 13 @( 2, 0) z 120
260 ) 11 @( 3, 0) z  60
270 ) 12 @( 3, 2) z 180
320 ) 13 @( 2, 0) z 120
```

## Compilation Instructions


To compile the project, execute the following commands in the terminal:

```
    make build
```


## Notes

- This project uses pthreads for thread management.
- Ensure that the input file format matches the expected format.
- The grid dimensions and number of threads are provided as input.
- Each thread follows a predefined path in the grid, accessing positions in a synchronized manner.