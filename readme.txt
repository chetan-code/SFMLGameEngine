
Assignment 2 :

Program Specifications :

-give randow rotation to all player and enemies

Player :

- has shape in config
- center spawn at start and after die
- player speed - as per config - WASD movement
- player movement confined in window bounds
- player shoot bullet at mouse pointer - left mouse click
- the speed size and lifespan of buller - as per config

Special Ability :

- make it look cool visually
- use new component to implement the new special mechanic 
- special ability slows down all the enemies - they remain stationery for - 5 seconds
- cooldown timer - you can use special ablity after every 30 sec
- properties of special moves are hard coded in code

Enemies :

- Enemies spawn - random locations every x frames - x in config
- Enemies must not overlap at the window border - i.e they should spawn inside the window border
- Enemies can have vertices - in between min and max verticies count - as per config
- Enemies shape radius - config
- Enemies will have random color at spawn
- Enemies will have random speed as per min and max - in config
- Enemies hit border - they are deflected in opposite direction
- When large enemies collide with bullet or player - they are destroyed - with a visual effect - where N
number of small entities (half of original) spawn on its place - Where N is number of vertices of origional enemy.
Each small entities must have the same number of vertices and color as of original. The small entities travel outward
at angles at fixed intervals equal to (360 / vertices)

Score :

- score of enemy - N*100 - smaller enemies has double this value 200 * N
- if player bullet hit player score is increase by score assgined to enemy
- score displayed at top left corner - with font as per config

Drawing :

- add rotation for all entities
- any entity with lifespan also changes alpha color of entity - from 255(100% in first frame of life) to 0 (last frame of lifespan)
 like a bullet will fade out - small enemy will also fade out

Misc :
-"P"" key pause the game
- "Esc" closes the game


Config file details : 

Window width height framelimit fullscreen(1 for fullscreen, 0 for window) 
Font filepath size r g b
Player shapeRadius collisionRadius speed(magnitude) fillr fillg fillb outlineR outlineG OutlineB outlineThickness vertices
Enemey shapeRadius collisionRadius smin smax outlineR outlineG OutlineB outlineThickness vertexMin vertexMax SmallLifespan spawnInterval
Bullet shapeRadius collisionRadius speed fillR fillG fillB outlineR outlineG outlineB outlineThickness vertices lifespan 


Hints :

1. vec2 class
2. basic of entityManager


Recommendation to approach the assignment :
 -Save the configuration file reading until for later
 -Implement vec2 class - will be used in all other components
 -Implement basic functionality in entityManager class
    




