

<h1>Generator.html Documentation</h1>

Scripts are plain-text files processed by the CnCn engine. Each line is one command followed by its arguments. Strings are quoted with `"double quotes"`, numbers are unquoted.

## Commands list
```

TXT "text" - new text into the textbox
ROW n - next n commands will be executed together with ROW command
BG "file" - change background. Speed can be changed in vars
LD "file" - load new sprite and place it into ${LID} + 1 index of sprites
CHSPR id "file" - change sprite of sprites[n]. Speed can be changed in vars
RET "name/finale" - change scene or exit
SET "var" string or n - set var. To get var you can use ${var}
MV id x y t - move sprites[id]. t - time.
CLTB - clear tb
LDSIZE id w h - LD with size
LDXYWH id x y w h - optimal LD with x y w and h
CALL "name" execute function (not lua)
OPERATION a op b - operation with var(s)
TBCAP "text" -  change textbox footer text - name of talking character and so on
WAIT ms - wait (WAIT 0 updates screen, so its useful inside of ROW)
IF var/n op var/n
LUA "text" - execute lua string
BPM "file" - play background music
SOUND "file" - play sound
BPMFADEIN -
LUA_IMPORT "file" - import lua file
LDFILE "file" - switch executable .bin file. change the scene to main scene of new file
BPMVOL n - change volume
SOUNDVOL id n - change volume of sound id
BPMCROSS - new track with fade out. not implemented
TALK "file" - sound, but it stops previous sounds
INPUT "text" - input into the __input variable. text will be printed in textbox
TBRECT x y w h - change position of textbox
TBFILL "#hex" - change color of textbox
HIDE id - hide sprite
WAITV var - dont continiue script until var is 1 (for choice and so on)
SETACTIVE startindex endindex "lua_func_name" - make text from last txt active ( {{active word | lua_func_name}})
```


## Example

```
SCRIPT main
ROW 4

BG "bg1.png"
SET "place" "room1"
LUA "function hesaidyes() txt('Yeeees!') end"
LUA "function hesaidno() txt('Noooo!') end"

TXT "hello world"
LUA "=2+2"
IF __return == 4
TXT "2+2=${__return}!"
LDXYWH "sprite.jpg" 10 10 60 50
MV 0 20 20 10
ELSE
TXT "do you understand the mistake? {{yes|hesaidyes()}} or {{no | hesaidno()}}"
ENDIF


RET "finale"
END


### Structure of the project
```
project_folder
    bg1.png
    bg2.png
    functions1.lua
    functions2.lua
    scriptMain.txt
    scriptMain.bin - generated automaticaly
    script2.txt
    script2.bin
    scriptMain.json - save from web generator to continiue work
    script2.json
    music.mp3
    music2.wav
    sound.ogg
    chunk1/ - loads only when its needed. for large files  !!!ОНИ ПОКА ВСЕ ПО ОДНОМУ ЗАГРУЖАЮТСЯ!!!
        some_huge_file.wav
```

## Notes
```
- Variable names are case-sensitive strings.
- The special variable `__input` holds the last `INPUT` result.
- You can get last sprite id by ${LID}
- `ROW n` groups the following `n` commands to run together — useful for simultaneous animations and audio.
- Some commands are not listed here. However they have not been implemented yet
```