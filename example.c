#include "stdio.h"

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "ckey.h"

int main() {

    InitWindow(680, 400, "Example");
    SetTargetFPS(60);

    Keyframe frames[1] = {
        // InitKeyframe((Keyframe){.AOffset = 3, .BScale = 1.2f, .EasingFrames=60, .HeldFrames=60}),
        // InitKeyframe((Keyframe){.AScale = 0.8, .EasingFrames=60, .HeldFrames=60}),
        KEYFRAME({.BOffset = 70, .EasingFrames=20, .HeldFrames=60})
        };
    
    for(int i = 0; i < 3; i++) {
        printf("%f, %f, %f, %f\n", frames[i].AOffset, frames[i].BOffset, frames[i].AScale, frames[i].BScale);
    }

    TransformContext ctx = {.Keyframes = frames, .NumKeyframes=1};

    Vector2 position = {30,30};
    Vector2 dimensions = {100,100};

    while(!WindowShouldClose()) {

        if(IsKeyPressed(KEY_A)) {
            ctx.Playing = !ctx.Playing;
        }
        //printf("Playing: %d\n", ctx.Playing);

        BeginDrawing();

            ClearBackground(RED);

            Vector2 new_position = Transform_Vector2(&ctx, position);
            DrawRectangle(new_position.x, new_position.y, dimensions.x, dimensions.y, BLACK);
        
        EndDrawing();
    }

    return 0;
}