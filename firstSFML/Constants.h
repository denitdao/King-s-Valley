#pragma once
#include "pch.h"

// screen settings
constexpr float ASPECT_RATIO = 3.f / 4.f;
constexpr float WINDOW_SIZE_X = 1024.f; // 1024.f
constexpr float WINDOW_SIZE_Y = WINDOW_SIZE_X * ASPECT_RATIO;
constexpr int FPS_LOCK = 60;

// map settings
constexpr int MAX_MAP_SIZE_X = 64;
constexpr int MAP_SIZE_X = 32;
constexpr int MAP_SIZE_Y = 24;
constexpr float BLOCK_SIZE_X = WINDOW_SIZE_X / MAP_SIZE_X;
constexpr float BLOCK_SIZE_Y = WINDOW_SIZE_Y / MAP_SIZE_Y;

static bool xRay = false;

// player settings
constexpr float PLAYER_SIZE_X = WINDOW_SIZE_X / MAP_SIZE_X;
constexpr float PLAYER_SIZE_Y = (WINDOW_SIZE_Y / MAP_SIZE_Y) * 2;
constexpr int LIVES_CONST = 4;
constexpr float CHANGE_TEXTURE_DELTA_X = 10.f;

static int lives = LIVES_CONST;

// gravity settings
constexpr float X_MOVE_SPEED = WINDOW_SIZE_X / 512.f; // 2.0f
constexpr float GRAVITY_SPEED = X_MOVE_SPEED * -2.5f; // -5.0f
constexpr float JUMP_CHANGE_STEP = GRAVITY_SPEED * (-3.f / 100.f); // 0.15f

// enums
typedef enum direction { toleft = -1, none = 0, toright = 1 } t_direcrion;
typedef enum textureDir { leftTexture = 0, rightTexture = 1} t_textureDir;
typedef enum texture { noTexture = 0, wall = 1, stairLeftUnder = 2, stairLeft = 3, stairLeftTop = 4, stairRightUnder = 5, stairRight = 6, stairRightTop = 7, hardWall = 8, bot = 9, coin = '*' } t_texture;
typedef enum collided { rColl, lColl, bColl, tColl, no, colliding } t_collided;

// logging
static Logger myLog(Logger::ERR, Logger::WARN);

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