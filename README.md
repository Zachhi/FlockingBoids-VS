# Flocking Boids
This program simulates how fish behave (flock) in large groups, and how they run from a predator when flocking.

A major part of this program was to make it look as clean as possible. I focused on having it look professionally done, and I put a lot of thought into the design of the simulation itself. There have been plenty of flocking boid programs done, and I wanted mine to pop out and look better than any others. If you search for flocking boid programs around the web, almost all of them look the same, with a select few that really blow you away. I think this simulation is worth a look at, so go ahead and scroll to the Demo section to watch the youtube video.

The base idea comes from Craig Reynolds, who developed a model for flocking in 1986. More can be read here: https://www.red3d.com/cwr/boids/

**Flocking Boids considers 3 rules: Seperation, Cohesion, and Allignment**
* Seperation defines the way boids avoid each other and avoid contact with each other. 
* Cohesion refers to how the boids group together. They will attempt to move to the average center of mass of the boids around them. 
* Allignment defines the way boids allign, as they will steer towards the average heading of the boids around them. 

The union of these three simple rules gives you incredible flocking behavior. The three rules are each multiplied by a certain coefficient, and changing these coefficients will signifigantly change their behavior.

**This is the very simple, very base idea that doesn't do the simulation justice. Scroll down to the demo section and watch the youtube video in order to see the simulation in all its detail** 

Animations were drawn myself, The "Clair De Lune" and "Comptine d'un autre été - Amélie" music tracks were performed myself.

**Note: This version requires Visual Studio. If you do not have access to Visual Studio, here is a version that works for linux and windows that requires no setup: https://github.com/Zachhi/FlockingBoids-Windows-Linux**

## Demo

## Controls

#### GUI
* Top Right: Shows the three rules and which are toggled, the FPS, and the game speed
* Bottom Right: Shows the current boid you are spwaning
* Bottom Left: Shows the current counts of the boids on screen
* Top Left: Shows the rules

#### Input
* LShift: See all the controls (will show in top left)
* Left click: Spawn the current boid type (either a prey or predator)
* Space: Spawn 20 of the current boid types in random locations
* X: Spawn 2 of the current boid types facing each other on opposite sides of screen
* Left/Right Arrow Keys: Next/Previous boid type
* P: Change current boid type to predator and back
* Right Click: Create/delete repulsion
* O: Spawn a circle of repulsions
* I: Change the type of repulsion circle that will spawn
* 1: Toggle rule 1 (Separation)
* 2: Toggle rule 2 (Cohesion)
* 3: Toggle rule 3 (Allignment)
* LTab: cycle to a new flocking behavior
* B: Toggle borders on and off
* H: Toggle boid headings on and off
* C: Clear everything from the screen
* V: Clear current object type from the screen
* R: Clear all repulsions from the screen
* Up/Down Arrow Keys: Increase/decrease game speed (slow-mo or fast-mo)
* N: Cycle to next song
* LCtrl: Hide GUI
* Esc: Exit program

### Dependencies

* Windows
* Visual Studio 19 or above
* SFML (Simple and Fast Multi-Media Library) 2.5.1 or later is required in order to run this program. You can install SFML here: https://www.sfml-dev.org/download/sfml/2.5.1/
* Since we are using Visual Studio, download the Visual c++ 15 from the sfml website

**If you don't have access to Visual Studio, or you are on linux, scroll to the top to find the other version**

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
* A very easy and simple 5 minute tutorial for linking SFML with a Visual Studio project can be found here: https://www.youtube.com/watch?v=YfMQyOw1zik
* Click the run button at the top and the program should start

**If you would prefer not having to link libraries, and would prefer a version fully set up, see the link at the top**

## Authors

Zachary Chi
zachchi@tamu.edu

## License

This project is licensed under the MIT License - see the LICENSE.md file for details
