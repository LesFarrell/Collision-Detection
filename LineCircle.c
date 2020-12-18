#include <math.h>
#include "raylib.h"


// Get distance between two points using the Pythagorean Theorem.
float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1)));
}


// LINE/POINT
bool linePoint(float x1, float y1, float x2, float y2, float px, float py) {

  // Get distance from the point to the two ends of the line
  float d1 = distance(px, py, x1, y1);
  float d2 = distance(px, py, x2, y2);

  // Get the length of the line
  float lineLen = distance(x1, y1, x2, y2);

  // Since floats are so minutely accurate, add a little buffer zone that will give collision.
  float buffer = 0.1;    // higher # = less accurate

  // If the two distances are equal to the line's length, the point is on the line!
  // Note we use the buffer here to give a range, rather than one #
  if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) return true;

  return false;
}


// POINT/CIRCLE
bool pointCircle(float px, float py, float cx, float cy, float r) {

  // Get distance between the point and circle's centre using the Pythagorean Theorem.
  float dist = distance( px,py,cx,cy );

  // If the distance is less than the circle's radius the point is inside!
  if (dist <= r) return true;

  return false;
}


// LINE/CIRCLE
bool lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r) {

  // Is either end INSIDE the circle? If so, return true immediately.
  bool inside1 = pointCircle(x1, y1, cx, cy, r);
  bool inside2 = pointCircle(x2, y2, cx, cy, r);
  if (inside1 || inside2) return true;

  // Get length of the line.
  float lineLen = distance(x1, y1, x2, y2);

  // Get dot product of the line and circle.
  float dot = (((cx - x1) * (x2 - x1)) + ((cy - y1) * (y2 - y1))) / pow(lineLen, 2);

  // Find the closest point on the line.
  float closestX = x1 + (dot * (x2 - x1));
  float closestY = y1 + (dot * (y2 - y1));

  // Is this point actually on the line segment? If so keep going, but if not, return false.
  bool onSegment = linePoint(x1, y1, x2, y2, closestX, closestY);
  if (!onSegment) return false;

  // Optionally, draw a circle at the closest point on the line.
  DrawCircle(closestX, closestY, 5, RED);

  // Get distance to closest point.
  float dist = distance(closestX, closestY, cx, cy);
  if (dist <= r) return true;

  return false;
}


int main(void) {
	float cx = 0;  // circle 1 position
	float cy = 0;  // (controlled by mouse)
	float cr = 30; // radius

	float x1 = 100; // circle 2 position
	float y1 = 300;
	float x2 = 500;
    float y2 = 100;

	InitWindow(640, 400, "Line / Circle");

	while (!WindowShouldClose()) {

        ClearBackground(WHITE);
		BeginDrawing();

		cx = GetMouseX();
		cy = GetMouseY();

		// Circle, controlled by mouse
		DrawCircle(cx, cy, cr, GRAY);
        DrawLine(x1,y1,x2,y2,GRAY);

		bool hit = lineCircle(x1,y1, x2,y2, cx,cy,cr);
		if (hit) {
			DrawCircle(cx, cy, cr, RED);
        } else {
			DrawCircle(cx, cy, cr, SKYBLUE);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
