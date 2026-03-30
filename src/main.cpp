#include <iostream>
#include <stdint.h>
#include <cmath>
#include <ctime>
#include <map>
#include <array>
#include <string>
#include "astronomy.h"
#include "epsim.h"
#include "ws.h"

#define JUPITER_RADIUS_IN_PIXELS 15             // Largest planet
#define NEPTUNE_ORBITAL_RADIUS_IN_PIXELS 440    // Largest orbit
#define J2000_UNIX 946728000
#define SECONDS_IN_DAY 86400

typedef struct 
{
    int x;
    int y;
} vec2;

static const std::array<astro_body_t, 8> planets = { BODY_MERCURY, BODY_VENUS, BODY_EARTH, BODY_MARS, BODY_JUPITER, BODY_SATURN, BODY_URANUS, BODY_NEPTUNE };
static const std::array<std::string, 8> planet_names = { "Mercury","Venus","Earth","Mars","Jupiter","Saturn","Uranus","Neptune" };
static const bool darkmode = true;


vec2 get_good_center()
{
    const int max_shift_x = 100;
    const int max_shift_y = 100;
    // average jupiter, saturn, uranus, neptune to shift orrery for all planets to be visible
    double outer_planet_sum = 0;
    double outer_planet_avg;

    astro_time_t time = Astronomy_CurrentTime();
    for (size_t i = 0; i < planets.size(); ++i)
    {
        astro_vector_t position = Astronomy_HelioVector(planets[i], time);
        double angle = std::atan2(position.y, position.x);
        double deg = angle * 180.0 / 3.1415926535;
        if (deg < 0.0) deg += 360.0;
        deg = 360 - deg;

        if (i >= 4)
        {
            outer_planet_sum += deg;
        }

        // std::cout << planet_names[i] << "angle = " << deg << "\n";
    }

    outer_planet_avg = outer_planet_sum / 4;
    
    double outer_planet_avg_d = outer_planet_avg*0.01745329;
    printf("%f\n", outer_planet_sum);
    printf("%f\n", outer_planet_avg_d);
    printf("%f\n", std::cos(outer_planet_avg_d));
    vec2 shift = {std::cos(outer_planet_avg_d) * -max_shift_x, std::sin(outer_planet_avg_d) * -max_shift_y};

    return shift;

}


//
//
//                          M       V       E       M       J       S       U       N
float planet_radius[8] =    {0.035, 0.087,  0.091,  0.049,  1.0,    0.83,   0.363,  0.352};     // Relative to Jupiter's radius

float planet_distance[8] =  {0.013, 0.024,  0.033,  0.051,  0.173,  0.317,  0.639,  1.0};       // Relative to Neptune's orbital radius

// looks ok
// float radius_mod[8] =       {4,     3,      3,      3,      .9,      .9,      .9,   .9};
// float distance_mod[8] =     {2,     2,      2,      2,      1.2,      1,      .6,    .45};

float radius_mod[8] =       {4,     3,      3,      3,      .9,      .9,      .9,   .9};
float distance_mod[8] =     {2,     2,      2,      2,      1.2,      1,      .67,    .53};

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
    // std::cout << seconds/SECONDS_IN_DAY << std::endl;
    return seconds/SECONDS_IN_DAY;
}

double planetAngle2(int planet_i)
{
    astro_time_t time = Astronomy_CurrentTime();

    astro_vector_t position = Astronomy_HelioVector(planets[planet_i], time);
    double angle = std::atan2(position.y, position.x);
    double deg = angle * 180.0 / 3.1415926535;    
    if (deg < 0.0) deg += 360.0;
    deg = 360 - deg;

    // printf("%d: %.1f\n", planet_i, deg);

    return deg;

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
        angle += 360.0;
    }

    // put 0 deg at top
    return angle - 90;
}



// What angle from vertical, percent to edge of display (0-300 in horizontal)
vec2 deg2coords(float deg, int distance, vec2 offset = {0, 0})
{
    const int center_x = 200 + offset.x;
    const int center_y = 150 + offset.y;

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

    // std::cout << "from astronomy engine:\n";
    vec2 offset = get_good_center();
    // vec2 offset = {0,0};

    printf("offset: (%d,%d)\n", offset.x, offset.y);



    Ws ws(darkmode);    // "Waveshare" object contains c functions from waveshare's library (draw line, circle...)
    Epsim e(400, 300);  // E-paper "simulator" creates a PNG using the data from waveshare object

    // ws.Paint_NewImage()

    // Placeholder for sun (really big)
    // ws.Paint_DrawCircle(200, 150, (9.96*JUPITER_RADIUS_IN_PIXELS), BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY); 

    // Iterate over planets
    for (int i = 0; i < 8; ++i)
    {
        // Draw orbit line
        int orbital_radius_px = (distance_mod[i]*planet_distance[i])*NEPTUNE_ORBITAL_RADIUS_IN_PIXELS;
        printf("Paint_DrawCircle(%d, %d, %d, %s, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);\n", 200 + offset.x, 150 + offset.y, orbital_radius_px, darkmode ? "WHITE" : "BLACK");
        ws.Paint_DrawCircle(200 + offset.x, 150 + offset.y, orbital_radius_px, darkmode ? WHITE : BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY); 

        // Draw planet & outline
        int planet_radius_px = (radius_mod[i]*planet_radius[i])*JUPITER_RADIUS_IN_PIXELS;
        int outline_radius_px = planet_radius_px + i;
        
        // Find x, y coords on canvas corresponding to planet's distance
        // vec2 pos = deg2coords(planetAngle(orbital_periods[i])+initial_angles[i], orbital_radius_px);
        // vec2 pos = deg2coords(planetAngle2(i), orbital_radius_px);
        vec2 pos = deg2coords(planetAngle2(i), orbital_radius_px, offset);

        printf("Paint_DrawCircle(%d, %d, %d, %s, DOT_PIXEL_1X1, DRAW_FILL_FULL);\n", pos.x, pos.y, outline_radius_px, darkmode ? "BLACK" : "WHITE");
        printf("Paint_DrawCircle(%d, %d, %d, %s, DOT_PIXEL_1X1, DRAW_FILL_FULL);\n", pos.x, pos.y, outline_radius_px, darkmode ? "WHITE" : "BLACK");
        ws.Paint_DrawCircle(pos.x, pos.y, outline_radius_px, darkmode ? BLACK : WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        ws.Paint_DrawCircle(pos.x, pos.y, planet_radius_px, darkmode ? WHITE : BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }

    e.Image2Vector(ws.m_paint.Image, ws.m_imagesize);
    e.Save("image.png");

    return 0;
}