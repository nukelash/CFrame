#include "raylib.h"
#include "../cframe.hpp"

#include <vector>

struct myfloat {
    float f;
};

int main() {

    InitWindow(680, 400, "Color Animation");
    SetTargetFPS(60);

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

    std::vector<CF::Keyframe<float>> roundness_keyframes = {
        {
            .transform = 1.0f,
            .type = CF::TransformType::OFFSET,
            .easing_frames = 120
        }
    };

    CF::Animation<float> roundness = {0.0f, roundness_keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::QUADRATIC_IN_OUT};

    CF::Animation<Rectangle> rectangle = {{200, 250, 60, 60}, rectangle_keyframes, CF::PlayMode::LOOP, CF::EasingFunction::QUADRATIC_IN_OUT};

    CF::Animation<Color> color = {{255, 0, 0, 255}, color_keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::CUBIC_IN_OUT};

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawRectangleRounded(rectangle.Next(), roundness.Next(), 8, color.Next());
   
        EndDrawing();
    }

    return 0;
}