# DAFT: Raytracer Engine
![Render](https://frayzen.github.io/DAFT/assets/img/test.png)

**DAFT** is a powerful and flexible *raytracer engine* developed as part of a project at EPITA engineer school. It allows you to generate stunning 3D images by simulating the behavior of light in a virtual scene. Whether you're a computer graphics enthusiast, a student, or a professional, DAFT provides a solid foundation for creating realistic renderings.

## Website
You can find more information about the engine on the [official website](https://frayzen.github.io/DAFT/).

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
git clone --depth 1 https://github.com/Frayzen/DAFT.git
```

Please make sure you have the [required dependecies](https://frayzen.github.io/DAFT/#dependecies) installed on your system.
```
sudo apt-get install make gcc libsdl2-dev libsdl2-image-dev libgtk-3-dev
```

You can now **compile** the source code using the following commands:
```bash
cd ./DAFT/main && make
```
If any problem occurs, you can try to **clean** the project and recompile it:
```bash
make clean && make
```
Once the compilation is done, you can **run** the engine using the following command:
```bash
./bin/DAFT <scene_file path>
```
If needed, you can find [sample scene here](https://frayzen.github.io/DAFT/#download).

### Keys
Please find below the list of keys used to interact with the engine:
* **WASD**: Move the camera
* **Mouse**: Rotate the camera
* **P**: Render and save the image to a PNG file named `out.png`. If you want to change the quality of the render, feel free to edit the `include/constant.h`.
* **V**: Place a camera point in the scene
* **B**: Render a video based on the camera points placed in the scene (the order of the placement is important) and save it to a MP4 file named `out.mp4`. The video is rendered at 30 FPS. If you want to change the quality of the render, feel free to edit the `include/constant.h`.
* **I**: Activate or deactivate the shading
* **R**: `When shading is on` Activate or deactivate the ambient shading
* **T**: `When shading is on` Activate or deactivate the diffuse shading
* **Y**: `When shading is on` Activate or deactivate the specular shading 