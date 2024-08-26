# TERMINAL JUMP

Terminal Jump is a simple game where you jump over obstacles to complete a scenario.
This game was created using the `ncurses` library.

This repository also includes the source code for [Centered Menus](https://github.com/pedresp/CenteredMenus), which was used for the game's menus.

## How to play

To play **Terminal Jump**, download this repository and ensure that the `ncurses` 
library is installed. Once you have downloaded the source code, you will need to
compile it.

To compile this project using `CMake`, follow these steps:

1. Create a `build/` folder and set up a build system:

    ```bash
    mkdir build
    cd build/
    cmake ../CMakeLists.txt -B .
    ```

2. Compile the project

    ```bash
    cmake --build .
    ```

3. Run the executable

    ```bash
    ./main
    ```

#### Warning

The game executable should be executed inside the `build/` directory as it searches the
possible scenarios in using the following relative route: `../scenarios/`.

As a consequence, if it is not run inside `build/` folder it won't find any scenario.

## Controls

### Menu

The Menu used in this repository is taken from the [Centered Menus](https://github.com/pedresp/CenteredMenus) repository, so it's controls are the same.

To select the scenario you would like to play use the `arrow key` and press `Enter` 
to confirm. If you want to exit, press the `Esc` key.

### Scenario

In order to jump, press any key except `Esc`. If you want to exit the scenario, press
`Esc` key. 

## Desing your own scenarios

With **Terminal Jump**, you can design your own scenarios; however, there is currently 
not a great variety of obstacles or options available.

Scenario are stored in a text file that describes the order and characteristics of the
elements it contains. This repository includes some sample scenarios for users to
play with and learn how to create their own.

Scenarios contain the following elements:

- Spaces
- boxes

### Spaces

Spaces are represented by the '**_**' character. To improve scenario comprehensibility 
you can add multiple spaces by adding a number before '**_**' character.

### Boxes
Boxes are represented by the '**|**' character. They have 1x1 dimensions by default and
can be modified by adding the new dimensions as show below:

```
y_value x x_value
```

So, in order to create a box with a height of 2 and a width of 3 you will need to write the following expression: `2x3|`

#### Warning
Neither spaces nor eol characters are supported right now, so avoid them to allow correct
reading of your scenarios.