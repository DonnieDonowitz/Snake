#pragma once
#include <QWidget>
#include <QKeyEvent>

class Snake :
	public QWidget
{
public:
	Snake(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent*);
	void keyPressEvent(QKeyEvent*);

private:
	QImage dot, head, apple;

	static const int B_WIDTH = 300;
	static const int B_HEIGHT = 300;
	static const int DOT_SIZE = 10;
	static const int ALL_DOTS = 900;
	static const int RAND_POS = 29;
	static const int DELAY = 140;
	
	int timerId, dots, apple_x, apple_y;
	int x[ALL_DOTS], y[ALL_DOTS];
	bool left, right, down, up, inGame;

	void loadImages();
	void initGame();
	void locateApple();
	void checkApple();
	void checkCollision();
	void move();
	void draw();
	void gameOver(QPainter&);
};

