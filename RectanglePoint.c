#include <math.h>
#include "raylib.h"

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1)));
}

// POINT/RECTANGLE
bool pointRect(float px, float py, float rx, float ry, float rw, float rh)
{

    // is the point inside the rectangle's bounds?
    if (px >= rx &&      // right of the left edge AND
        px <= rx + rw && // left of the right edge AND
        py >= ry &&      // below the top AND
        py <= ry + rh)
    { // above the bottom
        return true;
    }
    return false;
}

int main(void)
{
    float px = 0; // point position (move with mouse)
    float py = 0;

    float sx = 200; // square position
    float sy = 100;
    float sw = 200; // and dimensions
    float sh = 200;

    Vector2 Startpos;
    Vector2 Endpos;

    InitWindow(640, 400, "Rectangle / Point");

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        px = GetMouseX();
        py = GetMouseY();

        // Check for collision if hit, change the color of the rectangle
        bool hit = pointRect(px, py, sx, sy, sw, sh);
        if (hit)
        {
            DrawRectangle(sx, sy, sw, sh, RED);
        }
        else
        {
            DrawRectangle(sx, sy, sw, sh, SKYBLUE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
