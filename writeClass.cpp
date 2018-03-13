#include "Snake.h"

//*************************************************
//  Constructor, Destructor of Write Snake Class
//*************************************************
HSnake::HSnake()
{
	tmp1 = 0;
	tmp2 = 0;
	K = new write [1];
	while (tmp1 != 1)
	{
		system("CLS");
		cout << "\n\t\t\t*************";
		cout << "\n\t\t\t    SNAKE";
		cout << "\n\t\t\t*************";

		cout << "\n\n\n\t1. Play Game";
		cout << "\n\t2. View High Scores";
		cout << "\n\t3. Exit\n\t\t\t\t" << (char)16 << ' ';

		cin >> tmp1;
		cin.ignore();

		switch (tmp1)
		{
		 case 3:
			 exit(0);

		 case 2:
			 ViewHS();
			 break;

		 case 1:break;

		 default:cout << "\n\t\tIncorrect Input. Rerunning Game....";
			 cin.get();
		}
	}
}
HSnake::~HSnake()
{ delete[] K; }

//***********************************
//	  High Score View Function
//***********************************
void HSnake::ViewHS()
{
	tmp2 = 0;
	fin.close();
	fin.open("HS.dat");					//HS.dat holds the High Scores amd Players
	if (!fin)
	{
		cout << "\n\t\tNo Records Exist....";
		cin.get();
	}
	else
	{
		while (fin.read((char*)&K[0], sizeof(K[0]))) ++tmp2;
		fin.close();

		delete[] K;
		K = new write [tmp2];
		int i = 0;
		char t[10];
		fin.open("HS.dat");
		while (fin.read((char*)&K[i++], sizeof(write)));
		fin.close();

		sort();
		system("CLS");
		cout << '\n';
		for (i = 0; i < 80; ++i) cout << '*';
		cout << "*  Ranks  *\t\tName\t\t\t*\t\tScore\t       *";
		for (i = 0; i < 80; ++i) cout << '*';

		++tmp2;
		for (i = 1; i < tmp2; ++i)
		{
			cout << endl <<'*';
			_itoa_s(i, t, 7);
			centerString(t, 9);
			cout << '*';

			centerString(K[i - 1].name, 37);
			cout << '*';

			_itoa_s(K[i-1].s, t, 10);
			centerString(t, 30);
			cout << '*' <<endl;
		}
		for (i = 0; i < 80; i += 2) cout << '*' <<' ';
	}
	cin.get();
}

//***********************************
//		Sort Function
//***********************************		//Selection Sort of Players, Ordered by their Scores
void HSnake::sort()
{
	unsigned long int small;
	write tmp;
	int pos;

	for (int i = tmp2 - 1; i > -1; --i)
	{
		small = K[i].s;
		pos = i;
		for (int j = i - 1; j > -1; --j)
			if (K[j].s < small)
			{
				small = K[j].s;
				pos = j;
			}

		tmp = K[i];
		K[i] = K[pos];
		K[pos] = tmp;
	}
}

//***********************************
//		  Write Function
//***********************************
void HSnake::Write()
{
	fout.open("HS.dat", ios::app);
	cout << "\n\n\tEnter Player Name : ";
	cin >> K[0].name;
	cin.ignore();
	K[0].s = score;

	fout.write((char*)&K[0], sizeof(K[0]));
	fout.close();

	cout << "\n\n\n\t\t\tThanks for Playin!!";
}

//***********************************
//	    Center Align Function
//***********************************
void HSnake::centerString(char *str, int width)
{
	   int l = strlen(str);
	   int pos = (int)((width - l) / 2);
	   for (int i = 0; i < pos; i++)
			cout << ' ';

	   cout << str;
	   for (int i = 0; i < (width - pos - l); ++i)
		   cout << ' ';
}