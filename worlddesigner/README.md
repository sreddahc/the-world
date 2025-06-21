# World Designer

A simple python project for creating levels in The World.

## Setup instructions

World Designer application uses [wxPython](https://wxpython.org/), which wraps [wxWidgets](https://wxwidgets.org/). This application requires a number of [dependencies](https://github.com/wxWidgets/Phoenix/blob/wxPython-4.2.3/README.rst#id9). You can install these dependencies on [Debian](https://www.debian.org/) by running the following command:

```console
$ sudo apt install dpkg-dev build-essential python3-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libgstreamer-plugins-base1.0-dev libgtk-3-dev libjpeg-dev libnotify-dev libpng-dev libsdl2-dev libsm-dev libtiff-dev libwebkit2gtk-4.0-dev libxtst-dev
```

This python application is managed using [uv](https://docs.astral.sh/uv/). You will also require this. Install uv by following their [instructions](https://docs.astral.sh/uv/getting-started/installation/). Or running the following commands derived from their instructions on Debian:

```console
$ sudo apt install pipx
$ pipx install uv
```

Setup your environment by running the following commands in the base worlddesigner folder:

```console
$ uv venv
$ source .venv/bin/activate
$ uv sync
```

You're now good to go!

## How to use

### Creating a new level

```console
uv run main.py new /path/to/level_name.json
```

### Editing an existing level

```console
uv run main.py load /path/to/level_name.json
```
