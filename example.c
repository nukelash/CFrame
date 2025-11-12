#include "stdio.h"

#include "raylib.h"
#include "ckey.h"

int main() {

    InitWindow(680, 400, "Example");
    SetTargetFPS(60);


    Keyframe_Rectangle keyframes[3] = {
        NEW_KEYFRAME_Rectangle({.Add.x=300, .Add.y=100, .EasingFrames=60, .HeldFrames=10}), 
        NEW_KEYFRAME_Rectangle({.Add.y=150, .EasingFrames=60, .HeldFrames=10}),
        NEW_KEYFRAME_Rectangle({.Mult.width=2.5, .EasingFrames=60, .HeldFrames=10})
    };

    Keyframe_Color color_frames[2] = {
        NEW_KEYFRAME_Color({.Add.r=-255,
        .Add.g=255, 
        .EasingFrames=80}),
        NEW_KEYFRAME_Color({.Add.g=-255,
        .Add.b=255, 
        .EasingFrames=80})
    };
    TransformContext_Color ctx_color = {
        .Keyframes=color_frames,
        .NumKeyframes=2,
        .Mode=PLAYMODE_LOOP
    };
    Color c = {255, 0, 0, 255};

    TransformContext_Rectangle ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=3,
        .Mode=PLAYMODE_PLAY_ONCE
    };

    Keyframe_Rectangle alt_keyframes[2] = {
        (Keyframe_Rectangle) {.Add.y=50, .EasingFrames=80},
        (Keyframe_Rectangle) {.Add.x=30, .EasingFrames=30}
    };

    TransformContext_Rectangle alt_ctx_rec = {
        .Keyframes=alt_keyframes,
        .NumKeyframes=2,
        .Mode=PLAYMODE_LOOP
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
            Rectangle animated_rec = Animate_Rectangle(&ctx_rec, rec);
            DrawRectangleRec(animated_rec, Animate_Color(&ctx_color, c));

            // printf("\nOG REC: %f, %f, %f, %f\n", __rec.x, __rec.y, __rec.width, __rec.height);
            // printf("ANI REC: %f, %f, %f, %f\n", animated_rec.x, animated_rec.y, animated_rec.width, animated_rec.height);
        
        EndDrawing();
    }

    return 0;
}