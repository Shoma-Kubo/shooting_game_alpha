#include <windows.h>

#define MSG(str) {\
  MessageBox(NULL, str, "Message", MB_OK);}

#define NUM_OF_SHOT 20;
#define SHOT_SPEED  12;

extern char key[256];

struct SHOT {

  bool flag;
  int w, h, img;
  double x, y;
};
