#include "define.h"

class PLAYER {

  private:
    bool alive;
    int w, h, img[12];
    int move_left, move_right, move_up, move_down, move_distance, movie;
    double x, y;

    SHOT shot[NUM_OF_SHOT];
    int count_shot;

  private:
    void Move();
    void Draw();
    void Shot();

  public:
    PLAYER();
    void All();
};
