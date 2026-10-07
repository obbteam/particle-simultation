# Particle Simulation
 
2D particle simulation in C++ and SFML 3. Verlet integration, grid-based collisions, circular boundary.
 
**20,000 particles at 60 FPS.**
 
<!-- Video: drag the .mp4 into the GitHub editor, or paste a link here -->
 
## Features
 
- Verlet integration, 4 substeps per frame
- Particle collisions with mass and restitution
- Uniform grid broad phase: each particle is only checked against its neighbours
- Circular boundary
- Particles spawn from the center, click to add more
- Gravity in 4 directions
- 1 px particles drawn as soft textured quads for a liquid look
- One vertex array, one draw call
- 5 themes, switchable at runtime
- Live particle count and FPS
## Controls
 
| Input | Action |
| --- | --- |
| Left mouse button | Add a particle inside the circle |
| Arrow keys | Set gravity direction |
| `1`-`5` / `Numpad 1`-`5` | Theme: Ocean, Lava, Clean light, Neon, Mint |
 
## Build
 
Requires CMake 3.28+ and a C++20 compiler. SFML 3.1.0 is fetched automatically if it is not installed.
 
```bash
cmake -S . -B build
cmake --build build
./build/bin/particle-simulation
```
 
On Windows: `.\build\bin\particle-simulation.exe`
 
CMake copies `ARIAL.TTF` next to the executable.
 
## Structure
 
```text
include/
  constants.hpp         constants and themes
  particle.hpp          particle
  verlet.hpp            Verlet object
  solver.hpp            physics and collisions
  grid.hpp              uniform grid
  renderer.hpp          rendering, FPS and count text
  ISimulation.hpp       simulation interface
  circleSimulation.hpp  circle scene
source/
  circleSimulation.cpp
  solver.cpp
  verlet.cpp
main.cpp
CMakeLists.txt
ARIAL.TTF
```
 
## Configuration
 
Everything is in `include/constants.hpp`: `FRAME_RATE`, `SUB_STEPS`, `MAX_PARTICLES`, `GRAVITY`, `COR`, `CIRCLE_RADIUS`, `VISUAL_SCALE` and the themes.
 
