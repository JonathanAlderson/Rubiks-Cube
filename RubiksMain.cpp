#include <QApplication>
#include <QVBoxLayout>
#include <GL/glut.h>
#include "RubiksWindow.h"

int main(int argc, char *argv[])
	{ // main()
	// create the application

	QApplication app(argc, argv);
	glutInit(&argc, argv);
	// create model (polygon) as a triangle
	//	GLPolygon *polygon = new GLPolygon();

	// create a master widget
  RubiksWindow *window = new RubiksWindow(NULL);

	// create a controller to hook things up
	//	GLPolygonController *controller = new GLPolygonController(window, polygon);

	// resize the window
	window->resize(1160, 900);

	// show the label
	window->show();

	// start it running
	app.exec();


	// clean up
	//	delete controller;
	delete window;

	// return to caller
	return 0;
	} // main()
