# CFrame - A Header-Only, C99 Keyframing and Easing Library for RayLib

Easily animate raylib shapes, positions, and colors!

## Quick Start

Setup some keyframes:
```C
CF_RectangleKeyframe keyframes[3] = {
        CF_SetRectangleKeyframe({.Add.x=300, .Add.y=100, .EasingFrames=60, .HeldFrames=10}), 
        CF_SetRectangleKeyframe({.Add.y=150, .EasingFrames=60, .HeldFrames=10}),
        CF_SetRectangleKeyframe({.Mult.width=2.5, .EasingFrames=60, .HeldFrames=10})
    };
```

Attach keyframes to a context:
```C
CF_RectangleContext ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=3,
        .Mode=CF_PLAYMODE_ONCE
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

#
## API
The API is designed to be dead simple, with only 2 structs and 2 functions per keyframe-able struct:


### struct CF_*Keyframe;
### CF_Set*Keyframe();
### struct CF_*Context;
### CF_*Process();

#


Build:
```
cmake -DCMAKE_BUILD_TYPE=DEBUG -S . -B build
cmake --build build
```