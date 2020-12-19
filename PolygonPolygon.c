#include <math.h>
#include "raylib.h"

bool polyPoly(Vector2 p1[], int NumVertices, Vector2 p2[], int NumVertices2);
bool polyLine(Vector2 vertices[], int NumVertices, float x1, float y1, float x2, float y2);
bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
bool polyPoint(Vector2 vertices[], int NumVertices, float px, float py);
int random(int low, int high);
float radians(float Degrees);

float radians(float Degrees)
{
    return Degrees * 1.74532925199433E-02; // (PI / 180)
}

/* Get random number between low and high, inclusively */
int random(int low, int high)
{
    if (high <= low)
        return (low); /* Avoid divide by zero */
    return (low + (rand() % (high - low)));
}

// POLYGON/POLYGON
bool polyPoly(Vector2 p1[], int NumVertices, Vector2 p2[], int NumVertices2)
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
        Vector2 vc = p1[current]; // c for "current".
        Vector2 vn = p1[next];    // n for "next".

        // Now we can use these two points (a line) to compare to the other polygon's vertices using polyLine().
        bool collision = polyLine(p2, NumVertices2, vc.x, vc.y, vn.x, vn.y);
        if (collision)
            return true;

        // Optional: check if the 2nd polygon is INSIDE the first.
        collision = polyPoint(p1, NumVertices, p2[0].x, p2[0].y);
        if (collision)
            return true;
    }

    return false;
}

// POLYGON/LINE
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

        // Get the Vector2s at our current position extract X/Y coordinates from each.
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

// LINE/LINE
bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    // Calculate the direction of the lines
    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // If uA and uB are between 0-1, lines are colliding.
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
    {
        return true;
    }
    return false;
}

// POLYGON/POINT
// Used only to check if the second polygon is INSIDE the first.
bool polyPoint(Vector2 vertices[], int NumVertices, float px, float py)
{
    bool collision = false;

    // Go through each of the vertices, plus the next vertex in the list
    int next = 0;
    for (int current = 0; current < NumVertices; current++)
    {

        // Get next vertex in list if we've hit the end, wrap around to 0
        next = current + 1;
        if (next == NumVertices)
            next = 0;

        // Get the Vector2 at our current position this makes our if statement a little cleaner.
        Vector2 vc = vertices[current]; // c for "current"
        Vector2 vn = vertices[next];    // n for "next"

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
    // Array of Vector2, one for each vertex in the polygon array of Vectors for each shape.
    Vector2 pentagon[100];
    int pentagonVertices = 5;
    Vector2 SecondPoly[100];
    int SecondVertices;
    int i;
    float cx, cy;

    // Set position of the pentagon's vertices.
    float angle = 6.28318530717958647693 / pentagonVertices;
    for (i = 0; i < pentagonVertices; i++)
    {
        float a = angle * i;
        float x = 300 + cos(a) * 100;
        float y = 200 + sin(a) * 100;
        pentagon[i].x = x;
        pentagon[i].y = y;
    }
    pentagon[i].x = pentagon[0].x;
    pentagon[i].y = pentagon[0].y;
    pentagonVertices++;

    InitWindow(640, 400, "Polygon / Polygon");

    while (!WindowShouldClose())
    {
        cy = GetMouseY();
        cx = GetMouseX();

        SecondPoly[0].x = cx - 100 / 2;
        SecondPoly[0].y = cy - 000 / 2;
        SecondPoly[1].x = cx - 300 / 2;
        SecondPoly[1].y = cy - 050 / 2;
        SecondPoly[2].x = cx - 250 / 2;
        SecondPoly[2].y = cy - 200 / 2;
        SecondPoly[3].x = cx - 150 / 2;
        SecondPoly[3].y = cy - 200 / 2;
        SecondPoly[4].x = cx - 100 / 2;
        SecondPoly[4].y = cy - 000 / 2;

        ClearBackground(WHITE);
        BeginDrawing();

        bool hit = polyPoly(pentagon, pentagonVertices, SecondPoly, 5);
        if (hit)
        {
            DrawPolyExLines(pentagon, pentagonVertices, RED);
            DrawPolyExLines(SecondPoly, 5, RED);
        }
        else
        {
            DrawPolyExLines(pentagon, pentagonVertices, SKYBLUE);
            DrawPolyExLines(SecondPoly, 5, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
