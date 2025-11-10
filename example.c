#include "stdio.h"

#include "raylib.h"
#include "ckey.h"

int main() {

    temp_func();

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

    Keyframe_Rectangle __frames[2] = {
        (Keyframe_Rectangle){.Add.x=100, .EasingFrames=50}, 
        (Keyframe_Rectangle){.Add.y=150, .EasingFrames=20, .HeldFrames=60}
    };
    
    TransformContext_Rectangle ctx_rec = {.Keyframes=__frames, .NumKeyframes=2};

    Rectangle __rec = {60, 60, 30, 30};

    while(!WindowShouldClose()) {

        if(IsKeyPressed(KEY_A)) {
            ctx.Playing = !ctx.Playing;
            ctx_rec.Playing = !ctx_rec.Playing;
        }
        if(IsKeyPressed(KEY_S)) {
            dim_ctx.Playing = !dim_ctx.Playing;
        }
        //printf("Playing: %d\n", ctx.Playing);

        BeginDrawing();

            ClearBackground(RED);

            // Vector2 new_position = Transform_Vector2(&ctx, position);
            // Vector2 new_dims = Transform_Vector2(&dim_ctx,dimensions);
            // DrawRectangle(new_position.x, new_position.y, new_dims.x, new_dims.y, BLACK);

            Rectangle animated_rec = Animate_Rectangle(&ctx_rec, __rec);
            DrawRectangleRec(animated_rec, WHITE);

            // printf("\nOG REC: %f, %f, %f, %f\n", __rec.x, __rec.y, __rec.width, __rec.height);
            // printf("ANI REC: %f, %f, %f, %f\n", animated_rec.x, animated_rec.y, animated_rec.width, animated_rec.height);
        
        EndDrawing();
    }

    return 0;
}