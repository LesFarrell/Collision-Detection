#include <math.h>
#include "raylib.h"

// CIRCLE/CIRCLE
bool circleCircle(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{

	// Get distance between the circle's centers use the Pythagorean Theorem to compute the distance
	float distX = c1x - c2x;
	float distY = c1y - c2y;
	float distance = sqrt((distX * distX) + (distY * distY));

	// If the distance is less than the sum of the circle's radii, the circles are touching!
	if (distance <= c1r + c2r)
	{
		return true;
	}
	return false;
}

int main(void)
{
	float c1x = 0;  // circle 1 position
	float c1y = 0;  // (controlled by mouse)
	float c1r = 30; // radius

	float c2x = 300; // circle 2 position
	float c2y = 200;
	float c2r = 100;

	InitWindow(640, 400, "Circle / Circle");

	while (!WindowShouldClose())
	{
		ClearBackground(WHITE);
		BeginDrawing();

		c1x = GetMouseX();
		c1y = GetMouseY();

		// Other circle, controlled by mouse
		DrawCircle(c2x, c2y, c2r, GRAY);

		bool hit = circleCircle(c1x, c1y, c1r, c2x, c2y, c2r);
		if (hit)
		{
			DrawCircle(c1x, c1y, c1r, RED);
		}
		else
		{
			DrawCircle(c1x, c1y, c1r, SKYBLUE);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
