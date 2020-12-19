#include <math.h>
#include "raylib.h"

bool polygonPoint(Vector2 vertices[], int NumVertices, float px, float py);
bool polyRect(Vector2 vertices[], int NumVertices, float rx, float ry, float rw, float rh);
bool lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);
bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
bool polygonPoint(Vector2 vertices[], int NumVertices, float px, float py);
float distance(float x1, float y1, float x2, float y2);

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1)));
}

// POLYGON/RECTANGLE
bool polyRect(Vector2 vertices[], int NumVertices, float rx, float ry, float rw, float rh)
{
    // Go through each of the vertices, plus the next vertex in the list.
    int next = 0;
    for (int current = 0; current < NumVertices; current++)
    {
        // Get next vertex in list if we've hit the end, wrap around to 0.
        next = current + 1;
        if (next == NumVertices)
            next = 0;

        // Get the Vector2 at our current position this makes our if statement a little cleaner.
        Vector2 vc = vertices[current]; // c for "current".
        Vector2 vn = vertices[next];    // n for "next".

        // Check against all four sides of the rectangle.
        bool collision = lineRect(vc.x, vc.y, vn.x, vn.y, rx, ry, rw, rh);
        if (collision)
            return true;

        // Optional: test if the rectangle is INSIDE the polygon note that this iterates all sides of the polygon
        // again, so only use this if you need to.
        bool inside = polygonPoint(vertices, NumVertices, rx, ry);
        if (inside)
            return true;
    }

    return false;
}

// LINE/RECTANGLE
bool lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh)
{
    // Check if the line has hit any of the rectangle's sides uses the Line/Line function below.
    bool left = lineLine(x1, y1, x2, y2, rx, ry, rx, ry + rh);
    bool right = lineLine(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
    bool top = lineLine(x1, y1, x2, y2, rx, ry, rx + rw, ry);
    bool bottom = lineLine(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);

    // If ANY of the above are true, the line has hit the rectangle.
    if (left || right || top || bottom)
    {
        return true;
    }
    return false;
}

// LINE/LINE
bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    // Calculate the direction of the lines.
    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // If uA and uB are between 0 - 1, lines are colliding.
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
    {
        return true;
    }
    return false;
}

// POLYGON/POINT
// Only needed if you're going to check if the rectangle is INSIDE the polygon.
bool polygonPoint(Vector2 vertices[], int NumVertices, float px, float py)
{
    bool collision = false;

    // Go through each of the vertices, plus the next vertex in the list.
    int next = 0;
    for (int current = 0; current < NumVertices; current++)
    {
        // Get next vertex in list if we've hit the end, wrap around to 0.
        next = current + 1;
        if (next == NumVertices)
            next = 0;

        // Get the Vector2 at our current position this makes our if statement a little cleaner.
        Vector2 vc = vertices[current]; // c for "current".
        Vector2 vn = vertices[next];    // n for "next".

        // Compare position, flip 'collision' variable back and forth.
        if (((vc.y > py && vn.y < py) || (vc.y < py && vn.y > py)) &&
            (px < (vn.x - vc.x) * (py - vc.y) / (vn.y - vc.y) + vc.x))
        {
            collision = !collision;
        }
    }
    return collision;
}


int DrawPolyExLines(Vector2 vertices[],int  numvertices,Color color)
{
    for (int i=0;i<numvertices-1;i++)
    {
        DrawLineV(vertices[i],vertices[i+1],color);
    }
}

int main(void)
{
    float sx = 0; // A square, controlled by the mouse.
    float sy = 0;
    float sw = 100; // width and height.
    float sh = 100;

    // Array of Vector2, one for each vertex in the polygon.
    Vector2 vertices[10];

    // Set position of the vertices here we draw a distorted trapezoid, but
    // you could make much more complex shapes or even randomize the points!
    vertices[0].x = 200;
    vertices[0].y = 100;
    vertices[1].x = 400;
    vertices[1].y = 130;
    vertices[2].x = 350;
    vertices[2].y = 300;
    vertices[3].x = 250;
    vertices[3].y = 300;
    vertices[4].x = 200;
    vertices[4].y = 100;

    InitWindow(640, 400, "Polygon / Rectangle");

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        sx = GetMouseX();
        sy = GetMouseY();

        bool hit = polyRect(vertices, 5, sx, sy, sw, sh);
        if (hit)
        {
            DrawPolyExLines(vertices, 5, RED);
            DrawRectangle(sx, sy, sw, sh, RED);
        }
        else
        {
            DrawPolyExLines(vertices, 5, SKYBLUE);
            DrawRectangle(sx, sy, sw, sh, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
