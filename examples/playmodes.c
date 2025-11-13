#include "raylib.h"
#include "../cframe.h"

int main() {
    InitWindow(850, 600, "Playmodes");
    SetTargetFPS(60);

    // Set up keyframe and contexts
    CF_RectangleKeyframe keyframe = CF_SetRectangleKeyframe({.Add.x=400, .EasingFrames=60, .HeldFrames=10});

    CF_RectangleContext ctx_once = {
        .Keyframes = &keyframe,
        .NumKeyframes = 1,
        .Mode = CF_PLAYMODE_ONCE
    };

    CF_RectangleContext ctx_loop = {
        .Keyframes = &keyframe,
        .NumKeyframes = 1,
        .Mode = CF_PLAYMODE_LOOP
    };

    CF_RectangleContext ctx_boomerang_once = {
        .Keyframes = &keyframe,
        .NumKeyframes = 1,
        .Mode = CF_PLAYMODE_BOOMERANG_ONCE
    };

    CF_RectangleContext ctx_boomerang_loop = {
        .Keyframes = &keyframe,
        .NumKeyframes = 1,
        .Mode = CF_PLAYMODE_BOOMERANG_LOOP
    };

    // Set up initial Rectangles
    Rectangle rec_once = {250, 100, 60, 60};
    Rectangle rec_loop = {250, 200, 60, 60};
    Rectangle rec_boomerang = {250, 300, 60, 60};
    Rectangle rec_boomerang_loop = {250, 400, 60, 60};
    bool play = false;

    while(!WindowShouldClose()) {

        // Play/pause
        if(IsKeyPressed(KEY_P)) {
            play = !play;
            ctx_once.Playing = play;
            ctx_loop.Playing = play;
            ctx_boomerang_once.Playing = play;
            ctx_boomerang_loop.Playing = play;
        }

        // Reset
        if(IsKeyPressed(KEY_R)) {
            play = false;
            ctx_once.Playing = play;
            ctx_loop.Playing = play;
            ctx_boomerang_once.Playing = play;
            ctx_boomerang_loop.Playing = play;
            ctx_once.Index = 0;
            ctx_loop.Index = 0;
            ctx_boomerang_once.Index = 0;
            ctx_boomerang_loop.Index = 0;
            ctx_once.__Reverse = false;
            ctx_loop.__Reverse = false;
            ctx_boomerang_once.__Reverse = false;
            ctx_boomerang_loop.__Reverse = false;
        }

        char once_index[64];
        char loop_index[64];
        char boomerang_index[64];
        char boomerang_loop_index[64];

        BeginDrawing();

            ClearBackground(GRAY);

            DrawText("P to Play/Pause, R to Reset", 300, 550, 20, BLACK);

            DrawText("ONCE", rec_once.x-200, rec_once.y+25, 14, BLACK);
            DrawText("LOOP", rec_loop.x-200, rec_loop.y+25, 14, BLACK);
            DrawText("BOOMERANG_ONCE", rec_boomerang.x-200, rec_boomerang.y+25, 14, BLACK);
            DrawText("BOOMERANG_LOOP", rec_boomerang_loop.x-200, rec_boomerang_loop.y+25, 14, BLACK);

            sprintf(once_index, "Index: %d", ctx_once.Index);
            sprintf(loop_index, "Index: %d", ctx_loop.Index);
            sprintf(boomerang_index, "Index: %d", ctx_boomerang_once.Index);
            sprintf(boomerang_loop_index, "Index: %d", ctx_boomerang_loop.Index);

            DrawText(once_index, rec_once.x+500, rec_once.y+25, 10, BLACK);
            DrawText(loop_index, rec_loop.x+500, rec_loop.y+25, 10, BLACK);
            DrawText(boomerang_index, rec_boomerang.x+500, rec_boomerang.y+25, 10, BLACK);
            DrawText(boomerang_loop_index, rec_boomerang_loop.x+500, rec_boomerang_loop.y+25, 10, BLACK);

            DrawLineEx((Vector2){rec_once.x - 200, rec_once.y + 80}, (Vector2){rec_once.x + 550, rec_once.y + 80}, 1.5, BLACK);
            DrawLineEx((Vector2){rec_loop.x - 200, rec_loop.y + 80}, (Vector2){rec_loop.x + 550, rec_loop.y + 80}, 1.5, BLACK);
            DrawLineEx((Vector2){rec_boomerang.x - 200, rec_boomerang.y + 80}, (Vector2){rec_boomerang.x + 550, rec_boomerang.y + 80}, 1.5, BLACK);
            
            // Actual rectangle animation
            DrawRectangleRec(CF_RectangleProcess(&ctx_once, rec_once), BLUE);
            DrawRectangleRec(CF_RectangleProcess(&ctx_loop, rec_loop), BLUE);
            DrawRectangleRec(CF_RectangleProcess(&ctx_boomerang_once, rec_boomerang), BLUE);
            DrawRectangleRec(CF_RectangleProcess(&ctx_boomerang_loop, rec_boomerang_loop), BLUE);

        
        EndDrawing();
    }
}