#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

#define MIN_PIPE_OFFSET 10
#define MIN_PIPE_LENGTH 5

// Struct that defines the actions of the player
struct Player {
    int xvelocity; // What the current direction of motion is in the x direction (horizontally)
    int yvelocity; // What the current direction of motion is in the y direction (vertically)
    int row; // Current row of the top left corner of img
    int col;  // Current col of the top left corner of img
} player;

struct Pipes {
    int col; // Current col of top left corner of pipe
    int holeRow; // Top row of hole in pipe;
    int width;
} pipe[2];

void initializePlayState(void);
void initializeStartState(void);
void drawStartScreen(void);
void drawPlayScreen(void);

#endif
