#include "stdio.h"

#include "raylib.h"
#include "ckey.h"

int main() {

    temp_func();

    InitWindow(680, 400, "Example");
    SetTargetFPS(60);


    Keyframe_Rectangle keyframes[3] = {
        (Keyframe_Rectangle){.Add.x=300, .Add.y=100, .EasingFrames=60, .HeldFrames=10}, 
        (Keyframe_Rectangle){.Add.y=150, .EasingFrames=60, .HeldFrames=10},
        (Keyframe_Rectangle){.Add.x=100, .EasingFrames=60, .HeldFrames=10}
    };

    TransformContext_Rectangle ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=3,
        .Mode=PLAYMODE_BOOMERANG
    };

    Keyframe_Rectangle alt_keyframes[2] = {
        (Keyframe_Rectangle) {.Add.y=50, .EasingFrames=80},
        (Keyframe_Rectangle) {.Add.x=30, .EasingFrames=30}
    };

    TransformContext_Rectangle alt_ctx_rec = {
        .Keyframes=alt_keyframes,
        .NumKeyframes=2,
        .Mode=PLAYMODE_BOOMERANG
    };

    printf("playing: %d\n", ctx_rec.Playing);

    Rectangle rec = {60, 60, 30, 30};

    while(!WindowShouldClose()) {

        if(IsKeyPressed(KEY_A)) {
            ctx_rec.Playing = !ctx_rec.Playing;
            alt_ctx_rec.Playing = !alt_ctx_rec.Playing;
        }


        BeginDrawing();

            ClearBackground(RED);

            Rectangle animated_rec = Animate_Rectangle(&alt_ctx_rec, Animate_Rectangle(&ctx_rec, rec));
            DrawRectangleRec(animated_rec, WHITE);

            // printf("\nOG REC: %f, %f, %f, %f\n", __rec.x, __rec.y, __rec.width, __rec.height);
            // printf("ANI REC: %f, %f, %f, %f\n", animated_rec.x, animated_rec.y, animated_rec.width, animated_rec.height);
        
        EndDrawing();
    }

    return 0;
}