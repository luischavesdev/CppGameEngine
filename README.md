# C++ Game Engine
<p align="justify">
 Custom game engine/framework built using C++ and on top of some of the usual culprits, i.e. Box2D for physics, OpenGL for graphics and SDL for window creation, input handling as well as audio. Being 2D only, there 
 are some common features already implemented, like 2D transformations, tiling, and spritesheet based animations. Common classes like <code>GameObject</code>, <code>Pawn</code> and <code>Sprite</code> are also 
 already built-in, with the engine being compilable into a library that can then be used to build your own game on top of it. The project already comes with a mock shmup to exemplify this. 
</p>

<p align="justify">
 <b>Disclaimer:</b> project was done in simpler times. Expect stuff like raw pointers and such galore, used under the pretense of making us learn the hard way... or something of that sort. Proceed with caution. 
 An overall cleanup was done since then, but only the minimum to get the project properly running and accessible. All the questionable coding decisions still stand.
</p>

## Build/Run Instructions
<p align="justify">
 By running the appropriate script under <code>BuildScripts</code> you should be able to pretty easily build the project. Be aware that technically there is no support for other platforms other than Windows since 
 all the libraries used are Windows libraries i.e. .lib, .dll, etc. If you really wanna go for it, after hooking in the platform corresponding libraries, in theory everything should still work. In case you're in 
 Windows but don't want to build a Visual Studio solution, Premake also supports Makefiles, so you just have to edit the build script.
</p>

## Resources
- **SDL**: used for window creation and input handling
- **SDL_mixer**: used for audio
- **Box2D**: used for physics
- **glad**: used to access OpenGL functions
- **glm**: used for the matrix math needed for OpenGL
- **stbimage**: used to get images into OpenGL

- **Sounds**: from Freesound
- **Graphics**: from [Xenon 2000: Project PCF](https://archive.org/details/Xenon_2000_Project_PCF)

## Demo Video
[![ C++ Game Engine](https://img.youtube.com/vi/YrV5QRa83ns/0.jpg)](https://www.youtube.com/watch?v=YrV5QRa83ns)
