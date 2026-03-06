#include "raylib.h"
#include "../cframe.hpp"

#include <vector>

// CF_DEFINE_4(Rectangle, float, x, y, width, height);
// CF_DEFINE_4(Color, unsigned char, r, g, b, a);
// CF_DEFINE_2(Vector2, float, x, y);

struct myfloat {
    float f;
};

int main() {

    InitWindow(680, 400, "Color Animation");
    SetTargetFPS(60);


    // CF_RectangleKeyframe rec_keyframes[3] = {
    //     CF_InitRectangleKeyframe((CF_RectangleKeyframe){
    //         .Add.x=200, 
    //         .EasingFrames=60, 
    //         .HeldFrames=10}), 
    //     CF_InitRectangleKeyframe((CF_RectangleKeyframe){
    //         .Add.x=-100, 
    //         .Add.y=-200, 
    //         .EasingFrames=60, 
    //         .HeldFrames=10}),
    //     CF_InitRectangleKeyframe((CF_RectangleKeyframe){
    //         .Add.x=-100, 
    //         .Add.y=200, 
    //         .EasingFrames=60, 
    //         .HeldFrames=10})
    // };

    std::vector<CF::Keyframe<Rectangle>> rectangle_keyframes {
        {
            .transform = {.x = 200},
            .type = CF::TransformType::OFFSET,
            .easing_frames = 60,
            .held_frames = 10
        },
        {
            .transform = {.x = -100, .y = -200},
            .type = CF::TransformType::OFFSET,
            .easing_frames = 60,
            .held_frames = 10
        },
        {
            .transform = {.x = -100, .y = 200},
            .type = CF::TransformType::OFFSET,
            .easing_frames = 60,
            .held_frames = 10
        }
    };

    // CF_ColorKeyframe color_keyframes[3] = {
    //     CF_InitColorKeyframe((CF_ColorKeyframe){
    //         .Add.r=-255,
    //         .Add.g=255, 
    //         .EasingFrames=60,
    //         .HeldFrames=10}),
    //     CF_InitColorKeyframe((CF_ColorKeyframe){
    //         .Add.g=-255,
    //         .Add.b=255, 
    //         .EasingFrames=60,
    //         .HeldFrames=10}),
    //     CF_InitColorKeyframe((CF_ColorKeyframe){
    //         .Add.r=255,
    //         .Add.b=-255,
    //         .EasingFrames=60,
    //         .HeldFrames=10})
    // };

    std::vector<CF::Keyframe<Color>> color_keyframes = {
        {
            .transform = {.r = 15, .g = 255},
            .type = CF::TransformType::OFFSET
        },
        {
            .transform = {.r = 15, .g = 255},
            .type = CF::TransformType::OFFSET
        }
    };

    // CF_Vector2Keyframe v2_keyframes[1] = {
    //     CF_InitVector2Keyframe((CF_Vector2Keyframe){
    //         .Add.x=1,
    //         .EasingFrames=120
    //     })
    // };

    std::vector<CF::Keyframe<float>> roundness_keyframes = {
        {
            .transform = 1.0f,
            .type = CF::TransformType::OFFSET,
            .easing_frames = 120
        }
    };

    // CF_Vector2Context v2_ctx = {
    //     .Keyframes = v2_keyframes,
    //     .NumKeyframes = 1,
    //     .Mode=CF_PLAYMODE_BOOMERANG_LOOP,
    //     .Playing=true
    // };

    CF::Animation<float> roundness = {0.0f, roundness_keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::QUADRATIC_IN_OUT};

    // CF_RectangleContext ctx_rec = {
    //     .Keyframes=rec_keyframes,
    //     .NumKeyframes=3,
    //     .Mode=CF_PLAYMODE_LOOP,
    //     .Playing=true,
    //     .EasingFunction=CF_EASING_QUADRATIC_IN_OUT
    // };

    CF::Animation<Rectangle> rectangle = {{200, 250, 60, 60}, rectangle_keyframes, CF::PlayMode::LOOP, CF::EasingFunction::QUADRATIC_IN_OUT};

    // CF_ColorContext ctx_color = {
    //     .Keyframes=color_keyframes,
    //     .NumKeyframes=3,
    //     .Mode=CF_PLAYMODE_BOOMERANG_LOOP,
    //     .Playing=true,
    //     .EasingFunction=CF_EASING_CUBIC_IN_OUT
    // };

    CF::Animation<Color> color = {{255, 0, 0, 255}, color_keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::CUBIC_IN_OUT};

    // Rectangle rec = {200, 250, 60, 60};
    // Color c = {255, 0, 0, 255};
    // Vector2 roundness = {0, 0};

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            // float r = CF_Vector2Process(&v2_ctx, roundness).x;

            // DrawRectangleRounded(CF_RectangleProcess(&ctx_rec, rec), r, 8, CF_ColorProcess(&ctx_color, c));

            DrawRectangleRounded(rectangle.Next(), roundness.Next(), 8, color.Next());
   
        EndDrawing();
    }

    return 0;
}