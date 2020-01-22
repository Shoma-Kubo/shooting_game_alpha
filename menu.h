class MENU {

  private:
    int cnt_menu;

    int  selected;
    bool selected_yes;
    int  cnt_key_pushed;

    bool confirm;
    bool options_opened;
    bool select_diff;

    int color;
    int color_white = GetColor(255, 255, 255);
    int color_blue  = GetColor(100, 100, 255);

  private:
    void MainMenu();
    void GameMenu();
    void Options();
    void Confirm();
    void SelectDifficulty();
    void Move();

  public:
    MENU();
    void OpenGameMenu();
    void All();
};
