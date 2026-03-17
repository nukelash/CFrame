#include "raylib.h"

#define CFRAME_IMPLEMENTATION
#include "../cframe.hpp"

#include <vector>

int main() {

    InitWindow(680, 400, "Color Animation");
    SetTargetFPS(60);

    std::vector<CF::Keyframe<Rectangle>> rectangle_keyframes {
        {
            .type = CF::TransformType::OFFSET,
            .transform = {200, 0, 0, 0},
            .easing_frames = 60,
            .held_frames = 0
        },
        {
            .type = CF::TransformType::OFFSET,
            .transform = {-100, -200, 0, 0},
            .easing_frames = 60,
            .held_frames = 0
        },
        {
            .type = CF::TransformType::OFFSET,
            .transform = {-100, 200, 0, 0},
            .easing_frames = 60,
            .held_frames = 0
        }
    };

    std::vector<CF::Keyframe<Color>> color_keyframes = {
        {
            .type = CF::TransformType::TO,
            .transform = {0, 255, 0, 255},
            .easing_frames = 60,
            .held_frames = 0
            
        },
        {
            .type = CF::TransformType::TO,
            .transform = {0, 0, 255, 255},
            .easing_frames = 60,
            .held_frames = 0
            
        },
        {
            .type = CF::TransformType::TO,
            .transform = {255, 0, 0, 255},
            .easing_frames = 60,
            .held_frames = 0
            
        }
    };

    std::vector<CF::Keyframe<float>> roundness_keyframes = {
        {
            .type = CF::TransformType::OFFSET,
            .transform = {1.0f},
            .easing_frames = 60,
            .held_frames = 0
        },
        {
            .type = CF::TransformType::OFFSET,
            .transform = {-1.0},
            .easing_frames = 60,
            .held_frames = 0
        }
    };

    CF::Animation<float> roundness = {0.0f, roundness_keyframes, CF::PlayMode::LOOP, CF::EasingFunction::CUBIC_OUT};

    CF::Animation<Rectangle> rectangle = {{200, 250, 60, 60}, rectangle_keyframes, CF::PlayMode::LOOP, CF::EasingFunction::CUBIC_OUT};

    CF::Animation<Color> color = {{255, 0, 0, 255}, color_keyframes, CF::PlayMode::LOOP, CF::EasingFunction::CUBIC_OUT};

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawRectangleRounded(rectangle.get(), roundness.get(), 8, color.get());
   
        EndDrawing();
    }

    return 0;
}