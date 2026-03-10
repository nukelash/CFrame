#include "raylib.h"

#define CFRAME_IMPLEMENTATION
#include "../cframe.hpp"

int main() {

    InitWindow(680, 400, "Basic Example");
    SetTargetFPS(60);

    std::vector<CF::Keyframe<Rectangle>> keyframes = {
        {
            .type = CF::TransformType::OFFSET,
            .transform = {280, 0, 0, 0},
        }
    };

    CF::Animation<Rectangle> rec({150, 150, 100, 100}, keyframes, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::CUBIC_IN_OUT);

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);
            DrawRectangleRec(rec.get(), BLUE);
   
        EndDrawing();
    }

    return 0;
}