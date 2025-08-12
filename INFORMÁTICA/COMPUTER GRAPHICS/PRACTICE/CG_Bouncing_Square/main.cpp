#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include<GL/glu.h>
#include <math.h>

//Variables
float pos_y=0.0; //Position
float dt=0.001; //time increment
float v=0; //Speed
float c=0.8; //Constant to describe the bouncing
float g=9.8; //Constant of gravity

void DrawCube()
{
    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    glTranslatef(0.0,pos_y,0.0);

    glBegin(GL_QUADS);			// top face
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
    glBegin(GL_QUADS);			// front face
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_QUADS);			// right face
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);			// left face
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
    glBegin(GL_QUADS);			// bottom face
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
    glBegin(GL_QUADS);			// back face
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
    glPopMatrix();
}

void DrawLine(){

    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(0.0,-5.0,0.0);

    glBegin(GL_LINES);
			glVertex3f(-10.0f, 0.0f, 0.0f);
			glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
}


void init()
{
    glClearColor(0.0, 1.0, 0.0, 1.0);
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

    glTranslatef(0.0,0.0,-20.0);

    DrawCube();
    DrawLine();

    pos_y-=v*dt + 0.5*g*dt*dt;
    v+=g*dt;

    if(pos_y<=-5.0) {
        v=-c*v;
        pos_y=-5.0;
    }

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
    while (loop==1)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                loop = 0;
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




