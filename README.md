# Pak-Engine

Pak-Engine is a game engine written in C++ for the Engine Development subject project for the CITM Bachelor's degree in Video Game Design and Development. In which we have to develop a game engine under 4 months.

# Developer

Pak-Engine is being developed by me:

photo


* [Loproxi](https://github.com/Loproxi) (Pol Rius Banús)


# Core Subsystems

* There are more sub systems but the ones i'm going to mention are the core ones.

## GameObjects & Components

Pak-Engine uses a GameObject and Component system that makes it easier to understand how entities work for anyone.

## Custom File Format

In order to optimize the import of Meshes/Textures onto the engine, each time a Meshes/Textures is imported, Pak-Engine will create a json where it will save all the necessary data from that Meshes/Textures for the next time that the Meshes/Textures is being used it will be gathering the data from that json.

## Scene & Game ViewPorts

In order to achieve rendering multiple viewports at the same time Pak-Engine uses a camera component with has a framebuffer inside. Since the camera is a component that means that every gameobject that has this component could be a new viewport.

## Optimized 3D Rendering with OPENGL

In order to optimize Pak-Engine's opengl rendering, the engine avoids using deprecated mode also known as immediate mode. By using the retained mode the engine improves the performance of 3D rendering.

## Particle System Component

On any gameobject you can create a particle system component which will allow you to spawn particles according to the settings established on the inspector as well as, all the settings will be saved on a json.

## Camera Frustum Culling

To improve the perfomance on scene and game scenes the camera discards all the gameobjects that theirs AABB boxes are outside the frustum of vision of the active camera.

# Installation Guide

* Download the most recent release
* Extract the .zip
* Click on the Pak-Engine folder and Execute Pak-Engine.exe

# Link to the latest release

Click [HERE ](https://github.com/Loproxi/Pak-Engine/releases) to download the latest release

## License

MIT License

Copyright (c) 2022 Pol Rius Banús

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
