#include <math.h>
#include "architecture.h"




typedef struct
{
    double x, y,z;
}Vector;


typedef struct {
    Vector normal;
    double d;
} Plane;

typedef struct
{
    Vector origin;
    Vector direction;
}Ray;

double dotProduct(Vector a, Vector b);


//detect intersection between the Ray ray and the plane 
//returns 
int intersectRayPlane(ray ray, Plane plane, point *intersection);
//int Raycast(point int p1, point p2, point p3, Ray);

