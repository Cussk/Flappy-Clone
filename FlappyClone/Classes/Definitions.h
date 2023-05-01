#pragma once

//time macros
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.5
#define PIPE_SPAWN_FREQUENCY 0.004

//pipe positioning macros
#define PIPE_GAP 6	//X* the size of player sprite
#define UPPER_SCREEN_PIPE_THRESHOLD 0.65
#define LOWER_SCREEN_PIPE_THRESHOLD 0.35

//pipe movement macros
#define PIPE_MOVEMENT_SPEED 0.015

//unique hex bitmask for each collision type
#define BALL_COLLISION_BITMASK 0x000001
#define OBSTACLE_COLLISION_BITMASK 0x000002
#define POINT_COLLISION_BITMASK 0x000003

//movement macros
#define BALL_FALLING_SPEED 0.0025
#define BALL_FLYING_SPEED 0.00375
#define BALL_FLY_DURATION 0.5

//font macros
#define SCORE_FONT_SIZE 0.1