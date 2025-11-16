# CFrame - Streamlined Keyframing and Easing in C

**CFrame** makes it a ***breeze*** to implement beautiful animations in your C/C++ UI/GUI application.

### **Major Features**
- Header only, C99 library with no dependencies
- Dead-simple API with only **2 structs, 2 functions, and 1 macro**
- Implement keyframing and easing on almost ***any*** data structure
- Flexible keyframing options
- Built in easing functions such as Quadratic, Sine, and more

<p align="center"> 
<img src=ac5xme.gif />
</p>


## Basic Example
The following example uses CFrame to animate a Rectangle in raylib.
```C
#include "raylib.h"
#include "../cframe.h"

// Tell CFrame you want to animate a struct called "Rectangle," which has 4 floats named x, y, width, and height
CF_DEFINE_4(Rectangle, float, x, y, width, height);

int main() {

    InitWindow(680, 400, "Basic Example");
    SetTargetFPS(60);

    // Initialize one (or more) keyframes
    CF_RectangleKeyframe keyframes[1] = {
        CF_InitRectangleKeyframe((CF_RectangleKeyframe) {
            .Add.x=200, 
            .EasingFrames=60
            }), 
    };

    // Attach the keyframes to a context
    CF_RectangleContext ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=1,
        .Mode=CF_PLAYMODE_BOOMERANG_LOOP,
        .Playing=true
    };

    Rectangle rec = {200, 150, 60, 60};

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            //Process
            DrawRectangleRec(CF_RectangleProcess(&ctx_rec, rec), BLUE);
   
        EndDrawing();
    }

    return 0;
}
```
The above example will produce the following. You can check `basic.c` and other examples out in the `examples` folder.

# **API**

## macro **CF_DEFINE_#(** *\<name>*, *subtype*, *members...* **)**

You must call this first for each struct you'd like to keyframe. This generates the other functions and structures in the API to be used with \<name>.

**#**
> Number of members in the data structure 

**\<name>**
>Name of the data structure 

**subtype**
>types contained in the data structure

**members**
> the members of the data structure

Ex:

```
CF_DEFINE_4(Rectangle, float, x, y, width, height);
```

#

## func CF_\<name>Keyframe **CF_Init**\<name>**Keyframe(** CF_\<name>Keyframe *keyframe* **)**

Call this to initializa a keyframe. This fills all fields with appropriate defaults, and should be used when creating keyframes.

**keyframe**
> Input keyframe

Ex:

```C
CF_RectangleKeyframe kf = CF_InitRectangleKeyframe((CF_RectangleKeyframe) {.Add.x = 10, .EasingFrames = 120});
```

## struct **CF_**\<name>**Keyframe {** CF__\<name>f *Add*; CF__\<name>f *Mult*; int *EasingFrames*; int *HeldFrames*; **}**

Structure that holds details about how to mutate \<name>.

**Add**
> Offset the members of \<name>

**Mult**
> Scale the members of \<name>

**EasingFrames**
> The number of frames it takes to transition to this keyframe

**HeldFrames**
> The number of frames this keyframe is held before starting to transition to the next one

Ex:
```C
CF_RectangleKeyframe keyframe = {
    .Add.x = 100,
    .Mult.width = 1.2,
    .EasingFrames = 50,
    .HeldFrames = 20
};
```

## struct **CF_**\<name>**Context {**  CF_\<name>Keyframe *Keyframes*, int *NumKeyframes*, int *Index*, bool *Playing*, CF_PlayMode *Mode*, bool *__Reverse*, int *__KeyframeIndex*, bool *__Held* **}**

| Type | Name | Description | Members/Arguments |
| ------ | ---- | ------| -----|
| macro | CF_DEFINE_#(\<name>, subtype, members...) | You must call this first for each struct you'd like to keyframe. This generates the appropriate functions and structure. | **#**: number of members in the data structure <br> **\<name>**: name of the data structure<br> **subtype**: types contained in the data structure<br> **members**: the members of the data structure |
| struct | CF_\<name>Keyframe | Represents a fram|
| struct | CF_\<name>Context | asdf |
| func | CF_Init\<name>Keyframe() | asdf |
| func | CF_\<name>Process(<br>CF_\<name>Context\* ctx,<br>\* input) | Process the data structure <br><br> **


## Quick Start

Define your data structure to be keyframed:
```
CF_DEFINE_4(Rectangle, float, x, y, width, height);
```

Set up some keyframes:
```C
CF_RectangleKeyframe keyframes[1] = {
    CF_InitRectangleKeyframe((CF_RectangleKeyframe) {
            .Add.x=300, 
            .Add.y=100, 
            .EasingFrames=60
    })
};
```

Attach keyframes to a context:
```C
CF_RectangleContext ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=1,
        .Mode=CF_PLAYMODE_BOOMERANG_LOOP
    };
```

Process your initial shape through CFrame
```C
Rectangle rec = {30, 30, 100, 100};

BeginDrawing();

    ClearBackground(GRAY);

    DrawRectangleRec(CF_RectangleProcess(rec), BLUE);

EndDrawing();
```



## Building the Examples
The examples are built with CMake and depend on raylib:
```
cmake -DCMAKE_BUILD_TYPE=DEBUG -S . -B build
cmake --build build
```