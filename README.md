# RobotFlier
![Build Windows](https://github.com/AdsGames/RobotFlier/workflows/Build%20Windows/badge.svg)
![Build Linux](https://github.com/AdsGames/RobotFlier/workflows/Build%20Linux/badge.svg)
![Build Mac OS](https://github.com/AdsGames/RobotFlier/workflows/Build%20Mac%20OS/badge.svg)

An ADS Games production! A space arcade game where you have to fly through space and collect energy.

#### Linking
You must link with allegro 5. This can be found here:
- [Allegro 5](http://liballeg.org/download.html)

Your linker settings should look something like this:
```
-lallegro
-lallegro_primitives
-lallegro_image
-lallegro_audio
-lallegro_font
-lallegro_color
-lallegro_dialog
-lallegro_ttf
-lallegro_acodec
```
