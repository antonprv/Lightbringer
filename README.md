## Introduction
This repository holds the game code for Lightbringer, along with Continuous Integration/Continuous Deployment (CI/CD) scripts and four custom-developed plugins.

### Usage Terms
All code here is intended exclusively for **non-commercial**, **educational** purposes. Commercial usage of the raw code is strictly forbidden. However, pre-compiled standalone plugin versions may be used commercially once they become available on Fab upon completion of development.

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
Enhances Unreal's Material Editor functionality, bringing it closer to Blender's Shader Editor experience while incorporating Photoshop-like filter capabilities such as Gaussian blur:

- Adds blur nodes, animated mask generators, and shape creators
- Includes a basic High Level Shader Language (HLSL) compiler enabling direct integration of custom HLSL code into materials via customizable nodes
- Heavily utilized by the Fake Shadow plugin for advanced shading techniques

---

Thank you for reading! Have a fantastic day ahead!
