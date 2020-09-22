#include<iostream>
#include<time.h>
#include<conio.h>
using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class cBall
{
private:
	int x, y;  //current position of the ball
	int posX, posY;  //original position of the ball
	eDir direction;


public:
	cBall(int posX, int posY)
	{
		this->posX = posX;
		this->posY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	void Reset();
	void changeDirection(eDir d);
	void randomDirection();
	void Move();
	friend ostream & operator<<(ostream & o, cBall c);

	inline int getX()
	{
		return x;
	}

	inline int getY()
	{
		return y;
	}

	inline eDir getDirection()
	{
		return direction;
	}
};

void cBall::Reset()
{
	x = posX;
	y = posY;
	direction = STOP;
}

void cBall::changeDirection(eDir d)
{
	direction = d;
}

void cBall::randomDirection()  //þu fonksiyona tekrar bak, hep ayný random deðerler çýkýyor
{
	direction = (eDir)((rand() % 6) + 1);
}

void cBall::Move()
{
	switch (direction)
	{
	case STOP:
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UPLEFT:
		x--; y--;
		break;
	case UPRIGHT:
		x++; y--;
		break;
	case DOWNLEFT:
		x--; y++;
		break;
	case DOWNRIGHT:
		x++; y++;
		break;
	default:
		break;
	}
}

ostream & operator<<(ostream & o, cBall c) //friend functions are not member of class so we can acces like this
{
	o << "Ball [" << c.x << " , " << c.y << "][" << c.direction << "]";
	return o;
}


class cPaddle //raket gibi düþün
{
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle()
	{
		x = y = 0;
	}

	cPaddle(int originalX, int originalY) : cPaddle()
	{
		this->originalX = originalX;
		this->originalY = originalY;
		x = originalX;
		y = originalY;
	}

	inline void Reset()
	{
		x = originalX;
		y = originalY;
	}

	inline int getX() {
		return x;
	}

	inline int getY()
	{
		return y;
	}

	inline void moveUp() { y--; }

	inline void moveDown() { y++; }

	friend ostream & operator<<(ostream & o, cPaddle c)
	{
		o << "Paddle [" << c.x << " , " << c.y << "]";
		return o;
	}
};

class cGameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool exit;
	cBall *ball;
	cPaddle *player1, *player2;
public:
	cGameManager(int width, int height)
	{
		srand(time_t(NULL));
		exit = false;
		up1 = 'w'; up2 = 'u';
		down1 = 's'; down2 = 'j';
		score1 = score2 = 0;
		this->width = width;
		this->height = height;
		ball = new cBall(width / 2, height / 2);  //(20,10)
		player1 = new cPaddle(1, height / 2 - 3);  // (1.7)
		player2 = new cPaddle(width - 2, height / 2 - 3);  // (38,7)
	}

	~cGameManager()  //bc we uses pointer we need the delete them after using
	{
		delete ball, player1, player2;
	}

	void scoreUp(cPaddle *player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}


	void Draw()
	{
		system("cls");

		for (int i = 0; i < width + 2; i++)
			cout << "\xDB";
		cout << endl;

		for (int i = 0; i < height; i++) //y-axis
		{
			for (int j = 0; j < width; j++) //x-axis
			{
				int ballx = ball->getX();
				int bally = ball->getY();

				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();

				if (j == 0) cout << "\xDB";

				if (ballx == j && bally == i)
					cout << "O";
				else if (player1x == j && player1y == i)    //raketlerin konumunu ve boyunu ayarliyor
					cout << "\xDB";
				else if (player2x == j && player2y == i)
					cout << "\xDB";

				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB";

				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB";
				else
					cout << " ";

				if (j == width - 1) cout << "\xDB";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xDB";
		cout << endl;


		cout << "Score1: " << score1 << "\nScore2: " << score2 << endl;
	}

	void Input()
	{
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		if (_kbhit)
		{
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->moveUp();

			if (current == up2)
				if (player2y > 0)
					player2->moveUp();

			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();

			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current == 'q')
				exit = true;
		}
	}

	void Logic()
	{
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		//left paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)  //x konumu zaten degismeyecek
				if (bally == player1y + i)  //y konumu yukari asagi dogru degisir
					ball->changeDirection((eDir)((rand() % 3) + 4)); //+4= 4.den itibaren baslicak random atmaya demek

		//right paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		//bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		//top wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		//right wall
		if (ballx == width - 1)
			scoreUp(player1);

		//left wall
		if (ballx == 0)
			scoreUp(player2);
	}
	void Run()
	{
		while (!exit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};

int main()
{
	cGameManager play(40, 20);
	play.Run();


	system("pause");
	return 0;
}