# PNMHIDE

This program is hiding text in an image file.

## Report

[Open Report](HW6.pdf)

## Prerequisites

What things you need to install the software and how to install them:

- GCC (for Ubuntu/Debian): `sudo apt install gcc`
- CMake (for Ubuntu/Debian): `sudo apt install cmake`
- Make (for Ubuntu/Debian): `sudo apt install make`
- Doxygen (for Ubuntu/Debian): `sudo apt install doxygen`
- Libnetpbm (for Ubuntu/Debian): `sudo apt install netpbm libnetpbm10 libnetpbm10-dev`

## Installing

A step by step series of examples that tell you how to get a development env running

Place the follwoing step into terminal to build the project:

```
mkdir build && cd build && cmake ..
make
```

To hide text run:

```
./src/pnmhide -e "hello world" ../test/cover.pnm > ../test/stego.pnm
```

To retrive the text:

```
./src/pnmhide -d ../test/stego.pnm
```

To make docs run:

```
make doc
google-chrome-stable doc/html/index.html
```


## Contributor
* **Dragi Kamov** - [Github](https://github.com/dragikamov)
