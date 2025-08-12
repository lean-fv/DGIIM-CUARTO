#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include<GL/glu.h>
#include <math.h>
#include <iostream>
using namespace std;

//Variables
const int BOARD_SIZE=3;
const float SPACE=0.1;
const int P0_PAINTS=0, P1_PAINTS=1, SELECTION=-1;

int posx=0, posy=0;
int board[BOARD_SIZE][BOARD_SIZE];
bool player=false;

void DrawPlane(float i, float j){

    glBegin(GL_QUADS);			// bottom face
			glVertex3f(-i,-j, 0);
			glVertex3f(i,-j, -0);
			glVertex3f(i, j, -0);
			glVertex3f(-i, j, 0);
    glEnd();
}

void DrawBoard(int n){
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            glPushMatrix();
            glTranslatef(2*j,-2*i,0);
            glScalef(1-SPACE,1-SPACE,1.0);

            if(j==posx && i==posy){
                if(board[i][j]==SELECTION){
                    glColor3f(0.0,1.0,0.0);
                }

                if(board[i][j]==P0_PAINTS){
                    glColor3f(1.0,1.0,0.0);
                }

                if(board[i][j]==P1_PAINTS){
                    glColor3f(0.0,1.0,1.0);
                }
            }else{

                if(board[i][j]==SELECTION){
                    glColor3f(1.0,1.0,1.0);
                }

                if(board[i][j]==P0_PAINTS){
                    glColor3f(1.0,0.0,0.0);
                }

                if(board[i][j]==P1_PAINTS){
                    glColor3f(0.0,0.0,1.0);
                }
            }

            DrawPlane(1,1);
            glPopMatrix();
        }
    }
}


bool Winner() {

    bool winner=false;

    //Diagonals
    bool mainDiagonalWin = true;
    bool secondaryDiagonalWin = true;

    for (int i = 1; i < BOARD_SIZE; i++) {
        if (board[i][i] != board[0][0] || board[0][0] == SELECTION)
            mainDiagonalWin = false;

        if (board[i][BOARD_SIZE - i - 1] != board[0][BOARD_SIZE - 1] || board[0][BOARD_SIZE - 1] == SELECTION)
            secondaryDiagonalWin = false;
    }
    winner = (mainDiagonalWin || secondaryDiagonalWin);


    //Checking rows and columns
    for (int i = 0; i < BOARD_SIZE && !winner; i++) {
        bool rowWin = true;
        bool colWin = true;

        for (int j = 1; j < BOARD_SIZE; j++) {
            //Checking rows
            if (board[i][j] != board[i][0] || board[i][0] == SELECTION)
                rowWin = false;

            //Checking columns
            if (board[j][i] != board[0][i] || board[0][i] == SELECTION)
                colWin = false;
        }
        winner=(rowWin || colWin);
    }

    return winner;
}


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-2.0,2.0,-10.0);

    DrawBoard(BOARD_SIZE);

}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    SDL_Window* window = SDL_CreateWindow("My SDL OpenGL project",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glcontext);

    int loop = 1;
    SDL_Event event;
    init();

    for(int i=0; i<BOARD_SIZE;i++)
        for(int j=0; j<BOARD_SIZE;j++)
            board[i][j]=SELECTION;



    while (loop==1)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    loop = 0;
                break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){

                        case SDLK_s:
                            if(posy!=BOARD_SIZE-1) posy++;

                        break;


                        case SDLK_w:
                            if(posy!=0) posy--;
                        break;


                        case SDLK_a:
                            if(posx!=0) posx--;
                        break;


                        case SDLK_d:
                            if(posx!=BOARD_SIZE-1) posx++;
                        break;


                        case SDLK_SPACE:
                            if(board[posy][posx]==SELECTION){
                                if(!player) board[posy][posx]=P0_PAINTS;
                                else board[posy][posx]=P1_PAINTS;
                                player=!player;
                            }

                            if(Winner()) cout << "There is a winner"<<endl;

                        break;
                    }
                break;
            }
        }

        display();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}





