#include "raylib.h"
#include "../cframe.hpp"



/*
MAYBE the way forward is just a single T struct, and an enum that describes the transformation i.e. CF_TRANSFORM_TO, CF_TRANSFORM_ADD etc. Then the T types themselves don't need to be optional
BUT then I'd still need each T member to be optional... maybe that's where the boost pfr library comes in.
*/

/*

Rectangle rec = {1, 2, 3, 4};

CF::Animated<Rectangle> anim_rec(rec, keyframes)

if (mouse_clicked) {
    anim_rec.Play();
    anim_rec.playing = true; // I think I like this better -- more control to the user
}

DrawRectanlgeRec(anim_rec.Get(), BLUE); // Next(), Get(), Step(), Process(), etc..

vs
DrawRectangleRec(anim_rec.Process(rec), BLUE); // with this option, rec, doesn't need to get defined before anim_rec, it can do it to any rectangle. Is this truly helpful?

I think the first option, where an Animated<> object is instantiated by the OG object and its keyframes, is pretty straightforward and elegant
*/



int main() {

    sin(30);

    InitWindow(680, 400, "Basic Example");
    SetTargetFPS(60);

    std::vector<CF::Keyframe<Rectangle>> keyframes = {
        {
            .transform = {.x = 20},
            .type = CF::TransformType::OFFSET
        },
        {
            .transform = {.x = 1, .y = 1, .width = 3, .height = 3},
            .type = CF::TransformType::SCALE
        }
    };

    Rectangle rec = {100, 100, 100, 100};
    CF::Animation<Rectangle> moving_rectangle(rec, keyframes);

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);
            DrawRectangleRec(moving_rectangle.Next(), BLUE);
   
        EndDrawing();
    }

    return 0;
}