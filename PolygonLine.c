#include <math.h>
#include "raylib.h"

// LINE / LINE
bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{

    // Calculate the direction of the lines.
    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // If uA and uB are between 0-1, lines are colliding.
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
    {
        return true;
    }
    return false;
}

// POLYGON / LINE
bool polyLine(Vector2 vertices[], int NumVertices, float x1, float y1, float x2, float y2)
{
    // Go through each of the vertices, plus the next vertex in the list.
    int next = 0;
    for (int current = 0; current < NumVertices; current++)
    {

        // Get next vertex in list if we've hit the end, wrap around to 0.
        next = current + 1;
        if (next == NumVertices)
            next = 0;

        // Get the Vectors at our current position extract X/Y coordinates from each.
        float x3 = vertices[current].x;
        float y3 = vertices[current].y;
        float x4 = vertices[next].x;
        float y4 = vertices[next].y;

        // Do a Line/Line comparison if true, return 'true' immediately and stop testing (faster).
        bool hit = lineLine(x1, y1, x2, y2, x3, y3, x4, y4);
        if (hit)
        {
            return true;
        }
    }

    // Never got a hit.
    return false;
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
    // Update line to mouse coordinates.
    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;
    Vector2 Startpos;
    Vector2 Endpos;

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

    InitWindow(640, 400, "Polygon / Circle");

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        x1 = GetMouseX();
        y1 = GetMouseY();

        if (IsMouseButtonPressed(1))
        {
            x2 = GetMouseX();
            y2 = GetMouseY();
        }

        Startpos.x = x1;
        Startpos.y = y1;
        Endpos.x = x2;
        Endpos.y = y2;

        bool hit = polyLine(vertices, 5, x1, y1, x2, y2);
        if (hit)
        {
            DrawLineEx(Startpos, Endpos, 4, RED);
            DrawPolyExLines(vertices, 5, RED);
        }
        else
        {
            DrawLineEx(Startpos, Endpos, 4, SKYBLUE);
            DrawPolyExLines(vertices, 5, SKYBLUE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
