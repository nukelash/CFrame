#include "raylib.h"

#define CFRAME_IMPLEMENTATION
#include "../cframe.hpp"

int main() {
    InitWindow(850, 600, "Playmodes");
    SetTargetFPS(60);

    // Set up initial Rectangles
    Rectangle rec_once = {250, 80, 60, 60};
    Rectangle rec_loop = {250, 180, 60, 60};
    Rectangle rec_boomerang = {250, 280, 60, 60};
    Rectangle rec_boomerang_loop = {250, 380, 60, 60};
    bool play = false;

    // Set up keyframe and contexts
    CF::Keyframe<Rectangle> keyframe = {
        .type = CF::TransformType::OFFSET,
        .transform = {400, 0, 0, 0}
    };

    CF::Animation<Rectangle> ctx_once = {rec_once, {keyframe}, CF::PlayMode::ONCE, CF::EasingFunction::CUBIC_IN_OUT};

    CF::Animation<Rectangle> ctx_loop = {rec_loop, {keyframe}, CF::PlayMode::LOOP, CF::EasingFunction::CUBIC_IN_OUT};
    
    CF::Animation<Rectangle> ctx_boomerang_once = {rec_boomerang, {keyframe}, CF::PlayMode::BOOMERANG_ONCE, CF::EasingFunction::CUBIC_IN_OUT};

    CF::Animation<Rectangle> ctx_boomerang_loop = {rec_boomerang_loop, {keyframe}, CF::PlayMode::BOOMERANG_LOOP, CF::EasingFunction::CUBIC_IN_OUT};

    while(!WindowShouldClose()) {

        // Play/pause
        if(IsKeyPressed(KEY_P)) {
            play = !play;
            ctx_once.playing = play;
            ctx_loop.playing = play;
            ctx_boomerang_once.playing = play;
            ctx_boomerang_loop.playing = play;
        }

        // Reset
        if(IsKeyPressed(KEY_R)) {
            play = false;
            ctx_once.playing = play;
            ctx_loop.playing = play;
            ctx_boomerang_once.playing = play;
            ctx_boomerang_loop.playing = play;
            ctx_once.index = 0;
            ctx_loop.index = 0;
            ctx_boomerang_once.index = 0;
            ctx_boomerang_loop.index = 0;
            ctx_once._reverse = false;
            ctx_loop._reverse = false;
            ctx_boomerang_once._reverse = false;
            ctx_boomerang_loop._reverse = false;
        }

        char once_index[64];
        char loop_index[64];
        char boomerang_index[64];
        char boomerang_loop_index[64];

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawText("P to Play/Pause, R to Reset", 300, 550, 20, BLACK);

            DrawText("ONCE", rec_once.x-200, rec_once.y+25, 14, BLACK);
            DrawText("LOOP", rec_loop.x-200, rec_loop.y+25, 14, BLACK);
            DrawText("BOOMERANG_ONCE", rec_boomerang.x-200, rec_boomerang.y+25, 14, BLACK);
            DrawText("BOOMERANG_LOOP", rec_boomerang_loop.x-200, rec_boomerang_loop.y+25, 14, BLACK);

            sprintf(once_index, "Index: %d", ctx_once.index);
            sprintf(loop_index, "Index: %d", ctx_loop.index);
            sprintf(boomerang_index, "Index: %d", ctx_boomerang_once.index);
            sprintf(boomerang_loop_index, "Index: %d", ctx_boomerang_loop.index);

            DrawText(once_index, rec_once.x+500, rec_once.y+25, 10, BLACK);
            DrawText(loop_index, rec_loop.x+500, rec_loop.y+25, 10, BLACK);
            DrawText(boomerang_index, rec_boomerang.x+500, rec_boomerang.y+25, 10, BLACK);
            DrawText(boomerang_loop_index, rec_boomerang_loop.x+500, rec_boomerang_loop.y+25, 10, BLACK);

            DrawLineEx((Vector2){rec_once.x - 200, rec_once.y + 80}, (Vector2){rec_once.x + 550, rec_once.y + 80}, 1.5, BLACK);
            DrawLineEx((Vector2){rec_loop.x - 200, rec_loop.y + 80}, (Vector2){rec_loop.x + 550, rec_loop.y + 80}, 1.5, BLACK);
            DrawLineEx((Vector2){rec_boomerang.x - 200, rec_boomerang.y + 80}, (Vector2){rec_boomerang.x + 550, rec_boomerang.y + 80}, 1.5, BLACK);
            
            // Actual rectangle animation
            DrawRectangleRec(ctx_once.get(), BLUE);
            DrawRectangleRec(ctx_loop.get(), BLUE);
            DrawRectangleRec(ctx_boomerang_once.get(), BLUE);
            DrawRectangleRec(ctx_boomerang_loop.get(), BLUE);

        
        EndDrawing();
    }
}