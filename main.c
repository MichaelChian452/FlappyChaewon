#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/flappyBirdBackground.h"
#include "images/chaewon.h"
#include "images/lesserafim.h"
#include "images/sadchaewon.h"
/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  PLAY,
  LOSE,
};

void initializePlayState(void) {
  drawFullScreenImageDMA(flappybirdbackground);
  //fillScreenDMA(BLACK);

  player.col = 5;
  player.row = (HEIGHT / 2) - (CHAEWON_HEIGHT / 2);
  player.xvelocity = 0;
  player.yvelocity = 0;
  drawImageDMA(player.row, player.col, CHAEWON_WIDTH, CHAEWON_HEIGHT, chaewon);

  pipe[0].col = WIDTH;
  pipe[0].holeRow = randint(MIN_PIPE_LENGTH, HEIGHT - CHAEWON_HEIGHT - MIN_PIPE_OFFSET - MIN_PIPE_LENGTH);
  pipe[0].width = CHAEWON_WIDTH;
  pipe[1].col = WIDTH + 120;
  pipe[1].holeRow = randint(MIN_PIPE_LENGTH, HEIGHT - CHAEWON_HEIGHT - MIN_PIPE_OFFSET - MIN_PIPE_LENGTH);
  pipe[1].width = CHAEWON_WIDTH;
  
}

void initializeStartState(void) {
  drawFullScreenImageDMA(lesserafim);
  char title[] = "Flappy Chaewon";
  drawCenteredString(3, 0, WIDTH, HEIGHT / 10, title, GREEN);

  char instruc[] = "Press ENTER to start";
  drawCenteredString(HEIGHT / 2, 0, WIDTH, HEIGHT / 10, instruc, GREEN);
}

void initializeLoseState(void) {
  drawFullScreenImageDMA(sadchaewon);
  char title[] = "chaewon thinks you can do better.";
  drawCenteredString(3, 0, WIDTH, HEIGHT / 10, title, RED);

  char instruc[] = "Press ENTER to make her proud";
  drawCenteredString(HEIGHT / 2, 0, WIDTH, HEIGHT / 10, instruc, RED);
}

void drawStartScreen(void) {

}

void drawPlayScreen(void) {
  /*
  for(int i = 0; i < 2; i++) {
    if(pipe[i].col >= 0 && pipe[i].col < WIDTH) {
      for(int j = 0; j < pipe[i].holeRow; j++) {
        setPixel(j, pipe[i].col, GREEN);
      }
      //drawRectDMA(0, pipe[i].col, 1, pipe[i].holeRow, GREEN);
      int h = pipe[i].holeRow + CHAEWON_HEIGHT + MIN_PIPE_OFFSET;
      for(int j = h; j < HEIGHT; j++) {
        setPixel(j, pipe[i].col, GREEN);
      }
      //drawRectDMA(h, pipe[i].col, 1, HEIGHT - h, GREEN);
    }
    if(pipe[i].col + pipe[i].width < WIDTH) {
      for(int j = 0; j < pipe[i].holeRow; j++) {
        setPixel(j, pipe[i].col + pipe[i].width, flappybirdbackground[OFFSET(j, pipe[i].col + pipe[i].width, WIDTH)]);
      }
      //undrawImageDMA(0, pipe[i].col + pipe[i].width, 1, pipe[i].holeRow, flappybirdbackground);
      int h = pipe[i].holeRow + CHAEWON_HEIGHT + MIN_PIPE_OFFSET;
      // for(int j = 0; j < pipe[i].holeRow; j++) {
      //   setPixel(j, pipe[i].col + pipe[i].width, BLACK);
      // }
      for(int j = h; j < HEIGHT; j++) {
        setPixel(j, pipe[i].col + pipe[i].width, flappybirdbackground[OFFSET(j, pipe[i].col + pipe[i].width, WIDTH)]);
      }
      //undrawImageDMA(h, pipe[i].col + pipe[i].width, 1, HEIGHT - h, flappybirdbackground);
      // for(int j = h; j < HEIGHT; j++) {
      //   setPixel(j, pipe[i].col + pipe[i].width, BLACK);
      // }
    }
    pipe[i].col--;
    if(pipe[i].col + pipe[i].width < 0) {
      pipe[i].col = WIDTH;
      pipe[i].holeRow = randint(MIN_PIPE_LENGTH, HEIGHT - CHAEWON_HEIGHT - MIN_PIPE_OFFSET - MIN_PIPE_LENGTH);
    }
  } 
  */
  //for(int i = 0; i < HEIGHT; i++) {
  //   for(int j = 0; j < 2; j++) {
  //     if(i >= pipe[j].holeRow && i <= pipe[j].holeRow + CHAEWON_HEIGHT + MIN_PIPE_OFFSET) {
  //       continue;
  //     }
  //     if(pipe[j].col >= 0 && pipe[j].col < WIDTH) {
  //       setPixel(i, pipe[j].col, GREEN);
  //     }
  //     if(pipe[j].col + pipe[j].width < WIDTH) {
  //       //setPixel(i, pipe[j].col + pipe[j].width, BLACK);
  //       setPixel(i, pipe[j].col + pipe[j].width, flappybirdbackground[OFFSET(i, pipe[j].col + pipe[j].width, WIDTH)]);
  //     }
  //   }
  // }
  
  int pipe0 = 0;
  int pipe1 = 0;
  while(pipe0 != HEIGHT && pipe1 != HEIGHT) {
    if (pipe0 == pipe[0].holeRow) {
      pipe0 = pipe[0].holeRow + CHAEWON_HEIGHT + MIN_PIPE_OFFSET;
    }
    if (pipe1 == pipe[1].holeRow) {
      pipe1 = pipe[1].holeRow + CHAEWON_HEIGHT + MIN_PIPE_OFFSET;
    }
    if(pipe[0].col >= 0 && pipe[0].col < WIDTH) {
      setPixel(pipe0, pipe[0].col, GREEN);
    }
    if(pipe[0].col + pipe[0].width < WIDTH) {
      setPixel(pipe0, pipe[0].col + pipe[0].width, flappybirdbackground[OFFSET(pipe0, pipe[0].col + pipe[0].width, WIDTH)]);
    }
    if(pipe[1].col >= 0 && pipe[1].col < WIDTH) {
      setPixel(pipe1, pipe[1].col, GREEN);
    }
    if(pipe[1].col + pipe[1].width < WIDTH) {
      setPixel(pipe1, pipe[1].col + pipe[1].width, flappybirdbackground[OFFSET(pipe1, pipe[1].col + pipe[1].width, WIDTH)]);
    }
    pipe0++;
    pipe1++;
  }

  for(int i = 0; i < 2; i++) {
    pipe[i].col--;
    if(pipe[i].col + pipe[i].width < 0) {
      pipe[i].col = WIDTH;
      pipe[i].holeRow = randint(MIN_PIPE_LENGTH, HEIGHT - CHAEWON_HEIGHT - MIN_PIPE_OFFSET - MIN_PIPE_LENGTH);
    }
  } 
  

}

void moveChaewon(void) {
  if (KEY_DOWN(BUTTON_UP, BUTTONS) == BUTTON_UP) {
    player.yvelocity = -2;
  }
  else if(KEY_DOWN(BUTTON_DOWN, BUTTONS) == BUTTON_DOWN) {
    player.yvelocity = 2;
  } 
  else {
    player.yvelocity = 0;
  }
  if(KEY_DOWN(BUTTON_LEFT, BUTTONS) == BUTTON_LEFT) {
    player.xvelocity = -1;
  }
  else if(KEY_DOWN(BUTTON_RIGHT, BUTTONS) == BUTTON_RIGHT) {
    player.xvelocity = 1;
  }
  else {
    player.xvelocity = 0;
  }
  //drawRectDMA(player.row, player.col, CHAEWON_WIDTH, CHAEWON_HEIGHT, BLACK);
  undrawImageDMA(player.row, player.col, CHAEWON_WIDTH, CHAEWON_HEIGHT, flappybirdbackground);
  player.col += player.xvelocity;
  player.row += player.yvelocity;
  if(player.col < 0) {
    player.col = 0;
  }
  if(player.col + CHAEWON_WIDTH > WIDTH) {
    player.col = WIDTH - CHAEWON_WIDTH;
  }
  if(player.row < 0) {
    player.row = 0;
  }
  if(player.row + CHAEWON_HEIGHT > HEIGHT) {
    player.row = HEIGHT - CHAEWON_HEIGHT;
  }
  drawImageDMA(player.row, player.col, CHAEWON_WIDTH, CHAEWON_HEIGHT, chaewon);

}

void checkCollisions(enum gba_state *statePointer) {
  for(int i = 0; i < 2; i++) {
    if((player.col + CHAEWON_WIDTH > pipe[i].col) && (player.col < pipe[i].col + pipe[i].width)) {
      if((player.row <= pipe[i].holeRow) || (player.row + CHAEWON_HEIGHT >= pipe[i].holeRow + CHAEWON_HEIGHT + MIN_PIPE_OFFSET)) {
          *statePointer = LOSE;
          initializeLoseState();
          return;
      }
    }
  }
}

void drawTime(u32 vBlankStartTime) {
  drawRectDMA(HEIGHT - 22, 3, 30, 12, BLACK);
  int min = (vBlankCounter - vBlankStartTime) / 3600;
  int sec = (vBlankCounter - vBlankStartTime) / 60;
  char time[] = {'0' + (min % 10), ':', '0' + ((sec / 10) % 10), '0' + (sec % 10), '\0'};
  drawString(HEIGHT - 20, 5, time, RED);
}

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  u32 vBlankStartTime = 0;

  // Load initial application state
  enum gba_state state = START;
  initializeStartState();

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    waitForVBlank();

    if(KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
      state = START;
      initializeStartState();
    }

    switch (state) {
      case START:
        drawStartScreen();
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = PLAY;
          vBlankStartTime = vBlankCounter;
          initializePlayState();
        }
        break;
      case PLAY:
        moveChaewon();
        drawPlayScreen();
        drawTime(vBlankStartTime);
        checkCollisions(&state);
        break;
      case LOSE:
      if(KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
        state = START;
        initializeStartState();
      }
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }
  return 0;
}
