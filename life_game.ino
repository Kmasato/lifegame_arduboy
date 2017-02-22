#include "Arduboy.h"

#define W 3
#define WIDTH 25
#define HEIGHT 25

Arduboy arduboy;

bool field[WIDTH][HEIGHT];
bool game_flag = false;
int cX = 0;
int cY = 0;
int gene = 0;


void first_setting(){
  
   for(int i=0; i<WIDTH;i++){
    for(int j=0; j<HEIGHT; j++){
      field[i][j] = false;
      }
    }
  }

void draw(){

  arduboy.clear();
  
  for(int i=0; i<WIDTH; i++){
    for(int j=0; j<HEIGHT; j++){
      if(field[i][j] == false){
        arduboy.fillRect(W*i + 30,W*j,W,W,WHITE);
        }
       if(field[i][j] == true)
        arduboy.fillRect(W*i +30, W*j,W,W,BLACK);
       if(game_flag == false) 
        arduboy.fillRect(W*cX + 30, W*cY,W,W,BLACK);
      }
    }

    arduboy.setCursor(4,20);
    if(game_flag == false)
      arduboy.print(F("STOP"));
    else
      arduboy.print(F("PLAY"));
    arduboy.setCursor(4,32);
    arduboy.print(gene);


  arduboy.display();
}

void update_field(){
  bool next_field[WIDTH][HEIGHT];
  int x=0, y=0;
  int count = 0;

  gene ++;
  
  for(int i=0; i<WIDTH; i++){
    for(int j=0; j<HEIGHT; j++){
      next_field[i][j] = field[i][j];
    }
  }
    for(int i = 0; i<WIDTH; i++){
      for(int j = 0; j<HEIGHT; j++){
        count = 0;
        
        for(int k=0; k<9; k++){
          x=i+k%3-1;
          y=j+k/3-1;
          if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT){
            if(next_field[x][y]==true)
              count++;
          }
        
        }
      

      switch(count){
        case 3:
          field[i][j] = true;
          break;
        case 4:
          field[i][j] = next_field[i][j];
          break;
        default:
          field[i][j] = false;
          break;
        }
      }
    }

  
}
void operate_button(){
  int r_up = 0, l_up = 0, u_up = 0, d_up = 0;
  int a_up = 0, b_up = 0;
  
  if(arduboy.pressed(RIGHT_BUTTON) && cX < WIDTH){
    cX++;
    delay(100);
    }
  if(arduboy.pressed(LEFT_BUTTON) && cX > 0){
    cX--;
    delay(100);
    }
  if(arduboy.pressed(UP_BUTTON) && cY > 0){
    cY--;
    delay(100);
    }
  if(arduboy.pressed(DOWN_BUTTON) && cY < HEIGHT){
    cY++;
    delay(100);
    }
  if(arduboy.pressed(B_BUTTON)){
    if(field[cX][cY] == true)
      field[cX][cY] = false;
    else
      field[cX][cY] = true;
    delay(100);
  }

  if(arduboy.pressed(A_BUTTON)){
    if(game_flag == false){
      game_flag = true;
      }
    else if(game_flag == true)
      game_flag = false;

    delay(100);
    }

   //Reset Display
   if(arduboy.pressed(UP_BUTTON) && arduboy.pressed(DOWN_BUTTON)){
    first_setting();
    gene = 0;
    delay(100);
    }
}
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  first_setting();
  arduboy.display();
}

void loop() {
  
  operate_button();
  if(game_flag == true)
    update_field();
  draw();
  
}
