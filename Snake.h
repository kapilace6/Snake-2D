#ifndef SNAKE_H
#define SNAKE_H

#include <cstdlib>						//Pre-Requisite Header Files
#include <iostream>
#include <gl\glut.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <math.h>
#include <cstring>
using namespace std;

class Var
{
 protected:
	 Var();
	 struct XY
	 {
		 float x, y;
	 };

	 int level, length;
	 int numline[5];					//Number of Blocks in Each Quadrant
	 int tmp1, tmp2;
	 XY **xy;

	 struct SBody						//Structure Of Snake
	 {
		 float x, y;
		 SBody *next;
	 } *Head, *Tail, *p, *np;

	 unsigned int len;
	 unsigned long int score;
	 unsigned const int w, d;

	 unsigned short int speed;
	 float Hx, Hy;						//Coordinates of Head
	 unsigned short int dir, tdir;
	 float Ax, Ay;

	 float mod(float x)
	 { return (x > 0) ? x : -x; }

	 void T()								//Reposition Game Window after Death
	 {
		 glutReshapeWindow(200, 112);
		 glutPositionWindow(w - 200, d - 112);
	 }
	 void reset();
};

class RSnake: virtual public Var			//Read Class
{
private:
	void Block(float x, float y);

 protected:
	ifstream fin;

	RSnake();
	~RSnake();

	void Disp();
	void GetLevelStats();
	bool isCollide(float x, float y);
};
class HSnake :public RSnake					//Write Class
{	
private:
	ofstream fout;							//tmp2 holds Number of Records
	void ViewHS();
	struct write
	{
		unsigned long int s;
		char name[20];
	}*K;

	void sort();
	void centerString(char *str, int width);

protected:
	void Write();
	HSnake();
	~HSnake();
};

class Sys: virtual public Var				//System Class
{
 private:
	 friend void SpecKeyPress(int key, int x, int y);
	 friend void handleKeypress(unsigned char key, int x, int y);

 protected:
	 void SpecKeyPress(int key, int x, int y);
	 void handleKeypress(unsigned char key, int x, int y);
	 void update(int value);
};

class Snake: public Sys, public HSnake				//Move by 0.2f units, Apple Size is 0.15f
{
 private:
	 friend void drawScene();
	 friend void update(int value);

	 bool isEat();				//Is Apple Eaten?
	 void ReDirect();			//Redirect Snake into Game (Endless)

 protected:
	 bool cDead();				//Check if Dead
	 void Dead();
	 unsigned short int Speed() { return speed; }

	 void Traverse();
	 void Update();
	 void GameOver();

 public:
	 Snake();
	 ~Snake();
};

#endif