#include <iostream>
#include <string>
#include <fstream>

/**
 * 
 *  A simple header file containing function to write header to ppm file, and reading the earth.ppm file.
 * 
*/

/**
 * 
 * Simple function that writes the header, so I only have to change it in one place.
 *  
*/
void write_ppm_header(std::ofstream* file)
{
    *(file) << "P3" << '\n';
    *(file) << "#Oskar Mampe" << '\n';
    *(file) << "128 128" << '\n';
    *(file) << "255" << '\n';
}

/**
 * 
 * Read the earth.ppm file.
 *  
*/
void readEarthPPM(double earthCoords[512][256][3])
{
    // Open the stream
    std::ifstream earth("earth.ppm");

    // Read the first 4 lines
    // They're not particularly necessary as the height, width can be hardcoded
    std::string line;
    std::getline(earth, line);
    std::getline(earth, line);
    std::getline(earth, line);
    std::getline(earth, line);

    // Initialise variables to read.
    double r, g, b;
    int x = 0;// row
    int y = 0;// column

    // For each pixel read
    while(earth >> r >> g >> b)
    {
        // Append to array
        earthCoords[x][y][0] = r;
        earthCoords[x][y][1] = g;
        earthCoords[x][y][2] = b;

        // Reset the rows
        if (y == 255){
            y = -1;
            x++;
        }
        y++;

        // If end of file, stop reading
        if (earth.eof())
        {
            break;
        }
    }
    earth.close();
}
