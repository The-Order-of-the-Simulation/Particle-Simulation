# Particle Simulation

This project simulates 3D Particles.

## Compiling

### General Cross-Platform

If you want to bring your own compiler, all you need to do is compile `main.cpp` with POISX Threads support.

### Windows (Mingw-w64)

To compile this project on a Windows system using [Mingw-w64](https://www.mingw-w64.org/), just make sure you have it installed and run:

```cmd
build.bat
```

You can now run `simulation.exe`.

### Linux (GCC)

To compile this project on a Debian-based Linux system using [GCC (GNU Compiler Collection)](https://gcc.gnu.org/), just make sure you have it installed and run:

```sh
build.sh
```

You can now run `simulation`.

### MacOS

MacOS is not and will not be officially supported. You will just have to test your luck and bring your own compiler. There is no official MacOS support because I [(Zi7ar21)](https://github.com/Zi7ar21) do not have access to a Mac and have no interest in gaining access to one because Apple is absolutely proprietary. Normally I would just disregaurd Mac support entirely but if you do have an issue running this then you can submit an issue and I _might_ fix it.

## Running

At this time there isn't any command-line arguments and you can just run the executable (either `simulation.exe` or `simulation`) and it will run a simulation and output a rendered animation.
