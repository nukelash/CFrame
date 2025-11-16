#include "raylib.h"
#include "../cframe.h"

typedef struct _word {
    char _1;
    char _2;
    char _3;
} Word;

CF_DEFINE_4(Rectangle, float, x, y, width, height);
CF_DEFINE_3(Word, char, _1, _2, _3);

int main() {

    char* w2 = "AB";
    printf("%d\n", w2[0]);
    printf("%d\n", w2[1]);



    InitWindow(680, 400, "Basic Example");
    SetTargetFPS(60);


    CF_RectangleKeyframe keyframes[1] = {
        CF_InitRectangleKeyframe((CF_RectangleKeyframe) {
            .Add.x=200, 
            .EasingFrames=60
            }), 
    };

    CF_RectangleContext ctx_rec = {
        .Keyframes=keyframes,
        .NumKeyframes=1,
        .Mode=CF_PLAYMODE_BOOMERANG_LOOP,
        .Playing=true
    };

    CF_WordKeyframe kf[1] = {
        CF_InitWordKeyframe((CF_WordKeyframe) {
            .Add._1=40,
            .Add._2=10,
            .Add._3=15,
            .EasingFrames=80
        })
    };

    CF_WordContext wc = {
        .Keyframes = kf,
        .NumKeyframes = 1,
        .Playing = true,
        .Mode = CF_PLAYMODE_BOOMERANG_LOOP
    };

    Rectangle rec = {200, 150, 60, 60};
    Word word = {'T', 'H', 'E'};


    while(!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawRectangleRec(CF_RectangleProcess(&ctx_rec, rec), BLUE);
            Word w = CF_WordProcess(&wc, word);
            char full_word[4] = {w._1, w._2, w._3, '\0'};
            DrawText(full_word, 20, 30, 14, BLACK);

   
        EndDrawing();
    }

    return 0;
}