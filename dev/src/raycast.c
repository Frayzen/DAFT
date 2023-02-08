#include "../include/raycast.h"





double dotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
//returns 0 : the ray and plane are almost parallel
//
//returns 1 : we have detected the intersection, its coordinates are stored in
//           intersetion parameter
int intersectionRayPlane(Ray ray, Plane plane, point *intersection) {
    
    //check if plane and ray are parallel
    double d = dotProduct(plane.normal, ray.direction);
    if (fabs(d) < 1e-6) {
        return 0;
    }
    double t = -(dotProduct(plane.normal, ray.origin) + plane.d) / d;
    if (t < 0) {
        return 0;
    }
    intersection->x = ray.origin.x + t * ray.direction.x;
    intersection->y = ray.origin.y + t * ray.direction.y;
    intersection->z = ray.origin.z + t * ray.direction.z;
    return 1;
}


/*int Raycast(Point p1, Point p2, Point p3, Ray ray)
{
    //TODO
}*/
