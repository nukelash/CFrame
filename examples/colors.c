#include "raylib.h"
#include "../cframe.h"

CF_DEFINE_4(Rectangle, float, x, y, width, height);

int main() {

    InitWindow(680, 400, "Color Animation");
    SetTargetFPS(60);


    CF_RectangleKeyframe rec_keyframes[3] = {
        CF_InitRectangleKeyframe((CF_RectangleKeyframe){
            .Add.x=200, 
            .EasingFrames=60, 
            .HeldFrames=10}), 
        CF_InitRectangleKeyframe((CF_RectangleKeyframe){
            .Add.x=-100, 
            .Add.y=-200, 
            .EasingFrames=60, 
            .HeldFrames=10}),
        CF_InitRectangleKeyframe((CF_RectangleKeyframe){
            .Add.x=-100, 
            .Add.y=200, 
            .EasingFrames=60, 
            .HeldFrames=10})
    };

    CF_ColorKeyframe color_keyframes[3] = {
        CF_InitColorKeyframe((CF_ColorKeyframe){
            .Add.r=-255,
            .Add.g=255, 
            .EasingFrames=60,
            .HeldFrames=10}),
        CF_InitColorKeyframe((CF_ColorKeyframe){
            .Add.g=-255,
            .Add.b=255, 
            .EasingFrames=60,
            .HeldFrames=10}),
        CF_InitColorKeyframe((CF_ColorKeyframe){
            .Add.r=255,
            .Add.b=-255,
            .EasingFrames=60,
            .HeldFrames=10})
    };

    CF_Vector2Keyframe v2_keyframes[1] = {
        CF_InitVector2Keyframe((CF_Vector2Keyframe){
            .Add.x=1,
            .EasingFrames=120
        })
    };

    CF_Vector2Context v2_ctx = {
        .Keyframes = v2_keyframes,
        .NumKeyframes = 1,
        .Mode=CF_PLAYMODE_BOOMERANG_LOOP,
        .Playing=true
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
    Vector2 roundness = {0, 0};

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            float r = CF_Vector2Process(&v2_ctx, roundness).x;

            DrawRectangleRounded(CF_RectangleProcess(&ctx_rec, rec), r, 8, CF_ColorProcess(&ctx_color, c));
   
        EndDrawing();
    }

    return 0;
}