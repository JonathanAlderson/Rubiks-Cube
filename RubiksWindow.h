#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QImage>
#include <QString>
#include <QCheckBox>
#include <QPixmap>
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include "RubiksWidget.h"

class RubiksWindow: public QWidget
	{
	public:


	// constructor / destructor
	RubiksWindow(QWidget *parent);
	~RubiksWindow();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
	// file menu
	QMenu *fileMenu;
	// quit action
	QAction *actionQuit;

	// window layout
	QGridLayout *windowLayout;

	// left hand side

	// beneath that, the main widget
	RubiksWidget *cubeWidget;

	// right hand side
	QImage *rubiksLogo;
	QLabel *rubiksLogoLabel;

	QLabel *instructionsLabel;

	// Settings Box
	QGroupBox *settingsBox;

		// Camera Distance Slider Title
		QLabel *distanceSliderTitle;
		// Camera Distance Slider
		QSlider *cameraDistanceSlider;

		// Rotation Speed Slider Title
		QLabel *rotationSpeedSliderTitle;
		// Rotation Speed Slider
		QSlider *rotationSpeedSlider;

		// Cube Spacing Slider Title
		QLabel *cubeSpacingSliderTitle;
		// Cube Spacing Slider
		QSlider *cubeSpacingSlider;

		// Edge Thickness Slider Title
		QLabel *edgeThicknessSliderTitle;
		// Edge Thickness Slider
		QSlider *edgeThicknessSlider;

		// Radius Slider Title
		QLabel *radiusSliderTitle;
		// Radius Slider
		QSlider *radiusSlider;

		// Texture Drop Down
		QComboBox *textureDropDown;

		// Confetti Checkbox
		QCheckBox *confettiCheckBox;

		// Checkbox for Circular path
		QCheckBox *rotateCheckBox;

		// Checkbox for helper cubes
		QCheckBox *helperCubesCheckbox;

		// Stretch Factor Slider Title
		QLabel *stretchFactorSliderTitle;
		// Stretch Factor Slider
		QSlider *stretchFactorSlider;

		// Checkbox to change the materials to metal
		QCheckBox *shinyCheckBox;

		// Checkbox to add 3 extra cubes to see other faces
		QCheckBox *helperCheckBox;

		// This button solves the cube
		QPushButton *solveButton;

		// This button scrambles the cube
		QPushButton *scrambleButton;


	// resets all the interface elements
	void ResetInterface();
	};

#endif
