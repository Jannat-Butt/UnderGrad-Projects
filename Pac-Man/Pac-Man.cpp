// Adding Libraries
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h> // I have also used the std::cin for get characters but it needs enter after each insertion
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

// The size of maze is fixed
#define row_maze 30
#define col_maze 61

// initial pacman x and y
int pac_x = 1; int pac_y = 4;

// init with zero
int mx = 0; int my = 0;

// init ghost locations 
int g1_x = 3;  int g1_y = 5; 
int g2_x = 4; int g2_y = 1;

// safe area initialization for ghost and pallets so it will not go out of maze
int max_safe_x = col_maze-5;
int max_safe_y = row_maze-5;
int min_safe_x = 5;
int min_safe_y = 5;

// declaring globals 
char key;
int score;

// assign original and total pallets: they are same
int orig_pallets = 6;
int total_pallets = 6;

// distance and angle for ghost eucledian: initialize with zero
float d = 0.0;
double theta = 0.0;

// GLobal maze
char pacman_maze[row_maze][col_maze] = 
{  
   { "############################################################" },
   { "#        #####                               ####          #" },
   { "#                         ####                             #" },
   { "#                                                          #" },
   { "#        ####                                    ####      #" },
   { "#                                                          #" },
   { "#         ###############################                  #" },
   { "#        #                                                 #" },
   { "#        #                                                 #" },
   { "#        #                                                 #" },
   { "#        #                                                 #" },
   { "#        #                                                 #" },
   { "#        # # # # # # # # # # # # #  #                      #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#          #####                          #####            #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                #################                         #" },
   { "#                                                          #" },
   { "#            #####                           #####         #" },
   { "#                                                          #" },
   { "############################################################" }
}; // <-- CAUTION! Semicolon necessary!

/*void random_maze()
{   
    
    int n = 0;
    int total_walls = 20;
    while(n<total_walls)
    {
        int plx, ply;
        plx = rand() % max_safe_x + min_safe_x;
        ply = rand() % max_safe_y + min_safe_y;
        if (pacman_maze[ply][plx]==' ')
        {   
            pacman_maze[ply][plx] = '#';
            n = n + 1;
        }
    }
} */

// pallet random function
void random_pallets()
{   
    
    int n = 1;
    // this will run upto total pallets
    srand(time(0));
    while(n <=total_pallets)
    {   
        // each time pallets x and y coordinates are generated randomly but in the safe area
        int plx, ply;
        plx = rand() % max_safe_x + min_safe_x;
        ply = rand() % max_safe_y + min_safe_y;
        // insert this pallet location into maze empty regions: this if loop never insert at the other locations
        if (pacman_maze[ply][plx]==' ')
        {
            pacman_maze[ply][plx] = 'o'; 
            n = n + 1;
        }
    }
}

// ghost function
void ghost(int pacman_x, int pacman_y)
{ 
    // it is important to clear previous ghost location from maze
    pacman_maze[g2_y][g2_x] = ' ';
    pacman_maze[g1_y][g1_x] = ' '; 

    //First we create the random ghost (#2) by creating x and y location of ghost at random place in safe area
    g2_x = rand() % max_safe_x + min_safe_x;
    g2_y = rand() % max_safe_y + min_safe_y;
    
    // It is important that ghost will never go to walls and pallets : OR this will not let ghost 2 to eat pallets and walls
    if ((pacman_maze[g2_y][g2_x]=='#')||(pacman_maze[g2_y][g2_x]=='o'))
       {
         g2_x = 1;
         g2_y = 1;
       }
    // Place ghost #2  in the free location of maze
    if (pacman_maze[g2_y][g2_x] == ' ')
    {
          pacman_maze[g2_y][g2_x] = '8';
    }
    
    //Ghost # 1 : eucledian distance
    // calculate the eucledian distance between ghost # 1 and pacman
    d = sqrt(pow((pacman_x - g1_x),2) + pow((pacman_y - g1_y),2)); 
    
   
    // Heading angle for ghost by using atan("/")
    theta =atan((pacman_y - g1_y)/(pacman_x - g1_x)); //float
    
    // here we will get this by sine cosine identities polar to cartesian coordiante
    int vg_x = round(d * cos(theta));           
    int vg_y = round(d * sin(theta));

    // new coordinates components
    int new_g1x = pacman_x - vg_x;
    int new_g1y = pacman_y - vg_y;
    
    // update ghost # 1 location
    g1_x = g1_x + new_g1x;
    g1_y = g1_y + new_g1y;
    
    // it is important that ghost will be in safe area
    if (g1_x >= max_safe_x)
    {
        g1_x = max_safe_x;
    }

     if (g1_x <  min_safe_x)
    {
        g1_x = min_safe_x;
    }


    if (g1_y >= max_safe_y)
    {
        g1_y = max_safe_y;
    }

      if (g1_y <  min_safe_y)
    {
        g1_y = min_safe_y;
    }

    // this will not let ghost 1 to eat pallets and walls: Same as ghost 2
    if ((pacman_maze[g1_y][g1_x]=='#')||(pacman_maze[g1_y][g1_x]=='o'))
       {
         g1_x = 1;
         g1_y = 1;
       }

    // place ghost 1 in free location
    if (pacman_maze[g1_y][g1_x]==' ')
       {pacman_maze[g1_y][g1_x] = '8';}
      
    
    d = 0.0;
    theta = 0.0;
}

// Get inputs from keys i-up , k-down, l-right, j-left
/*void give_input()
{   

    key = getch();
    switch(key)
        {
            case 'i': my = -1; break;//up in row 
            case 'k': my = +1; break;//down in row
            case 'l': mx = +1; break;//left in col
            case 'j': mx = -1; break;//right in col
        }
    
}*/

void give_input()
{   
   cin>>key;        //you need to press enter after every direction command i,j,k,l.
   
    switch(key)
        {
            case 'i': my = -1; break;//up in row 
            case 'k': my = +1; break;//down in row
            case 'l': mx = +1; break;//left in col
            case 'j': mx = -1; break;//right in col
        }
    
}

void pacman()
{
    // first delete the old position of pacman in print
    pacman_maze[pac_y][pac_x] = ' ';

    // here we will just find the next coordinates of pacman to check different things
    int nx = mx + pac_x; 
    int ny = my + pac_y; 
 
    // if pacman coordinates after user input are at ghost location, pacman loses
    if (pacman_maze[ny][nx] == '8')
    {
        cout << "You Lose: Ghost eats you"<<endl;
        exit(0);
    }
     // if pacman coordinates after user input are at wall location, do not move pacman
    if (pacman_maze[ny][nx] == '#')
    {
        mx = 0;
        my = 0;
    }
     // if pacman coordinates after user input are at pallet location, pacman get the point and upon eating all pallets pacman wins
    if (pacman_maze[ny][nx] == 'o')
    {
        score = score + 1;
        total_pallets = total_pallets - 1;
        if (score == orig_pallets)
        {
            cout << "You won: All pallets are eaten: Enjoy the score"<<endl;
            exit(0);
            
        }
    }

    // update pacman coordinates
    pac_x = pac_x + mx; 
    pac_y = pac_y + my; 
    
    // print pacman > V ^ < according to key
    if (key == 'k')
    {pacman_maze[pac_y][pac_x] = 'v';}
    if (key == 'i')
    {pacman_maze[pac_y][pac_x] = '^';}
    if (key == 'j')
    {pacman_maze[pac_y][pac_x] = '<';}
    if (key == 'l')
    {pacman_maze[pac_y][pac_x] = '>';}
    mx = 0;
    my = 0;
    
}

// this will display maze
void disp_maze()
{
   for (int i = 0; i < row_maze; i++)
   {
      for (int j = 0; j < col_maze; j++)
      {
         cout<<pacman_maze[i][j];
      }
      cout << "\n";
   }
}

int main()
{   
    
    char enter; 
    cout<< "Welcome to pacman game: Please first enter e to enter the game and then press i to start the game"<< endl;
    cin>>enter;
    if (enter == 'e')
    {
     
   // random_maze();
    random_pallets();
    while(1)
    {   
        give_input();
         system("clear"); 
        pacman();
        ghost(pac_x,pac_y);
        cout<<"Use i,k,l,j for up,down,right,left respectively"<<endl;
        cout << "The score is = " << " " << score << endl;
        cout << " Pacman Location" << " " << "X = " << " " << pac_x << " " << "Y =" << pac_y<< endl;     
        disp_maze();
       
    }
  }
   
   return 0;
}
