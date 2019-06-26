#include <math.h>
#include "raylib.h"

// TRIANGLE/POINT
bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3, float px, float py)
{
    // Get the area of the triangle
    float areaOrig = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));

    // Get the area of 3 triangles made between the point and the corners of the triangle
    float area1 = abs((x1 - px) * (y2 - py) - (x2 - px) * (y1 - py));
    float area2 = abs((x2 - px) * (y3 - py) - (x3 - px) * (y2 - py));
    float area3 = abs((x3 - px) * (y1 - py) - (x1 - px) * (y3 - py));

    // If the sum of the three areas equals the original, we're inside the triangle!
    if (area1 + area2 + area3 == areaOrig)
    {
        return true;
    }
    return false;
}


int main(void)
{
    float px = 0; // Point (set by mouse)
    float py = 0;

    float x1 = 300; // Three points of the triangle
    float y1 = 100;
    float x2 = 450;
    float y2 = 300;
    float x3 = 150;
    float y3 = 300;
    Vector2 v1, v2, v3;

    InitWindow(640, 400, "Triangle / Point");

    v1.x = x1;
    v1.y = y1;
    v2.x = x2;
    v2.y = y2;
    v3.x = x3;
    v3.y = y3;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        px = GetMouseX();
        py = GetMouseY();

        // Check for collision if hit, change colour
        bool hit = triPoint(x1, y1, x2, y2, x3, y3, px, py);
        if (hit)
        {
            DrawTriangleLines((Vector2){x1, y1},
                              (Vector2){x2, y2},
                              (Vector2){x3, y3}, RED);

            DrawCircle(px, py, 5, RED);
        }
        else
        {
            DrawTriangleLines((Vector2){x1, y1},
                              (Vector2){x2, y2},
                              (Vector2){x3, y3}, SKYBLUE);

            DrawCircle(px, py, 5, SKYBLUE);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
