# Breakout · raylib

A small Breakout clone in C++, built on a hand-written particle class and a dynamic particle container that handle 2D movement, bouncing and collisions, rendered with raylib.

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![raylib](https://img.shields.io/badge/raylib-6.x-black?style=flat-square)
![Make](https://img.shields.io/badge/build-Make-427819?style=flat-square&logo=gnu&logoColor=white)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey?style=flat-square)
![License: MIT](https://img.shields.io/badge/license-MIT-blue?style=flat-square)

![Gameplay](docs/gameplay.gif)

## Features

- **Playable Breakout:** a 5 × 10 brick wall, 3 lives, a score (higher rows are worth more) and win / game-over screens with instant restart.
- **Paddle control:** the ball launches at a random angle, and where it hits the paddle decides the bounce angle. It speeds up slightly with every brick, up to a cap.
- **Custom particle model (`Particula`):** position, velocity and radius, with movement, edge bouncing, circle-to-circle collision, rotation around a point and stream I/O.
- **Dynamic container (`ConjuntoParticulas`):** a manually managed array that grows and shrinks in blocks, with copy constructor, assignment, destructor and overloaded operators (`+`, `[]`, `==`, `<`, `<<`).
- **Separate rendering layer (`Pintar`):** all raylib drawing calls live in one module, so the particle classes don't depend on the graphics library.

## Tech stack

| Technology | Used for |
|---|---|
| C++17 | Game logic, particle model and container with manual memory management |
| [raylib](https://www.raylib.com/) | Window, input, 60 FPS game loop, 2D drawing and circle-vs-rectangle collision checks |
| Make + pkg-config | Building and linking against raylib on macOS and Linux |

## Getting started

**Requirements:** a C++17 compiler (Apple Clang or g++), `make`, raylib and `pkg-config`.

On macOS with [Homebrew](https://brew.sh/):

```bash
brew install raylib pkg-config
```

On Debian/Ubuntu, install raylib from your package manager or [build it from source](https://github.com/raysan5/raylib#build-and-installation), plus `pkg-config`.

Then build and run:

```bash
make run
```

| Command | What it does |
|---|---|
| `make` | Builds the `./breakout` binary |
| `make run` | Builds and launches the game |
| `make clean` | Removes build output |

**Controls:** `Space` launches the ball, ← / → (or `A` / `D`) move the paddle, `R` restarts after a win or game over, `Esc` quits.

## Project structure

```
.
├── breakout.cpp              # Game loop: setup, input, collisions, win/lose checks
├── Particula.h / .cpp        # Particle: position, velocity, movement, collisions
├── ConjuntoParticulas.h/.cpp # Dynamic particle container with operator overloads
├── Pintar.h / .cpp           # raylib drawing helpers for balls and bricks
├── docs/                     # Screenshots / GIF for this README
└── Makefile
```

## What I learned

- **Manual memory management in C++:** implementing the copy constructor, assignment operator and destructor together, and resizing a heap array in blocks instead of on every insert.
- **Operator overloading:** designing a container API (`+`, `[]`, `==`, `<`, `<<`) that reads naturally, with `const` and non-`const` access.
- **Separating logic from rendering:** keeping the physics in plain classes and isolating raylib in one module meant I could reuse a data structure from coursework as the model for a real-time game.
- **Revisiting old code:** when preparing this repo I found the game hung after a loss (the window was closed inside the loop) and its collisions didn't match what was drawn. I reworked the loop into a small state machine (ready, playing, won, lost) and switched to circle-vs-rectangle collisions.

## Context & credits

Personal, individual project. The `Particula` and `ConjuntoParticulas` classes started as a programming assignment at the **Universidad de Granada**: their interfaces (method signatures and doc comments in the headers) follow the assignment specification, and the implementation is mine. The Breakout game, the rendering module and the build setup are my own work, built on top of those classes.

- [raylib](https://github.com/raysan5/raylib) by Ramon Santamaria and contributors, licensed under the zlib/libpng license. It is linked as a system library, not bundled.

Released under the [MIT License](LICENSE).
