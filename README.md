# Cocapture

### Application dependencies
Cocapture uses [Dear ImGui](https://github.com/ocornut/imgui), a bloat-free graphical user interface library for C++ with [SDL2](http://www.libsdl.org/) and [OpenGL3](https://www.opengl.org/) backend.

Install OpenGL3 with:

    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev  

Install SDL2 with:

    sudo apt-get install libsdl2-dev

### Camera dependencies
This software supports cameras from different vendors with different SDK's (listed below). You need to install the SDK's needed for your specific camera. For the once that you do not need change the CMakeLists.txt like so:

    set(USE_<SDK-NAME> FALSE)  

- Pylon, from https://www.baslerweb.com/de/downloads/downloads-software/
    - Version >7.2.0 is required

- OpenEB, from https://github.com/prophesee-ai/openeb
    - Version 2.3.0 or 3.0.2 is required (version 4.0.0 is currently not supported)

      
### Further dependencies
- OpenCV, from https://github.com/opencv/opencv
- Boost, from https://www.boost.org/users/download/
