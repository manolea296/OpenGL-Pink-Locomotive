# 🚂 OpenGL Pink Locomotive (3D Project)

An interactive 3D graphics application developed in **C++** using **OpenGL**, **GLU**, and **GLAUX** libraries. The project renders a detailed 3D locomotive with custom geometry, material properties, lighting, shadow projections, and real-time keyboard controls.

---

## 🚀 Key Features

* **3D Procedural Modeling:** The locomotive is constructed from custom cubes and cylindrical wheels generated via specialized geometric algorithms (`drawCube`, `drawCylinderWheel`).
* **Lighting System:** Implements ambient, diffuse, and specular lighting configurations using `glLightfv` alongside custom material attributes (`glMaterialfv`).
* **Shadow Matrix Projection:** Dynamic casting of the locomotive's shadow onto the ground plane.
* **Interactive Controls:** 
  * `A` / `D`: Move the locomotive along the X-axis within defined boundaries (`LIMITA_SOL`).
  * `Left / Right Arrow Keys`: Rotate the camera angle smoothly around the scene (`cameraAngle`).
* **Double Buffering:** Flicker-free rendering powered by `AUX_DOUBLE`.

---

## 🛠️ System Requirements & Dependencies

Because this project relies on **GLAUX** (a legacy utility toolkit common in classic educational OpenGL environments), it requires:
* **Visual Studio** (Recommended: 2019 / 2022)
* **Windows SDK**
* Proper linker dependencies: `opengl32.lib`, `glu32.lib`, `glaux.lib`, and `glos.h`.

---

## 🕹️ Controls

| Key | Action |
| :--- | :--- |
| **A / D** | Move Locomotive Left / Right |
| **Left / Right Arrows** | Rotate Camera Around Scene |

---

## 📂 Code Structure Overview

* `myinit()`: Sets up the background clear color, smooth shading model (`GL_SMOOTH`), depth testing (`GL_DEPTH_TEST`), and main light source (`GL_LIGHT0`).
* `drawLocomotive()`: Assembles the structural components of the locomotive and applies material colors.
* `drawCylinderWheel()`: Renders wheels utilizing triangle fans (`GL_TRIANGLE_FAN`) and quad strips (`GL_QUAD_STRIP`).
* `display()`: Manages frame rendering, camera positioning via `gluLookAt`, and shadow matrix computation.

---

## 📝 License
This project is developed for educational purposes.