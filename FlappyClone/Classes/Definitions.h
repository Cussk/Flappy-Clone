#pragma once

//macros
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.5
#define PIPE_SPAWN_FREQUENCY 0.005

#define PIPE_GAP 3	//X* the size of player sprite
#define UPPER_SCREEN_PIPE_THRESHOLD 0.65
#define LOWER_SCREEN_PIPE_THRESHOLD 0.35

#define PIPE_MOVEMENT_SPEED 0.01

//unique hex bitmask for each collision type
#define BALL_COLLISION_BITMASK 0x000001
#define OBSTACLE_COLLISION_BITMASK 0x000002