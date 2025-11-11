#include "raylib.h"
#include "ckey.h"
#include "stdio.h"

int num_buttons = 5;

int main() {

    InitWindow(680, 400, "Hover");
    SetTargetFPS(60);

    Rectangle buttons[num_buttons];
    Rectangle animated_buttons[num_buttons];
    Keyframe_Rectangle hover_keyframe = NEW_KEYFRAME_Rectangle({
        .Add.x=-2, 
        .Add.y=2, 
        .EasingFrames=5
        });
    TransformContext_Rectangle ctx[num_buttons];

    for (int i = 0; i < num_buttons; i++) {
        buttons[i] = (Rectangle) {50.0f + (70.0f*i), 40, 50, 50};
        ctx[i] = (TransformContext_Rectangle){
            .Keyframes = &hover_keyframe,
            .NumKeyframes = 1,
            .Playing = true
            };
    }

    while(!WindowShouldClose()) {

        Vector2 mouse_position = GetMousePosition();
        for (int i = 0; i < num_buttons; i++) {
            animated_buttons[i] = Animate_Rectangle(&ctx[i], buttons[i]);
            if (!CheckCollisionPointRec(mouse_position, animated_buttons[i])) {
                ctx[i].__Reverse = true;
            }
            else {
                ctx[i].__Reverse = false;
            }
        }

        BeginDrawing();

            ClearBackground(RED);

            for (int i = 0; i < num_buttons; i++) {
                DrawRectangleRec(animated_buttons[i], BLACK);
            }
        
        EndDrawing();
    }

    return 0;
}