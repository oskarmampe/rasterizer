# University of Leeds 2019-2020
# COMP 5812M Assignment 3
# Oskar Mampe
# 201368087
#

This project is very simple to execute, as it does not contain many source files. First, compile the files

[userid@machine Assignment3Rasterizer]$ make

This will make create a binary file called rasterizer. Execute the file:

[userid@machine Assignment3Rasterizer]$ ./rasterizer

This will create all the ppm files: abg.ppm, halfplane.ppm, triangle.ppm, rgb.ppm, texture.ppm.
The binary will also print to the console the lat/long coordinates of the building, as well as the building name for part f).

Description of each part:

a) Rendering all the pixels using the triangle vertices to calculate baycentric coordinates. 
Then, the colour was calculated using the formula given, i.e. red = 100 + alpha * 100 etc.
Lastly, I took away the calculated colour from the colour yellow, as if the background is yellow, the resulting colour will be whatever the background is minus calculated colour.
Any RGB values under 255 have been taken the absolute value of.

b) Demostrating half-plane test by rendering everything outside the triangle in the colour calculated using barycentric coordinates.

c) Demostrating half-plane test by rendering a triangle in black and the background in white.

d) Using the half-plane test to colour the triangle in RGB by interpolation, and rendering the background in white.

d) By file, I assumed earth.ppm. Using the U,V coordinates given, calculate the index i and j by multiplying by width and height respectively. The triangle given, is then given the texture of the earth.

e) To find the lat and long I have used a formula to convert from U,V coordinates to a point in the sphere. That point will of course be in radians, and long/lat are in degrees so conversion is needed. I have found the building to be Port of Vancouver/Canada Place.

