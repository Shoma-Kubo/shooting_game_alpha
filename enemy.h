class ENEMY {

private:
  bool alive, stay, end;
  int phase, waiting;
  int w, h, img[16];
  int in, phase_out, e_movie;

  double x, y;

  int hp, item;

  int move_pattern[5], shot_pattern[5], shot_pattern_index;
  int count_shot;

  ENEMY_SHOT e_shot[NUM_OF_ENEMY_SHOT];

private:
  void Move();
  void Shot();
  void Draw();

public:
  bool All();
  ENEMY(char *char_filename, int *move_pattern, double x, double y, int in, int phase_out, int *shot_pattern, int hp, int item);
  void GetPosition(double *x, double *y);
  void Reset();
};
