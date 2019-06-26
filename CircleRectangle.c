#include <math.h>
#include "raylib.h"

// CIRCLE/RECTANGLE
bool circleRect(float cx, float cy, float radius, float rx, float ry, float rw, float rh)
{
    // Temporary variables to set edges for testing
    float testX = cx;
    float testY = cy;

    // Which edge is closest?
    if (cx < rx)
        testX = rx; // Test left edge
    else if (cx > rx + rw)
        testX = rx + rw; // Right edge
    if (cy < ry)
        testY = ry; // Top edge
    else if (cy > ry + rh)
        testY = ry + rh; // Bottom edge

    // Get distance from closest edges
    float distX = cx - testX;
    float distY = cy - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    // If the distance is less than the radius, collision!
    if (distance <= radius)
    {
        return true;
    }
    return false;
}

int main(void)
{
    float cx = 0; // Circle position (set with mouse)
    float cy = 0;
    float r = 30; // Circle radius

    float sx = 200; // Square position
    float sy = 100;
    float sw = 200; // and dimensions
    float sh = 200;

    InitWindow(640, 400, "Circle / Rectangle");

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);

        // Update square to mouse coordinates
        cx = GetMouseX();
        cy = GetMouseY();

        // Check for collision if hit, change rectangle color.
        bool hit = circleRect(cx, cy, r, sx, sy, sw, sh);
        if (hit)
        {
            DrawRectangle(sx, sy, sw, sh, RED);
        }
        else
        {
            DrawRectangle(sx, sy, sw, sh, SKYBLUE);
        }

        // Draw the circle
        DrawCircle(cx, cy, r, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
