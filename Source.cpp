
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define n 3


enum colors {RED, BLUE, YELLOW, GREEN, WHITE, BLACK, PURPLE};

struct coordinate
{
	float x;
	float y;
	colors col;
	
};


//Prototypes
const char* getColName(colors col);
int sortByCol(coordinate* coord);
int findDist(coordinate coord[]);
double countDistance(const coordinate & p1, const coordinate & p2);
//End Prototypes

int main()
{
	coordinate points[n];

	printf("Enter %d points.\n", n);
	puts("You should enter digits for X and Y and a corresponding value for color.");
	puts("0 - RED, 1 - BLUE, 2 - YELLOW, 3 - GREEN, 4 - WHITE, 5 - BLACK, 6 - PURPLE;");
	puts("Example of an input sequence: 1.8 58 0");
	for (int i = 0; i < n; i++)
	{
		printf("-P%d-\n", i+1);
		scanf_s("%f%f%d", &points[i].x, &points[i].y, &points[i].col);
	}


	sortByCol(points);
	puts("Points were grouped by colors.");

	for (int i = 0; i < n; i++)
	{
		printf("P%d %.2f %.2f %s\n", i+1, points[i].x, points[i].y, getColName(points[i].col));
	}

	findDist(points);

	system("pause");
	return 0;
}


/* Takes a value of enumeration "color" type and returns a correaponding string value. */
const char* getColName(colors col)
{
	switch (col)
	{
	case RED:
		return "RED";
	case BLUE:
		return "BLUE";
	case YELLOW:
		return "YELLOW";
	case GREEN:
		return "GREEN";
	case WHITE:
		return "WHITE";
	case BLACK:
		return "BLACK";
	case PURPLE:
		return "PURPLE";
	default: 
		return "UNKNOWN COLOR";
	}
}

/* Takes a pointer to the first element of array of "coordinate" elements and groups the array
   by colors. */
int sortByCol(coordinate* coord)
{
	coordinate temp;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		if ((coord + j)->col >(coord + j + 1)->col)
		{

			temp = *(coord + j);
			*(coord + j) = *(coord + j + 1);
			*(coord + j + 1) = temp;
		}
	}
	return 0;
};

/* Takes a pointer to the first element of array of "coordinate" elements and finds least distance 
   between two points of each color if there are more than 1 point of this color. */
int findDist(coordinate coord[])
{
	float maxDist;
	float dist = 0, x, y;
	int point1 = -1, point2 = -1;
	int flags[n];


	for (int i = 0; i < n; i++) flags[i] = false;


	for (int i = 0; i < n; i++)
	{
		if (!flags[i])
		{
			maxDist = 0;
			point1 = -1;
			point2 = -1;
			for (int j = 0; j < n; j++)
			{
				if (coord[i].col == coord[j].col)
				{
						flags[j] = true;
						dist = countDistance(coord[i], coord[j]);
				

					if ((dist > maxDist) && (i != j))
					{
							maxDist = dist;
							point1 = i;
							point2 = j;
					}
				}
			}
			flags[i] = true;
			if(point1 != -1) printf("The biggest distance of color %s is %5.2f between P%d and P%d.\n", getColName(coord[point1].col), maxDist, point1 + 1 , point2 + 1);
		}
		else
		{
			continue;
		}
	}
	return 0;
}

/* Takes two points and counts distance between them. */
double countDistance(const coordinate & p1, const coordinate & p2)
{
	return sqrt(pow(p1.x - p2.x, 2.0) + pow(p1.y - p2.y, 2.0));
}