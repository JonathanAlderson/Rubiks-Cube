#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include "RubiksWidget.h"
#include <iostream>
#include <QTimer>
#include <string>


// constructor
RubiksWidget::RubiksWidget(QWidget *parent) : QGLWidget(parent),
                                              _earthTexture("./earth.ppm"),  // Load in the images for our textures
                                              _marcTexture("./Moi.ppm"),
                                              _moneyTexture("./money.ppm")
{ // constructor
  enableFocus();
  setUpdatesEnabled(true);
  angle = 30;
  viewDistance = 12;

  rotateAboutCircle = 0;
  radius = 0;

  // Create mainloop timer, running at 60 fps
  QTimer* timer2 = new QTimer();
  QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(update()));
  timer2->start(15); // A low number so it's nice and smooth

  // Timer to increment the rotation amount
  QTimer* timer1 = new QTimer();
  QObject::connect(timer1, SIGNAL(timeout()), this, SLOT(updateScene()));
  timer1->start(15); // A low number so it's nice and smooth



	cubes.push_back(Cube()); // Calls the constructor
  cubes.push_back(Cube()); // This is for the 3 cubes to help you see
  cubes.push_back(Cube()); // the other
  cubes.push_back(Cube()); // sides

  cubesToDraw = 1; // We don't show the hepler cubes initially

  // Helper cubes info
  // these are the translations needed for the helper cubes
  spacing = 16.0;
  cubeTrans = {{0.0, 0.0, 0.0},
              {-spacing, 0.0, 0.0},
              {0.0, 0.0, -spacing},
              {0.0, -spacing, 0.0}};

  cubeRot = {{0.0, 0.0, 1.0, 0.0},
             {180.0, 0.0, 1.0, 0.0},
             {180.0, 0.0, 1.0, 0.0},
             {180.0, 1.0, 0.0, 0.0},};

   // Add all the confetti
   for(unsigned int i = 0; i < 500; i ++)
   {
     confetti.push_back(Confetti(-5, 5, 15, 150, -5 , 5, (float)0.01));
   }
   showConfetti = 0; // Wait until we've clicked the button

} // constructor


// Make the earth texture the active one
void RubiksWidget::setEarthTexture()
{
  glEnable(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _earthTexture.Width(), _earthTexture.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _earthTexture.imageField());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glDisable(GL_TEXTURE_2D);
}

// Make the marc texture the active one
void RubiksWidget::setMarcTexture()
{
  glEnable(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _marcTexture.Width(), _marcTexture.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _marcTexture.imageField());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glDisable(GL_TEXTURE_2D);
}

// Make the money texture the active one
void RubiksWidget::setMoneyTexture()
{
  glEnable(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _moneyTexture.Width(), _moneyTexture.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _moneyTexture.imageField());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glDisable(GL_TEXTURE_2D);
}

// Allows Keyboard Input
void RubiksWidget::enableFocus()
{
  this->setFocusPolicy(Qt::StrongFocus);
}

// All Keyboard input
void RubiksWidget::keyPressEvent(QKeyEvent *_event)
{
  // Keycodes
  int shift = 16777248;

  int keyPressed = _event->key();

  string move = "None"; // This gets updated when something valid happends
  if(keyPressed != shift)
  {
    if(_event->modifiers() & Qt::ShiftModifier)
    {
      // If we are pressing shift then the command is reversed
      if(keyPressed == 85){ move = "u'";}
      if(keyPressed == 70){ move = "f'";}
      if(keyPressed == 76){ move = "l'";}
      if(keyPressed == 82){ move = "r'";}
      if(keyPressed == 66){ move = "b'";}
      if(keyPressed == 68){ move = "d'";}
    }
    else
    {
      //These are just normal
      // go through face rotations aswell as full cube rotations
      if(keyPressed == 85){ move = "u";}
      if(keyPressed == 70){ move = "f";}
      if(keyPressed == 76){ move = "l";}
      if(keyPressed == 82){ move = "r";}
      if(keyPressed == 66){ move = "b";}
      if(keyPressed == 68){ move = "d";}

      if(keyPressed == 16777234){ move = "Y";}
      if(keyPressed == 16777236){ move = "Y'";}
      if(keyPressed == 16777235){ move = "X";}
      if(keyPressed == 16777227){ move = "X'";}
      if(keyPressed == 16777238){ move = "Z";}
      if(keyPressed == 16777232){ move = "Z'";}

    }
  }

  if(move != "None")
  {
    // For all the cubes and helper cubes
    for(unsigned int i = 0; i < cubes.size(); i++)
    {
      cubes[i].rotate(move);
    }
  }
}

// called when OpenGL context is set up
void RubiksWidget::updateScene()
{
  // this angle is used for rotating the whole scene
  this->angle = this->angle + 1;
}

void RubiksWidget::updateCameraDistance(int i)
{
  // Have an offset of +4 or else we end
  // up inside the cube.
  viewDistance = i+4;
}

void RubiksWidget::updateRotateSpeed(int i)
{
  // Have a mapping from 0 - 100
  // to the speeds we actually want
  // to make the slider appear more smooth
  vector<int> speeds = {1, 2, 3, 5, 6, 9, 10, 15, 18, 30};

  // This makes sure that the speed does not change
  // on this frame. But after the cube has completed
  // A full rotation, if we do it isntantly. We get
  // errors where the rotations overshoot, because
  // the speeds are not multiples of eachother
  for(unsigned int j = 0; j < cubes.size(); j++)
  {
    cubes[j].updatedRotateSpeed = speeds[i/10];
  }
}

void RubiksWidget::updateCubeSpacing(int i)
{
  // Updates how far apart each of the cubes are
  for(unsigned int j = 0; j < cubes.size(); j++)
  {
    cubes[j].space = 2 + 0.03 * i;
  }
}

void RubiksWidget::updateEdgeThickness(int i)
{
  // Updates how large the rounded edges are
  for(unsigned int j = 0; j < cubes.size(); j++)
  {
    cubes[j].edgeThickness = float(i) / 100;
  }
}

void RubiksWidget::updateStretchFactor(int i)
{
  // Updates how large the rounded edges are
  for(unsigned int j = 0; j < cubes.size(); j++)
  {
    cubes[j].stretchFactor = float(i) / 20;
  }
}

void RubiksWidget::updateRadius(int i)
{
  // My project is not suited to having everything
  // rotate about a circle, but there you go. :)
  radius = (float)i / 10.0;
}

void RubiksWidget::toggleConfetti(bool toggle)
{
  // Will show or hide the confetti
  if(toggle == true)
  {
    showConfetti = 1;
  }
  else
  {
    showConfetti = 0;
  }
}

void RubiksWidget::updateTexture(int index)
{
  // We set the texture,
  // if we are drawing the money,
  // we change some of the confetti
  // render setttings
  if(index == 0){ setMarcTexture(); }
  if(index == 1){ setEarthTexture(); }
  if(index == 2)
  {
    setMoneyTexture();
    // we have to set this for each piece of confetti
    for(unsigned int i = 0; i < 500; i ++){confetti[i].rainingMoney = 1;}
  }
  else
  {
    for(unsigned int i = 0; i < 500; i ++){confetti[i].rainingMoney = 0;}
  }
}

void RubiksWidget::toggleRotateAboutCircle(bool toggle)
{
  // Will make the whole scene rotate about a circle
  if(toggle == true)
  {
    rotateAboutCircle = 1;
    this->angle = 0;
  }
  else
  {
    rotateAboutCircle = 0;
  }
}

void RubiksWidget::toggleHelperCubes(bool toggle)
{
  // Will show or hide the helper cubes
  if(toggle == true)
  {
    this->cubesToDraw = 4;
  }
  else
  {
    this->cubesToDraw = 1;
  }
}

void RubiksWidget::toggleShinyMaterials(bool toggle)
{
  // Will show the shiny metallic materials or the normal
  // plastic materials
  int newOffset = 0;

  if(toggle == true)
  {
    newOffset = 7;
  }

  // Update all the cubies of all the cubes
  for(unsigned int j = 0; j < cubes.size(); j++)
  {
    for(unsigned int k = 0; k < cubes[j].cubies.size(); k++)
    {
      cubes[j].cubies[k].materialsOffset = newOffset;
    }
  }
}

void RubiksWidget::solveCubeButton()
{
  // Try to solve the cube, unless it is already
  // being solved or scrambled
  for(unsigned int j = 0; j < cubes.size(); j++)
  {
    cubes[j].startSolve();
  }
}

void RubiksWidget::scrambleCubeButton()
{
  // Try to scramble the cube, unless somethings already happening
  // We have to make a global list of random scramble moves.
  // If we let each cube pick their own, they will just pick
  // randomly and mess up the cubes relative to eachother
  // so we have to make a list here and pass it to each cube
  srand(time(NULL));
  vector<string> allMoves = {"u", "d", "l", "r", "f", "b"};
  vector<string> randomMoves;
  for(int i = 0; i < cubes[0].movesInAScramble; i++)
  {
    randomMoves.push_back(allMoves[rand() % 6]);
  }
  for(unsigned int j = 0; j < cubes.size(); j++)
  {
    cubes[j].startScramble(randomMoves);
  }
}



// called when OpenGL context is set up
void RubiksWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.0, 0.6, 0.8, 0.0);

	} // initializeGL()


// called every time the widget is resized
void RubiksWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget

	glViewport(0, 0, w, h);
  glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  glEnable(GL_DEPTH_TEST);

  // Lighting

  GLfloat allOnes[] = {1, 1, 1, 1};
  GLfloat ambient[] = {0.0, 0.0, 0.0, 0.0};
  GLfloat diffuse[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
  glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 180.);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);


  glEnable(GL_LIGHT1);
  glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 180.);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 180.0);
  glMatrixMode(GL_MODELVIEW);

  setMarcTexture();

	} // resizeGL()


// called every time the widget needs painting
void RubiksWidget::paintGL()
	{ // paintGL()
	// clear the widget
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(viewDistance, viewDistance, viewDistance, 0.0,0.0,0.0, 0.0,1.0,0.0);



  ///////////////////////////////////////////
  // Lighting
  ///////////////////////////////////////////
  GLfloat light_pos2[] = {8., 8., 8., 1.};

  // for the light y positon
  float lightY = 0;
  float r = this->angle % 1080;

  // This is a beautiful line
  // This nicely lerps my light height
  // between 8, 4 and -4 on each rotation
  // show that 3 different relfection types
  // can be shown, making the scene nicer
  lightY = 8.0 -min(max(0.0, r - 330.0) * 0.1, 4.0)    // The component to change from 8 -> 4
               - min(max(0.0, r - 690.0) * 0.1, 8.0)   // The component to chagne from 4 -> -4
               + min(max(0.0, r - 960.0) * 0.1, 12.0); // The last to go back up from -4 -> 8


  GLfloat light_pos1[] = {0., lightY, 8., 1.};  // -4 bottom reflection
                                            //  4 boring reflection
                                            //  8 cool top ref

  // Rotating light for reflections
	glPushMatrix();
  glRotatef(this->angle, 0.0, 1.0, 0.0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos1);
  glPopMatrix();

  // Secondary light, for constant lightnig
  glPushMatrix();
  glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
  glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 180.);
  glPopMatrix();




   ///////////////////////////////////////////
   // Rotate Scene about circle
   ///////////////////////////////////////////
  if(rotateAboutCircle == 1)
  {
    glTranslatef(-radius, 0, -radius);
    glRotatef(this->angle, 0.0, 1.0, 0.0);
    glTranslatef(-radius, 0, -radius);
  }

  ///////////////////////////////////////////
  // Rendering Cubies
  ///////////////////////////////////////////
  for(unsigned int i = 0; i < cubes.size(); i++)
  {
    // Here we still do everything else
    // to the helper cubes except from the drawing
    glPushMatrix();
    glTranslatef(cubeTrans[i][0], cubeTrans[i][1], cubeTrans[i][2]);
    glRotatef((int)cubeRot[i][0], cubeRot[i][1], cubeRot[i][2], cubeRot[i][3]);
    cubes[i].update();
    if(i < this->cubesToDraw)
    {
      cubes[i].draw();
    }
    glPopMatrix();
  }

  ///////////////////////////////////////////
  // Confetti
  ///////////////////////////////////////////
  if(showConfetti == 1)
  {
    glEnable(GL_TEXTURE_2D);
    for(unsigned int i = 0; i < confetti.size(); i++)
    {
      confetti[i].update();
    }
    glDisable(GL_TEXTURE_2D);
  }


	// flush to screen
	glFlush();

	} // paintGL()
