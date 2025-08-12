#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include<GL/glu.h>

float angle=0,angle1=0,angle2=0;

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

    glTranslatef(0.0,0.0,-15.0);
    glRotatef(angle,0.0, 1.0, 0.0);
    glTranslatef(0.0,0.0,6.0);



    //Cabin

    //Front
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

		glVertex3f(-1.0,-1.0, -5.0);
		glVertex3f( -1.0,-3.0, -5.0);
		glVertex3f( 1.0,-3.0, -5.0);
		glVertex3f( 1.0,-1.0, -5.0);

	glEnd();

	//Back
	glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(-1.0,-1.0, -7.0);
		glVertex3f( -1.0,-3.0, -7.0);
		glVertex3f( 1.0,-3.0, -7.0);
		glVertex3f( 1.0,-1.0, -7.0);

    glEnd();

    //Right
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f( 1.0,-3.0, -5.0);
		glVertex3f( 1.0,-1.0, -5.0);
        glVertex3f( 1.0,-1.0, -7.0);
		glVertex3f( 1.0,-3.0, -7.0);

    glEnd();


    //Left
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(-1.0,-3.0, -5.0);
		glVertex3f( -1.0,-1.0, -5.0);
        glVertex3f(-1.0,-1.0, -7.0);
		glVertex3f( -1.0,-3.0, -7.0);

    glEnd();

    //Bottom
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(-1.0,-3.0, -7.0);
		glVertex3f(-1.0,-3.0, -5.0);
        glVertex3f(1.0,-3.0, -5.0);
		glVertex3f(1.0,-3.0, -7.0);

    glEnd();

    //----------------------------------------------------------------------------------


    //Tail

    //Top
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(-0.5,-1.5, -5.0);
		glVertex3f(-0.5,-1.5, -10.0);
		glVertex3f(0.5,-1.5, -10.0);
		glVertex3f(0.5,-1.5, -5.0);

    glEnd();

	//Back
	glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(-0.5,-1.5, -10.0);
		glVertex3f( -0.5,-2.5, -10.0);
		glVertex3f( 0.5,-2.5, -10.0);
		glVertex3f( 0.5,-1.5, -10.0);

    glEnd();

    //Right
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(0.5,-1.5, -5.0);
		glVertex3f(0.5,-2.5, -5.0);
		glVertex3f( 0.5,-2.5, -10.0);
		glVertex3f( 0.5,-1.5, -10.0);

    glEnd();


    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(-0.5,-1.5, -5.0);
		glVertex3f(-0.5,-2.5, -5.0);
		glVertex3f(-0.5,-2.5, -10.0);
		glVertex3f(-0.5,-1.5, -10.0);

    glEnd();

    //Bottom
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

        glVertex3f(-0.5,-2.5, -5.0);
		glVertex3f(-0.5,-2.5, -10.0);
		glVertex3f(0.5,-2.5, -10.0);
		glVertex3f(0.5,-1.5, -5.0);

    glEnd();


	//----------------------------------------------------------------------------------


	//Blades

	//Top

    glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glTranslatef(0.0,-1.0,-6.0);
    glRotatef(angle1,0.0, 1.0, 0.0);
    glTranslatef(0.0,1.0,6.0);
    glBegin(GL_QUADS);

        glVertex3f(-0.125,-1.0, -8.0);
		glVertex3f(-0.125,-1.0, -4.0);
		glVertex3f(0.125,-1.0, -4.0);
		glVertex3f(0.125,-1.0, -8.0);

    glEnd();
    glPopMatrix();

	//Tail
    glPushMatrix();
	glColor3f(0.0,0.0,0.0);

	glTranslatef(0.5,-2.25,-9.125);
    glRotatef(angle,1.0, 0.0, 0.0);
    glTranslatef(-0.5,2.25,9.125);



    glBegin(GL_QUADS);

        glVertex3f(0.5,-1.0, -9.0);
		glVertex3f(0.5,-1.0, -9.25);
		glVertex3f(0.5,-3.5, -9.25);
		glVertex3f(0.5,-3.5, -9.0);

    glEnd();
    glPopMatrix();

	//----------------------------------------------------------------------------------

    angle +=0.01;
	angle1+=0.04;
	angle2-=0.02;


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


