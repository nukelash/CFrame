#include "stdio.h"

#include "raylib.h"
#include "ckey.h"

int main() {

    InitWindow(680, 400, "Example");
    SetTargetFPS(60);


    CF_RectangleKeyframe keyframes[3] = {
        CF_SetRectangleKeyframe({.Add.x=300, .Add.y=100, .EasingFrames=60, .HeldFrames=10}), 
        CF_SetRectangleKeyframe({.Add.y=150, .EasingFrames=60, .HeldFrames=10}),
        CF_SetRectangleKeyframe({.Mult.width=2.5, .EasingFrames=60, .HeldFrames=10})
    };

    CF_ColorKeyframe color_frames[2] = {
        CF_SetColorKeyframe({.Add.r=-255,
        .Add.g=255, 
        .EasingFrames=80}),
        CF_SetColorKeyframe({.Add.g=-255,
        .Add.b=255, 
        .EasingFrames=80})
    };
    TransformContext_Color ctx_color = {
        .Keyframes=color_frames,
        .NumKeyframes=2,
        .Mode=CF_PLAYMODE_LOOP
    };
    Color c = {255, 0, 0, 255};

    CF_RectangleContext ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=3,
        .Mode=CF_PLAYMODE_ONCE
    };

    CF_RectangleKeyframe alt_keyframes[2] = {
        CF_SetRectangleKeyframe({.Add.y=50, .EasingFrames=80}),
        CF_SetRectangleKeyframe({.Add.x=30, .EasingFrames=30})
    };

CF_RectangleContext alt_ctx_rec = {
        .Keyframes=alt_keyframes,
        .NumKeyframes=2,
        .Mode=CF_PLAYMODE_LOOP
    };

    Rectangle rec = {60, 60, 30, 30};

    while(!WindowShouldClose()) {

        if(IsKeyPressed(KEY_A)) {
            ctx_rec.Playing = !ctx_rec.Playing;
            alt_ctx_rec.Playing = !alt_ctx_rec.Playing;
            ctx_color.Playing = !ctx_color.Playing;
        }


        BeginDrawing();

            ClearBackground(GRAY);

            //Rectangle animated_rec = Animate_Rectangle(&alt_ctx_rec, Animate_Rectangle(&ctx_rec, rec));
            Rectangle animated_rec = CF_RectangleProcess(&ctx_rec, rec);
            DrawRectangleRec(animated_rec, CF_ColorProcess(&ctx_color, c));

            // printf("\nOG REC: %f, %f, %f, %f\n", __rec.x, __rec.y, __rec.width, __rec.height);
            // printf("ANI REC: %f, %f, %f, %f\n", animated_rec.x, animated_rec.y, animated_rec.width, animated_rec.height);
        
        EndDrawing();
    }

    return 0;
}