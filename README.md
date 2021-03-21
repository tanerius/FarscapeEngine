# Farscape Game Engine
What started as a sandbox testing project for opengl in April 2017, came a long way into an interesting name engine. My initial goal was to experiment with a way to manage vast distances and floating point rounsing errors when rendering vast distanced. 
  
Now, Farscape is a 3D game engine, the purpose of which is to make it easier for the developer to build and work with large landsacpes and vast distances seamlessly. I.e. a game engine with a focus on space games.

### Inspiration
Being a software engineer and an avid gamer myself was enough reason to start experimenting with games and gaming. After countless hours spent downloading and playing around with some commercially available game engine solutions online I started compiling a list of things that I found particularly irritating or difficult to work with using other game engines. It was a coincidence that all of these things were somehow connected to working with objects related to space. I.e. big objects and vast spaces. 

Being a fan of astronomy and the scifi resulted in the name of this project - **Farscape Engine** - after the TV show. 

Together with a combination of the right motivational factors I thought I'd start experimenting with my own implementation of a game engine which will make it easy to do things I found hard or impossible in other game engines. 

### Specifications
#### OSes
The plan is to make this work on every major OS including:
* MacOS
* Windows
* Linux
  
Time being a critical factor here, and this not being a full time job for me, currently, this is windows only. I do plan on extending the functionality for mobile development too, but it is a painstakingly slow process and so far I am the only one writing this purely out of enthusiasm. 
  
#### Rendering API
The only rendering API currently supported is OpenGL 4.x. Plans are to include DirectX, Metal amd Vulkan.

 
 ### Non-github Contributors
 Here are some special shout-outs to people who were kind enough to point out my mistakes.
   
 * Nathalie Hess - proofreading
 
### TODOs and input
As mentioned before, being in the very early stages of development so I will be updating this document as I progress. The things I am currently working on are:

In order of importance
* Performance/code optimization (always)
* Cleanups (redundant stuff are bad)
* Precision timing (feature)
* Procedural generation (feature)
* Threadding
* ECS
* Scripting (Lua or C# or something ...we will see)

Contributions, inputs, suggestions, observations and any other help is appretiated.

