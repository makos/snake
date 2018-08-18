# Snake
The classic game we all know and love.

## Requirements
The game is made and tested on Windows 10 with PDCurses and MinGW-w64, but since PDCurses is compatible with native ncurses it should compile on Linux. Not tested (yet).

Required libraries:
* ncurses (PDCurses)

Other requirements:
* GNU Make and GCC (for building)
* a terminal emulator (even `cmd.exe` will do)
* arrow keys

## Building

Pre-compiled binaries are planned. For now you have to compile from source (which is dead-easy once you have the required tools).

````
git clone https://github.com/makos/snake.git
cd snake
make release && make run_release
````

The executables are in `target/debug` or `target/release` subdirectories.

## Options

You can specify the speed the game should run at. Higher number is slower. Example:
````
./snake 100
````
Will run with game speed set to `100`. It is basically the amount of milliseconds the program sleeps every frame. Default is `125`.

## Planned features
* Persistent high-score table
* Custom game board size (customized via command-line arguments)
* Minimal bugs

## Copyright
Licensed under MIT (Expat) license. This program is free software.