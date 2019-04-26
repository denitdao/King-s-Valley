#pragma once
#include "pch.h"

// screen settings
constexpr float ASPECT_RATIO = 3.f / 4.f;
constexpr float WINDOW_SIZE_X = 1024.f;
constexpr float WINDOW_SIZE_Y = WINDOW_SIZE_X * ASPECT_RATIO;

// map settings
constexpr int MAP_SIZE_X = 32;
constexpr int MAP_SIZE_Y = 24;
constexpr float BLOCK_SIZE_X = WINDOW_SIZE_X / MAP_SIZE_X;
constexpr float BLOCK_SIZE_Y = WINDOW_SIZE_Y / MAP_SIZE_Y;

// player settings
constexpr float PLAYER_SIZE_X = WINDOW_SIZE_X / MAP_SIZE_X;
constexpr float PLAYER_SIZE_Y = WINDOW_SIZE_Y / MAP_SIZE_Y * 2;

// gravity settings
static float gravity_speed = -0.45f;
static float x_move_speed = 0.2f;
static float jump_change_step = 0.001f;

constexpr float GRAVITY_SPEED_CONST = -0.45f;
constexpr float X_MOVE_SPEED_CONST = 0.2f;
constexpr float JUMP_CHANGE_STEP_CONST = 0.001f;

// enums
typedef enum direction { toleft = -1, none = 0, toright = 1 } t_direcrion;
typedef enum condition {normal, inJump, onStairs} t_condition;
typedef enum collided { xcoll, ycoll, no, colliding } t_collided;
typedef enum heroMovement {} t_heroMovement;
typedef enum mummyMovement {} t_mummyMovement;
typedef enum texture { noTexture = 0, wall = 1, stairLeftUnder = 2, stairLeft = 3, stairLeftTop = 4, stairRightUnder = 5, stairRight = 6, stairRightTop = 7, hardWall = 8 } t_texture;

