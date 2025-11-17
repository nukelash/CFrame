# CFrame - Streamlined Keyframing and Easing in C

**CFrame** makes it a ***breeze*** to implement beautiful animations in your C/C++ UI/GUI application.

### **Major Features**
- Header only, C99 library with no dependencies
- Dead-simple API with only **2 structs, 2 functions, and 1 macro**
- Implement keyframing and easing on almost ***any*** struct
- Flexible keyframing options
- Built in easing functions such as Quadratic, Sine, and more

<p align="center"> 
<img src=hover.gif />
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
            })
    };

    // Attach the keyframes to a context
    CF_RectangleContext ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=1,
        .Mode=CF_PLAYMODE_BOOMERANG_LOOP,
        .Playing=true,
        .EasingFunction=CF_EASING_QUADRATIC_IN_OUT
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

<p align="center"> 
<img src=basic.gif />
</p>

# **API**

## macro **CF_DEFINE_#(** *\<name>*, *subtype*, *members...* **)**

You must call this first for each struct you'd like to keyframe. This generates the other functions and structures in the API to be used with \<name>.

> **Note:** \<name> must be a struct where all members are the same type. Currently, CFrame only allows a max of 4 members in each struct.

| Argument | Description |
| -------- | ----------- |
| # | Number of members in the data structure |
| \<name> | Name of the data structure |
| subtype | The type contained in \<name> |
|members | The names of the members of \<name>


Ex:

```
CF_DEFINE_4(Rectangle, float, x, y, width, height);
```

#

## func CF_\<name>Keyframe **CF_Init**\<name>**Keyframe(** CF_\<name>Keyframe *keyframe* **)**

Call this to initializa a keyframe. This fills all fields with appropriate defaults, and should be used when creating keyframes.

| Argument | Type | Description |
| -------- | ---- | ----------- |
| keyframe | CF_\<name>Keyframe| The keyframe struct to initialize | 

Ex:

```C
CF_RectangleKeyframe kf = CF_InitRectangleKeyframe((CF_RectangleKeyframe) {.Add.x = 10, .EasingFrames = 120});
```
#

## struct **CF_**\<name>**Keyframe {** CF__\<name>f *Add*; CF__\<name>f *Mult*; int *EasingFrames*; int *HeldFrames*; **}**

Structure that holds details about how to mutate \<name>.

| Member | Type | Description |
| ------ | ---- | ----------- |
| Add | CF_\<name>Keyframe | The offset amount of each the members of \<name> |
| Mult | CF_\<name>Keyframe | The scale amount of each the members of \<name> |
| EasingFrames| int | The number of frames it takes to transition to this keyframe |
| HeldFrames | int | The number of frames this keyframe is held before starting to transition to the next one |

Ex:
```C
CF_RectangleKeyframe keyframe = {
    .Add.x = 100,
    .Mult.width = 1.2,
    .EasingFrames = 50,
    .HeldFrames = 20
};
```
#
## struct **CF_**\<name>**Context {**  CF_\<name>Keyframe *Keyframes*, int *NumKeyframes*, int *Index*, bool *Playing*, CF_PlayMode *Mode*, bool *__Reverse*, int *__KeyframeIndex*, bool *__Held* **}**

Structure that holds internal details about how each instance of \<name> is being keyframed. Typically, one CF_\<name>Context is needed for each \<name>.

| Member | Type | Description |
| ------ | ---- | ----------- |
| Keyframes | CF_\<name>Keyframe* | A pointer to an array of keyframes |
| NumKeyframes | int | The number of keyframes in `Keyframes` |
| Index | int | The index of the context. This is incremented automatically by CF_\<name>Process() if `Playing` is true. |
| Playing | bool | Whether the index is incrementing or not |
| Mode | CF_PlayMode | The play behaviour of the context. See playmodes.c in `\examples` for a demonstration. |
| EasingFunction | CF_EasingFunction | The easing function to use. |
| __Reverse | bool | Whether `Index` is incrementing in reverse or not. |
| __KeyframeIndex | int | *(read only)* Which keyframe in `Keyframes` the `Index` is currently at |
| __Modification | CF_\<name>Modifier | *(read only)* The modification to be made during CF_\<name>Process() |
Ex:
```C
CF_RectangleKeyframe keyframe = CF_InitRectangleKeyframe((CF_RectangleKeyframe) {
    .Add.x = 100,
    .Mult.width = 1.2,
    .EasingFrames = 50,
    .HeldFrames = 20
});

CF_RectangleContext ctx_rec = {
        .Keyframes=keyframe,
        .NumKeyframes=1,
        .Mode=CF_PLAYMODE_LOOP,
        .Playing=true,
        .EasingFunction=CF_EASING_QUADRATIC_IN_OUT
    };
```
#
## func \<name> **CF_\<name>Process(** CF_\<name>Context *ctx*, \<name> *input* **)**
Process the input data structure.

| Argument | Type | Description |
| -------- | ---- | ----------- |
| ctx | CF_\<name>Context | The context associated with `input` |
| input | \<name> | The input data structure to be keyframed |

Ex. 
```C
Rectangle keyframed_rec = CF_RectangleProcess(&ctx_rec, rec);
```
#


## Building the Examples
The examples are built with CMake and depend on raylib:
```
cmake -DCMAKE_BUILD_TYPE=DEBUG -S . -B build
cmake --build build
```