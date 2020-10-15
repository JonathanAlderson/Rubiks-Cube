#include "RubiksWindow.h"

// constructor / destructor
RubiksWindow::RubiksWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// set a nice background
	//this->setStyleSheet("background-image:url(\"bkg.jpg\"); background-position: center; ");


	// create menu bar
	menuBar = new QMenuBar(this);

	// create file menu
	fileMenu = menuBar->addMenu("&File");

	// create the action
	actionQuit = new QAction("&Quit", this);

	// add the item to the menu
	fileMenu->addAction(actionQuit);

	// create the window layout
	windowLayout = new QGridLayout(this);

	// left hand side

	// create main widget
	cubeWidget = new RubiksWidget(this);
	windowLayout->addWidget(cubeWidget, 1, 1, 3, 1);

	// Right hand side

	// Rubiks Logo
	rubiksLogo = new QImage;
	rubiksLogo->load("logo.jpg");

	rubiksLogoLabel = new QLabel;
	rubiksLogoLabel->setPixmap(QPixmap::fromImage(*rubiksLogo));
	rubiksLogoLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	windowLayout->addWidget(rubiksLogoLabel, 1, 2);

	instructionsLabel = new QLabel;
	instructionsLabel->setText("Instructions\n\nWhole Cube Rotations (Numpad)\n8/5 X-Axis    4/6 Y-Axis    7/9 Z-Axis\n\nFace Rotations\nF - Front    B - Back    L - Left\nR - Right    U - Up    D - Down\n\nHold Shift for Anticlockwise");
	windowLayout->addWidget(instructionsLabel, 2, 2);


	// Settings Page
	settingsBox = new QGroupBox(tr("Settings"));
	QVBoxLayout *settingsLayout = new QVBoxLayout;

	// Distance Slider Title
	distanceSliderTitle = new QLabel();
	distanceSliderTitle->setText("Camera Distance");
	distanceSliderTitle->setFixedHeight(15);
	settingsLayout->addWidget(distanceSliderTitle);
	// Distance Slider
	cameraDistanceSlider = new QSlider(Qt::Horizontal);
	cameraDistanceSlider->setSliderPosition(8);
	connect(cameraDistanceSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateCameraDistance(int)));
	settingsLayout->addWidget(cameraDistanceSlider);


	// Rotation Speed Slider Title
	rotationSpeedSliderTitle = new QLabel();
	rotationSpeedSliderTitle->setText("Rotation Speed");
	rotationSpeedSliderTitle->setFixedHeight(15);
	settingsLayout->addWidget(rotationSpeedSliderTitle);
	// Rotation Speed Slider
	rotationSpeedSlider = new QSlider(Qt::Horizontal);
	rotationSpeedSlider->setSliderPosition(35);
	connect(rotationSpeedSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateRotateSpeed(int)));
	settingsLayout->addWidget(rotationSpeedSlider);


	// Cube Spacing Slider Title
	cubeSpacingSliderTitle = new QLabel();
	cubeSpacingSliderTitle->setText("Cube Spacing");
	cubeSpacingSliderTitle->setFixedHeight(15);
	settingsLayout->addWidget(cubeSpacingSliderTitle);
	// Cube Spacing Slider
	cubeSpacingSlider = new QSlider(Qt::Horizontal);
	cubeSpacingSlider->setSliderPosition(3);
	connect(cubeSpacingSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateCubeSpacing(int)));
	settingsLayout->addWidget(cubeSpacingSlider);


	// Edge Thickness Slider Title
	edgeThicknessSliderTitle = new QLabel();
	edgeThicknessSliderTitle->setText("Edge Thickness");
	edgeThicknessSliderTitle->setFixedHeight(15);
	settingsLayout->addWidget(edgeThicknessSliderTitle);
	// Edge Thickness Slider
	edgeThicknessSlider = new QSlider(Qt::Horizontal);
	edgeThicknessSlider->setSliderPosition(20);
	connect(edgeThicknessSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateEdgeThickness(int)));
	settingsLayout->addWidget(edgeThicknessSlider);


	// Stretch Factor Slider Title
	stretchFactorSliderTitle = new QLabel();
	stretchFactorSliderTitle->setText("Stretch Factor");
	stretchFactorSliderTitle->setFixedHeight(15);
	settingsLayout->addWidget(stretchFactorSliderTitle);
	// Stretch Factor Slider
	stretchFactorSlider = new QSlider(Qt::Horizontal);
	stretchFactorSlider->setSliderPosition(0);
	connect(stretchFactorSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateStretchFactor(int)));
	settingsLayout->addWidget(stretchFactorSlider);


	// Radius Slider Title
	radiusSliderTitle = new QLabel();
	radiusSliderTitle->setText("Path Radius");
	radiusSliderTitle->setFixedHeight(15);
	settingsLayout->addWidget(radiusSliderTitle);
	// Radius Slider
	radiusSlider = new QSlider(Qt::Horizontal);
	radiusSlider->setSliderPosition(0);
	connect(radiusSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateRadius(int)));
	settingsLayout->addWidget(radiusSlider);

	textureDropDown = new QComboBox();
	textureDropDown->addItem(*new QString("Marc"));
	textureDropDown->addItem(*new QString("Earth"));
	textureDropDown->addItem(*new QString("Money"));
	connect(textureDropDown, SIGNAL(currentIndexChanged(int)), cubeWidget, SLOT(updateTexture(int)));
	settingsLayout->addWidget(textureDropDown);

	// Checkbox to show confetti or not
	confettiCheckBox = new QCheckBox();
	confettiCheckBox->setText("Confetti");
	connect(confettiCheckBox, SIGNAL(clicked(bool)), cubeWidget, SLOT(toggleConfetti(bool)));
	settingsLayout->addWidget(confettiCheckBox);


	// Checkbox to rotate the whole thing about a circle
	rotateCheckBox = new QCheckBox();
	rotateCheckBox->setText("Move in a Circular Path");
	connect(rotateCheckBox, SIGNAL(clicked(bool)), cubeWidget, SLOT(toggleRotateAboutCircle(bool)));
	settingsLayout->addWidget(rotateCheckBox);

	// Check box to show helper cubes
	helperCubesCheckbox = new QCheckBox();
	helperCubesCheckbox->setText("Helper Cubes");
	connect(helperCubesCheckbox, SIGNAL(clicked(bool)), cubeWidget, SLOT(toggleHelperCubes(bool)));
	settingsLayout->addWidget(helperCubesCheckbox);

	// Checkbox to use metal materials or plastic
	shinyCheckBox = new QCheckBox();
	shinyCheckBox->setText("Use Shiny Materials");
	connect(shinyCheckBox, SIGNAL(clicked(bool)), cubeWidget, SLOT(toggleShinyMaterials(bool)));
	settingsLayout->addWidget(shinyCheckBox);


	// Add a button to solve the cube
  solveButton = new QPushButton("Solve");
	connect(solveButton, SIGNAL(clicked()), cubeWidget, SLOT(solveCubeButton()));
	settingsLayout->addWidget(solveButton);

	// Add a button to scramble the cube
  scrambleButton = new QPushButton("Scramble");
	connect(scrambleButton, SIGNAL(clicked()), cubeWidget, SLOT(scrambleCubeButton()));
	settingsLayout->addWidget(scrambleButton);

	settingsBox->setLayout(settingsLayout);
	windowLayout->addWidget(settingsBox, 3, 2);

	// Makes both elements the correct size
	windowLayout->setColumnStretch(1, 10);
	windowLayout->setColumnStretch(2, 3);

	} // constructor

RubiksWindow::~RubiksWindow()
	{ // destructor
	delete cubeWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void RubiksWindow::ResetInterface()
	{ // ResetInterface()

	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
