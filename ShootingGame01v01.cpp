#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

  ChangeWindowMode(TRUE);

  if (DxLib_Init() == -1) {
    return -1;
  }

  char key[256];

  int player_x, player_y;

  player_x = 300;
  player_y = 240;

  int alive = 1;

  int move_left, move_right, move_up, move_down;
  move_left = move_right = move_up = move_down = 0;
  int move_distance = 8;

  int gh[12];
  LoadDivGraph("pictures/image_player.png", 12, 3, 4, 32, 32, gh);

  int background_01 = LoadGraph("pictures/image_background_01.png");

  int background_y = -450;

  int movie_player = 0;

  SetDrawScreen(DX_SCREEN_BACK);

  while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

    DrawGraph(0, background_y, background_01, FALSE);
    
    if (alive) {
      DrawGraph(player_x, player_y, gh[9 + (movie_player / 7)], TRUE);
    }

    move_distance = key[KEY_INPUT_LSHIFT] == 1 ? 3 : 8;

    background_y += 4;
    if (background_y >= 0) background_y = -450;

    if (key[KEY_INPUT_LEFT]) move_left = move_left > -move_distance ? move_left - 1 : -move_distance;
    else if (move_left < 0) move_left ++;

    if (key[KEY_INPUT_RIGHT]) move_right = move_right < move_distance ? move_right + 1 : move_distance;
    else if (move_right > 0) move_right --;

    if (key[KEY_INPUT_UP]) move_up = move_up > -move_distance ? move_up - 1 : -move_distance;
    else if (move_up < 0) move_up ++;

    if (key[KEY_INPUT_DOWN]) move_down = move_down < move_distance ? move_down + 1 : move_distance;
    else if (move_down > 0) move_down --;

    player_x += move_right + move_left;
    player_y += move_up + move_down;

    if (player_x < -16) {
      player_x = -16;
      move_left = 0;
    }
    if (player_x > 624) {
      player_x = 624;
      move_right = 0;
    }
    if (player_y < -16) {
      player_y = -16;
      move_up = 0;
    }
    if (player_y > 460) {
      player_y = 460;
      move_down = 0;
    }

    if (key[KEY_INPUT_ESCAPE] == 1) {
      break;
    }

    movie_player = movie_player >= 20 ? 0 : movie_player + 1;
  }

  DxLib_End();

  return 0;
}
