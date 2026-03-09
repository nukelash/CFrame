#include "raylib.h"
#include "../cframe.hpp"

int num_buttons = 5;

int main() {

    InitWindow(530, 250, "Hover");
    SetTargetFPS(60);

    Rectangle buttons[num_buttons];

    CF::Keyframe<Rectangle> hover_keyframe = {
        CF::TransformType::OFFSET,
        {-4, -4, 8, 8},
        5,
        0
    };
    
    CF::Animation<Rectangle> ctx[num_buttons];

    for (int i = 0; i < num_buttons; i++) {
        buttons[i] = (Rectangle) {100.0f + (70.0f*i), 80, 50, 50};
        ctx[i].init(buttons[i], {hover_keyframe}, CF::PlayMode::ONCE, CF::EasingFunction::LINEAR);
    }

    while(!WindowShouldClose()) {

        Vector2 mouse_position = GetMousePosition();
        for (int i = 0; i < num_buttons; i++) {
            if (!CheckCollisionPointRec(mouse_position, buttons[i])) {
                ctx[i]._reverse = true;
            }
            else {
                ctx[i]._reverse = false;
            }
        }

        BeginDrawing();

            ClearBackground(GRAY);

            for (int i = 0; i < num_buttons; i++) {
                DrawRectangleRec(ctx[i].get(), BLACK);
            }
        
        EndDrawing();
    }

    return 0;
}