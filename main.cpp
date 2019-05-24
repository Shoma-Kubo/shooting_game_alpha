#include "pch.h"
#include "control.h"

char key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

  ChangeWindowMode(TRUE);

  if (DxLib_Init() == 01) {

    return -1;
  }

  CONTROL *control = new CONTROL;

  while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

    control -> All();

    if (key[KEY_INPUT_ESCAPE] == 1) {
      break;
    }
  }

  DxLib_End();

  return 0;
}
