# RobotFlier

![Build Windows](https://github.com/AdsGames/RobotFlier/workflows/Build%20Windows/badge.svg)
![Build Linux](https://github.com/AdsGames/RobotFlier/workflows/Build%20Linux/badge.svg)
![Build Mac OS](https://github.com/AdsGames/RobotFlier/workflows/Build%20Mac%20OS/badge.svg)

An ADS Games production! A space arcade game where you have to fly through space and collect energy.

## Setup

### Windows (MSYS2)

#### Install Libraries

```bash
pacman --noconfirm -S mingw-w64-i686-gcc-libs mingw-w64-i686-dumb mingw-w64-i686-flac mingw-w64-i686-opusfile mingw-w64-i686-freetype mingw-w64-i686-libjpeg-turbo mingw-w64-i686-libpng mingw-w64-i686-libvorbis mingw-w64-i686-libwebp mingw-w64-i686-openal mingw-w64-i686-physfs mingw-w64-i686-allegro
```

### Mac OS

#### Install Libraries

```bash
brew install allegro
```

### Linux

#### Install Libraries

```bash
sudo apt install liballegro5-dev liballegro-acodec5-dev liballegro-audio5-dev liballegro-image5-dev liballegro-dialog5-dev liballegro-ttf5-dev
```

## Build

```bash
mkdir build
cd build
cmake ../
```

```bash
make
```
