# Pastry crunch

This is a "midars miner" like game and it's about finding at least 3 matches either horizontally or vertically
of the same pastry.

Everything is configurable from the `assets.json` [link](https://github.com/kohnech/bakery-street-game/blob/master/assets/assets.json) file. Here you can choose any of the important
game parameters and even change skins and the look and feeling of the game as it should
be.

Any questions? Please ask me or post a PR.

## Techniques and 3rd-party libraries
### 3rd-party libraries
This games relys soly on the SDL2 set of libraries:
* SDL2 (Basic game engine)
* SDL2_image (displays jpg/png etc...)
* SDL2_ttf (display fonts & text)
* SDL2_mixer (play sounds like wav)
* Hlohmann Json: https://github.com/nlohmann/json

If you don't have these installed, don't worry, they are included in the Runtime
environment as a they should be (best practise) so you don't need to search for any
obscure libraries on the internet. In order to setup the correct runtime environment
under linux, the simplest way to run the game is
```
make run
```

### References
* Gameartguppy (Game assets, skins): https://www.gameartguppy.com/shop/pastry-icons/
* Ideas and techniques learnt from: http://www.sdltutorials.com/sdl-tutorial-basics
* Some ideas and game logic learnt from: https://github.com/dgkanatsios/matchthreegame


## Building & setup

### Linux
```
make help
```
will show you a list of all the make targets. To start building it type:
```
make all
```
and to run it:
```
make run
```


## Game logic
![alt text](https://github.com/kohnech/bakery-street-game/blob/master/state_machine.png "Game logic")