#pragma once
#include "pch.h"

// screen settings
constexpr float ASPECT_RATIO = 3.f / 4.f;
constexpr float WINDOW_SIZE_X = 1024.f;
constexpr float WINDOW_SIZE_Y = WINDOW_SIZE_X * ASPECT_RATIO;

// map settings
constexpr int MAX_MAP_SIZE_X = 64;
constexpr int MAP_SIZE_X = 32;
constexpr int MAP_SIZE_Y = 24;
constexpr float BLOCK_SIZE_X = WINDOW_SIZE_X / MAP_SIZE_X;
constexpr float BLOCK_SIZE_Y = WINDOW_SIZE_Y / MAP_SIZE_Y;
static bool xRay = false;
static int lives = 3;
// player settings
constexpr float PLAYER_SIZE_X = WINDOW_SIZE_X / MAP_SIZE_X;
constexpr float PLAYER_SIZE_Y = (WINDOW_SIZE_Y / MAP_SIZE_Y) * 2;

// gravity settings
static float gravity_speed = 0.f;
static float x_move_speed = 0.f;
static float jump_change_step = 0.f;
static float stair_move_speed = 0.f;
//Denys
constexpr float GRAVITY_SPEED_CONST = -4.5f;
constexpr float X_MOVE_SPEED_CONST = 1.4f;
constexpr float JUMP_CHANGE_STEP_CONST = 0.09f;
//Alex
constexpr float GRAVITY_SPEED_CONST1 = -4.7f;
constexpr float X_MOVE_SPEED_CONST1 = 4.0f;
constexpr float JUMP_CHANGE_STEP_CONST1 = 0.12f;
// enums
typedef enum direction { toleft = -1, none = 0, toright = 1 } t_direcrion;
typedef enum condition { normal, inJump, onStairs } t_condition;
typedef enum collided { rColl, lColl, bColl, tColl, no, colliding } t_collided;
typedef enum heroMovement {} t_heroMovement;
typedef enum mummyMovement {} t_mummyMovement;
typedef enum texture { noTexture = 0, wall = 1, stairLeftUnder = 2, stairLeft = 3, stairLeftTop = 4, stairRightUnder = 5, stairRight = 6, stairRightTop = 7, hardWall = 8, bot = 9, coin = '*' } t_texture;
typedef enum textureDir { leftTexture = 0, rightTexture = 1} t_textureDir;
/*
fps locked 200 - xiaomi
constexpr float GRAVITY_SPEED_CONST = -2.7f;
constexpr float X_MOVE_SPEED_CONST = 1.5f;
constexpr float JUMP_CHANGE_STEP_CONST = 0.04f;
*/

/*
fps locked 100 - xiaomi
constexpr float GRAVITY_SPEED_CONST = -4.1f;
constexpr float X_MOVE_SPEED_CONST = 1.4f;
constexpr float JUMP_CHANGE_STEP_CONST = 0.09f;
*/