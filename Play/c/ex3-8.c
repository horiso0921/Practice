#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

void draw_mino(int y, int x, int f_mino[4][2]);
void create_mino(int type, int f_mino[4][2]);
void rotate_mino(int type, int f_mino[4][2]);

int mino_data[7][4][2] = {
  { {1, 0}, {2, 0}, {1, 1}, {2, 1} }, //O type
  { {1, 0}, {1, 1}, {1, 2}, {1, 3} }, //I type
  { {1, 1}, {2, 1}, {0, 2}, {1, 2} }, //S type
  { {0, 1}, {1, 1}, {1, 2}, {2, 2} }, //Z type
  { {2, 0}, {0, 1}, {1, 1}, {2, 1} }, //L type
  { {0, 0}, {0, 1}, {1, 1}, {2, 1} }, //J type
  { {1, 1}, {0, 2}, {1, 2}, {2, 2} }  //T type
};

int main(void)
{
  int x, y, h, w;
  int key, mino, f_mino[4][2];

  initscr();
  noecho();
  cbreak();
  timeout(0);
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, h, w); 
  y = 2;
  x = w / 2;

  mino = rand() % 7;
  create_mino(mino, f_mino);

  while (1) {
    erase();
    border(0,0,0,0,0,0,0,0);
    draw_mino(y,x,f_mino);
    refresh();

    key = getch();
    if (key == 'p') {
      while (1) {
        int _key = getch();
        if(_key == 'p') break;
        if(_key == 'q'){
          key = 'q';
          break;
        }
      }
    }
    if (key == 'q')
      break;
    if (key == KEY_UP){
      rotate_mino(mino, f_mino);
    }
    if (key == KEY_LEFT){
    }
    if (key == KEY_RIGHT){
    }
    y++;
    if (y >= h-1) {
      //y = 2;
      y = 0;
      mino = rand() % 7;
      create_mino(mino, f_mino);
    }
  
  usleep(100000);
  }
  endwin();
  return 0;
}
void rotate_mino(int type, int f_mino[4][2])
{
  int i, rx, ry;
  for(i=0;i<4;i++){
    rx = f_mino[i][1];
    ry = - f_mino[i][0] + 3;
    f_mino[i][0] = rx;
    f_mino[i][1] = ry;
  }
}

void create_mino(int type, int f_mino[4][2])
{
  int i;
  for(i=0;i<4;i++){
    f_mino[i][0] = mino_data[type][i][0];
    f_mino[i][1] = mino_data[type][i][1];
  }
}

void draw_mino(int y, int x, int f_mino[4][2])
{
  int i;

  ACS_CKBOARD = '#';
  for(i=0;i<4;i++){
    mvhline(y + f_mino[i][1], x + f_mino[i][0], ACS_CKBOARD,1);
  }
}