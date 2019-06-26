#include <math.h>
#include "raylib.h"

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1)));
}

// LINE / POINT
bool linePoint(float x1, float y1, float x2, float y2, float px, float py)
{
	// Get distance from the point to the two ends of the line
	float d1 = distance(px, py, x1, y1);
	float d2 = distance(px, py, x2, y2);

	// Get the length of the line
	float lineLen = distance(x1, y1, x2, y2);

	// Since floats are so minutely accurate, add a little buffer zone that will give collision
	float buffer = 0.1; // higher # = less accurate

	// If the two distances are equal to the line's  length, the point is on the line!
	// Note we use the buffer here to give a range, rather than one #
	if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer)
	{
		return true;
	}
	return false;
}

int main(void)
{
	float x1 = 100; // Line defined by two points
	float y1 = 300;
	float x2 = 500;
	float y2 = 100;
	float px = 0;
	float py = 0;
	Vector2 Startpos;
	Vector2 Endpos;

	InitWindow(640, 400, "Line / Point");

	while (!WindowShouldClose())
	{
		ClearBackground(WHITE);
		BeginDrawing();

		px = GetMouseX();
		py = GetMouseY();

		// Used for drawing the line
		Startpos.x = x1;
		Startpos.y = y1;
		Endpos.x = x2;
		Endpos.y = y2;

		// Check for collision if hit, change the color of the line
		bool hit = linePoint(x1, y1, x2, y2, px, py);
		if (hit)
		{
			DrawLineEx(Startpos, Endpos, 4, RED);
		}
		else
		{
			DrawLineEx(Startpos, Endpos, 3, SKYBLUE);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
