# Terroir - 2D Game Engine

![Logo](/resources/TerroirNewLogo.png)
---

_The word Terroir derives as a French term used to describe environmental factors that affect a crop's phenotype. These
such crops consist of many of the finer things in life, including wine, tobacco, and even chocolate. All the
characteristics that make up a terroir give the crop a distinctive character. Terroir even references this character._

---

## CAUTION

Terroir is currently in a fairly early state and not recommended now or the considerable future for the use in
serious
commercial projects. Hobbyists and others are welcome to use the engine at your delight!  Just be warned, the API will
undergo considerable changes over this period.

Terroir from now to at least v1.0 does not support development on macOS or iOS as this is an OpenGL
only backend engine. Apple since 2018/2019 have deemed OpenGL depreciated so in the wise words of a Redditor I forgot
the name of, I deem that Apple has been depreciated.... But if you wanna try to compile and run on your Mac, go ahead by
all means.

---

Terroir 1.0 is planned to be a simple but powerful tool to create interactive 2D video games and experiences featuring
first-class support for both Windows and Linux through OpenGL.

Overall, the main goal is to provide a thorough interface that focuses and emphasizes on ease of development and
scalability while maintaining high performance. Because of this, the LuaJIT embedded runtime will be used for scripting
in the Terroir engine. Modern C++ as a language has come a long way in terms of memory safety and other productivities,
but for most 2D interactive experiences and to take advantage of hot reloading, the LuaJIT will be powerful enough to
make the developers dream a reality.

Terroir will also have an Entity Component System (ECS) plugin based API will allow the developer the freedom to
modularize how their code is structured as well as providing the foundation in how Terroir manages game data.

## Examples

### Green Rectangle in Vintage v0.1

![Green Rectangle](/resources/Rect.png)

```c++
// In Sandbox/src/main.cpp
// Enter the name of the app and window dimensions as arguments
std::unique_ptr<Application> Terroir::CreateApplication()
{
    TERR_APP_INFO("Your app created!"); // Optional application logging
    return std::make_unique<SandboxGame>("Your Terroir app", 1280, 720);
}
```

```c++
// In Sandbox/src/Sandbox2D.cpp
void Sandbox2D::OnUpdate(Timestep dt)
{
    TERR_PROFILE_FUNC;

    // Clear Screen to color
    RenderCommand::Clear(Color::BLACK);

    // Start draw calls
    Renderer2D::BeginScene(*m_Camera);

    // Rect dimensions
    constexpr const auto rectSize {100.0f};
    constexpr const auto rectPos {Vec3(0.0f, 0.0f, 1.0f)};

    // Draw calls (Vec2/3(pos)), Vec2(scale), Vec4(color))
    Renderer2D::DrawRect(rectPos, {rectSize, rectSize}, Color::GREEN);

    Renderer2D::EndScene();
}
```

### Pong

![Pong](/resources/pong.png)

```C++
// Check out Sandbox/src/pong/* for example!
```

## Getting Started

Building Requirements:

- C++20 capable compiler (built and tested on g++ (Unix) and MSVC (Windows))
- CMake (min version 3.0)
- Python 3

Terroir is a statically linked library that is linked at compile time with your chosen executable. Packages are handled
through Microsoft's [vcpkg](https://vcpkg.io/en/index.html); it has been added as a git submodule under .gitsubmodules.
All other dependencies are listed in vcpkg.json.

For both platforms, Terroir has been built and tested using CMake and Visual Studio Code. If you aren't familiar with
these tools, particularly CMake, I recommend learning the basics of these before attempting to fool around with the
engine.

Start by cloning the repo.

Cd into the directory and to build simply run:

Unix:
setup.sh

or for Windows:
setup.bat

It's highly recommended to build through your IDE of choice and allow CMake plugins create launch/compile configs based upon the root CMakeLists.txt.

To run the Sandbox app: <strong>SET CURRENT WORKING DIRECTORY TO ROOT OF PROJECT</strong>

## Planned Features

- Platform abstraction (windowing, sound, input, memory, etc.) ✅
- Logging and custom asserts ✅
- Integrated debugging tools
- 2D rendering ✅
- Text/Font rendering ✅
- UI management ✍️
- 2D physics
- ECS
- Math ✅

- Networking
- AI
- Scenes
- Scripting via LuaJIT
- Graphical Editor

### Current Vintage - (v0.1)

Terroir is currently capable of arcade style 2D games.  Look at Sandbox/src for examples.

| Feature                | Description                                               | Status |
| ---------------------- | --------------------------------------------------------- | ------ |
| Platform Abstraction   | Windowing, Sound, Input, Application, Asset Pipeline      | ✅️      |
| Basic Utilities        | Logging, Asserts, Profiling                               | ✅      |
| Event and Layer System | Events are passed into the engine and can be queried      | ✅      |
| 2D Renderer            | Put geometry and textures onto the screen via OpenGL      | ✅      |
| Fonts                  | TTF font support                                          | ✅      |
| Math                   | Linear algebra abstraction with types and transformations | ✅      |

## Road to the Next Vintage - (v0.2 - Batches)

Terroir is planned on receiving minor performance and optimization tweaks during this update as well as quality of life features like 2D Spritesheets!  
| Feature             | Description                                | Status |
| ------------------- | ------------------------------------------ | ------ |
| Spritesheet Support | Spritesheet support added to asset pipline | ⚙️      |
| 2D Batch Rendering  | Performance increases with the 2D renderer | ⚙️      |
| Concurrency Support | Scalability of integral systems            | ⚙️      |

## Out of scope (Not planned for version 1.0) 😭

- 3D rendering
- Mobile builds
- macOS builds

## License

Terroir is free and open source under [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).

I sincerely hope you enjoy working with the engine, all I ask is for credit or a shoutout in your project. :)
