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
            .type = CF::TransformType::OFFSET,
            .transform = {200, 0, 0, 0},
            .easing_frames = 60,
            .held_frames = 10
        },
        {
            .type = CF::TransformType::OFFSET,
            .transform = {-100, -200, 0, 0},
            .easing_frames = 60,
            .held_frames = 10
        },
        {
            .type = CF::TransformType::OFFSET,
            .transform = {-100, 200, 0, 0},
            .easing_frames = 60,
            .held_frames = 10
        }
    };

    std::vector<CF::Keyframe<Color>> color_keyframes = {
        {
            .type = CF::TransformType::OFFSET,
            .transform = {-255, 255, 0, 0},
            
        },
        {
            .type = CF::TransformType::OFFSET,
            .transform = {0, -255, 255, 0},
            
        },
        {
            .type = CF::TransformType::OFFSET,
            .transform = {255, 0, -255, 0},
            
        }
    };

    std::vector<CF::Keyframe<float>> roundness_keyframes = {
        {
            .type = CF::TransformType::OFFSET,
            .transform = {1.0f},
            .easing_frames = 120
        }
    };

    CF::Animation<float> roundness = {0.0f, roundness_keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::QUADRATIC_IN_OUT};

    CF::Animation<Rectangle> rectangle = {{200, 250, 60, 60}, rectangle_keyframes, CF::PlayMode::LOOP, CF::EasingFunction::QUADRATIC_IN_OUT};

    CF::Animation<Color> color = {{255, 0, 0, 255}, color_keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::CUBIC_IN_OUT};

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawRectangleRounded(rectangle.get(), roundness.get(), 8, color.get());
   
        EndDrawing();
    }

    return 0;
}