This repository contains Lightbringer game code, CI\CD scripts and 4 custom plugins.
<br>
<br>
You can use all of this code only non-commercially, only for educational purposes.
Any type of commercial use is strictly prohibited.
You can use standalone compiled plugin versions commercially though, and I will publish all of them on Fab at the end of the development.
<br>
<br>
Now, about plugins.
<br>
<br>
Simple Input serves as a middle ground between the Unreal Engine's legacy system and Epic's new Enchanced input.
It is just enough for most indie titles. It works, well, simple. You create a table with your input map and activate it.
If you need to change your input map for some reason - like, for driving a vehicle, you just create another input map and swap to it.
<br>
No sitting in project settigns like with legacy system and no file bloat (1 file per input action + 1 extra for input mapping context) like in the enchanced input.
<br>
Create tables, switch between them, subscribe to any of them at any time.
It should be compatible with literally any UE version from 4.0 to 5.6, as it is just a nice wrapper around legacy input system.
<br>
<br>
The plugin is fully data-driven - meaning, these tables are not classes, they're static, they're completely independent from the rest of the game, and you can easily scale up your games with it and not loose your sanity.
<br>
<br>
Extended control states allows you to easily switch to spectator mode if your character dies, it does so by adding extra control states which appear only in later version of UE. 
(This game is using Unreal Engine 4.23).
<br>
<br>
Fake shadow is my implementation of retro fake render target shadows and blob shadows. You just add the respective component to your character (fake or blob), and then adjust parameters to better suit your needs.
After adding fake shadow, all you need is to adjust its bounding box. It is currently one fake shadow per actor type, kind of going for fake shadow for main character and blob shadow for NPC's.
Blob shadow can be added only to a character class, and then you need to create a socket called "DecalSocket" parented to root bone or pelvis bone of your character. I might change that in the future updates.
<br>
<br>
Extended Shaders adds blur nodes, animated masks and shape ganerators, aiming to bring material editor closer to Blender's shader editor and add some Photoshop filters like gaussian blur.
It also includes a simple HLSL compiler which allows you to write your custom HLSL code with functions and classes and pipe it straight to material editor as custom nodes.
Fake shadow plugin is using this one heavily.
<br>
<br>
Anyways, if you've red up to this point - have a great day!
