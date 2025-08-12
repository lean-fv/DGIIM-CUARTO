#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include<GL/glu.h>
#include <math.h>
#include <iostream>
using namespace std;


//////////////////////////////////////////////////////////////////

/*

    @author Leandro Jorge Fernández Vega


    This project is a Basketball game.

    - The basket will be seen from the left side, leaving the ring by to the right of the basket.

    - The player will adjust the angle of the throw, having the distance to the basket
    and the velocity of throw fixed.

    - When the ball hits the board or the ring, it will bounce back.

    - The game will include a scoreboard.

*/
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//Constants
const float EPSILON=0.2; //Increment to adjust the precision when determining a score.
const float PI=M_PI, g=9.8, COLISION_FRICTION=0.8;

//Variables
float cx=25, cy=0.75; //Center of the ball
float velocity=17,vx,vy; //Speed of the ball
float angle=M_PI; //Angle of throw
float t=0; //Time

bool above_basket=false,ball_thrown=false,ascending_aim=true, descending_aim=false; //Flags
int score=0;
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//Down_Left -> Down_Right -> Up_Right -> Up_Left
void DrawPlane(pair<float,float> dl, pair<float,float> dr, pair<float,float> ur, pair<float,float> ul){

    glBegin(GL_QUADS);
        //Down_left
        glVertex3f(dl.first, dl.second, 0);
        //Down_right
        glVertex3f(dr.first, dr.second, 0);
        //Up_right
        glVertex3f(ur.first, ur.second, 0);
        //Up_left
        glVertex3f(ul.first, ul.second, 0);
    glEnd();
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//Overload for rectangular boards
void DrawPlane(float i, float j, float k, float l){

    pair<float,float> dl(i,j), dr(k,j), ur(k,l), ul(i,l);
    DrawPlane(dl,dr,ur,ul);
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//Function that draws the ground
void DrawGround(){
    glColor3f(0.6f, 0.3f, 0.0f);
    DrawPlane(-40,-2,40,0);
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//Function that draws the whole basket
void DrawBasket(){

    //Main Post
    glColor3f(1.0,1.0,1.0);
    DrawPlane(0,0,1,10);

    //Auxiliar Post
    pair<float,float> dl(1,5), dr(5,8), ur(5,9), ul(1,6);
    DrawPlane(dl,dr,ur,ul);

    //Board
    glColor3f(0.0,0.0,0.0);
    DrawPlane(5,6,5.5,11);

    //Ring
    glColor3f(1.0, 0.647, 0.0);
    DrawPlane(5.5,7.5,8.5,8);
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
/*Function that draws the ball, regular parametrization of the circle.
    Center=(cx,cy)
    Radius=r
*/
void DrawBall(float cx, float cy, float r) {

    glColor3f(1.0, 0.647, 0.0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy); //First point is the center

        for (int i = 0; i <= 360; i++) {
            float alpha = i * PI / 180; // Convert to rad
            float x = cx + r * cos(alpha);
            float y = cy + r * sin(alpha);
            glVertex2f(x, y);
        }
    glEnd();
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
/*Function which draws the aim based on the center and radius of
the ball*/

void DrawAim(float cx,float cy, float r, float alpha){

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2f(cx,cy);
        glVertex2f(cx+2*r*cos(alpha),cy+2*r*sin(alpha));
    glEnd();

}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
/*Function that determines whether the balled entered through the
ring or not.

We consider a score */
bool isScore() {

    bool score =false;
    if(cx <= 8.5 - EPSILON && cx >= 5.5 && cy<=8 && cy >= 7.5 && above_basket)
        score=true;

    return score;
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
/*Function to restart the game*/
void Restart(){

    cx=25;
    cy=0.75;
    t=0;
    velocity=17;
    angle=PI;
    ball_thrown=false;
    above_basket=false;
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
void init()
{
    glClearColor(0.0, 1.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-15,-5,-30.0);
    DrawGround();
    DrawBasket();
    DrawBall(cx,cy,0.75);
    if(!ball_thrown) DrawAim(cx,cy,0.75,angle);

    else{

        //Determines whether the ball surpased the height of the ring
        if(cy>=7.5) above_basket=true;

        cx=25 + vx*t;
        cy=0.75 + vy*t - 0.5*g*t*t;
        t+=0.001;


        //The ball collides.

        //Ground

        //Board and ring
        if((cx<= 5.5)&& (cy <= 11 && cy >= 6) ||
           (cx<= 8.5)&& (cy <= 8 && cy >= 7.5)){

            vx *= COLISION_FRICTION; //Reduces speed
            angle = -angle; //Inverts direction

        }
        //Base of the ring

        //Restart
        if(cx<=0 || cy>=20 || cy<=0) Restart();
    }

}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
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
                    if (event.key.keysym.sym== SDLK_SPACE && !ball_thrown){
                        ball_thrown=true;


                    }

                break;

            }
        }

        if(!ball_thrown){

            vx=velocity*cos(angle);
            vy= velocity*sin(angle);

            //The aim goes up
            if(angle>=PI){
                ascending_aim=true;
                descending_aim=false;
            }
            //The aim goes down
            if(angle<=PI/2){
                ascending_aim=false;
                descending_aim=true;
            }

            if(ascending_aim)  angle-=1e-4;
            if(descending_aim) angle+=1e-4;
        }


        //Score check
        if(isScore()) {
            Restart();
            score+=3;
            cout << "Score: " << score << endl;
            if(score >= 10)
                cout <<"Wow! You should play in the NBA" << endl;
        }

        display();


        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
//////////////////////////////////////////////////////////////////
