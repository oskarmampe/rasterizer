#include <iostream>

/**
 * 
 *  A simple header file containing function to calculate the barycentric coordinates.
 * 
*/

// Typedefs for clarity.
typedef double Vec2[2];
typedef double Vec3[3];

/**
 * 
 * Create barycentric coordinates from the 3 triangle vertices and a point p.
 * 
*/
double* create_bary_co(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 p)
{
    // Unpack for clarity, easier to read.
    double Ax = v0[0];
    double Ay = v0[1];
    double Bx = v1[0];
    double By = v1[1];
    double Cx = v2[0];
    double Cy = v2[1];

    int Px = p[0];
    int Py = p[1];

    // The area stays constant, as each barycentric coordinate is a ratio of a mini-triangle and the outermost triangle.
    double area = ((By - Cy) * (Ax - Cx)) + ((Cx - Bx) * (Ay - Cy));

    // Calculate the alpha and beta by cross product.
    double alpha = ((By - Cy) * (Px - Cx)) + ((Cx - Bx) * (Py - Cy));
    double beta = ((Cy - Ay) * (Px - Cx)) + ((Ax - Cx) * (Py - Cy));

    // Normalise to [0,1]
    alpha /= area;
    beta /= area;

    // Only 2 barycentric coordinates are needed, the third one is free.
    double gamma = 1 - alpha - beta;

    // Pack and return.
    double* bary = new double[3];
    bary[0] = alpha;
    bary[1] = beta;
    bary[2] = gamma;
    return bary;
}