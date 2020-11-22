
#include <iostream>
#include "ConsoleSnake.h"
#include <crtdbg.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool has_tail;
bool gameOver;
const int width = 20;
const int height = 20;

int player_x, player_y, fruitX, fruitY, score;

enum eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP, 
	DOWN
};

eDirection dir;

int tail_x[100], tail_y[100];
int tail_length;

void Setup() 
{
	gameOver = false;
	dir = STOP;
	player_x = width / 2;
	player_y = height / 2;

	fruitX = rand() % width;
	fruitY = rand() % width;

	score = 0;
}

void DrawTail(int cols, int rows)
{
	bool print = false;
	//loop through each elemt of tail to draw it
	for (int k = 0; k < tail_length; k++)
	{
		if (tail_x[k] == rows && tail_y[k] == cols)
		{
			cout << "o";
			print = true;
		}
	}

	if (!print)
	{
		cout << " ";
	}

}


void Draw() 
{
	system("cls"); //clear console;


	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		//this loop prints the rows for map
		for (int j = 0; j < width; j++)
		{
			//check if its the first field print wall
			if (j == 0)
			{
				cout << "#";
			}
			
			//check if its the last field in the row and print a wall
			if (j == width - 1)
			{
				cout << "#";
			}

			//draw the player if the loop is at the player coords
			if (i == player_y && j == player_x)
			{
				cout << "0";
			}
			//draw the fruit if the looop us at the fruit cords
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			//else we print a blnk space
			else
			{
				DrawTail(i, j);
			}
			
		}

		cout << endl;

	}

	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}

	cout << endl;


	cout << "Score: " << score << endl;
}


//Gets the players inputs and sets directions accordingly
void Input()
{
	//check if the keyboard is pressed will return 1 if pressed and 0 if not pressed
	if (_kbhit())
	{
		//_getch gets the ascii character and converts it to the key pressed
		switch (_getch())
		{
		case 'w':
			if (dir == DOWN && has_tail)
			{
				break;
			}
			else
			{
				dir = UP;
			}
			break;

		case 'a':
			if (dir == RIGHT && has_tail)
			{
				break;
			}
			else
			{
				dir = LEFT;
			}
			break;

		case 's':
			if (dir == UP && has_tail)
			{
				break;
			}
			else
			{
				dir = DOWN;
			}
			break;

		case 'd':
			if (dir == LEFT && has_tail)
			{
				break;
			}
			else
			{
				dir = RIGHT;
			}
			break;

		case 'x':
			gameOver = true;
			break;

		default:
			break;
		}
	}
}

void Logic()
{
	//makes tail follow the player
	int last_tail_x = tail_x[0];
	int last_tail_y = tail_y[0];

	int last_tail_x2, last_tail_y2;

	tail_x[0] = player_x;
	tail_y[0] = player_y;
	
	for (int i = 1; i < tail_length; i++)
	{
		last_tail_x2 = tail_x[i];
		last_tail_y2 = tail_y[i];

		tail_x[i] = last_tail_x;
		tail_y[i] = last_tail_y;

		last_tail_x = last_tail_x2;
		last_tail_y = last_tail_y2;
	}

	//moves the player based on the direction
	switch (dir)
	{
	case STOP:
		break;

	case LEFT:
		player_x--;
		break;
	case RIGHT:
		player_x++;
		break;

	case UP:
		player_y--;
		break;

	case DOWN:
		player_y++;
		break;

	default:
		break;
	}

	//if (player_x > width || player_x < 0 || player_y > height || player_y < 0)
	//{
	//	gameOver = true;
	//}

	//wraps the player around the map
	if (player_x >= width) 
	{
		player_x = 0;
	}
	else if (player_x < 0)
	{
		player_x = width - 1;
	}

	if (player_y >= height)
	{
		player_y = 0;
	}
	else if (player_y < 0)
	{
		player_y = height - 1;
	}
	
	//check for collision with each tail segment to end the game
	for (int i = 0; i < tail_length; i++)
	{
		if (player_x == tail_x[i] && player_y ==  tail_y[i])
		{
			gameOver = true;
		}
	}

	//check for collision witht the fruit and act accordingly
	if (player_x == fruitX && player_y == fruitY)
	{
		has_tail = true;

		score += 10;

		fruitX = rand() % width;
		fruitY = rand() % width;

		tail_length++;
	}
}


int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		//Sleep(50);
	}

	if (gameOver)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "You died! your score was: " << score << endl;
	}
	
	system("pause");
	return 0;

}
