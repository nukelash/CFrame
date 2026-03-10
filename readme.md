# CFrame - Streamlined Keyframing and Easing for C++

**CFrame** makes it a ***breeze*** to implement beautiful animations in your C++ UI/GUI application.

<i>Note: CFrame is now a C++20 library, rather than C99. This was done to take advantage of templates, making the library much more intuitive, expressive, and maintainable.</i>

### **Major Features**
- Header only, C++20 library with no dependencies
- Dead-simple API with only **2 structs:** Keyframe and Animation
- Implement keyframing and easing on almost ***any*** struct
- Flexible keyframing options
- Built in easing functions such as Quadratic, Sine, and more

<p align="center"> 
<img src=assets/hover.gif /> 
<img src=assets/colors.gif />
</p>

## Including in your project
Simply include `cframe.hpp` and define `CFRAME_IMPLEMENTATION` once somewhere in your project.

## Basic Example
The following is basic.cpp in the `examples` folder. It uses CFrame to animate a Rectangle in raylib.
```C++
#include "raylib.h"

#define CFRAME_IMPLEMENTATION
#include "../cframe.hpp"

int main() {

    InitWindow(680, 400, "Basic Example");
    SetTargetFPS(60);

    // Create one (or more) keyframe
    std::vector<CF::Keyframe<Rectangle>> keyframes = {
        {
            .type = CF::TransformType::OFFSET,
            .transform = {280, 0, 0, 0}, // This will add 280 to Rectangle::x
        }
    };

    // Create an animation
    CF::Animation<Rectangle> rec({150, 150, 100, 100}, keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::CUBIC_IN_OUT);

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);
            // Use .get() to step the animation and return the animated struct
            DrawRectangleRec(rec.get(), BLUE);
   
        EndDrawing();
    }

    return 0;
}
```
The above example will produce the following.

<p align="center"> 
<img src=assets/basic.gif />
</p>

## Building the Examples
The examples are built with CMake and depend on raylib. They've been tested only on MacOS:
```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=DEBUG -S . -B build
cmake --build build
```
