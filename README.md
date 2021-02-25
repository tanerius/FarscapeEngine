# Farscape Game Engine
Farscape is a 3D game engine, the purpose of which is to make it easier for the developer to build and work with large landsacpes and vast distances seamlessly.

### Current version
0.2.92-dev (early development)

### Inspiration
Being a software engineer and an avid gamer myself was enough reason to start experimenting with games and gaming. After countless hours spent downloading and playing around with some commercially available game engine solutions online I started compiling a list of things that I found particularly irritating or difficult to work with using other game engines. It was a coincidence that all of these things were somehow connected to working with objects related to space. I.e. big objects and vast spaces. 

Being a fan of astronomy and scifi resulted in the name of this project - **Farscape Engine**. 

Together with a combination of the right motivational factors I thought I'd start experimenting with my own implementation of a game engine which will make it easy to do things I found hard or impossible in other game engines. 



### Specifications
Currently I am working on three platforms simultaneously:

* MacOS 10.12+
* Windows
* Linux

I do plan on extending the functionality for mobile development too, but it is a painstakingly slow process and so far I am the only one writing this purely out of enthusiasm. 

The code itself is in object-oriented C++11 and using [OpenGL 4.1 API](https://khronos.org/registry/OpenGL/index_gl.php) for the main implementation, GLSL for the shaders  and the help from a few fairly standalone open source helpers like GLM, GLEW2 and GLFW3.
 
### TODOs and input
As mentioned before, being in the very early stages of development so I will be updating this document as I progress. The things I am currently working on are:

In order of importance
* Performance/code optimization (always)
* Cleanups (redundant stuff are bad)
* Precision timing (feature)
* Rendering text / font maps (feature)
* Procedural generation (feature)
* Level of detail (LOD) (feature)
* Threadding

Contributions, inputs, suggestions, observations and any other help is appretiated.

