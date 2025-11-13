#include "raylib.h"
#include "../cframe.h"

int main() {

    InitWindow(680, 400, "Color Animation");
    SetTargetFPS(60);


    CF_RectangleKeyframe rec_keyframes[3] = {
        CF_SetRectangleKeyframe({
            .Add.x=200, 
            .EasingFrames=60, 
            .HeldFrames=10}), 
        CF_SetRectangleKeyframe({
            .Add.x=-100, 
            .Add.y=-200, 
            .EasingFrames=60, 
            .HeldFrames=10}),
        CF_SetRectangleKeyframe({
            .Add.x=-100, 
            .Add.y=200, 
            .EasingFrames=60, 
            .HeldFrames=10})
    };

    CF_ColorKeyframe color_keyframes[3] = {
        CF_SetColorKeyframe({
            .Add.r=-255,
            .Add.g=255, 
            .EasingFrames=60,
            .HeldFrames=10}),
        CF_SetColorKeyframe({
            .Add.g=-255,
            .Add.b=255, 
            .EasingFrames=60,
            .HeldFrames=10}),
        CF_SetColorKeyframe({
            .Add.r=255,
            .Add.b=-255,
            .EasingFrames=60,
            .HeldFrames=10})
    };

    CF_RectangleContext ctx_rec = {
        .Keyframes=rec_keyframes,
        .NumKeyframes=3,
        .Mode=CF_PLAYMODE_LOOP,
        .Playing=true
    };

    CF_ColorContext ctx_color = {
        .Keyframes=color_keyframes,
        .NumKeyframes=3,
        .Mode=CF_PLAYMODE_BOOMERANG_LOOP,
        .Playing=true
    };

    Rectangle rec = {200, 250, 60, 60};
    Color c = {255, 0, 0, 255};

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawRectangleRounded(CF_RectangleProcess(&ctx_rec, rec), 0.4, 8, CF_ColorProcess(&ctx_color, c));
   
        EndDrawing();
    }

    return 0;
}