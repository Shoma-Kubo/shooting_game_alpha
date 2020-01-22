#include "pch.h"
#include "control.h"

bool quit = false;

char key[256];
int  gamecount = 0;
int  stage     = 0;

int  difficulty = 0;
bool menu_opened = true;

int volume_bgm = 50;
int volume_se = 50;

int invincibleTime = 0;
int dyingcount     = 0;

int img[50];
int imgW[50];
int imgH[50];

int  se[10];
int  bgm[10];
bool playSE[10];
bool playBGM[10];

//for Debug
double* addx;
double* addy;
double* addx2;
double* addy2;
double* addx3;
double* addy3;

//These may change
int px, py;

int debugAry[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

  InitGraph();

  ChangeWindowMode(TRUE);
  SetGraphMode(1280, 960, 32);

  if (DxLib_Init() == 01) {

    return -1;
  }

  CONTROL *control = new CONTROL;

  while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

    control -> All();

    if (quit) {
      break;
    }
  }

  InitGraph();

  DxLib_End();

  return 0;
}
