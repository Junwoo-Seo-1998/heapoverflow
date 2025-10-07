# HOF Project

This document provides instructions on how to build and run the project on a Linux environment.

## Building on Linux (Debian/Ubuntu)

Follow these steps to build the project from source on a Debian-based Linux distribution like Ubuntu.

### 1. Install Dependencies

First, you need to install the essential build tools and the libraries required for graphics, windowing, and input.

Open a terminal and run the following command to install all dependencies at once:

```bash
sudo apt update && sudo apt install build-essential cmake libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libgl1-mesa-dev
```

### 2. Configure and Build with CMake

Once the dependencies are installed, you can use CMake to configure the project and build it.

```bash
# Create a build directory
mkdir build

# Move into the build directory
cd build

# Configure the project with CMake
cmake ..

# Build the project
cmake --build .
```

### 3. Run the Application

After a successful build, the executable (`demo`) will be located in the `build/bin` directory.

To run the application, execute the following commands from the `build` directory:

```bash
cd bin
./demo
```
