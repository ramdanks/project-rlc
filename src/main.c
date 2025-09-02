#include <raylib.h>

#include "script.h"

int main(void)
{
    const int w = 800;
    const int h = 450;

    script_state_t s;
    script_new_state(&s);
    script_load_entity(&s);

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(w, h, "Raylib");
    SetTargetFPS(0);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, World!", 200, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    script_free_state(&s);
    return 0;
}
