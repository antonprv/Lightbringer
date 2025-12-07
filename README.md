## Introduction
This repository holds the game code for Lightbringer, along with Continuous Integration/Continuous Deployment (CI/CD) scripts and four custom-developed plugins.

### Usage Terms

All provided code is designated solely for non-commercial, educational purposes. Any form of commercial exploitation of the raw code is explicitly prohibited. Pre-compiled standalone plugin versions, however, may be utilized commercially after their release on Fab following full development completion. Fab release will also mean that all plugins used in this game are production-ready.

---

## Plugin Descriptions

### 🔧 Simple Input Plugin
Designed as an intuitive alternative between Unreal Engine's traditional input system and Epic's Enhanced Input framework. This plugin offers simplicity perfect for most indie projects:

- Create straightforward input maps organized into tables
- Easily switch between different input configurations (ideal for scenarios like switching to vehicle controls)
- Avoids clutter found in both legacy settings menus and enhanced input systems
- Compatible across virtually every Unreal Engine version from 4.0 through 5.6
- Fully data-driven design keeps inputs separate from core game logic, allowing scalable expansion without complexity headaches

### ⚙️ Extended Control States Plugin
Enables seamless transition to spectator mode when characters die by introducing additional control states typically present only in newer Unreal Engine iterations. Built specifically for compatibility with Unreal Engine 4.23.

### 🌄 Fake Shadow Plugin
Provides retro-style rendering effects including fake render target shadows and blob shadows:

- Add components directly to actors (either fake or blob shadows)
- Adjust parameters freely to match desired visual style
- Configure bounding boxes post-installation
- Currently supports one shadow type per actor category (main character vs NPCs)
- Blob shadows require creating a specific "DecalSocket" attached to either the root or pelvic bone of character models

### ✨ Extended Shaders Plugin

Supercharges Unreal's Material Editor, bridging the gap between Blender's versatile shader editing and Photoshop's powerful filtering tools. Now equipped with advanced procedural modeling capabilities, including real-time fractal generation and comprehensive Boolean operations.

Key Features Include:

- Blur Nodes, Animated Mask Generators, 2D and 3D Shape Creators.
- Real-Time 3D Fractal Generation: Dynamically produce infinitely detailed fractal patterns, perfect for organic models and abstract designs.
- Boolean Operations on Fractals and 3D Shapes: Combine, intersect, subtract, and manipulate  geometries interactively, even in-game!
- Integrated Procedural Modeling: Build complex 3D structures entirely within the Material Editor, bypassing traditional polygon-based workflows.
- Physics-Ready Geometry: Ensure seamless integration into game environments, where procedurally generated assets behave naturally with physics simulations.

---

Thank you for reading! Have a nice day!
