#include "pch.h"
#include "control.h"

CONTROL::CONTROL() {

  menu = new MENU;
  background = new BACKGROUND;
  player = new PLAYER;

  LoadResources();
  LoadEnemyData();
  LoadBossData();
}

CONTROL::~CONTROL() {

  delete player;
  delete background;
  for (int i = 0; i < NUM_OF_ENEMY; i++) {
    delete enemy[i];
  }
  for (int i = 0; i < NUM_OF_BOSS; i++) {
    delete boss[i];
  }
}

void CONTROL::LoadResources() {

  img[0]  = LoadGraph("pictures/shot_player_01.png");
  img[1]  = LoadGraph("pictures/shot_player_02.png");
  img[5]  = LoadGraph("pictures/boss_01.png");
  img[10] = LoadGraph("pictures/shot_doublecircle_00.png");
  img[11] = LoadGraph("pictures/shot_doublecircle_01.png");
  img[12] = LoadGraph("pictures/shot_doublecircle_02.png");
  img[13] = LoadGraph("pictures/shot_doublecircle_03.png");
  img[14] = LoadGraph("pictures/shot_doublecircle_04.png");
  img[15] = LoadGraph("pictures/shot_doublecircle_05.png");
  img[16] = LoadGraph("pictures/shot_doublecircle_06.png");
  img[17] = LoadGraph("pictures/shot_doublecircle_07.png");
  img[20] = LoadGraph("pictures/shot_star_00.png");
  img[21] = LoadGraph("pictures/shot_star_01.png");
  img[22] = LoadGraph("pictures/shot_star_02.png");
  img[23] = LoadGraph("pictures/shot_star_03.png");
  img[24] = LoadGraph("pictures/shot_star_04.png");
  img[25] = LoadGraph("pictures/shot_star_05.png");
  img[26] = LoadGraph("pictures/shot_star_06.png");
  img[27] = LoadGraph("pictures/shot_star_07.png");
  img[37] = LoadGraph("pictures/shot_petal_07.png");
  img[38] = LoadGraph("pictures/shot_petal_08.png");
  img[40] = LoadGraph("pictures/shot_bigstar_00.png");

  for (int i = 0; i < 40; i++) {
    GetGraphSize(img[i], &imgW[i], &imgH[i]);
  }

  se[0] = LoadSoundMem("se/se_maoudamashii_se_ignition04.wav");
  se[1] = LoadSoundMem("se/se_maoudamashii_explosion03.wav");
  se[2] = LoadSoundMem("se/se_maoudamashii_explosion04.wav");
  se[3] = LoadSoundMem("se/se_maoudamashii_explosion03.wav");

  for (int i = 0; i < 10; i++){
    ChangeVolumeSoundMem(100, se[i]);
    playSE[i] = false;
  }
  ChangeVolumeSoundMem(200, se[2]);

  bgm[0] = LoadSoundMem("bgm/bgm_maoudamashii_neorock83.ogg");

  for (int i = 0; i < 10; i++){
    ChangeVolumeSoundMem(100, bgm[i]);
    playBGM[0] = false;
  }
  playBGM[0] = true;
}

void CONTROL::LoadEnemyData() {

  char edata_char_filename[NUM_OF_ENEMY][50] = {"pictures/enemy_01.png"};
  int edata_move_pattern[NUM_OF_ENEMY][5]    = {{0}};
  int edata_shot_pattern[NUM_OF_ENEMY][5]    = {{0}};
  double edata_x[NUM_OF_ENEMY]               = {480};
  double edata_y[NUM_OF_ENEMY]               = {-40};
  int edata_in[NUM_OF_ENEMY]                 = {100};
  int edata_phase_out[NUM_OF_ENEMY]          = {6000};
  int edata_hp[NUM_OF_ENEMY]                 = {0};
  int edata_item[NUM_OF_ENEMY]               = {10};

  for (int i = 0; i < NUM_OF_ENEMY; i++) {
    enemy[i] = new ENEMY(edata_char_filename[i], edata_move_pattern[i], edata_x[i], edata_y[i], edata_in[i], edata_phase_out[i], edata_shot_pattern[i], edata_hp[i], edata_item[i]);
  }
}

void CONTROL::LoadBossData() {

  int    bdata_imgN[NUM_OF_BOSS]     = {5};
  double bdata_x[NUM_OF_BOSS]        = {480};
  double bdata_y[NUM_OF_BOSS]        = {- 40};
  int    bdata_maxHP[NUM_OF_BOSS]    = {1000};
  double bdata_nowHP[NUM_OF_BOSS]    = {1000};
  int    bdata_ptn_item[NUM_OF_BOSS] = {0};
  int    bdata_ptn_move[NUM_OF_BOSS] = {0};
  int    bdata_ptn_bom[NUM_OF_BOSS]  = {0};

  for (int i = 0; i < NUM_OF_ENEMY; i++) {
    boss[i] = new BOSS(bdata_imgN[i], bdata_x[i], bdata_y[i], bdata_maxHP[i], bdata_nowHP[i], bdata_ptn_item[i], bdata_ptn_move[i], bdata_ptn_bom[i]);
  }
}

void CONTROL::SoundAll() {

  for (int i = 0; i < 10; i++) {
    if(playSE[i]) {
      PlaySoundMem(se[i], DX_PLAYTYPE_BACK);
      playSE[i] = false;
    }
  }

  for (int i = 0; i < 10; i++) {
    if(playBGM[i] && !CheckSoundMem(bgm[i]) ) {
      PlaySoundMem(bgm[i], DX_PLAYTYPE_BACK);
    }
  }
}

void CONTROL::GetPlayerPosition(double *player_x, double *player_y) {

    double temp_x, temp_y;

    player -> GetPosition(&temp_x, &temp_y);
    *player_x = temp_x;
    *player_y = temp_y;
}

void CONTROL::GetEnemyPosition(int index, double *x, double *y) {

    double temp_x, temp_y;

    enemy[index] -> GetPosition(&temp_x, &temp_y);
    *x = temp_x;
    *y = temp_y;
}

void CONTROL::GetPlayersShotPosition(int i, int j, double *x, double *y) {

  double temp_x, temp_y;

  if (player -> GetShotPosition(i, j, &temp_x, &temp_y)){
    *x = temp_x;
    *y = temp_y;
  }
}

void CONTROL::All() {


  if (key[KEY_INPUT_ESCAPE] == 1 && !menu_opened) menu -> OpenGameMenu();

  if (menu_opened) {
    menu -> All();
  }
  else {

    SetDrawArea(10, 10, 950, 950);

    background -> All();

    for (int i = 0; i < NUM_OF_ENEMY; i++) {
      if (enemy[i] != NULL) {
        if (enemy[i] -> All()) {
          delete enemy[i];
          enemy[i] = NULL;
        }
      }
    }

    for (int i = 0; i < NUM_OF_BOSS; i++) {
      if (boss[i] != NULL) {
        if (boss[i] -> All()) {
          delete boss[i];
          boss[i] = NULL;
        }
      }
    }

	SetDrawArea(10, 10, 1270, 950);
	SetFontSize(30);

	for (int i = 0; i < 10; i++) {
		DrawFormatString(960, 400 + i * 50, GetColor(255, 255, 255), "%05d:   %010d", i, debugAry[i]);
	}

    player -> All();

	//debug
	double player_x, player_y;
	player -> GetPosition(&player_x, &player_y);
	debugAry[2] = player_x;
	debugAry[3] = player_y;

	//debug
	GetPlayerPosition(&player_x, &player_y);
	debugAry[4] = player_x;
	debugAry[5] = player_y;

    SoundAll();

    if (invincibleTime > 0) invincibleTime --;
    if (dyingcount > 0) dyingcount --;
    gamecount ++;
  }

}

void CONTROL::ResetAll() {

  gamecount = 0;

  for (int i = 0; i < 10; i++) StopSoundMem(bgm[i]);
  for (int i = 0; i < 10; i++) StopSoundMem(se[i]);

  gamecount = 0;
  stage     = 0;

  invincibleTime = 0;
  dyingcount     = 0;

  player -> Reset();
  for (int i = 0; i < NUM_OF_ENEMY; i++) if (enemy[i] != NULL) enemy[i] -> Reset();
  for (int i = 0; i < NUM_OF_BOSS; i++) if (boss[i] != NULL) boss[i] -> Reset();
}
