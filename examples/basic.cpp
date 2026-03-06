#include "raylib.h"
#include "../cframe.hpp"

int main() {

    InitWindow(680, 400, "Basic Example");
    SetTargetFPS(60);

    std::vector<CF::Keyframe<Rectangle>> keyframes = {
        {
            .transform = {.x = 20},
            .type = CF::TransformType::OFFSET
        },
        {
            .transform = {.x = 1, .y = 1, .width = 3, .height = 3},
            .type = CF::TransformType::SCALE
        }
    };

    CF::Animation<Rectangle> rec({100, 100, 100, 100}, keyframes);

    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);
            DrawRectangleRec(rec.Next(), BLUE);
   
        EndDrawing();
    }

    return 0;
}