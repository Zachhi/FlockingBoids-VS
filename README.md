# Flocking Boids

Simple ray casting simulation that shows how rays of light would behave depending on its source location and the walls around it

**Note: This version requires Visual Studio. If you do not have access to Visual Studio, here is a version that works for linux and windows that requires no setup: https://github.com/Zachhi/RayCasting-Windows-Linux**

## Demo

## Controls

* Click twice to draw a wall from the first click to the second click
* "C" to clear all walls
* Move mouse around to change light source position
* "Space" to change the source type. 
      3 Types:
      Draw all the light rays 
      Draw only the light rays that hit walls
      Draw no light rays
* "Up arrow" to increase amount of light rays
* "Down arrow" to decrease amount of light rays
* "Escape" to exit the program

### Dependencies

* Windows
* Visual Studio 19 or above
* SFML (Simple and Fast Multi-Media Library) 2.5.1 or later is required in order to run this program. You can install SFML here: https://www.sfml-dev.org/download/sfml/2.5.1/
* Since we are using Visual Studio, download the Visual c++ 15 from the sfml website

**If you don't have access to Visual Studio, or are on linux, scroll to the top to find the other version**

### Installing and Executing

* Download the source code from github, or clone the repository into Visual Studio
* Import into Visual Studio
* Build according to your need (x86 or x64)
* In project settings
  * Add the `/path/to/sfml/include` to your c++ include path
  * Add the `/path/to/sfml/libray` to the linker library path
  * Link the following sfml libraries: `sfml-graphics.lib, sfml-windows.lib, sfml-system.lib, sfml-audio.lib`
  * Link the following debug libraries: `sfml-graphics-d.lib, sfml-windows-d.lib, sfml-system-d.lib, sfml-audio-d.lib`
  * Copy the sfml dlls (in the `sfml/bin` folder) to your project folder
* If that is too hard to follow, a simple 5 minute tutorial for linking SFML with a Visual Studio project can be found here: https://www.youtube.com/watch?v=YfMQyOw1zik
* Click the run button at the top and the program should start

**If you would prefer not having to link libraries, and would prefer a version fully set up, see the link at the top**

## Authors

Zachary Chi
zachchi@tamu.edu

## License

This project is licensed under the MIT License - see the LICENSE.md file for details
