# The World

## Theme

The theme for this creative project was the Major Arcana (Tarot). For this project I have drawn inspiration from the tarot card \"[The World](https://en.wikipedia.org/wiki/The_World_(tarot_card))\".

## Goal

In order to gain a better understanding of C or C++ I have decided that this project will be the creation of a platformer from scratch. In the end I did not finish creating a platformer but I was successful in creating a game engine.

## Tools and resources

- [SDL2](https://www.libsdl.org/) ([Simple DirectMedia Layer](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer)) in order to manage many of the low level aspects of the game such as video, input, threads, shared object loading, timers, etc...
- Art from [opengameart.org](https://opengameart.org/) provided some basic assets as well as [DejaVu Fonts](https://dejavu-fonts.github.io/). Links to the sources can be found in the assets folder.
- [LazyFoo](https://lazyfoo.net/tutorials/SDL/index.php) tutorials were instrumental in getting me started with this project.
- A special thanks to friends who helped guide me greatly increasing the speed at which I was able to develop.

## Design

This engine required me to implement several features to make it easy to create the game.

### Entity Component System
See: https://en.wikipedia.org/wiki/Entity_component_system

The Entity Component System has the following primary objects:

- Scene (`TW_Scene`) - The scene contains all the entities for a given level, screen or otherwise.
- Entity (`TW_Entity`) - An entity in this case is a game object. It could be the player, a platform, etc... It will contain components which give the entity functionality.
- Component (`TW_Component`) - A component is the property object which gives an entity its functionality. It could be a texture object, physics object or otherwise some object that gives the entity functionality.

The supported compoents are:

**Graphics:**

- Texture (`TW_Texture`) - A texture to be rendered.
- Text (`TW_Text`) - A text texture.
- Sprite (`TW_Sprite`) - A portion of a bigger texture (sprite sheet).
- Animation (`TW_Animation`) - An animation based on a number of textures from a sprite sheet.

**Physics/Logic:**

- Transform (`TW_Transform`) - Describes the position of an entity.
- Velocity (`TW_Velocity`) - Describes the speed, acceleration, etc... of the entity.
- Collision (`TW_Collision`) - Identifies when an entity collides with other entities with this property (attempts to resolve physics if the entity has physics).
- Think (`TW_Think`) - Provides a way for an entity to have custom code that gets executed each game loop. This is implemented as a function pointer.

**Game:**

- Player (`TW_Player`) - The player
- Platform (`TW_Platform`) - A platform

### Input Handler

The Input Handler is an ECS-like architectural pattern that was created to monitor user input. It is a lot simpler since there is only one Input Handler in the game, though there can  be multiple listeners.

The listener is an object which checks if a specific event has taken place each game loop. If it has, it makes a note that this event occured.

Currently supported listeners are:

- Key-Down (`TW_L_KeyDown`) - Checks if a given key gets pressed. The key to listen for must be specified as the listener will not check for other keys.
- Key-Up (`TW_L_KeyUp`) - Like key-down, but instead checks if a key is depressed. Again the key to listen for must be specified.
- Mouse-Down (`TW_L_MouseDown`) - Checks if a mouse button was pressed (currently which mouse button is pressed is not supported).
- Mouse-Up (`TW_L_MouseUp`) - Checks if a mouse button was depressed.
- Mouse-Move (`TW_L_MouseMove`) - Checks if the mouse was moved.
- Quit (`TW_L_Quit`) - Checks if a quit request has been issued.

### Game Loop

Each game loop applies logic in the following order:

1. Clear the renderer for the next game frame.
1. Update the game state which includes calculating Delta Time, etc...
1. Update the listeners such that player input is registered.
1. Check if the a quit request has been registered... if yes exit the game.
1. Run all physics components in a scene. This moves objects that need to be moved and resolves any collisions of objects that have physics.
1. Run logic components in a scene. If there's any specific custom logic that has been added to an entity, this will be resolved here.
1. Render the scene and display it on the screen.
1. Clear listeners, reset stateful objects and limit the frame rate.

## After thoughts

In the end I was not able to create the game that I set out to create before the deadline for this theme arrived. Nonetheless I was successful in creating the beginnings of a functional game engine. In future themes I plan to enhance this project by using the engine to create a game and provide the theme music for it.
