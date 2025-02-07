# C++ Game Engine
<p align="justify">
 Custom game engine/framework built using C++ and on top of some of the usual culprits, i.e. Box2D for physics, OpenGL for graphics and SDL for window creation, input handling as well as audio. Being 2D only, there 
 are some common features already implemented, like 2D transformations, tiling, and spritesheet based animations. Common classes like <code>GameObject</code>, <code>Pawn</code> and <code>Sprite</code> are also 
 already built-in, with the engine being compilable into a library that can then be used to build your own game on top of it. 
</p>

<p align="justify">
 <b>Disclaimer:</b> project was done in simpler times. Stuff like raw pointers and such were used galore under the pretense of making us learn the hard way... or something of that sort. Proceed with caution.
</p>

## Build/Run Instructions
<p align="justify">
 The engine comes with a Game project to exemplify its workings, so be sure to compile the engine first before compiling the game. It should work out of the box with Visual Studio, just be sure to set the Game as 
 the startup project. Necessary dlls are already on the output debug folder. If you don't want to go with the Visual Studio route but do manage to crank out a CMake setup, do contact me in that sense! 
</p>

## Demo Video
[![ C++ Game Engine](https://img.youtube.com/vi/YrV5QRa83ns/0.jpg)](https://www.youtube.com/watch?v=YrV5QRa83ns)
