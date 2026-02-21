#include <iostream>
#include <stdint.h>
#include <cmath>
#include <ctime>
#include <map>
#include "epsim.h"
#include "ws.h"

#define JUPITER_RADIUS_IN_PIXELS 15             // Largest planet
#define NEPTUNE_ORBITAL_RADIUS_IN_PIXELS 440    // Largest orbit
#define J2000_UNIX 946728000
#define SECONDS_IN_DAY 86400

//                          M       V       E       M       J       S       U       N
float planet_radius[8] =    {0.035, 0.087,  0.091,  0.049,  1.0,    0.83,   0.363,  0.352};     // Relative to Jupiter's radius
float radius_mod[8] =       {4,     3,      3,      3,      .9,      .9,      .9,   .9};        // Scale radius
float planet_distance[8] =  {0.013, 0.024,  0.033,  0.051,  0.173,  0.317,  0.639,  1.0};       // Relative to Neptune's orbital radius
float distance_mod[8] =     {2,     2,      2,      2,      1.2,      1,      1,    1};

double orbital_periods[8] = {
    87.9691,
    224.701,
    365.25636,
    686.980,
    4332.589,
    10759.22,
    30688.5,
    60182
};

double initial_angles[8] = {
    360.0 - 358.3,
    360.0 - 250.1,
    0.0,
    360.0 - 187.8,
    360.0 - 228.3,
    360.0 - 297.4,
    360.0 - 142.6,
    360.0 - 261.9,
};

double getDaysSinceJ2000()
{
    std::time_t now = std::time(nullptr);
    double seconds = difftime(now, (std::time_t)J2000_UNIX);
    std::cout << seconds/SECONDS_IN_DAY << std::endl;
    return seconds/SECONDS_IN_DAY;
}

double planetAngle(double orbital_period)
{
    double days = getDaysSinceJ2000();
    double orbit_frac = fmod(days, orbital_period) / orbital_period;
    double angle = orbit_frac * 360.0;
    
    // Clockwise is positive
    angle = 360 - angle;

    // Normalize within 360 deg
    angle = fmod(angle, 360.0);
    if (angle < 0)
    {
        angle+= 360.0;
    }

    // put 0 deg at top
    return angle - 90;
}

typedef struct 
{
    int x;
    int y;
} vec2;

// What angle from vertical, percent to edge of display (0-300 in horizontal)
vec2 deg2coords(float deg, int distance)
{
    const int center_x = 200;
    const int center_y = 150;

    vec2 res = {0, 0};

    float rad = deg*0.01745329;

    float x = std::cos(rad) * (distance);
    float y = std::sin(rad) * (distance);
    x = x + center_x;
    y = y + center_y;
    res.x = static_cast<int>(x);
    res.y = static_cast<int>(y);

    return res;
}

int main() {
    std::cout << "---- epaper-orrery ----" << std::endl;

    Ws ws;              // "Waveshare" object contains c functions from waveshare's library (draw line, circle...)
    Epsim e(400, 300);  // E-paper "simulator" creates a PNG using the data from waveshare object

    // Placeholder for sun (really big)
    // ws.Paint_DrawCircle(200, 150, (9.96*JUPITER_RADIUS_IN_PIXELS), BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY); 

    
    std::string planet_names[8] = {"Mercury\t", "Venus\t", "Earth\t", "Mars\t", "Jupiter\t", "Saturn\t", "Uranus\t", "Neptune\t"};

    std::cout << "Planet\tOrbital Radius\tPlanet Radius" << std::endl;

    // Iterate over planets
    for (int i = 0; i < 8; ++i)
    {
        // Draw orbit line
        int orbital_radius_px = (distance_mod[i]*planet_distance[i])*NEPTUNE_ORBITAL_RADIUS_IN_PIXELS;
        ws.Paint_DrawCircle(200, 150, orbital_radius_px, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY); 

        // Draw planet & outline
        int planet_radius_px = (radius_mod[i]*planet_radius[i])*JUPITER_RADIUS_IN_PIXELS;
        int outline_radius_px = planet_radius_px + i;
        
        // Find x, y coords on canvas corresponding to planet's distance
        vec2 pos = deg2coords(planetAngle(orbital_periods[i])+initial_angles[i], orbital_radius_px);

        ws.Paint_DrawCircle(pos.x, pos.y, outline_radius_px, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        ws.Paint_DrawCircle(pos.x, pos.y, planet_radius_px, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);


        std::cout << planet_names[i] << ": \t" << orbital_radius_px << ", \t" << planet_radius_px << std::endl;
    }

    e.Image2Vector(ws.m_paint.Image, ws.m_imagesize);
    e.Save("image.png");

    return 0;
}