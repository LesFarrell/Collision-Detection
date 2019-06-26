#include "raylib.h"

// POINT / RECTANGLE
bool pointRect(float px, float py, float rx, float ry, float rw, float rh)
{

    // Is the point inside the rectangle's bounds?
    if (px >= rx &&      // right of the left edge AND
        px <= rx + rw && // left of the right edge AND
        py >= ry &&      // below the top AND
        py <= ry + rh)
    { // above the bottom
        return true;
    }
    return false;
}

// LINE/LINE
bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{

    // Calculate the direction of the lines
    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // If uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
    {
        return true;
    }

    return false;
}

// LINE / RECTANGLE
bool lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh)
{

    // Is either the end point or startpoint in rectangle?
    if (pointRect(x1, y1, rx, ry, rw, rh) || pointRect(x2, y2, rx, ry, rw, rh))
    {
        return true;
    }

    // Check if the line has hit any of the rectangle's sides
    bool left = lineLine(x1, y1, x2, y2, rx, ry, rx, ry + rh);
    bool right = lineLine(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
    bool top = lineLine(x1, y1, x2, y2, rx, ry, rx + rw, ry);
    bool bottom = lineLine(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);

    // If ANY of the above are true, the line has hit the rectangle
    if (left || right || top || bottom)
    {
        return true;
    }

    return false;
}

int main(void)
{
    Vector2 Startpos = {50, 50};
    Vector2 Endpos = {50, 50};

    // Update line to mouse coordinates.
    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;

    float s1x = 150; // square position (move with mouse)
    float s1y = 150;
    float s1w = 140; // and dimensions.
    float s1h = 140;

    InitWindow(640, 400, "Rectangle / Line");

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        if (IsMouseButtonPressed(1))
        {
            Endpos.x = GetMouseX();
            Endpos.y = GetMouseY();
        }
        else
        {
            Startpos.x = GetMouseX();
            Startpos.y = GetMouseY();
        }

        // bool hit = rectRect2(s1x, s1y, s1x + s1w, s1y + s1h, s2x, s2y, s2x + s2w, s2y + s2h);
        bool hit = lineRect(Startpos.x, Startpos.y, Endpos.x, Endpos.y, s1x, s1y, s1w, s1h);
        if (hit)
        {
            DrawRectangle(s1x, s1y, s1w, s1h, RED);
        }
        else
        {
            DrawRectangle(s1x, s1y, s1w, s1h, GRAY);
        }

        DrawLineEx(Startpos, Endpos, 5.0, SKYBLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
