

#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Window window;
	//window.setGeometry(100,100, 300, 150);
	window.show();

	return app.exec();

}

