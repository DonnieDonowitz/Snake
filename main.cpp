#include <QApplication>
#include "Snake.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	Snake window;

	window.setWindowTitle("CAM Snake");
	window.show();

	return app.exec();
}