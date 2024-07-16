# TwentyFourPoint
TwentyFourPoint, a 24-point game written in Qt6.

One of the most popular card games in China, 24-point game is a game that uses four cards to calculate the result of 24. The four cards can be added, subtracted, multiplied, and divided to get 24. The game is simple and fun, and it is suitable for all ages.

It initially started as a project for the "Programming Practice" course. It is now open source for everyone to enjoy and learn from.

## Build
### Windows
1. Install `vcpkg` and configure environment variable `VCPKG_ROOT`.
2. `vcpkg install qtdeclarative:x64-windows-static qttranslations:x64-windows-static`
3. Build with `cmake` and `ninja`, using presets defined in `CMakePresets.json`.

### Linux
1. Install `qt6-declarative` via your package manager. On Arch Linux, it should be `sudo pacman -S qt6-declarative`. Try to find it on your package manager if you are using other distributions.
2. Build with `cmake`. eg. `cmake -B build -S . && cmake --build build`

### MacOS
I'm sorry but I don't have a Mac, so I can't provide a detailed build guide.

## Development
### Format Code
This project uses `clang-format` & `qmlformat` to format.

```bash
qmlformat -i qml/*.qml
clang-format -i -style=file include/*.h
clang-format -i -style=file src/*.cpp
```

### Code Check
`clang-tidy` and `include-what-you-use` (iwyu) are used to check code.

To check code, you should install `clang` and `include-what-you-use` first. If you are using `paru` on Arch Linux, try the following command to install them:

```bash
paru -S clang include-what-you-use
```

To check code, you should build with preset `code-check` in `CMakePresets.json`. All code that fails to meet the requirements will trigger an error.

```bash
cmake --preset code-check
cmake --build --preset code-check
```

## License
This project is licensed under the GNU Affero General Public License v3.0 or later.

```
TwentyFourPoint, a 24-point game written in Qt6.
Copyright (C) 2023-2024 alampy <alampy.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
