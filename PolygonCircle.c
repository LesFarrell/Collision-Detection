#include <math.h>
#include "raylib.h"

float distance(float x1, float y1, float x2, float y2);
bool lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r);
bool linePoint(float x1, float y1, float x2, float y2, float px, float py);
bool pointCircle(float px, float py, float cx, float cy, float r);
bool polyPoint(Vector2 vertices[], int NumVertices, float px, float py);
bool polyCircle(Vector2 vertices[], int NumVertices, float cx, float cy, float r);

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1)));
}

// LINE/CIRCLE
bool lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r)
{
    // Is either end INSIDE the circle? if so, return true immediately.
    bool inside1 = pointCircle(x1, y1, cx, cy, r);
    bool inside2 = pointCircle(x2, y2, cx, cy, r);
    if (inside1 || inside2)
        return true;

    // Get length of the line.
    float distX = x1 - x2;
    float distY = y1 - y2;
    float len = sqrt((distX * distX) + (distY * distY));

    // Get dot product of the line and circle.
    float dot = (((cx - x1) * (x2 - x1)) + ((cy - y1) * (y2 - y1))) / pow(len, 2);

    // Find the closest point on the line.
    float closestX = x1 + (dot * (x2 - x1));
    float closestY = y1 + (dot * (y2 - y1));

    // Is this point actually on the line segment? if so keep going, but if not, return false.
    bool onSegment = linePoint(x1, y1, x2, y2, closestX, closestY);
    if (!onSegment)
        return false;

    // Optionally, draw a circle at the closest point on the line.
    // DrawCircle(closestX, closestY, 5, RED);

    // Get distance to closest point.
    distX = closestX - cx;
    distY = closestY - cy;
    float dist = sqrt((distX * distX) + (distY * distY));

    // Is the circle on the line?
    if (dist <= r)
    {
        return true;
    }
    return false;
}

// LINE/POINT
bool linePoint(float x1, float y1, float x2, float y2, float px, float py)
{

    // Get distance from the point to the two ends of the line.
    float d1 = distance(px, py, x1, y1);
    float d2 = distance(px, py, x2, y2);

    // Get the length of the line.
    float lineLen = distance(x1, y1, x2, y2);

    // Since floats are so minutely accurate, add a little buffer zone that will give collision.
    float buffer = 0.1; // higher # = less accurate

    // If the two distances are equal to the line's length, the point is on the line!
    // Note we use the buffer here to give a range, rather than one #
    if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer)
    {
        return true;
    }
    return false;
}

// POINT/CIRCLE
bool pointCircle(float px, float py, float cx, float cy, float r)
{
    // Get distance between the point and circle's center using the Pythagorean Theorem.
    float distX = px - cx;
    float distY = py - cy;
    float dist = sqrt((distX * distX) + (distY * distY));

    // If the distance is less than the circle's radius the point is inside!
    if (dist <= r)
    {
        return true;
    }
    return false;
}

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
        Vector2 vc = vertices[current]; // c for "current"
        Vector2 vn = vertices[next];    // n for "next"

        // Compare position, flip 'collision' variable back and forth.
        if (((vc.y >= py && vn.y < py) || (vc.y < py && vn.y >= py)) &&
            (px < (vn.x - vc.x) * (py - vc.y) / (vn.y - vc.y) + vc.x))
        {
            collision = !collision;
        }
    }
    return collision;
}

// POLYGON/CIRCLE
bool polyCircle(Vector2 vertices[], int NumVertices, float cx, float cy, float r)
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
        Vector2 vc = vertices[current]; // c for "current"
        Vector2 vn = vertices[next];    // n for "next"

        // Check for collision between the circle and a line formed between the two vertices.
        bool collision = lineCircle(vc.x, vc.y, vn.x, vn.y, cx, cy, r);
        if (collision)
            return true;
    }

    // The above algorithm only checks if the circle is touching the edges of the polygon – in most
    // cases this is enough, but you can un-comment the following code to also test if the center of the
    // circle is inside the polygon.
    bool centerInside = polyPoint(vertices, NumVertices, cx, cy);
    if (centerInside)
        return true;

    // Otherwise, after all that, return false.
    return false;
}

int main(void)
{
    float cx = 0; // Position of the circle
    float cy = 0;
    float r = 30; // Circle's radius

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

        cx = GetMouseX();
        cy = GetMouseY();

        bool hit = polyCircle(vertices, 5, cx, cy, r);
        if (hit)
        {
            DrawCircle(cx, cy, r, RED);
        }
        else
        {
            DrawCircle(cx, cy, r, SKYBLUE);
        }

        DrawPolyExLines(vertices, 5, SKYBLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
