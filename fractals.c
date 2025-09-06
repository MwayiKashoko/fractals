#include "gfx3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//width and height of the screen
#define size 900
#define mrgn 20
#define pi 3.14159265358979323

float dtr(float theta);
void point(float x, float y);
void triangle(int x1, int y1, int x2, int y2, int x3, int y3);
void rectangle(float x, float y, float width, float height);
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkingSquares(float x, float y, float width, float height);
void spiralSquares(float r, float theta, float width, float height);
void circularLace(float x, float y, float r);
void snowflake(float x, float y, float r);
void tree(float x, float y, float r, float theta);
void fern(float x, float y, float r, float theta, float shift);
void spiralOfSpirals(float x, float y, float theta);

int main() {
	gfx_open(size, size, "Fractals");

	//Used to get user input
	char c;
	//Used to see if the user has pressed the q key to end the program
	int loop = 1;

	while (loop) {
		c = gfx_wait();

		gfx_clear();
		gfx_flush();

		switch (c) {
			case '1': 
				sierpinski(mrgn, mrgn, size-mrgn, mrgn, size/2, size-mrgn);
				break;
			case '2':
				shrinkingSquares(size/4, size/4, size/2, size/2);
				break;
			case '3':
				spiralSquares(size/2-mrgn*4, dtr(330), size/6, size/6);
				break;
			case '4':
				circularLace(0, 0, size/3);
				break;
			case '5':
				snowflake(0, 0, size/2-mrgn*8);
				break;
			case '6':
				tree(size/2, size-mrgn, size/3, dtr(90));
				break;
			case '7':
				fern(size/2, size-mrgn, 2*size/3, dtr(90), 0);
				break;
			case '8':
				spiralOfSpirals(size/2, size/2, 16*pi);
				break;
			case 'q':
				loop = 0;
				break;
		}
	}

	return 0;
}

//Takes in a float in degrees and turns it into radians
float dtr(float theta) {
	return theta*pi/180;
}

//A function that draws points and takes rounding into account
void point(float x, float y) {
	gfx_point(round(x), round(y));
}

//A function that draws a triangle into the screen
void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

//Functino that makes a rectangle which takes rounding into account
void rectangle(float x, float y, float width, float height) {
	gfx_line(round(x), round(y), round(x+width), round(y));
	gfx_line(round(x), round(y+height), round(x+width), round(y+height));
	gfx_line(round(x), round(y), round(x), round(y+height));
	gfx_line(round(x+width), round(y), round(x+width), round(y+height));
}

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3) {
  // Base case. 
  if(abs(x2-x1) < 5) {
		 return;
	}

  // Draw a triangle
 	triangle(x1, y1, x2, y2, x3, y3); 

  // Recursive calls
  sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
  sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
  sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

void shrinkingSquares(float x, float y, float width, float height) {
	//Base case
	if (width < 3) {
		return;
	}

	//Draw a square
	rectangle(x, y, width, height);

	//Multiplier
	float d = 2.125;

	//Recrusive calls
	shrinkingSquares(x-width/(d*2), y-height/(d*2), width/d, height/d);
	shrinkingSquares(x+width-width/(d*2), y-height/(d*2), width/d, height/d);
	shrinkingSquares(x+width-width/(d*2), y+height-height/(d*2), width/d, height/d);
	shrinkingSquares(x-width/(d*2), y+height-height/(d*2), width/d, height/d);
}

void spiralSquares(float r, float theta, float width, float height) {
	//Base case
	if (width < 1) {
		return;
	}
	
	//Draws the rectangle
	rectangle(r*cos(theta)+size/2, -r*sin(theta)+size/2, width, height);

	//Multiplier
	float m = 0.9;
	
	//Recursive call
	spiralSquares(m*r, theta-pi/6, m*width, m*height);
}

void circularLace(float x, float y, float r) {
	//Base case
	if (r < 1) {
		return;
	}

	//Draws the circle to the screen
	gfx_circle(round(x+size/2), round(y+size/2), round(r));

	//Multiplier
	float m = 1.0/3;
	
	//Recursive calls
	for (int i = 0; i < 6; i++) {
		circularLace(x+r*cos(i*pi/3), y-r*sin(i*pi/3), m*r);
	}
}

void snowflake(float x, float y, float r) {
	//Base case
	if (r < 1) {
		return;
	}
	
	//Multiplier
	float s = 2*pi/5;

	//Draws lines to the screen and recursive calls
	for (int i = 0; i < 5; i++) {
		gfx_line(x+size/2, y+size/2, x+r*cos(i*s-s-pi/2)+size/2, y-r*sin(i*s-s-pi/2)+size/2);
		snowflake(x+r*cos(i*s-s-pi/2), y-r*sin(i*s-s-pi/2), 1.0*r/3);
	}
}

void tree(float x, float y, float r, float theta) {
	//Base case
	if (r < 1) {
		return;
	}

	//Draws lines to the screen
	gfx_line(x, y, x+r*cos(theta), y-r*sin(theta));

	//Recursive calls
	tree(x+r*cos(theta), y-r*sin(theta), r/1.5, theta+pi/6);
	tree(x+r*cos(theta), y-r*sin(theta), r/1.5, theta-pi/6);
}

void fern(float x, float y, float r, float theta, float shift) {
	//Base case
	if (r < 2) {
		return;
	}

	//Draws lines to the screen
	gfx_line(x, y, x+r*cos(theta), y-r*sin(theta));

	//Multiplier
	float m = 3.25;

	//Recursive calls
	for (int i = 0; i < 4; i++) {
		fern(x+r*(i+1)/4*cos(theta), y-r*(i+1)/4*sin(theta), r/m, theta+pi/6, shift/2.0);
		fern(x+r*(i+1)/4*cos(theta), y-r*(i+1)/4*sin(theta), r/m, theta-pi/6, shift/2.0);
	}
}

void spiralOfSpirals(float x, float y, float theta) {
	//Draws point to screen
	point(x, y);
       
	double r;
      
	//Multipliers
	float d = 4.95;
	float e = 1.95;
	float f = 1.5;

	//Base Case 
	if(exp(theta/(e*pi))/f < 1) {
		return;
	}

  for (float t = 0; t < theta; t += pi/d) {
		r = exp(t/(e*pi))/f;
		//Recursive calls which draw a larger spiral around a smaller one
		spiralOfSpirals(x+r*cos(t), y-r*sin(t), t-e*pi-pi/d);
	}
}
