#include "raylib.h"

// RECTANGLE/RECTANGLE
bool rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
{
	// Are the sides of one rectangle touching the other?
	if (r1x + r1w >= r2x && // r1 right edge past r2 left.
		r1x <= r2x + r2w && // r1 left edge past r2 right.
		r1y + r1h >= r2y && // r1 top edge past r2 bottom.
		r1y <= r2y + r2h)   // r1 bottom edge past r2 top.
	{
		return true;
	}
	return false;
}

// RECTANGLE/RECTANGLE
bool rectRect2(float MinX1, float MinY1, float MaxX1, float MaxY1, float MinX2, float MinY2, float MaxX2, float MaxY2)
{
	// Are the sides of one rectangle touching the other?
	if (MaxX1 >= MinX2 && // r1 right edge past r2 left.
		MinX1 <= MaxX2 && // r1 left edge past r2 right.
		MaxY1 >= MinY2 && // r1 top edge past r2 bottom.
		MinY1 <= MaxY2)   // r1 bottom edge past r2 top.
	{
		return true;
	}
	return false;
}

int main(void)
{
	float s1x = 0; // square position (move with mouse)
	float s1y = 0;
	float s1w = 100; // and dimensions.
	float s1h = 100;

	float s2x = 200; // same for second square.
	float s2y = 100;
	float s2w = 200;
	float s2h = 200;

	InitWindow(640, 400, "Rectangle / Rectangle");

	while (!WindowShouldClose())
	{
		ClearBackground(WHITE);
		BeginDrawing();

		s1x = GetMouseX();
		s1y = GetMouseY();

		DrawRectangle(s2x, s2y, s2w, s2h, SKYBLUE);

		bool hit = rectRect2(s1x, s1y, s1x + s1w, s1y + s1h, s2x, s2y, s2x + s2w, s2y + s2h);
		if (hit)
		{
			DrawRectangle(s1x, s1y, s1w, s1h, RED);
		}
		else
		{
			DrawRectangle(s1x, s1y, s1w, s1h, GRAY);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
