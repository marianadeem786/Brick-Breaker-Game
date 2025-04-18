#include <iostream>
#include <fstream>
#include <string>
#include "yourgraphics.h"
using namespace std;
//innitialisation for console
int x, y;
int w;
int w1 = w;
//innitialisation for bricks
int brickx[6][11]{};
int bricky[6][11]{};
int health[5][10]{};
//innitialisation for paddle
int startingPoint = 360;
int width = 200;
int height = 10;
//innitialisation for lives and score
int chances = 3;
bool over = false;
int score = 0;
//array to save 5 highscores
int high[5];
//if user wants saved game
bool load= false;
struct ball {
	int x1 = 400;
	int y1 = 400;
	int x2 = 20;
	int y2 = 20;
	int vx = 9;
	int vy = 9;

}balls;

void printbricks() {
	
		int  h = 40, x1 = 0, y1 = 20;
		int w1 = w;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				health[i][j] = 2;
				brickx[i][j] = x1;
				bricky[i][j] = y1;

				drawRectangle(x1, y1, w1, h, 0, 0, 0, 204, 51, 255);


				x1 += w;
				w1 += w;
			}
			//incrementing coordinate values
			y1 += 20;
			h += 20;
			w1 = x / 10;
			x1 = 0;
		}
}
void printsavebricks() {

	int  h = 40, x1 = 0, y1 = 20;
	int w1 = w;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			brickx[i][j] = x1;
			bricky[i][j] = y1;
			if (health[i][j] == 2)
			{
				drawRectangle(x1, y1, w1, h, 0, 0, 0, 204, 51, 255);
			}
			if (health[i][j] == 1)
			{
				drawRectangle(x1, y1, w1, h, 0, 0, 0, 204, 153, 255);
			}
			if (health[i][j] == -1)
			{
				drawRectangle(x1, y1, w1, h, 0, 0, 0, 0, 0, 0);
			}

			x1 += w;
			w1 += w;
		}
		//incrementing coordinate values
		y1 += 20;
		h += 20;
		w1 = x / 10;
		x1 = 0;
	}
}

void brickcollision()
{


	int h = 40;
	gotoxy(0, 0);
	cout << "score:" << score * 10;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 11; j++) {
			if (health[i][j] > 1) {

				if (brickx[i][j] + w > balls.x1 + balls.vx &&
					brickx[i][j] < balls.x1 + balls.vx + balls.x2 &&
					bricky[i][j] + 20 > balls.y1 + balls.vy &&
					bricky[i][j] < balls.y2 + balls.y1 + balls.vy)
				{
					balls.vy *= -1;
					//when ball hits the first time
					drawRectangle(brickx[i][j], bricky[i][j], w1, h, 0, 0, 0, 204, 153, 255);
					health[i][j] = 1;

				}

			}
			else if (health[i][j] == 1)
			{
				if (brickx[i][j] + w > balls.x1 + balls.vx &&
					brickx[i][j] < balls.x1 + balls.vx + balls.x2 &&
					bricky[i][j] + 20 > balls.y1 + balls.vy &&
					bricky[i][j] < balls.y2 + balls.y1 + balls.vy)
				{
					balls.vy *= -1;
					//when ball hits the second time 
					score += 1;
					gotoxy(0, 0);
					cout << "score:" << score * 10;

					drawRectangle(brickx[i][j], bricky[i][j], w1, h, 0, 0, 0, 0, 0, 0);
					health[i][j] = -1;

				}

			}
			w1 += w;

		}
		h += 20;
		w1 = w;

	}


}

void paddlecollision() {
	//checks all the edges
	if (balls.y1 + balls.y2 + 10 >= y - height - 30 && balls.x1 > startingPoint && balls.x1<startingPoint + width
		&& balls.x1 + balls.x2 > startingPoint && balls.x1 + balls.x2 < startingPoint + width)
		balls.vy *= -1;
}

void ballup() {
	getWindowDimensions(x, y);
	drawEllipse(balls.x1, balls.y1, balls.x2 + balls.x1, balls.y2 + balls.y1, 0, 0, 0, 0, 0, 0);

	paddlecollision();
	brickcollision();
	//checks the boundary collisions
	if (balls.x1 <= 0 || balls.x2 + balls.x1 >= x)
		balls.vx *= -1;
	if (balls.y1 <= 0)
		balls.vy *= -1;
	//check for bottom window boundary
	if (balls.y2 + balls.y1 >= y)
	{
		balls.x1 = 450;
		balls.y1 = 400;
		//reappearing ball after it falls down
		delay(1000);
		drawEllipse(balls.x1, balls.y1, balls.x2 + balls.x1, balls.y2 + balls.y1, 255, 130, 23, 255, 130, 23);

		delay(500);
		balls.vy *= -1;
		drawEllipse(balls.x1, balls.y1, balls.x2 + balls.x1, balls.y2 + balls.y1, 0, 0, 0, 0, 0, 0);


		delay(10);
	}
	//incrementing velocities to move the ball
	balls.y1 += balls.vy;
	balls.x1 += balls.vx;
	drawEllipse(balls.x1, balls.y1, balls.x2 + balls.x1, balls.y2 + balls.y1, 255, 130, 23, 255, 130, 23);


}

void savegame()
{
	ofstream myfile;

	myfile.open("savedgame.txt", ios::out);
	//storing all the values in file
	myfile << balls.y1 << " ";
	myfile << balls.x1 << " ";
	myfile << startingPoint << " ";
	myfile << chances << " ";
	myfile << score << " ";


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++)
		{
			myfile << health[i][j] << " ";

		}

	}


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++)
		{
			myfile << brickx[i][j] << " ";
		}


	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++)
		{
			myfile << bricky[i][j] << " ";
		}


	}


	myfile.close();


}
void printlives()
{
	if (chances == 3)
	{
		gotoxy(10, 0);
		cout << "lives: " << chances;


	}
	if (chances == 2)
	{
		gotoxy(10, 0);
		cout << "lives: " << chances;


	}
	if (chances == 1)
	{

		gotoxy(10, 0);
		cout << "lives: " << chances;
	}

}

int main()
{				
	cls();
	char key;

	gotoxy(10, 0);

	cout << "To load the game, press m: " << endl << "To start new game, press n :";
	cin >> key;


	//loading the previous game
	delay(1400);
	if (key == 'm')
	{
		load == true;
		ifstream myfile;


		myfile.open("savedgame.txt", ios::in);

		myfile >> balls.y1;
		myfile >> balls.x1;
		myfile >> startingPoint;
		myfile >> chances;
		myfile >> score;


		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++)
			{
				myfile >> health[i][j];

			}

		}


		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++)
			{
				myfile >> brickx[i][j];
			}


		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++)
			{
				myfile >> bricky[i][j];
			}


		}


		myfile.close();
	}
	else
		gotoxy(10, 20);
	cout << " new game is loading" << endl;
	delay(500);

	gotoxy(0, 0);
	SetProcessDPIAware();
	showConsoleCursor(false);
	cls();
	//printing a black block
	getWindowDimensions(x, y);
	drawRectangle(0, 0, x, y, 0, 0, 0, 0, 0, 0);
	w = x / 10;
	if (load == false)
	{
		printbricks();
	}
	else if (load == true)
	{
		printsavebricks;
	}
	//entering in main loop
	while (true)
	{


		char key = getKey();
		if (key == 'd' && (startingPoint + width) <= x) {
			
			drawRectangle(0, y - height - 30, x, y - 30, 0, 0, 0); //clear line
			startingPoint += 30; //move starting point of rectangle to right
			/*Beep(500, 100);*/
		}
		if (key == 'a' && startingPoint >= 0) {
			
			drawRectangle(0, y - height - 30, x, y - 30, 0, 0, 0); //clear line
			startingPoint -= 30; //move starting point of rectangle to left
			/*Beep(500, 100);*/
		}
		//to pause and resume
		if (key == 'p')
		{
			while (1)
			{

				key = getKey();
				if (key == 'r')
					break;



			}
		}


		//start here              top of rectangle          stop here (add width)        base of rectangle  colors
		drawRectangle(startingPoint, y - height - 30, startingPoint + width, y - 30, 255, 130, 23, 255, 130, 23);
		ballup();
		delay(20);
		printlives();

		if (balls.y2 + balls.y1 >= y)
			chances -= 1;
		printlives();

		int bric = 0;
		bool won = false;
		if (chances >= 1) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 10; j++)
				{
					if (health[i][j] == -1)
						bric++;
				}

			}
		}
		ofstream myfile2;
		//saving high scores
		myfile2.open("highscore.txt", ios::app);
		if (!myfile2)
		{
			cout << "cannot open file";
		}
		else
			myfile2 << score * 10 << " ";
		//saving the file
		myfile2.close();
		if (key == 's')
		{
			savegame();
		}
		//if won
		if (bric == 50)
		{
			gotoxy(50, 100);
			over = true;
			cout << "YOU WON!! YOUR SCORE IS= " << score * 10;

			break;
		}
		//if lost
		if (chances < 1)
		{
			int t = 0;
			over = true;
			gotoxy(50, 70);
			cout << "GAME OVER! YOUR SCORE IS = " << score * 10;

			ifstream file1("Scores.txt");
			int j = 0;
			while (j < 5)
			{
				file1 >> high[j];
				j++;
			}
			file1.close();

			//checking if score is greater then any exiistng score, if yes then replacing
			for (int i = 0; i < 5; i++)
			{
				if (score > high[i])
				{
					high[i] = score * 10;
					break;
				}
			}

			//sorting high scores
			for (int i = 0; i < 4; i++)
			{
				if (high[i] < high[i + 1])
				{
					t = high[i];
					high[i] = high[i + 1];
					high[i + 1] = t;
				}
			}

			//writing scores into the file
			ofstream file;
			file.open("Scores.txt");
			if (!file.is_open())
			{
				cout << "Error Opening File!" << endl;
			}
			for (int i = 0; i < 5; i++)
			{
				file << high[i] << endl;
			}
			file.close();

			//displaying highscore

			gotoxy(50, 70);
			cout << "GAME OVER! YOUR SCORE IS = " << score * 10 << endl << "your highest scores are= ";

			for (int i = 0; i < 5; i++)
			{
				gotoxy(50 + i * 3, 90);
				cout << high[i] << "  ";
			}
			break;
		}

	}

}

