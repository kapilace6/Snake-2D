//***********************************
//	  Header Files & Namespaces
//***********************************
#include "Snake.h"							//Custom made Header File which holds
											//the Definition of all Classes of the Game

//***********************************
//		Global Declarations
//***********************************
Snake S;

//***********************************
//		Keybord Inputs
//***********************************
void Sys::SpecKeyPress(int key, int x, int y)		//Primary Controls
{
	switch (key)
	{
	case GLUT_KEY_UP:
		tdir = 1;
		break;

	case GLUT_KEY_DOWN:
		tdir = 2;
		break;

	case GLUT_KEY_LEFT:
		tdir = 3;
		break;

	case GLUT_KEY_RIGHT:
		tdir = 4;
		break;
	}
}
void SpecKeyPress(int key, int x, int y) { S.SpecKeyPress(key, x, y); }

void Sys::handleKeypress(unsigned char key, int x, int y)		//Secondary Controls
{
	switch (key) 
	{
		case 27:							//ASCII value of the Escape Button
			exit(0);

		case 'w':							//Move Up
		case 'W':
			tdir = 1;
			break;

		case 's':							//Move Down
		case 'S':
			tdir = 2;
			break;

		case 'a':							//Move Left
		case 'A':
			tdir = 3;
			break;

		case 'd':							//Move Right
		case 'D':
			tdir = 4;
			break;

		case 'r':							//Admin Access : Reset Level
		case 'R':
			S.reset();
	}
}
void handleKeypress(unsigned char key, int x, int y) { S.handleKeypress(key, x, y); }

//***********************************
//	3D Rendering Initialization
//***********************************
void initRendering() 
{
	glEnable(GL_DEPTH_TEST);					//Enable Depth of Snake
	glEnable(GL_COLOR_MATERIAL);				//Enable Colours
	glEnable(GL_NORMALIZE);						//Enable Normalisation of Light on Scene
	glShadeModel(GL_SMOOTH);					//Smooth Shade the Snake
	glutSetCursor(GLUT_CURSOR_NONE);			//Disable Mouse Pointer
}

//***********************************
//		Resizing Of Window
//***********************************
void handleResize(int w, int h) 
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//***********************************
//		Drawing Scene
//***********************************
void drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			//Clear Screen to Redraw Scenario per Refresh
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);									//Game consists of 2 Lights
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat ambientcolor[] = { 0.2f, 0.2f, 0.2f, 1.0f };	//Shadow colour of Snake
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);
	
	GLfloat diff[] = { 1.0f, 1.0f, 1.0f, 1.0f };			//Colour of Light (White)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);

	GLfloat pos0[3] = { 4.5f, 3.0f, 5.0f };					//Positions of Lights
	GLfloat pos1[3] = { -4.5f, -3.0f, 5.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);

	if(!S.cDead())
		S.Traverse();
	else
	{
		S.T();
		S.Dead();
		glutSwapBuffers();
	}

	glutSwapBuffers();
}

//***********************************
//		Update Function
//***********************************
void update(int value) 
{	
	S.Update();

	glutPostRedisplay();
	glutTimerFunc(S.Speed(), update, 0);
}

//***********************************
//		Main Function
//***********************************
int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
//	glutInitWindowSize(S.w, S.d);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Snake 2D");					//Name of the Game
	glutFullScreen();								//Play Game in FullScreen
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutSpecialFunc(SpecKeyPress);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(250, update, 0);					//Begin Level 1 with Refresh Period of 250ms
	
	glutMainLoop();
	return 0;
}

