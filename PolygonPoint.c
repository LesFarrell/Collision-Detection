#include <math.h>
#include "raylib.h"

// POLYGON/POINT
bool polyPoint(Vector2 vertices[], int NumVertices, float px, float py)
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

        // Get the Vectors at our current position this makes our if statement a little cleaner.
        Vector2 vc = vertices[current]; // c for "current".
        Vector2 vn = vertices[next];    // n for "next".

        // compare position, flip 'collision' variable back and forth.
        /*
        if (((vc.y >= py && vn.y < py) || (vc.y < py && vn.y >= py)) &&
            (px < (vn.x - vc.x) * (py - vc.y) / (vn.y - vc.y) + vc.x))
        {
            collision = !collision;
        }
        */

        if ((vc.y >= py && vn.y < py) || (vc.y < py && vn.y >= py))
        {
            if (vn.x + (py - vn.y) / (vc.y - vn.y) * (vc.x - vn.x) < px)
            {
                collision = !collision;
            }
        }
    }
    return collision;
}

int main(void)
{
    float px = 0; // Point position.
    float py = 0;

    // Array of Vectors, one for each vertex in the polygon.
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

    InitWindow(640, 400, "Polygon / Point");

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        px = GetMouseX();
        py = GetMouseY();

        bool hit = polyPoint(vertices, 5, px, py);
        if (hit)
        {
            DrawPolyExLines(vertices, 5, RED);
        }
        else
        {
            DrawPolyExLines(vertices, 5, SKYBLUE);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
