

#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Window window;
	window.setGeometry(100,100, 3000, 1500);
	window.show();

	return app.exec();

}

