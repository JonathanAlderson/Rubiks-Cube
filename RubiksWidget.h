#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QKeyEvent>
#include "cube.h"
#include "confetti.h"
#include "Image.h"

class RubiksWidget: public QGLWidget
	{ //
	Q_OBJECT
	public:
		RubiksWidget(QWidget *parent);
		int angle;
		int viewDistance;

		vector<Cube> cubes;   // This includes the cubes to help you see the other sides
		int cubesToDraw;
		void enableFocus();

		// Confetti Stuff
		vector<Confetti> confetti; // the plural of confetti is confetti, what can you do.
		int showConfetti;


		//Texture stuff
		void setEarthTexture();
		void setMarcTexture();
		void setMoneyTexture();


		// For circular path rotations
		int rotateAboutCircle;
		float radius;

		// For helper cubes
		float spacing;
		vector<vector<float>> cubeTrans;
		vector<vector<float>> cubeRot;

	public slots:
		void updateScene();
		void updateCameraDistance(int);  // Moves the camera further or closer
		void updateRotateSpeed(int);     // Makes each move go faster
		void updateCubeSpacing(int);     // Makes the cubies further apart
		void updateEdgeThickness(int);   // Makes the rounded edges thicker
 		void updateStretchFactor(int i);  // Makes the cube more animated
		void updateRadius(int i);
		void toggleConfetti(bool toggle);
		void updateTexture(int index);
		void toggleRotateAboutCircle(bool toggle);
		void toggleHelperCubes(bool toggle); // will show or hide the helper cubes
		void toggleShinyMaterials(bool toggle); // will use the plastic or metal materials
		void solveCubeButton();          // Solves the cube
 		void scrambleCubeButton();       // Performs 20 random moves on the cube


	protected:
		// called when OpenGL context is set up
		void initializeGL();
		// called every time the widget is resized
		void resizeGL(int w, int h);
		// called every time the widget needs painting
		void paintGL();

		virtual void keyPressEvent(QKeyEvent*);


	private:

		void polygon(int, int, int, int);

		// Texture Stuff
		Image _earthTexture;
		Image _marcTexture;
		Image _moneyTexture;

	}; // class GLPolygonWidget

#endif
