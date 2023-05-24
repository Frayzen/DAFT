# DAFT: Raytracer Engine
![Render](https://frayzen.github.io/DAFT/assets/img/test.png)

DAFT is a powerful and flexible raytracer engine developed as part of a project at EPITA engineer school. It allows you to generate stunning 3D images by simulating the behavior of light in a virtual scene. Whether you're a computer graphics enthusiast, a student, or a professional, DAFT provides a solid foundation for creating realistic renderings.

## Features
* Raytracing: DAFT uses the raytracing technique to trace the path of light rays, simulating their interactions with virtual objects and calculating the final color of each pixel in the image.
* Shading Models: The engine supports various shading models, including Lambertian, Phong, and Blinn-Phong, to give objects different material appearances and lighting effects.
* Reflection and Refraction: DAFT accurately handles reflection and refraction of light rays, enabling the rendering of reflective surfaces, transparent materials, and complex optical effects.
* Shadows: The engine calculates shadows by casting rays from each point towards the light sources, providing realistic and accurate shadowing in the rendered images.
* Object Primitives: DAFT supports basic geometric primitives such as spheres, planes, and triangles, allowing you to create and arrange objects in your scenes easily.
* Texture Mapping: You can apply textures to objects using UV mapping, providing detailed and realistic surface appearances.
* Scene Description: Scenes are described using a simple text-based scene file format, allowing you to define camera positions, light sources, objects, and their materials easily.

## Usage
### Download
You can download the engine [here](https://frayzen.github.io/DAFT/#download). The archive contains the source code, the documentation, and sample scenes.

### Compile
You can also compile the engine from source.

First, **clone** the repository using the following command:
```bash
$ git clone --depth 1 https://github.com/Frayzen/DAFT.git
```
You can now **compile** the source code using the following commands:
```bash
$ cd ./DAFT/main && make
```
If any problem occurs, please make sure you have the [required dependecies](https://frayzen.github.io/DAFT/#dependecies) installed on your system. You can also try to **clean** the project and recompile it:
```bash
$ make clean && make
```
Once the compilation is done, you can **run** the engine using the following command:
```bash
$ ./daft <scene_file>
```
If needed, you can find [sample scene here](https://frayzen.github.io/DAFT/#download).