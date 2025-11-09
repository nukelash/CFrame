#include "stdio.h"

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "ckey.h"

int main() {

    InitWindow(680, 400, "Example");
    SetTargetFPS(60);

    Keyframe frames[2] = {
        // InitKeyframe((Keyframe){.AOffset = 3, .BScale = 1.2f, .EasingFrames=60, .HeldFrames=60}),
        InitKeyframe((Keyframe){.AScale = 2, .EasingFrames=20, .HeldFrames=60}),
        KEYFRAME({.AScale = 1.5, .BOffset = 70, .EasingFrames=20, .HeldFrames=60})
        };
    
    for(int i = 0; i < 3; i++) {
        printf("%f, %f, %f, %f\n", frames[i].AOffset, frames[i].BOffset, frames[i].AScale, frames[i].BScale);
    }

    TransformContext ctx = {.Keyframes = frames, .NumKeyframes=2};

    Keyframe dim_frames[1] = {KEYFRAME({.BScale=3, .EasingFrames=30, .HeldFrames=60})};
    TransformContext dim_ctx = {.Keyframes = dim_frames, .NumKeyframes=1};

    Vector2 position = {30,30};
    Vector2 dimensions = {100,100};

    while(!WindowShouldClose()) {

        if(IsKeyPressed(KEY_A)) {
            ctx.Playing = !ctx.Playing;
        }
        if(IsKeyPressed(KEY_S)) {
            dim_ctx.Playing = !dim_ctx.Playing;
        }
        //printf("Playing: %d\n", ctx.Playing);

        BeginDrawing();

            ClearBackground(RED);

            Vector2 new_position = Transform_Vector2(&ctx, position);
            Vector2 new_dims = Transform_Vector2(&dim_ctx,dimensions);
            DrawRectangle(new_position.x, new_position.y, new_dims.x, new_dims.y, BLACK);
        
        EndDrawing();
    }

    return 0;
}