![BubbleOut Logo](https://preview.ibb.co/jvBALx/Bubble_Out_Logo.png)
# BubbleOut

**BubbleOut** is basically a **BreakOut** clone with a twist: 

Instead of static *bricks* you are destroying *bubbles* that get pushed around by the player ball and other bubbles.



## The Rules
You as the player control the **platform** at the bottom of the screen.

You can only **move left and right** and not leave the boundaries of the window.
The platform is not completely flat but has a small raised part in the middle, so you can **deflect the ball**,
which is bouncing of the window boundaries, the bubbles and of course the player platform, at an other angle than the angle it 
arrives at.

Your **goal** is to **destroy all bubbles**.

Each time you **hit** a bubble with the **ball or the platform** it shrinks a little bit (and by this its **mass and drag are reduced**)
and once it reaches a **critical size** it is destroyed.

If one bubble hits another bubble, there are three possible outcomes:
1. If the bubble we are looking at is the **same size** as the other bubble, **nothing happens**, they just bounce of each other.
2. If the bubble we are looking at is **bigger** than the other bubble, **it grows** (if it didn't hit the size limit yet).
3. If the bubble we are looking at is **smaller** than the other bubble, **it shrinks** (or gets destroyed if it reached the critical 
size).

When the ball **hits the bottom of the window**, it is **destroyed** and you get a new ball and **lose a life**
(you can see your remaining lifes in the center of the platform).

When you have **no lifes left** and the ball hits the bottom of the window, it is **game over** and you lost.



## Controls
* Movement: **A** and **D**
* Release the ball: **SPACE**
* Start the game and restart after game over or winning: **RETURN**



## Features
* A verry crude **custom C++ engine** following very loosely the **ECS pattern**:
  * **Object Manager** that stores objects linearly in **Object Pools** 
  * Decoupleled **update and render loops**:
    * Only renders when update is not lagging behind
  * **Observer Pattern**
  * **Rigidbody Physics**:
    * Rigidbodies with **mass** and **drag** that can also be kinematic or completely disabled
    * **Physics System** that can calculate collisions between *Circle - Circle*, *Rect - Rect* and *Circle - Rect*
      * **Collision Enter** and **Collision Exit** dectetion
  * Entities with **tags** as **collections of components**
  * **Render System** with different **Sprite Renderers** that are drawn in a specified order and can have **render tags** 
  so only some are rendered or can be completely disabled
  * **Sound System** with multiple voices that plays sounds triggered by events **using the Observer Pattern**


* A **Player System**
  * **Moves player platform** inside the boundaries of the window using the inputs of the player
  * Makes player platform **release the ball** if it currently holds one
  * **Checks lifes** of the player and **triggers game over**
  * Makes sure the **ball retains its speed**
  * **Resets the platform and the ball** when the game is reset
* A **Bubble System**
  * **Spawns** bubbles at the beginning of the game
  * **Checks sizes** of bubbles and **disables** them when they reached the critical size
  * **Changes the Game State** when no bubbles are left and the player **won**
* Multiple **Game States**
  * startup, playing, won and game over
  
  
  
  
## Dependencies
My Engine uses **SFML**, which is included in the Project Folder.

To make the linker aware it is there, paste **$(SolutionDir)SFML\include;%(AdditionalIncludeDirectories)** into the *Additional Library Directories* field at the **linker settings**.

It does not use any other libraries appart from the *standard library* and does not have other dependencies.




## Additional Notes
All the assets in the game are produced by myself.
I designed and drew the graphics and produced all sound effects.
The music is a chiptune cover I made of the *Game Corner Theme* from the *Pokémon Diamond/Pearl/Platinum* games.

I had a lot of issues while programming this game, which is why it may not run very smooth on slower systems and why the code is rather
awkward at some places.
Originally I wanted to create an object manager that could create and delete objects dynamically and store them in arrays, giving only 
pointers to all entites.

It also was supposed to work with polymorphism, so if a system requested all objects of type A, it would not only return all objects
of type A but also all that are derived from A.

During programming however I realized that I am not able to code that. I could not work out how to delete objects and move all the other
ones so there would be no empty spaces in the object pools without jumbeling up all references to the objects. I worked on just that 
multiple days, but I finally gave up und made the game work without the need of deleting objects.

The Polymorphism support failed because I could not figure out how to iterate over the lists of derived objects. I was able to figure
out if an object was derived from a given type, but I could not iterate over a list of derived objects using a pointer of the base type,
because that lead to object slicing.

After several days of trying I still had no solution for that problem, so I made the game work without polymorphism used in systems.
I still derived stuff, for example colliders and renderes, but I had to handle every derived type seperately (write code for a 
`Circle Collider` and for a `Rect Collider` instead of just writing the code for `Collider`)

All of this lead to some pretty inefficient code, which makes the game run slower than I wished.

It does run pretty smooth on my machine with an *Intel Core i7-4790 3.6GHz* though.
