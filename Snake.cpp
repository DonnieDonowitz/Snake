#include "Snake.h"
#include <QPainter>
#include <QTime>
#include <QIcon>

Snake::Snake(QWidget *parent) : QWidget(parent) 
{
	setStyleSheet("background-color:black; color:red;");
	left = false;
	right = true;
	up = false;
	down = false;
	inGame = true;

	setFixedSize(B_WIDTH, B_HEIGHT);
	loadImages();
	initGame();

	setWindowIcon(QIcon("icon"));
}

void Snake::loadImages()
{
	dot.load("dot.png");
	head.load("head.png");
	apple.load("apple.png");
}

void Snake::initGame() 
{
	dots = 3;
	for (int z = 0; z < dots; z++) 
	{
		x[z] = 50 - z * 10;
		y[z] = 50;
	}

	locateApple();
	timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e);
	draw();
}

void Snake::draw() 
{
	QPainter qp(this);
	if (inGame)
	{
		qp.drawImage(apple_x, apple_y, apple);
		for (int z = 0; z < dots; z++) 
		{
			if (z == 0) 
			{
				qp.drawImage(x[z], y[z], head);
			}
			else 
			{
				qp.drawImage(x[z], y[z], dot);
			}
		}
	}
	else 
	{
		gameOver(qp);
	}
}

void Snake::gameOver(QPainter &qp) 
{
	QString message = "Game over";
	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.horizontalAdvance(message);

	qp.setFont(font);
	int h = height();
	int w = width();

	qp.translate(QPoint(w / 2, h / 2));
	qp.drawText(-textWidth / 2, 0, message);
}

void Snake::checkApple() 
{
	if ((x[0] == apple_x) && (y[0] == apple_y)) 
	{
		dots++;
		locateApple();
	}
}

void Snake::move() 
{
	for (int z = dots; z > 0; z--) 
	{
		x[z] = x[(z - 1)];
		y[z] = y[(z - 1)];
	}

	if (left)
	{
		x[0] -= DOT_SIZE;
	}

	if (right) 
	{
		x[0] += DOT_SIZE;
	}

	if (up) 
	{
		y[0] -= DOT_SIZE;
	}

	if (down) 
	{
		y[0] += DOT_SIZE;
	}
}

void Snake::checkCollision()
{
	for (int z = dots; z > 0; z--) 
	{
		if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z]))
		{
			inGame = false;
		}
	}

	if (y[0] >= B_HEIGHT)
	{
		inGame = false;
	}

	if (y[0] < 0) 
	{
		inGame = false;
	}

	if (x[0] >= B_WIDTH)
	{
		inGame = false;
	}

	if (x[0] < 0) 
	{
		inGame = false;
	}

	if (!inGame)
	{
		killTimer(timerId);
	}
}

void Snake::locateApple() 
{
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	int r = qrand() % RAND_POS;
	apple_x = (r * DOT_SIZE);

	r = qrand() % RAND_POS;
	apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) 
{
	Q_UNUSED(e);
	if (inGame) 
	{
		checkApple();
		checkCollision();
		move();
	}

	repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) 
{

	int key = e->key();

	if ((key == Qt::Key_Left) && (!right)) 
	{
		left = true;
		up = false;
		down = false;
	}

	if ((key == Qt::Key_Right) && (!left)) 
	{
		right = true;
		up = false;
		down = false;
	}

	if ((key == Qt::Key_Up) && (!down)) 
	{
		up = true;
		right = false;
		left = false;
	}

	if ((key == Qt::Key_Down) && (!up)) 
	{
		down = true;
		right = false;
		left = false;
	}

	QWidget::keyPressEvent(e);
}