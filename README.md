# Terroir - 2D Game Engine

<img src="/resources/TerroirLogo.PNG" alt="Terroir-Logo" height="300" width="300"/>

---

_The word Terroir derives as a French term used to describe environmental factors that affect a crop's phenotype. These
such crops consist of many of the finer things in life, including wine, tobacco, and even chocolate. All the
characteristics that make up a terroir give the crop a distinctive character. Terroir even references this character._

---

# CAUTION

Terroir is currently in a **extremely** early state and not recommended now or the considerable future for the use in serious
commercial or hobby projects. The API will undergo considerable changes over this period.

Terroir provides ABSOLUTELY NO WARRANTY.

---

Terroir is planned to be a simple but powerful tool to create interactive 2D video games and experiences without
worrying about cross-platform compatibility featuring first-class support for both Windows and Linux through OpenGL (for now).

Overall, the main goal is to provide a thorough interface that focuses and emphasizes on ease of development and scalability while maintaining high performance. Because of this, the LuaJIT embedded runtime and optionally through the Lisp [Fennel](https://fennel-lang.org/), will be used for scripting in the Terroir engine. Modern C++ as a language has come a long way in terms of memory safety and other productivity, but for most 2D interactive experiences, and to take advantage of hot reloading, the LuaJIT will be powerful enough to make the developers dream a reality.

Terroir will also have an Entity Component System (ECS) plugin based API will allow the developer the freedom to modularize how their code is structured as well as providing the foundation in how Terroir manages game data.

## Getting Started

Building Requirements:

- Any C++17 capable compiler
- CMake (min version 3.0)
- Python 3

Terroir is a statically linked library that is linked at compile time with your chosen executable.  Packages are handled through Microsoft's [vcpkg](https://vcpkg.io/en/index.html); it has been added as a git submodule under .gitsubmodules. All other dependencies are listen in vcpkg.json.

Start by cloning the repo.

Cd into the directory and to build simply run:
-- Coming Soon --
-- somebashscript.sh
-- somebatchfile.bat

## Examples

-- Coming Soon --

## Planned Features

- Platform abstraction (windowing, sound, input, memory, etc.) 
- Logging and custom asserts 
- Integrated debugging tools
- 2D rendering
- Text/Font rendering
- UI management 
- 2D physics
- ECS
- Math
- Networking
- AI
- Scenes
- Scripting via LuaJIT and Fennel
- Graphical Editor

## Out of scope (Not planned for open source releases)

- 3D rendering
- Mobile builds

## License

The 2D version of Terroir is free and open source under [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).

I sincerely hope you enjoy working with the engine, all I ask is for credit or a shoutout in your project. :)
