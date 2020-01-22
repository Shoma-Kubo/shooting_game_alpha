#include "pch.h"
#include "control.h"

PLAYER::PLAYER() {

  LoadDivGraph("pictures/player_02.png", 16, 4, 4, 32, 48, pimg);

  alive = true;

  pimgW = 32;
  pimgH = 48;

  moveL = moveR = moveU = moveD = 0;
  move_speed = 10;
  movie = 0;

  x = 480;
  y = 480;

  maxHP = nowHP = 1000;
  power = 4;
  score = 0;

  canShoot = true;
  shot_type = 0;
  shot_change_count = 0;
  count_shot = 0;

  shot_speed[0] = 27.5;

  boming = false;
  bom_type = 0;
  count_bom = 0;

  bom_time[0] = 3500;
  bom_time[1] = 3000;
  bom_time[2] = 3000;
  bom_time[3] = 3000;
  bom_time[4] = 3000;
  bom_time[5] = 2500;
  bom_time[6] = 2500;
  bom_time[7] = 3000;

  pre_adding_rad = 0;
  adding_rad = 0;

  memset(shot[0], 0, sizeof(shot[0]));
  memset(shot[1], 0, sizeof(shot[1]));
  memset(bom, 0, sizeof(bom));

  for (int n = 0; n < 2; n++) {
    for (int i = 0; i < NUM_OF_SHOT; i++) {

      shot[n][i].flag  = false;
      shot[n][i].imgN  = n;
      shot[n][i].speed = shot_speed[0];
    }
  }

  for (int i = 0; i < NUM_OF_BOMSHOT; i++) bom[i].flag = false;
}

void PLAYER::Move() {

  //Change bomtype or difficulty
  if (1) {
    if (key[KEY_INPUT_0]) bom_type = 0;
    if (key[KEY_INPUT_1]) bom_type = 1;
    if (key[KEY_INPUT_2]) bom_type = 2;
    if (key[KEY_INPUT_3]) bom_type = 3;
    if (key[KEY_INPUT_4]) bom_type = 4;
    if (key[KEY_INPUT_5]) bom_type = 5;
    if (key[KEY_INPUT_6]) bom_type = 6;
    if (key[KEY_INPUT_7]) bom_type = 7;
  }

  if (key[KEY_INPUT_X] && dyingcount == 0 && alive) dyingcount = DyingCountMax;

  move_speed = key[KEY_INPUT_LSHIFT] == 1 ? 4 : 10;

  if (key[KEY_INPUT_LEFT]) moveL = moveL > - move_speed ? moveL - 1 : - move_speed;
  else if (moveL < 0) moveL ++;

  if (key[KEY_INPUT_RIGHT]) moveR = moveR < move_speed ? moveR + 1 : move_speed;
  else if (moveR > 0) moveR --;

  if (key[KEY_INPUT_UP]) moveU = moveU > - move_speed ? moveU - 1 : - move_speed;
  else if (moveU < 0) moveU ++;

  if (key[KEY_INPUT_DOWN]) moveD = moveD < move_speed ? moveD + 1 : move_speed;
  else if (moveD > 0) moveD --;

  x += moveR + moveL;
  y += moveU + moveD;

  //When you are getting out of the screen
  if (x < LIMIT_L + 10) {
    x = LIMIT_L + 10;
    moveL = 0;
  }
  if (x > LIMIT_R - 10) {
	  x = LIMIT_R - 10;
    moveR = 0;
  }
  if (y < LIMIT_U + 10) {
	  y = LIMIT_U + 10;
    moveU = 0;
  }
  if (y > LIMIT_D - 10) {
	  y = LIMIT_D - 10;
    moveD = 0;
  }

  addx3 = &x;
  addy3 = &(this->x);
}

void PLAYER::Shot() {

  int num = 0;
  int shot_power = (int)power;

  if (key[KEY_INPUT_B] && !boming) {
    //canShoot = false;
    boming         = true;
    count_bom      = 0;
    adding_rad     = 0;
    pre_adding_rad = 0;
  }

  //Release shots
  if (key[KEY_INPUT_Z] && canShoot && alive) {

    if ((gamecount % (6 - shot_power / 2)) == 0 && shot_type == 0) {

      for (int i = 0; i < NUM_OF_SHOT; i++) {

        if (!shot[0][i].flag) {

          if (power >= 1) {

            switch (num) {
              case 0:

              shot[0][i].flag = true;
              shot[0][i].x    = key[KEY_INPUT_LSHIFT] ? x + 12 : x + 20;
              shot[0][i].y    = y;
              break;

              case 1:

              shot[0][i].flag = true;
              shot[0][i].x    = key[KEY_INPUT_LSHIFT] ? x - 12 : x - 20;
              shot[0][i].y    = y;
              break;

              case 2:
              break;

              default:
              break;
            }

          } else {

            shot[0][i].flag = true;
            shot[0][i].x    = x;
            shot[0][i].y    = y;

            break;
          }
          num ++;
        }
        if (num > power / 1) break;
      }
    }

    num = 0;

    if ((count_shot % (7 - shot_power)) == 0 && shot_power >= 2) {

      for (int i = 0; i < NUM_OF_SHOT; i++) {
        if (!shot[1][i].flag) {

          if (shot_type == 0 && num < 2) {

            shot[1][i].flag = true;
            shot[1][i].y = y;

            switch (num) {
              case 0:
              shot[1][i].x       = key[KEY_INPUT_LSHIFT] ? x - 12 : x - 32;
              shot[1][i].rad     = key[KEY_INPUT_LSHIFT] ?  -1.57 :  -1.99;
              break;

              case 1:
              shot[1][i].x       = key[KEY_INPUT_LSHIFT] ? x + 12 : x + 32;
              shot[1][i].rad     = key[KEY_INPUT_LSHIFT] ?  -1.57 :  -1.15;
              break;

              default:
              break;
            }
            shot[1][i].rota = shot[1][i].rad;
          }
          num ++;
        }
        if (num > 1) break;
      }
    }

    num = 0;
  }

  //Release bom shots
  if (boming) {

    switch (bom_type) {

      case 0:

      if (count_bom < bom_time[bom_type] && count_bom % (12 - difficulty * 3) == 0) {

        num = 0;

        for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
          if (!bom[i].flag && num < 16) {

            bom[i].flag  = true;
            bom[i].x     = (LIMIT_R + LIMIT_L) / 2;
            bom[i].y     = (LIMIT_D + LIMIT_U) / 3;
            bom[i].imgN  = 11 + num % 2 * 6;
            bom[i].speed = num % 2 ? 4 + difficulty : 6 + difficulty;
            bom[i].rad   = num % 2 ? 0.3927 * num + adding_rad : - 0.3926 * num - adding_rad;
            bom[i].rota  = bom[i].rad;

            num ++;
          }
          if (num >= 16) break;
        }

        if (count_bom < 200) {
          pre_adding_rad -= 0.004;
        } else if (count_bom < 500) {
          pre_adding_rad += 0.008;
        } else if (count_bom < 900) {
          pre_adding_rad -= 0.012;
        } else if (count_bom < 1500) {
          pre_adding_rad += 0.016;
        } else {
          pre_adding_rad -= /*0.13*/0.016;
        }

        adding_rad += pre_adding_rad;
        playSE[0] = true;
      }
      num = 0;
      break;

      case 1://桜吹雪・霊

      if (count_bom < bom_time[bom_type] && count_bom % (8 - difficulty * 2) == 0) {
        num = 0;
        for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
          if (!bom[i].flag && num < 6 + difficulty / 1 * 2) {

            bom[i].flag  = true;
            bom[i].x     = x;
            bom[i].y     = y;
            bom[i].imgN  = 38 - num / 6 * 28;
            bom[i].speed = 3 + num / 6 * 6 + difficulty;

            switch (num) {
              case  0:
              bom[i].rad = 1.570 + adding_rad;
              bom[i].x = LIMIT_L + 100;
              bom[i].y = LIMIT_U + 100;
              break;

              case  1:
              bom[i].rad = 1.570 - adding_rad;
              bom[i].x = LIMIT_R - 100;
              bom[i].y = LIMIT_U + 100;
              break;

              case  2:
              bom[i].rad = 3.665 + adding_rad;
              bom[i].x = LIMIT_L + 100;
              bom[i].y = LIMIT_U + 100;
              break;

              case  3:
              bom[i].rad = 3.665 - adding_rad;
              bom[i].x = LIMIT_R - 100;
              bom[i].y = LIMIT_U + 100;
              break;

              case  4:
              bom[i].rad = 5.759 + adding_rad;
              bom[i].x = LIMIT_L + 100;
              bom[i].y = LIMIT_U + 100;
              break;

              case  5:
              bom[i].rad = 5.759 - adding_rad;
              bom[i].x = LIMIT_R - 100;
              bom[i].y = LIMIT_U + 100;
              break;

              case  6:
              bom[i].rad = 1.570 + adding_rad / 2;
              bom[i].x = LIMIT_L + 100;
              bom[i].y = LIMIT_U + 100;
              break;

              case  7:
              bom[i].rad = 1.570 - adding_rad / 2;
              bom[i].x = LIMIT_R - 100;
              bom[i].y = LIMIT_U + 100;
              break;

              default:
              break;
            }
            bom[i].rota = bom[i].rad;
            num ++;
          }
          if (num >= 8) break;
        }
        adding_rad += 0.300 + num / 6 * 0.100;
        playSE[0] = true;
      }
      break;

      case 2:

      if (count_bom < bom_time[bom_type] && (count_bom % 250) < (100 + 50 * difficulty) && (count_bom % (8 - difficulty * 2)) == 0) {
        num = 0;
        for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
          if (!bom[i].flag && num < (1 + difficulty / 2)) {

            bom[i].flag  = true;
            bom[i].x     = difficulty < 2 ? (LIMIT_R + LIMIT_L) / 2 : num < 1 ? LIMIT_L + 100 : LIMIT_R - 100;
            bom[i].y     = 100;
            bom[i].imgN  = 23;
            bom[i].speed = 15;
            bom[i].rad   = atan2(y - bom[i].y, x - bom[i].x);
            bom[i].rota  = bom[i].rad;

            num ++;
          }
          if (num >= (1 + difficulty / 2)) break;
        }
        playSE[0] = true;
      }
      num = 0;
      break;

      case 3://Firefly Frontline -Counterblow

      if (count_bom < bom_time[bom_type] && (count_bom % (16 - difficulty * 3)) == 0 && (count_bom % 200) < 110 + difficulty * 30) {
        num = 0;
        for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
          if (!bom[i].flag && num < 2) {

            bom[i].flag  = true;
            bom[i].x     = num < 1 ? LIMIT_L + 100 : LIMIT_R - 100;
            bom[i].y     = 100;
            bom[i].imgN  = 17;
            bom[i].speed = 26;
            bom[i].rad   = atan2(y - bom[i].y, x - bom[i].x);
            bom[i].rota  = bom[i].rad;

            num ++;
          }
        }
        playSE[0] = true;
      }
      num = 0;
      break;

      case 4://Firefly Frontline

      if (count_bom < bom_time[bom_type] && (count_bom % (10 - difficulty * 2)) == 0) {
        num = 0;
        for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
          if (!bom[i].flag && num < 2) {

            bom[i].flag  = true;
            bom[i].x     = num < 1 ? LIMIT_L + 100 : LIMIT_R - 100;
            bom[i].y     = LIMIT_U + 100;
            bom[i].imgN  = 17;
            bom[i].speed = 24;
            bom[i].rad   = num < 1 ? 4.712 + adding_rad : 4.712 - adding_rad;
            bom[i].rota  = bom[i].rad;

            num ++;
          }
          if (num >= 2) break;
        }
        playSE[0] = true;
      }
      num = 0;
      break;

      case 5://Rainbow Eddy

      if (count_bom < bom_time[bom_type]) {

        if (count_bom % 150 == 0) {
          temp_x = LIMIT_L + 100 + ((LIMIT_R - LIMIT_L - 200) / 99) * (rand() % 100);
          temp_y = LIMIT_U + 100 + ((((LIMIT_D - LIMIT_U) / 5) - LIMIT_U - 100) / 49) * (rand() % 50);
        }

        if (difficulty > 1 && count_bom % (25 - difficulty / 3 * 5) == 0) {
          num = 0;
          for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
            if (!bom[i].flag && num < 1) {

              if (num != 7 || count_bom % 15 == 0) {
                bom[i].flag  = true;
                bom[i].x     = temp_x;
                bom[i].y     = temp_y;
                bom[i].imgN  = 40;
                bom[i].speed = 6;
                bom[i].rad   = atan2(y - bom[i].y, x - bom[i].x);
                bom[i].rota  = bom[i].rad;
                bom[i].id    = 7;
              }

              num ++;
            }
            if (num >= 1) break;
          }
          playSE[0] = true;
        }

        if (count_bom % 300 >= 0 && count_bom % 300 <= 30 + difficulty * 30) {
          num = 0;
          for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
            if (!bom[i].flag && num < 7) {

              bom[i].flag  = true;
              bom[i].x     = temp_x;
              bom[i].y     = temp_y;
              bom[i].imgN  = 21 + num;
              bom[i].speed = 15 + 5 * difficulty;
              bom[i].rad   = adding_rad + 0.230 * num;
              bom[i].rota  = bom[i].rad;
              bom[i].id    = num;

              num ++;
            }
            if (num >= 7 + difficulty / 2) break;
          }
          adding_rad += 0.170;
          playSE[0] = true;
        }

        else if (count_bom % 150 >= 0 && count_bom % 150 <= 30 + difficulty * 30) {
          num = 0;
          for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
            if (!bom[i].flag && num < 7) {

              bom[i].flag  = true;
              bom[i].x     = temp_x;
              bom[i].y     = temp_y;
              bom[i].imgN  = num < 7 ? 21 + num : 40;
              bom[i].speed = num < 7 ? 15 + 5 * difficulty : 6;
              bom[i].rad   = num < 7 ? 3.141 - adding_rad - 0.230 * num : atan2(y - bom[i].y, x - bom[i].x);
              bom[i].rota  = bom[i].rad;
              bom[i].id    = 10 + num;

              num ++;
            }
            if (num >= 7 + difficulty / 2) break;
          }
          adding_rad += 0.170;
          playSE[0] = true;
        }
        else adding_rad = 0;
      }
      num = 0;
      break;

      case 6://桜吹雪・風

      if (count_bom < bom_time[bom_type] && count_bom % (20 - difficulty * 2) == 0) {

        num = 0;
        int maxn = 30 + difficulty * 10;

        for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
          if (!bom[i].flag && num < maxn) {

            bom[i].flag  = true;
            bom[i].id    = count_bom % ((20 - difficulty * 2) * 2) == 0 ? 0 : 1;
            bom[i].x     = (LIMIT_R + LIMIT_L) / 2;
            bom[i].y     = 200;
            bom[i].imgN  = 37 + bom[i].id;
            bom[i].speed = 6 /*+ difficulty*/;
            bom[i].rad   = num * 6.283 / maxn + adding_rad;
            bom[i].rota  = bom[i].rad;

            num ++;
          }
          if (num >= maxn) break;
        }
        playSE[0] = true;
      }
      num = 0;
      break;

      case 7:

        if (difficulty > 0 && count_bom % (14 - difficulty * 2) == 0) {
          num = 0;
          for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
            if (!bom[i].flag && num < 4 * difficulty) {

              bom[i].flag  = true;
              bom[i].rad   = num % 2 == 0 ? 1.570 + 6.2832 / (2 * difficulty) * (num / 2) + adding_rad : 1.570 - 6.2832 / (2 * difficulty) * (num / 2) - adding_rad;
              bom[i].x     = (LIMIT_R + LIMIT_L) / 2;
              bom[i].y     = (LIMIT_D + LIMIT_U) / 2;
              bom[i].imgN  = 25 + num % 2 ;
              bom[i].id    = 1000 + (num % 2);
              bom[i].speed = 6;
              bom[i].rota  = bom[i].rad;

              num ++;
            }
            if (num >= 4 * difficulty) break;
          }
        }

        if (count_bom % 150 < 120) {
          for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
            if (!bom[i].flag) {

              bom[i].flag  = true;
              bom[i].rad   = count_bom % 300 < 150 ? 0.0523 * (count_bom % 150) : - 0.0523 * (count_bom % 150);
              bom[i].x     = (LIMIT_R + LIMIT_L) / 2 + cos(bom[i].rad) * 100;
              bom[i].y     = (LIMIT_D + LIMIT_U) / 2 + sin(bom[i].rad) * 100;
              bom[i].imgN  = 22 + count_bom % 2;
              bom[i].id    = count_bom % 2 + count_bom / 150 * 10;
              if (count_bom % 300 >= 150) bom[i].id += 2;
              bom[i].speed = 0;
              bom[i].rota  = bom[i].rad;

              break;
            }
          }
          playSE[0] = true;
        }

      break;

      default:
      break;
    }
  }

  //Move shots
  for (int i = 0; i < NUM_OF_SHOT; i++) {

    if (shot[0][i].flag) {
      shot[0][i].y -= shot[0][i].speed;
    }
    if (shot[1][i].flag) {
      shot[1][i].rota += shot[1][i].rad > 1.570 ? 0.200 : -0.200;
      shot[1][i].x += cos(shot[1][i].rad) * shot[1][i].speed;
      shot[1][i].y += sin(shot[1][i].rad) * shot[1][i].speed;
    }

    if (shot[0][i].y < -10) {
      shot[0][i].flag = false;
    }
    if (shot[1][i].y < LIMIT_U - 20 || shot[1][i].y > LIMIT_D + 20 || shot[1][i].x < LIMIT_L - 20 || shot[1][i].x > LIMIT_R + 20) {
      shot[1][i].flag = false;
    }
  }

  //Move bom shots
  if (dyingcount == 0) {
    switch (bom_type) {

      case 0:
      break;

      case 1:
      break;

      case 2:

      for (int i = 0; i < NUM_OF_BOMSHOT; i++) {

        bom[i].rota += 0.300;

        if (count_bom % 5 == 0 && bom[i].flag && !bom[i].getItem){
          if (bom[i].speed <= 0) {
            bom[i].speed = 16;
            bom[i].rad   = atan2(y - bom[i].y, x - bom[i].x);
          }
          else if (bom[i].speed < 16) {
            bom[i].speed -= 1;
          }
        }
      }
      break;

      case 3:

      for (int i = 0; i < NUM_OF_BOMSHOT; i++) {

        if (count_bom % 5 == 0 && bom[i].flag && !bom[i].getItem){
          if (bom[i].speed == 0) {
            bom[i].rad   = atan2(y - bom[i].y, x - bom[i].x) + 3.14;
            bom[i].imgN  = 13;
            bom[i].speed = -2;
          }
          if (bom[i].speed > 0) bom[i].speed -= 2;
        }
      }
      break;

      case 4:

      for (int i = 0; i < NUM_OF_BOMSHOT; i++) {

        adding_rad += 0.200;

        if (count_bom % 5 == 0 && bom[i].flag && !bom[i].getItem){
          if (bom[i].speed == 0) {
            bom[i].rad   = atan2(y - bom[i].y, x - bom[i].x) + 3.14;
            bom[i].imgN  = 13;
            bom[i].speed = - 2 - rand() % (difficulty + 1);
          }
          if (bom[i].speed > 0) bom[i].speed -= 2;
        }
      }
      break;

      case 5:

      for (int i = 0; i < NUM_OF_BOMSHOT; i++) {

        if ((bom[i].id % 10) < 7 && bom[i].speed > 9 - (bom[i].id % 10) && bom[i].flag && !bom[i].getItem) bom[i].speed -= 1;
        bom[i].rota += bom[i].id % 10 ? 0.130 : - 0.130;
      }

      break;

      case 6:

      for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
        if (bom[i].flag && !bom[i].getItem) {
          bom[i].rad += bom[i].id ? 0.006/* + 0.003 * difficulty*/ : - 0.006/* - 0.003 * difficulty*/;
          adding_rad += 0.033;
          bom[i].rota  = bom[i].rad;
        }
      }

      break;

      case 7:

        for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
          if (bom[i].flag && !bom[i].getItem) {

            if (bom[i].id / 1000 == 0 && (count_bom >= 150 * (bom[i].id / 10) + 130)) {
              bom[i].rad   += (bom[i].id % 10 / 3) == 0 ? 0.04 : - 0.04;
              bom[i].rota  += (bom[i].id % 10 / 3) == 0 ? 0.130 : - 0.130;
              if (count_bom % (20 + difficulty * 4) == 0) bom[i].speed += 1 + 1 * (bom[i].id % 2);
            }
            else if (bom[i].id / 1000 == 1){
              bom[i].rota += bom[i].id % 2 == 0 ? 0.1 : - 0.1;
            }
          }
        }
        adding_rad += 0.03;

      break;

      default:
      break;
    }
    count_bom ++;
  }

  for (int i = 0; i < NUM_OF_BOMSHOT; i++) {

    if (bom[i].flag) {

      if (dyingcount > 0 && !bom[i].getItem) {
        bom[i].imgN    = 1;
        bom[i].speed   = 20;
        bom[i].getItem = true;
      }

      if (bom[i].getItem) bom[i].rad = atan2(y - bom[i].y, x - bom[i].x);

      if (bom[i].getItem && sqrt((bom[i].x - x) * (bom[i].x - x) + (bom[i].y - y) * (bom[i].y - y)) < 32) {
        bom[i].flag    = false;
        bom[i].getItem = false;
        score += 10;
        playSE[3] = true;
      }
      else if (invincibleTime == 0 && sqrt((bom[i].x - x) * (bom[i].x - x) + (bom[i].y - y) * (bom[i].y - y)) < (imgW[bom[i].imgN] / 4 + 8)) {
        nowHP = nowHP > 100 ? nowHP - 1 : 0;

        if (nowHP == 0 && alive) {
          //playSE[2] = true;
          alive = false;
        }
        else if (alive){
          //playSE[1] = true;
          invincibleTime = 30;
        }
      }

      bom[i].x += cos(bom[i].rad) * bom[i].speed;
      bom[i].y += sin(bom[i].rad) * bom[i].speed;

      if (bom[i].y < LIMIT_U - 20 || bom[i].y > LIMIT_D + 20 || bom[i].x < LIMIT_L - 20 || bom[i].x > LIMIT_R + 20) {
        bom[i].flag = false;
      }
    }
  }
  if (count_bom > bom_time[bom_type] + 200) {

    boming = false;
    count_bom = 0;
  }
}

void PLAYER::Draw() {

  SetDrawArea(LIMIT_L, LIMIT_U, LIMIT_R, LIMIT_D);

  if (alive && invincibleTime % 6 < 3) {
    DrawGraph(x - pimgW / 2, y - pimgH / 2, pimg[12 + (movie / 5)], TRUE);
  }

  for (int i = 0; i < NUM_OF_SHOT; i++) {
    if (shot[0][i].flag) {
      DrawRotaGraph(shot[0][i].x, shot[0][i].y, 1.0f, shot[0][i].rota, img[shot[0][i].imgN], TRUE);
    }
    if (shot[1][i].flag) {
      DrawRotaGraph(shot[1][i].x, shot[1][i].y, 1.0f, shot[1][i].rota, img[shot[1][i].imgN], TRUE);
    }
  }

  for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
    if (bom[i].flag) {
      DrawRotaGraph(bom[i].x, bom[i].y, 1.0f, bom[i].rota, img[bom[i].imgN], TRUE);
    }
  }
}

void PLAYER::DrawStatus() {

  SetDrawArea(10, 10, 1270, 950);
  SetFontSize(30);

  DrawFormatString(960, 10, color_white, "GAMECOUNT: %07d", gamecount);
  DrawFormatString(960, 50, color_white, "SCORE:   %010d", score);

  double hpRate = nowHP / maxHP;
  color_HP = hpRate > 0.5 ? color_blue : hpRate > 0.3 ? color_yellow : color_red;
  DrawFormatString(960, 110, color_white, "HP: %5d/%5d", (int)nowHP, maxHP);
  DrawBox(960, 140, hpRate * 300 + 960, 160, color_HP, TRUE);

  double powerRate = power / 4.0;
  DrawFormatString(960, 190, color_white, "POWER: %3.2lf/4.00", power);
  DrawBox(960, 220, powerRate * 300 + 960, 240, color_blue, TRUE);

  DrawFormatString(960, 270, color_white, "BOM:");
  DrawBox(960, 300, 960 + 300, 320, color_blue, TRUE);
}

void PLAYER::GetStatus(int *max, double *now, double *power) {
    *max   = this -> maxHP;
    *now   = this -> nowHP;
    *power = this -> power;
}

void PLAYER::GetPosition(double *tmpx, double *tmpy) {
    *tmpx = (int)x;
    *tmpy = (int)y;
}

bool PLAYER::GetShotPosition(int i, int j, double *x, double *y) {

  if (shot[i][j].flag) {
    *x = shot[i][j].x;
    *y = shot[i][j].y;
    return true;
  }
  else {
    return false;
  }
}

void PLAYER::All() {

  Move();
  Shot();
  Draw();
  DrawStatus();

  //自機アニメーションカウント
  movie = movie % 20;

  shot_change_count = shot_change_count % 100;
  count_shot = count_shot % 1200;

  if (gamecount % 3 == 0) {
    power = power < 4 ? power + 0.01 : 4;
  }
}

void PLAYER::Reset() {

  alive = true;

  moveL = moveR = moveU = moveD = 0;
  move_speed = 10;
  movie = 0;

  x = 480;
  y = 480;

  power = 4;
  score = 0;

  canShoot = true;
  shot_type = 0;
  shot_change_count = 0;
  count_shot = 0;

  shot_speed[0] = 24;

  boming = false;
  bom_type = 0;
  count_bom = 0;

  pre_adding_rad = 0;
  adding_rad = 0;

  for (int n = 0; n < 2; n++) for (int i = 0; i < NUM_OF_SHOT; i++) shot[n][i].speed = shot_speed[0];
  for (int i = 0; i < NUM_OF_BOMSHOT; i++) bom[i].flag = false;
}
