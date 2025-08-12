#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include<GL/glu.h>

float angle=0;

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
    glTranslatef(0.0,0.0,-5);
    glRotatef(angle,0.0, 1.0, -5.0);

    //Roof
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_TRIANGLES);

		glVertex3f(0.0, 1.0, -5.0);
		glVertex3f(-1.0,-1.0, -5.0);
		glVertex3f( 1.0,-1.0, -5.0);

    glEnd();

    //Base
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);

		glVertex3f(-1.0,-1.0, -5.0);
		glVertex3f( -1.0,-3.0, -5.0);
		glVertex3f( 1.0,-3.0, -5.0);
		glVertex3f( 1.0,-1.0, -5.0);
	glEnd();

	//Door
	glColor3f(0.0,1.0,1.0);
    glBegin(GL_QUADS);

		glVertex3f(-0.25,-3.0, -4.99);
		glVertex3f( -0.25,-2.0, -4.99);
		glVertex3f( 0.25,-2.0, -4.99);
		glVertex3f( 0.25,-3.0, -4.99);

	glEnd();

	//Windows
	glColor3f(0.0,1.0,1.0);
    glBegin(GL_QUADS);

		glVertex3f(-0.75,-1.25, -4.99);
		glVertex3f(-0.75,-1.0, -4.99);
		glVertex3f( -0.25,-1.0, -4.99);
		glVertex3f( -0.25,-1.25, -4.99);

	glEnd();

	glColor3f(0.0,1.0,1.0);
    glBegin(GL_QUADS);

		glVertex3f(0.75,-1.25, -4.99);
		glVertex3f(0.75,-1.0, -4.99);
		glVertex3f(0.25,-1.0, -4.99);
		glVertex3f(0.25,-1.25, -4.99);

	glEnd();
	angle+=0.01;


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
                if (event.key.keysym.sym==SDLK_SPACE) ;
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

