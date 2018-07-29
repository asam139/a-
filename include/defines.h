//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __DEFINES_H__
#define __DEFINES_H__ 1

#include <math.h>
#include <algorithm>
#include <mathlib/vec2.h>

#define NOMINMAX

#define GAME_NAME "Steering Behaviors Demo"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

#define WINDOW_HALF_WIDTH WINDOW_WIDTH * 0.5
#define WINDOW_HALF_HEIGHT WINDOW_HEIGHT * 0.5

//Size of screen in tiles
#define COST_MAP_WIDTH 128
#define COST_MAP_HEIGHT 128
#define TILED_SIZE 8
#define MAX_PATH_SIZE 512

#define TICKS_PER_SECOND 30
#define MAX_FRAME_SKIP 10

#define FOREGROUND_COLOR { 0, 0, 0, 255 }
#define SHADOW_COLOR {160, 160, 160, 255}

#define FONT_FILE "../media/8bit.ttf"
#define AGENT_BLUE_PATH "../media/agent_blue.png"
#define AGENT_RED_PATH "../media/agent_red.png"
#define AGENT_GREEN_PATH "../media/agent_green.png"
#define AGENT_PURPLE_PATH "../media/agent_purple.png"

#define SOLDIER_PATH "../media/soldier.bmp"
#define SLAVE_PATH "../media/slave.bmp"
#define GUARD_PATH "../media/guard.bmp"
#define MAP_PATH "../media/map.bmp"
#define COST_MAP_PATH "../media/cost_map.bmp"

#define FPS_FONT_SIZE 12

#define SCENE_NUMBER 1

struct tiledPosition {
    int x;
    int y;
};

struct KinematicStatus {
    MathLib::Vec2 position { 0.0f, 0.0f };
    MathLib::Vec2 velocity { 0.0f, 0.0f }; //linear velocity
    MathLib::Vec2 acceleration { 0.0f, 0.0f }; //linear acceleration
    float orientation = 0;
    float angularAcceleration = 0; //angular velocity
    float speed = 0; // for manual movement
};

struct KinematicSteering {
    MathLib::Vec2 acceleration { 0.0f, 0.0f }; //linear velocity
    float angularAcceleration = 0; //angular velocity
};


template <typename T>
inline T clamp(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

inline MathLib::Vec2 rotate2D(const MathLib::Vec2& pivot, const MathLib::Vec2& point, const float angle) {
  const float s = sin(angle);
  const float c = cos(angle);

  return MathLib::Vec2(c * (point.x() - pivot.x()) - s * (point.y() - pivot.y()) + pivot.x(),
                       s * (point.x() - pivot.x()) + c * (point.y() - pivot.y()) + pivot.y());
}

//random value between two numbers
inline float randomFloat(float a, float b) {
  const float random = ((float)rand()) / (float)RAND_MAX;
  return a + (random * (b - a));
}

//wrap an angle between [-PI, PI)
inline float wrapAnglePI(double x) {
  x = fmod(x + M_PI, M_PI * 2.0f);
  if (x < 0) x += M_PI * 2.0f;
  return x - M_PI;
}

//returns (-1, 0 , 1), the sign of the number
template <typename T> int sign(T val) {
  return (T(0) < val) - (val < T(0));
}

#endif