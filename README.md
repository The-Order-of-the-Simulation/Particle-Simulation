# Particle Simulation

This project simulates particles in 3D with a few different types of physics systems.

## Compiling

> This section is under construction, we are using [GLM (OpenGL Mathematics)](https://github.com/g-truc/glm) now which makes stuff a bit more complex. While custom vector math was fun and easy to compile, it wasn't very practical for development...

### General Cross-Platform

If you want to bring your own compiler, all you need to do is make sure you have [GLM](https://github.com/g-truc/glm) installed and compile `main.cpp` with POISX Threads support.

### Linux (GCC)

To compile this project on a Debian-based Linux system using [GCC (GNU Compiler Collection)](https://gcc.gnu.org/), just make sure you have it installed. If you don't know if you have it, you can install it by running:

```sh
sudo apt install build-essential
```

If [GCC](https://gcc.gnu.org/) is already installed, apt will either say you have the latest version or tell you an upgrade is available. Now, make sure you have [GLM](https://github.com/g-truc/glm) installed. If you don't know if you have it, you can install it by runnning:

```sh
sudo apt install libglm-dev
```

Once you have [GLM](https://github.com/g-truc/glm), you can compile the project by running the build script:

```bash
build.sh
```

You should now be able to run the executable `simulation` simply by using:

```bash
./simulation
```

### Windows (Mingw-w64)

To compile this project on a Windows system using [Mingw-w64](https://www.mingw-w64.org/), just make sure you have it installed. If you don't have it, you can get it at <https://www.mingw-w64.org/downloads/>. Now, make sure you have [GLM](https://github.com/g-truc/glm) installed. If you don't have it, you can get it at <https://github.com/g-truc/glm>. Once you have [GLM](https://github.com/g-truc/glm), you can compile the project by running the build script:

```cmd
build.bat
```

You should now be able to run the executable `simulation.exe` from File Explorer, or simply by using:

```cmd
simulation.exe
```

### MacOS

MacOS is not and will not be officially supported. You will just have to test bring your own compiler and test your luck. There is no official MacOS support because I (@Zi7ar21) do not have access to a Mac and have no interest in getting one because Apple's ecosystem is absolutely proprietary and cringe. Normally I would just disregaurd Mac support entirely but if you do have an issue running this then you can submit an issue and I _might_ fix it.

## Running

At this time there isn't any command-line arguments and you can just run the executable (either `simulation` or `simulation.exe`) and it will run a simulation and output a rendered animation.
