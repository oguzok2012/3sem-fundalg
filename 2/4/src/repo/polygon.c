#include "../../include/repo.h"


typedef struct {
    double x, y;
} Point;


double CrossProduct(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}


bool IsConvexPolygon(int num_points, ...) {
    va_list args;
    va_start(args, num_points);

    Point points[num_points];
    for (int i = 0; i < num_points; i++) {
        points[i].x = va_arg(args, double);
        points[i].y = va_arg(args, double);
    }
    va_end(args);

    int sign = 0;

    for (int i = 0; i < num_points; i++) {
        double cross_product = CrossProduct(
            points[i], 
            points[(i + 1) % num_points], 
            points[(i + 2) % num_points]
        );
        
        if (cross_product > 0) {
            if (sign < 0) {
                printf("Polygon is NOT convex\n");
                return false;
            }
            sign = 1;
        } else if (cross_product < 0) {
            if (sign > 0) {
                printf("Polygon is NOT convex\n");
                return false;
            }
            sign = -1;
        }
    }
    printf("Polygon IS convex\n");
    return true;
}
