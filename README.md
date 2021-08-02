# Flocking Boids
imulates how fish flock and run from a predator in a closed enviroment

The base idea comes from Craig Reynolds. However I changed it up a ton. In this simulation, you will find the ability to change flocking patterns, the type of boid, and more. Each type of boid has different attributes (how they run from a predator, rotation speed, movement speed,  etc.). You can add "repulsions" which repulse the boids away, add and delete the borders, and toggle the 3 rules. 

**Flocking Boids considers 3 rules: Seperation, Allignment, and Cohesion**
* Seperation defines the way boids avoid each other and avoid contact with each other. 
* Allignment defines the way boids allign, as they will steer towards the average heading of the boids around them. 
* Cohesion refers to how the boids group together. They will attempt to move to the average center of mass of the boids around them. 

The union of these three simple rules gives you incredible flocking behavior. The three rules are each multiplied by a certain coefficient, and changing these coefficients will signifigantly change their behavior. This allows for different flocking patterns. 

More complex behavior can be added, such as obstacle advoidance. This can be seen in this simulation with repulsions and predators. Repulsions are standstill obstacles the boids will avoid. Once can place them wherever, or make a circle of them, leading to interesting results. Predators are the most entertaining part of this simulation. They will chase the boids and the boids will flee, each type of a boid with a different method of fleeing. I reccomend you play with it yourself to see.



**Note: This version requires Visual Studio. If you do not have access to Visual Studio, here is a version that works for linux and windows that requires no setup: https://github.com/Zachhi/FlockingBoids-Windows-Linux**

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
