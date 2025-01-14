# CUB3D

A lightweight raycaster game engine built for Linux and MacOS.

## Getting Started

Everything you need to get the game up and running on your machine!

### Prerequisites

The game uses a simple graphics library called minilibx to display the window and draw the graphics on screen.

If on MacOS, minilibx is already in the repository and you're good to go!

If on linux, you need to download [minilibx for linux](#https://github.com/42Paris/minilibx-linux), and simply copy the folder to the root of the repository.
Make sure to name the folder "minilibx-linux", or you'll get a compilation error!

### Installing

On Linux, if you've followed the prerequisites you can simply clone the repository and you should be good to play!

On the MacOS version of minilibx, some functions are missing, including one that we use to free the memory associated with the display.
To make the game playable on MacOS, please go to the file "cleanup.c" and to line 68, and comment/remove this line:

```
mlx_destroy_display(game->win->mlx_ptr);
```

After this the game should compile with no errors! (You may get some warning messages, these are fine and come from the minilibx, not the project)

## Utilisation

**Game Setup**

The program takes a command-line argument to indicate which map file to use for the game, in the form of:

```
./cub3d path_to_map
```

Some ready-made maps are stored in the maps folder in the repo. Most of them are for testing our error-handling strategies, but maps/test.cub is a playable one!
That being said, feel free to make your own map. There are just a few rules to follow:

* The map file has to finish with an extension .cub
* The map file has to contain the path to 4 xpm textures (we have some located in the textures folder) like so:

```
NO ./path_to_file/file_NO.xpm
SO ./path_to_file/file_SO.xpm
EA ./path_to_file/file_EA.xpm
WE ./path_to_file/file_WE.xpm
```

* The map file has to contain two lines which indicate the floor and ceiling colour, like so:

```
C 40,35,30
F	85,119,136
```

* After these 6 lines of information, the last element of the map file has to be the map itself.
* In the map, 0 indicates empty space, 1 indicates a wall, and N/S/W/E indicates the player's starting position and direction (note that there can only be one character to indicate the player).
* The map has to be fully surrounded by walls, eg:

```
1111111
1000001
10000N1
1111111
```

It is probably easier to modify a pre-existing map file than to create one from scratch, but whatever floats your boat!

**Controls**

```
W KEY: move up
S KEY: move down
A KEY: move left
D KEY: move right
LEFT ARROW KEY: player looks left
RIGHT ARROW KEY: player looks right
esc/window red cross: exit game
```
Thanks for playing!

## Authors

* **Juliette Le Goff**
* **Gonçalo Veríssimo**

## Acknowledgments

* Thank you to developer Lode for creating a really comprehensive [explanation](#https://lodev.org/cgtutor/raycasting.html) of a possible way to create a raycaster, this was very informative!
