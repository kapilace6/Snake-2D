#include "Snake.h"

//*************************************************
//    Constructor, Destructor of Snake Class
//*************************************************
Snake::Snake()										//The Snake is a Dynamically Allocated Queue
{
	Head = new SBody;					//Head of the Snake
	Head -> x = 0.0f;
	Head -> y = -0.2f;
	Head -> next = NULL;

	Tail = new SBody;					//Tail of the Snake
	Tail -> x = 0.0f;
	Tail -> y = -0.4f;
	Tail -> next = Head;

	np = new SBody;

	dir = 1;
	tdir = 1;
	score = 0;
	speed = 210;
	len = 3;

	srand(time(NULL));						//Generation of Apple
 re:
	Ax = pow(-1, (double)rand()) * (rand() % (int)(13 * w / d - 1)) / 5;
	Ay = pow(-1, (double)rand()) * (rand() % 12) / 5;

	if (isCollide(Ax, Ay))
		goto re;
}
Snake::~Snake()
{
	while(Tail -> next != NULL)
	{
		np = Tail;
		Tail = Tail->next;
		delete np;
	}
	delete Head;
}

//***********************************
//  Collision with Itself Check
//***********************************
bool Snake::cDead()
{
	p = Tail;
	while(p->next != NULL)
	{
		if(mod(p->x - Hx) < 0.05 && mod(p->y - Hy) < 0.05)
			return true;

		p = p->next;
	}

	if (isCollide(Hx, Hy))
		return true;

	return false;
}
bool Snake::isEat()
{ return (mod(Ax - Hx) < 0.05 && mod(Ay - Hy) < 0.05) ? true : false; }

//***********************************
//		Draw Snake Function
//***********************************
void Snake::Traverse()
{
	glDisable(GL_LIGHTING);
		Disp();
	glEnable(GL_LIGHTING);

	p = Tail;
	while(p->next != NULL)
	{
	 glPushMatrix();
		glColor3f(0.2f, 0.8f, 0.4f);				//Green Body
		glTranslatef(p->x, p->y, -6.0f);
			glutSolidSphere(0.1f, 20, 2);
	 glPopMatrix();

		p = p->next;
	}

	glPushMatrix();	
		glTranslatef(p->x, p->y, -6.0f);	
			glutSolidSphere(0.1f, 20, 2);
	glPopMatrix();

	glPushMatrix();									
		glColor3f(0.4f, 0.2f, 0.8f);				//Purple Head
		glTranslatef(Hx, Hy, -6.0f);
			glutSolidSphere(0.1f, 20, 2);
	glPopMatrix();

	glPushMatrix();
		if(isEat()) glColor3f(0.4f, 0.2f, 0.8f);
		else glColor3f(0.9f, 0.1f, 0.1f);			//Red Apple
		
		glTranslatef(Ax, Ay, -6.0f);
			glutSolidSphere(0.15f, 20, 2);
	glPopMatrix();
}

//***********************************
//		Update Snake Function
//***********************************
void Snake::Update()
{
	if (length < (int)len)					//If Minimum Length is Reached, Load the Next Level
	{
		GetLevelStats();
		reset();
	}
	ReDirect();
	if(!cDead())
	{
		if(isEat())
		{
			np = new SBody;
			np -> next = Tail;
			Tail = np;

		 re:
			Ax = pow(-1, (double)rand()) * (rand() % (int)(13 * w / d - 1)) / 5;
			Ay = pow(-1, (double)rand()) * (rand() % 12) / 5;

			p = Tail;
			while(p->next != NULL)
			{
				if((mod(p->x - Ax) < 0.05 && mod(p->y - Ay) < 0.05) || isCollide(Ax, Ay))
					goto re;

				p = p->next;
			}

			++len;
			if(speed != 70)							//Speed Incrementation
				if(!(len % 5))
					speed -= 30;

			score += (len - 2) * (260 - speed);
		}
		
		p = Tail;
		while(p->next != NULL)
		{
			p -> x = p->next -> x;
			p -> y = p->next -> y;
			p = p->next;
		}

		p -> x = Hx;
		p -> y = Hy;

		(dir % 2 == 0) ? ((tdir != dir-1) ? dir = tdir : false) : ((tdir != dir+1) ? dir = tdir : false);  
	}
	else
		GameOver();

	switch (dir)
	{
	case 1:
		Hy += 0.2f;
		break;

	case 2:
		Hy -= 0.2f;
		break;

	case 3:
		Hx -= 0.2f;
		break;

	case 4:
		Hx += 0.2f;
		break;
	}
	if(mod(Hx) < 0.01)
		Hx = 0.0f;
	if(mod(Hy) < 0.01)
		Hy = 0.0f;
}

//***********************************
//		Redirection Function
//***********************************
void Snake::ReDirect()
{
	switch(dir)
	{
	 case 1:
		 if(Hy + 0.1 > 2.4)
			 Hy = -2.4f;
		 break;

	 case 2:
		 if(Hy - 0.1 < -2.4)
			 Hy = 2.4f;
		 break;

	 case 3:
		 if(Hx - 0.1 < -((float)(((int)(13*w/d - 1)) / (float)5)))
			 Hx = ((float)(((int)(13*w/d - 1)) / (float)5));
		 break;

	 case 4:
		 if(Hx + 0.1 > ((float)(((int)(13*w/d - 1)) / (float)5)))
			 Hx = -((float)(((int)(13*w/d - 1)) / (float)5));
		 break;
	}
}

void Snake::Dead()
{
	p = Tail;
	while(p->next != NULL)
	{
	 glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);				
		glTranslatef(p->x, p->y, -6.0f);
			glutSolidSphere(0.1f, 20, 2);
	 glPopMatrix();

		p = p->next;
	}

	glPushMatrix();	
		glTranslatef(p->x, p->y, -6.0f);	
			glutSolidSphere(0.1f, 20, 2);
	glPopMatrix();

	glPushMatrix();									
		glColor3f(1.0f, 0.0f, 0.0f);				
		glTranslatef(Hx, Hy, -6.0f);
			glutSolidSphere(0.1f, 20, 2);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.9f, 0.1f, 0.1f);				
		glTranslatef(Ax, Ay, -6.0f);
			glutSolidSphere(0.15f, 20, 2);
	glPopMatrix();
}

//***********************************
//		Game Over Function
//***********************************
void Snake::GameOver()
{
	cout <<"\n\n\t\tYour Score : " <<score;
	Write();
	cin.get();
	exit(0);
}

//***********************************
//		Reset Function
//***********************************
void Var::reset()
{
	tmp2 = 0; 
	++level;
	
	while (Tail->next != NULL)
	{
		np = Tail;
		Tail = Tail->next;
		delete np;
	}
	delete Head;

	Head = new SBody;
	Head->x = 0.0f;
	Head->y = -0.2f;
	Head->next = NULL;

	Tail = new SBody;
	Tail->x = 0.0f;
	Tail->y = -0.4f;
	Tail->next = Head;

	np = new SBody;

	Hx = 0.0f;
	Hy = 0.0f;

	dir = 1;
	tdir = 1;
	speed = 180;
	len = 3;
}