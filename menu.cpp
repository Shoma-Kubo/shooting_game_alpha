#include "pch.h"
#include "control.h"

MENU::MENU() {

  cnt_menu = CNT_MENU_MAX;

  selected = 0;
  selected_yes = false;
  cnt_key_pushed = 0;

  confirm = false;
  options_opened = false;
  select_diff = false;
}

void MENU::MainMenu() {

  SetDrawArea(10, 10, 1270, 950);
  SetFontSize(50);
  DrawFormatString(590, 100, color_white, "MENU");

  SetFontSize(30);
  color = selected == 0 ? color_blue : color_white;
  DrawFormatString(120 + cnt_menu, 200, color, "GAME START");

  color = selected == 1 ? color_blue : color_white;
  DrawFormatString(140 + cnt_menu, 300, color, "OPTIONS");

  color = selected == 2 ? color_blue : color_white;
  DrawFormatString(160 + cnt_menu, 400, color, "QUIT GAME");
}

void MENU::GameMenu() {

  SetDrawArea(10, 10, 1270, 950);
  SetFontSize(50);
  DrawFormatString(705, 100, color_white, "GAME MENU");

  SetFontSize(30);
  color = selected == 10 ? color_blue : color_white;
  DrawFormatString(120 + cnt_menu, 200, color, "BACK TO GAME");

  color = selected == 11 ? color_blue : color_white;
  DrawFormatString(140 + cnt_menu, 300, color, "RESTART");

  color = selected == 12 ? color_blue : color_white;
  DrawFormatString(160 + cnt_menu, 400, color, "BACK TO MENU");

  color = selected == 13 ? color_blue : color_white;
  DrawFormatString(180 + cnt_menu, 500, color, "OPTIONS");

  color = selected == 14 ? color_blue : color_white;
  DrawFormatString(200 + cnt_menu, 600, color, "QUIT GAME");
}

void MENU::Options() {

  SetDrawArea(10, 10, 1270, 950);
  SetFontSize(50);
  DrawFormatString(527, 100, color_white, "OPTIONS");

  SetFontSize(30);
  color = selected == 20 ? color_blue : color_white;
  DrawFormatString(120 + cnt_menu, 200, color, "BGM :  %3d %", volume_bgm);

  color = selected == 21 ? color_blue : color_white;
  DrawFormatString(140 + cnt_menu, 300, color, "SE :  %3d %", volume_se);

  color = selected == 22 ? color_blue : color_white;
  DrawFormatString(160 + cnt_menu, 400, color, "DONE");
}

void MENU::Confirm() {

  SetFontSize(30);
  DrawFormatString(600, 200 + (selected % 10) * 100, color_white, "Is it OK?");
  color = selected_yes ? color_blue : color_white;
  DrawFormatString(800, 200 + (selected % 10) * 100, color, "YES");
  color = !selected_yes ? color_blue : color_white;
  DrawFormatString(880, 200 + (selected % 10) * 100, color, "NO");
}

void MENU::SelectDifficulty() {

  SetFontSize(30);
  color = difficulty == 0 ? color_blue : color_white;
  DrawFormatString(600, 200, color, "LOLLIPOP      |o---");
  color = difficulty == 1 ? color_blue : color_white;
  DrawFormatString(600, 300, color, "MILK TEA      |oo--");
  color = difficulty == 2 ? color_blue : color_white;
  DrawFormatString(600, 400, color, "CHOCOLATE     |ooo-");
  color = difficulty == 3 ? color_blue : color_white;
  DrawFormatString(600, 500, color, "BLACK COFFEE  |oooo");
  color = difficulty == 4 ? color_blue : color_white;
  DrawFormatString(600, 600, color, "CANCEL");

  SetFontSize(20);
  DrawFormatString(600, 240, color_white, "Sweetest. Nobody fails.");
  DrawFormatString(600, 340, color_white, "Good afternoon. You may have one more cup.");
  DrawFormatString(600, 440, color_white, "Some says this is bitter, but you don't.");
  DrawFormatString(600, 540, color_white, "Keep trying. That's only.");
}

void MENU::Move() {

  CONTROL &control = CONTROL::GetInstance();

  if (!confirm && !select_diff) {

    if (key[KEY_INPUT_UP] && cnt_key_pushed == 0) {

      if      (selected < 10) selected = (selected + 2) % 3;
      else if (selected < 20) selected = (selected % 10 + 4) % 5 + 10;
      else if (selected < 30) selected = (selected % 20 + 2) % 3 + 20;

      cnt_key_pushed = 6;
    }

    if (key[KEY_INPUT_DOWN] && cnt_key_pushed == 0) {

      if      (selected < 10) selected = (selected + 1) % 3;
      else if (selected < 20) selected = (selected % 10 + 1) % 5 + 10;
      else if (selected < 30) selected = (selected % 20 + 1) % 3 + 20;

      cnt_key_pushed = 6;
    }

    if (key[KEY_INPUT_RIGHT] && cnt_key_pushed == 0) {

      if (selected == 20) {
        volume_bgm = volume_bgm < 100 ? volume_bgm + 5 : 100;
        for (int i = 0; i < 10; i++) ChangeVolumeSoundMem(200 * (volume_bgm / 100.0), bgm[i]);
      }
      if (selected == 21) {
        volume_se = volume_se < 100 ? volume_se + 5 : 100;
        for (int i = 0; i < 10; i++) ChangeVolumeSoundMem(200 * (volume_se / 100.0), se[i]);
      }

      cnt_key_pushed = 6;
    }

    if (key[KEY_INPUT_LEFT] && cnt_key_pushed == 0) {

      if (selected == 20) {
        volume_bgm = volume_bgm > 0 ? volume_bgm - 5 : 0;
        for (int i = 0; i < 10; i++) ChangeVolumeSoundMem(200 * (volume_bgm / 100.0), bgm[i]);
      }
      if (selected == 21) {
        volume_se = volume_se > 0 ? volume_se - 5 : 0;
        for (int i = 0; i < 10; i++) ChangeVolumeSoundMem(200 * (volume_se / 100.0), se[i]);
      }

      cnt_key_pushed = 6;
    }

  }
  else if (confirm && !select_diff) {

    if ((key[KEY_INPUT_RIGHT] || key[KEY_INPUT_LEFT]) && cnt_key_pushed == 0) {
      if (selected_yes) selected_yes = false;
      else selected_yes = true;

      cnt_key_pushed = 6;
    }
  }
  else if (select_diff) {

    if (key[KEY_INPUT_UP] && cnt_key_pushed == 0) {

      difficulty = (difficulty + 4) % 5;
      cnt_key_pushed = 6;
    }

    if (key[KEY_INPUT_DOWN] && cnt_key_pushed == 0) {

      difficulty = (difficulty + 1) % 5;
      cnt_key_pushed = 6;
    }
  }

  if ((key[KEY_INPUT_Z] || key[KEY_INPUT_RETURN]) && cnt_key_pushed == 0 && cnt_menu == 0) {

    if (!confirm && !select_diff) {

      switch (selected) {

        case  0:

          difficulty = 1;
          select_diff = true;
          break;

        case 10:

          menu_opened = false;
          break;

        case  1:
        case 13:

          options_opened = true;
          cnt_menu = CNT_MENU_MAX;
          selected = 20;
          break;

        case  2:
        case 11:
        case 14:

          confirm = true;
          selected_yes = false;
          break;

        case 12:

          confirm = true;
          selected_yes = false;
          break;

        case 22:

          options_opened = false;
          selected = gamecount == 0 ? 0 : 10;
          cnt_menu = CNT_MENU_MAX;
          break;

        default:
          break;
      }

    }
    else if (confirm && !select_diff) {

      if (selected_yes) {

        if (selected == 2 || selected == 14) {
          quit = true;
        }
        else if (selected == 10) {
          menu_opened = false;
        }
        else if (selected == 11) {
          menu_opened = false;
          control.ResetAll();
        }
        else if (selected == 12) {
          selected = 0;
          cnt_menu = CNT_MENU_MAX;
          control.ResetAll();
        }
      }
      confirm = false;
    }
    else if (select_diff) {

      if (difficulty < 4) {

        menu_opened = false;
        control.ResetAll();
      }
      select_diff = false;
    }

    cnt_key_pushed = 6;
  }
}

void MENU::OpenGameMenu() {

  menu_opened = true;
  selected = 10;
  cnt_menu = CNT_MENU_MAX;
}

void MENU::All() {

  if (options_opened) Options();
  else {
    if (gamecount == 0) MainMenu();
    else GameMenu();
  }
  if (confirm) Confirm();
  if (select_diff) SelectDifficulty();
  Move();

  if (cnt_key_pushed > 0) cnt_key_pushed -= 1;
  if (cnt_menu > 0) cnt_menu -= 5;
}
