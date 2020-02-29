# Tamago

<p>
<a href="https://github.com/mupfelofen-de/Tamago">
  <img src="https://img.shields.io/badge/project-GitHub-blue?style=flat?svg=true" alt="GitHub project" />
</a>
<a href="https://github.com/mupfelofen-de/Tamago/blob/master/LICENCE.md">
  <img src="https://img.shields.io/badge/licence-BEER--WARE-blue?style=flat?svg=true" alt="Licence" />
</a>
<a href="https://travis-ci.org/mupfelofen-de/Tamago">
  <img src="https://travis-ci.org/mupfelofen-de/Tamago.svg?branch=master" alt="Build status" />
</a>
</p>

## About

Tamago [たま
ご](https://en.wiktionary.org/wiki/%E3%81%9F%E3%81%BE%E3%81%94), which
means "egg" will be a clone of the famous digital pet from 1996 that
uses a P10 LED panel as its display.

This project is built upon
[BluePrint](https://github.com/mupfelofen-de/BluePrint), a base project
for the STM32F103C8T6 aka [blue pill board](http://reblag.dk/stm32/).

## Status

Far from finished; work in progress.

## Schematic

Todo.

## Installation

1. Install [PlatformIO Core](http://docs.platformio.org/page/core.html)
2. Run these commands:

```bash
    # Build project
    > platformio run

    # Upload firmware
    > platformio run --target upload

    # Clean build files (optional)
    > platformio run --target clean
```

## Documentation

The documentation can be generated using Doxygen:
```
doxygen
```

A automatically generated version of the documentation can be found
here:  [Documentation](https://docs.dailyhack.eu/tamago/)

## Licence

The source code of this software is licenced, unless stated otherwise,
under the terms of [The Beerware Licence](LICENCE.md).

Logo icon made by [Good Ware](https://www.flaticon.com/authors/good-ware)
from [Flaticon](https://www.flaticon.com/).

Tamagotchi is a trademark of Bandai.  This project is not affiliated or
endorsed by Bandai in any way.
