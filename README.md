This repository contains Lightbringer game code and my custom input plugin.
<br>
<br>
You can use all of this code only non-commercially, only for educational purposes.
Any type of commercial use is strictly prohibited.
You can use standalote compiled Simple Input plugin commercially though, and I will publish it on Fab at the end of the development, when I feel confident in its technical state and feature-completeness.
<br>
<br>
Now, about the plugin.
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
Anyways, if you've red up to this point - have a great day!
