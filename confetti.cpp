#include "confetti.h"
#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>

Confetti::Confetti(int xMin, int xMax,
                   int yMin, int yMaxIn,
                   int zMin, int zMax,
                   float speedIn)
{
  // On initiailse, give random variables between input parameters
  yMax = yMaxIn;
  x = randFloat(xMin, xMax);
  y = randFloat(yMin, yMax);
  z = randFloat(zMin, zMax);
  size = randFloat(0.2, 0.9);

  speed = speedIn;
  chaos = speed;
  xRot = rand() % 360;
  zRot = rand() % 360;

  // Money paraters
  moneySize = 0.5;
  rainingMoney = 0;

  frame = rand() % 360; // Stars the sin functions in different places

  // Random Colours
  r = randFloat(0.0, 1.0);
  g = randFloat(0.0, 1.0);
  b = randFloat(0.0, 1.0);
}

void Confetti::update()
{

  // Update the colours and clamp them
  r += randFloat(-0.1, 0.1);
  g += randFloat(-0.1, 0.1);
  b += randFloat(-0.1, 0.1);

  if(r < 0.0){ r = 0.0; }
  if(r > 1.0){ r = 1.0; }
  if(g < 0.0){ g = 0.0; }
  if(g > 1.0){ g = 1.0; }
  if(b < 0.0){ b = 0.0; }
  if(b > 1.0){ b = 1.0; }
  

  frame += 1; // Frame controls the position in the sin function
  chaos = chaos + randFloat(0.0, speed / 5.0); // Makes the speed vary as it's going down
  y = y - chaos;
  zRot = 8 * frame; // Have a constant spin
  xRot = (sin((float)frame / (speed*1000.0)) * 90) + 90; // makes the nice flopping back and forth
  draw();

  // Check if went too far down, then reset the position
  if(y < -30)
  {
    y = 15;
    chaos = speed;
  }
}

float Confetti::randFloat(float a, float b)
{
  // just a simple random float function.
  // because I kept on having to make random
  // numbers so I thought I'd make one
  float c = a + (float) (rand()) /( (float) (RAND_MAX/(b-a)));
  return c;
}

void Confetti::draw()
{
  glPushMatrix();
  glTranslatef(x, y ,z);            // Move to position
  glRotatef(xRot, 1.0, 0.0, 0.0);   // do the x and z rotation
  glRotatef(zRot, 0.0, 0.0, 1.0);

  glDisable(GL_LIGHTING);           // disable lighting for the textures part
  glBegin(GL_POLYGON);

  // Either the earth texture or the marc texture
  if(rainingMoney == 0)
  {
    glColor3f(r, g, b);
    glTexCoord2f(0.0, 1.0);           // Plot out the texture and draw a simple square
    glVertex3f(-size, -size, size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f( size, -size, size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( size,  size, size);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size,  size, size);
  }

  // Draw with money parameters
  else
  {
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);           // Plot out the texture and draw a simple square
    glVertex3f(-moneySize, -moneySize * 2, moneySize);
    glTexCoord2f(0.0, 0.0);
    glVertex3f( moneySize, -moneySize * 2, moneySize);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( moneySize,  moneySize * 2, moneySize);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-moneySize,  moneySize * 2, moneySize);
  }


  glEnd();
  glEnable(GL_LIGHTING);
  glPopMatrix();
}
