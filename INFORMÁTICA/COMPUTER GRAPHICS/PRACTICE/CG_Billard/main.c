#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include<GL/glu.h>
#include <math.h>

//Variables
float angle=30.0, posx=0.0, posy=0.0, s=0.01;
float increment_x, increment_y;


void DrawCube()
{
    glPushMatrix();

    glColor3f(0.0,0.0,1.0);
    glTranslatef(posx,0.0,posy); //This way because later on we rotate in the display function
    //glRotatef(angle,0.0,1.0,0.0);

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
		glBegin(GL_QUADS);			// right face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
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

void DrawPlane(){

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glScalef(30.0,1.0,30.0);

    glBegin(GL_QUADS);			// bottom face
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
    glPopMatrix();
}


void init()
{
    increment_x=s*cos(angle*M_PI/180);
    increment_y=s*sin(angle*M_PI/180);

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

    glTranslatef(0.0,-2.0,-50.0);
    glRotatef(90,1.0,0.0,0.0);

    DrawCube();
    DrawPlane();

    if(posx>=0.5*30 || posx<=-0.5*30) increment_x=-increment_x;
    if(posy>=0.5*30 || posy<=-0.5*30) increment_y=-increment_y;

    posx+=increment_x;
    posy+=increment_y;
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

                case SDL_KEYDOWN:


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




