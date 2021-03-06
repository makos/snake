# Snake
The classic game we all know and love.

[![asciicast](https://asciinema.org/a/197056.png)](https://asciinema.org/a/197056)

## Requirements
The game is made and tested on Windows 10 with PDCurses and MinGW-w64. Tested
on Windows 10 with `cmd.exe`, `Cygwin` and Git for Windows' `bash.exe`. Tested
to be working on Arch Linux VM. 

Required libraries:
* ncurses (PDCurses)

Other requirements:
* For building:
    * GNU Make and GCC, preferably with bash or other shell (just not `cmd.exe`)
* For playing:
    * a terminal emulator 
    * arrow keys

## Building

Pre-compiled binaries are planned. For now you have to compile from source (which is dead-easy once you have the required tools).

````
git clone https://github.com/makos/snake.git
cd snake
make && make run
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
&copy; 2018 Mateusz Makowski
