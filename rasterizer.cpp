#include <cstdio>
#include <cstdlib>

#include "rasterizer_io.h"
#include "barycentric.h"

#define _USE_MATH_DEFINES

#include <cmath>

/*
 *
 * An implementation of a 2D rasterizer. There are 6 parts, each split up with its own function.
 * See barycentric.h for the function that calculates the barycentric coordinates.
 * On the other hand, rasterizer_io.h contains printing out a simple ppm header and reading the earth file.
 * 
*/


// Width and height of the image that is going to be built.
const int width = 128;
const int height = 128;

// Vec2 and Vec3 are defined in barycentric.h represeting a 2d and 3d vector respectively.
// Create the triangle vertices.
Vec2 v0 = {61, 10};
Vec2 v1 = {100, 100};
Vec2 v2 = {25, 90};

/*
 *
 * First part of the assignment; rasterising an image.
 * 
*/
void partA()
{
    // Initialise file to write.
    std::ofstream ppm("abg.ppm");
    write_ppm_header(&ppm);

    // For each pixel
    for (int j = height; j > 0; --j)
    {
        for (int i = width; i > 0; --i) 
        {
            // Create barycentric coordinates
            Vec2 p = {i, j};
            double* bary = create_bary_co(v0, v1, v2, p); // Create barycentric coordinates. See barycentric.h
            
            // Get the coordinates
            double alpha = bary[0];
            double beta = bary[1];
            double gamma = bary[2];

            // Get the colours from coordinates
            double alphar = alpha * 100 + 100;
            double betag = beta * 100 + 100;
            double gammab = gamma * 100 + 100;

            // The background is yellow, so to get the correct colour, subtract the found colour from yellow.
            int r = 255 - alphar;
            int g = 255 - betag;
            int b = 192 - gammab;

            // Squish the values to [0, 255] 
            if (r < 0)
                r=abs(r);

            if (g < 0)
                g=abs(g);

            if (b < 0)
                b=abs(b);

            // Write the colours.
            ppm << (int)r << " " << (int)g << " " << (int)b << " ";
        }
        ppm << '\n';
        
    }
    ppm.close();
}

/*
 *
 * Second part of the assignment; half plane test.
 * 
*/
void partB()
{
    // Initialise file to write. 
    std::ofstream hpppm("halfplane.ppm");
    write_ppm_header(&hpppm);

    // For every pixel
    for (int j = height; j > 0; --j)
    {
        for (int i = width; i > 0; --i) 
        {

            // Get the barycentric coordinates
            Vec2 p = {i, j};
            
            double* bary = create_bary_co(v0, v1, v2, p); // Create barycentric coordinates. See barycentric.h
            
            double alpha = bary[0];
            double beta = bary[1];
            double gamma = bary[2];

            // Perform half plane test
            if (alpha < 0)
            {
                hpppm << 0 << " ";
            }
            else
            {
                hpppm << 255 << " ";
            }

            if (beta < 0)
            {
                hpppm << 0 << " ";
            }
            else
            {
                hpppm << 255 << " ";
            }

            if (gamma < 0)
            {
                hpppm << 0 << " ";
            }
            else
            {
                hpppm << 255 << " ";
            }
        }
        hpppm << '\n';
    }
    hpppm.close();
}

/*
 *
 * Third part of the assignment; colouring using half plane test.
 * 
*/
void partC()
{
    // Initialise file to write. 
    std::ofstream tri("triangle.ppm");
    write_ppm_header(&tri);
    // For every pixel
    for (int j = height; j > 0; --j)
    {
        for (int i = width; i > 0; --i) 
        {

            // Get the barycentric coordinates

            Vec2 p = {i, j};
            
            double* bary = create_bary_co(v0, v1, v2, p); // Create barycentric coordinates. See barycentric.h
            
            double alpha = bary[0];
            double beta = bary[1];
            double gamma = bary[2];

            // Perform a test, if the alpha, beta or gamma are negative then outside triangle.
            if (alpha < 0 || beta < 0 || gamma < 0)
            {
                tri << 255 << " " << 255 << " " << 255 << " ";
            }
            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                tri << 0 << " " << 0 << " " << 0 << " ";
            }
        }
        tri << '\n';
    }
    tri.close();
}

/*
 *
 * Fourth part of the assignment; colouring a rgb triangle.
 * 
*/
void partD()
{
    // Initialise file to write.
    std::ofstream rgb("rgb.ppm");

    write_ppm_header(&rgb);

    // Colour values
    Vec3 c0 = {255, 0, 0};
    Vec3 c1 = {0, 255, 0};
    Vec3 c2 = {0, 0, 255};

    // For every pixel.
    for (int j = height; j > 0; --j)
    {
        for (int i = width; i > 0; --i) 
        {
            // Get the barycentric coordinates
            Vec2 p = {i, j};
            
            double* bary = create_bary_co(v0, v1, v2, p); // Create barycentric coordinates. See barycentric.h
            
            double alpha = bary[0];
            double beta = bary[1];
            double gamma = bary[2];
            
            // Half plane test
            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                // Get the red, green and blue values.
                double r = alpha * c0[0] + beta * c1[0] + gamma * c2[0];
                double g = alpha * c0[1] + beta * c1[1] + gamma * c2[1];
                double b = alpha * c0[2] + beta * c1[2] + gamma * c2[2];

                rgb << (int)r << " " << (int)g << " " << (int)b << " ";
            }
            else
            {
                rgb << 0 << " " << 0 << " " << 0 << " ";
            }
        }
        rgb << '\n';
    }

    rgb.close();
}
/*
 *
 * Fifth part of the assignment; texture coordinates.
 * 
*/
void partE()
{
    // Create a lookup array by loading all the pixels in a 3D array.
    double earthCoords[256][512][3];
    readEarthPPM(earthCoords);// Read the file see rasterizer_io.h

    std::ofstream texture("texture.ppm");

    write_ppm_header(&texture);

    for (int j = height; j > 0; --j)
    {
        for (int i = width; i > 0; --i)        
        {

            // Get the barycentric coordinates
            Vec2 p = {i, j};
            double* bary = create_bary_co(v0, v1, v2, p); // Create barycentric coordinates. See barycentric.h
            
            double alpha = bary[0];
            double beta = bary[1];
            double gamma = bary[2];

            // If within the triangle get the texture.
            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                // Get global coordinates using U,V
                double Puvx = alpha * 0.160268 + beta * 0.083611 + gamma * 0.230169;
                double Puvy = alpha * 0.290086 + beta * 0.159907 + gamma * 0.222781;

                // Multiply by image width and height to get the correct indices.
                int px = Puvx * 512;
                int py = Puvy * 256;

                texture << earthCoords[py][px][0] << " " << earthCoords[py][px][1] << " " << earthCoords[py][px][2] << " ";
            }
            else
            {
                texture << 0 << " " << 0 << " " << 0 << " ";
            }
        }
        texture << '\n';
    }

    texture.close();
}
/*
 *
 * Sixth part of the assignment; finding the building.
 * 
*/
void partF()
{
    // Read the earth.ppm and initialise the array.
    double earthCoords[256][512][3];
    readEarthPPM(earthCoords);

    // For every pixel.
    for (int j = height; j > 0; --j)
    {
        for (int i = width; i > 0; --i) 
        {
            Vec2 p = {i, j};
            
            double* bary = create_bary_co(v0, v1, v2, p); // Create barycentric coordinates. See barycentric.h
            
            double alpha = bary[0];
            double beta = bary[1];
            double gamma = bary[2];

            // If its within the triangle
            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {

                long double Puvx = alpha * 0.160268 + beta * 0.083611 + gamma * 0.230169;
                long double Puvy = alpha * 0.290086 + beta * 0.159907 + gamma * 0.222781; 

                int px = Puvx * 512;
                int py = Puvy * 256;
                
                // Find the correct pixel.
                if(i == 62 && j == 65)
                {
                    // ~ (50 -123)
                    // Somewhere in Vancouver, Canada - Port of Vancouver?
                    // Using s = (THETA + PI)/2*PI and t = (PHI + PI/2) / PI
                    long double theta = (Puvx *(2L*M_PI)) - M_PI;  // longtitude
                    long double phi = (M_PI/2L)-(Puvy * M_PI);  // latitude

                    long double lng = theta*(180L/M_PI);//Convert to degrees.
                    long double lat = phi*(180L/M_PI);//Convert to degrees.

                    // Print latitude, and longtitude
                    std::cout << "lat/lng: " << lat << ", " << lng << std::endl;
                    std::cout << "Building: Port of Vancouver" << std::endl;
                }
            }
        }
    }
}

// Main loop, execute everything.
int main()
{
    partA();
    partB();
    partC();
    partD();
    partE();
    partF();
    return 0;
}