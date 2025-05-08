# The World

## Theme

The theme for this creative project was the Major Arcana (Tarot). For this project I have drawn inspiration from the tarot card \"[The World](https://en.wikipedia.org/wiki/The_World_(tarot_card))\".

## Goal

In order to gain a better understanding of C or C++ I have decided that this project will be the creation of a platformer from scratch. In the end I did not finish creating a platformer but I was successful in creating a game engine.

## Design

This game engine utilised [SDL2](https://www.libsdl.org/) ([Simple DirectMedia Layer](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer)) in order to manage many of the low level aspects of the game such as video, input, threads, shared object loading, timers, etc...

```mermaid
Scene-->Entity
Entity-->Component
Component-->Component_Objects*
```