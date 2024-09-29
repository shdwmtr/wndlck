## Winlock

A simple, yet very useful utility for full screen games on dual monitor. Some games that don't I/O block interacting with the other monitor in full screen can be rather annoying as you can accidentally click off the game. 


## Usage

Simply edit the window name in `wnd_target.txt` and start the executable. While it runs it forces your mouse to stay within the boundaries of the target window while it's focused. 

### Advanced Usage

If you would like to start the software automatically when you launch a game through Steam, you can edit the launch arguments to be as follows
    
```
path/to/start.ps1 %COMMAND% -your_optional_game_arguments=0
```

and then edit the `start.ps1` to use the proper game executable. 
