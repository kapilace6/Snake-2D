#include "Snake.h"

//***********************************
//	Constructor of Variables Class
//***********************************			//Initializes w & d with the Width and Height
												//of the Screen (FullScreen)
Var::Var() : w(1920), d(1080) {}

//*************************************************
//   Constructor, Destructor of Read Snake Class
//*************************************************
RSnake::RSnake()
{
	fin.open("level.txt");						//level.txt holds the 5 Levels of the Game
	tmp2 = 0;
	tmp1 = 0;
	xy = new XY *[5];

	GetLevelStats();							//Reads amd Stores Level 1 of the Game
	GetLevelStats();
}
RSnake::~RSnake()
{
	fin.close();
	delete[] xy;
}

//***********************************
//	   Level Reading Function
//***********************************			//Quadrant 5 Represents on-Axis Obstacles
void RSnake::GetLevelStats()
{
	fin >> level >> length;
	tmp2 = 0;
	while (tmp2 != 5)
	{
		fin >> tmp1 >> numline[tmp2];
		xy[tmp2] = new XY[numline[tmp2]];

		for (int i = 0; i < numline[tmp2]; i++)
		{
			fin >> xy[tmp2][i].x >> xy[tmp2][i].y;
			xy[tmp2][i].x = (float)(((int)((xy[tmp2][i].x * 5) * w / d)) / (float)5);
		}

		++tmp2;
	}
	tmp2 = 0;
}

//***********************************
//	  Obstacle Drawing Functions
//***********************************
void RSnake::Block(float x, float y)
{
	glPushMatrix();
	glTranslatef(x, y, -6.0f);
	glColor3f(0.7f, 0.3f, 0.0f);

	glBegin(GL_QUADS);
		glVertex3f(0.1f, 0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
	glEnd();
	glPopMatrix();
}
void RSnake::Disp()
{
	--level;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < numline[i]; j++)
			Block(xy[i][j].x, xy[i][j].y);

	++level;
}

//***********************************
//	  Obstacle Collision Check
//***********************************			//The 4 If Statements are for Collision 
												//of the Head of the Snake with an Obstacle
												//In a particular Quadrant of the Scene
bool RSnake::isCollide(float x, float y)
{
	if (x > 0 && y > 0)
		for (int i = 0; i < numline[0]; i++)
		{
			if ((mod(x - xy[0][i].x) < 0.05f) && (mod(y - xy[0][i].y) < 0.05f))
				return true;
		}
	else if (x < 0 && y > 0)
		for (int i = 0; i < numline[1]; i++)
		{
			if ((mod(x - xy[1][i].x) < 0.05f) && (mod(y - xy[1][i].y) < 0.05f))
				return true;
		}
	else if (x < 0 && y < 0)
		for (int i = 0; i < numline[2]; i++)
		{
			if ((mod(x - xy[2][i].x) < 0.05f) && (mod(y - xy[2][i].y) < 0.05f))
				return true;
		}
	else if (x > 0 && y < 0)
		for (int i = 0; i < numline[3]; i++)
		{
			if ((mod(x - xy[3][i].x) < 0.05f) && (mod(y - xy[3][i].y) < 0.05f))
				return true;
		}
	else
		for (int i = 0; i < numline[4]; i++)
			if ((mod(x - xy[4][i].x) < 0.05f) && (mod(y - xy[4][i].y) < 0.05f))
				return true;

	return false;
}