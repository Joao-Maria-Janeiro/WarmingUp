# WarmingUp

Final Project for the programming course of electrical and computer engineering first year second semester

## What you need to install
* SDL2
* SDL2_image
* SDL2_ttf

## For Ubuntu simply run:
```
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-dev
$ sudo apt-get install libsdl2-ttf-dev
```

## Compile through the terminal:
```
$  gcc *.c -g -I/usr/local/include -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o WarmingUp
```

If you want the textual mode simply run:
```
$ ./WarmingUp -f2 tempcities.csv -f1 tempcountries_all.csv -t
```

If you want the graphical mode run:
```
$ ./WarmingUp -f2 tempcities.csv -f1 tempcountries_all.csv -g
```
