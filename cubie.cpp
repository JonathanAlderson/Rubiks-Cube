#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <iostream>
#include <algorithm>
#include <vector>
#include "cubie.h"
using namespace std;


Cubie::Cubie(int xIn, int yIn, int zIn, int scaleIn,
      int upIn, int frontIn, int leftIn,
      int rightIn, int backIn, int downIn, int idIn)
{
  // cubie relative positon to cube
  x = xIn;
  y = yIn;
  z = zIn;

  // How big the 'stickers' are
  size = scaleIn;

  // integers to reprsent which material each face should have
  up = upIn;
  front = frontIn;
  left = leftIn;
  right = rightIn;
  back = backIn;
  down = downIn;

  // refernecing ID
  id = idIn;

  // Plastic Materials
  materials.push_back(whitePlasticMaterials);
  materials.push_back(greenPlasticMaterials);
  materials.push_back(redPlasticMaterials);
  materials.push_back(cyanPlasticMaterials);
  materials.push_back(orangeMaterials);
  materials.push_back(yellowPlasticMaterials);
  materials.push_back(blackPlasticMaterials);


  // Metal alternative Materials
  materials.push_back(emeraldMaterials);
  materials.push_back(pearlMaterials);
  materials.push_back(jadeMaterials);
  materials.push_back(goldMaterials);
  materials.push_back(orangeGoldMaterials);
  materials.push_back(rubyMaterials);
  materials.push_back(blackPlasticMaterials);


  materialsOffset = 0; // This is either 0 or 6
                           // Giving an offset into the
                           // material choices we are using

  // Modeling glu objects
  edge = gluNewQuadric();
  corner = gluNewQuadric();
}

void Cubie::rotateCube(string rotation)
{
  // This function updates a cubies info
  // after a rotation
  char move = rotation[0];
  char axis  = rotation[0];
  int prime = 0;


  /////////////////////////////////////////////////
  // INPUT FORMATTING
  /////////////////////////////////////////////////
  // Finds out what the axis is based on the whole cube
  // rotation or face rotation, and if it's prime
  if(rotation.length() == 1)
  { // Standard Move
    if(axis == 'l' or axis == 'd' or axis == 'b') { prime = 1;}
    else                                          { prime = 0;}
  }
  if(rotation.length() == 2)
  { // Inverted Move
    if(axis == 'l' or axis == 'd' or axis == 'b') { prime = 0;}
    else                                          { prime = 1;}

  }
  if(axis == 'f') {axis = 'Z';}
  if(axis == 'b') {axis = 'Z';}

  if(axis == 'u') {axis = 'Y';}
  if(axis == 'd') {axis = 'Y';}

  if(axis == 'l') {axis = 'X';}
  if(axis == 'r') {axis = 'X';}


  /////////////////////////////////////////////////
  // UPDATE POSITION
  /////////////////////////////////////////////////
  vector<vector<int>> cornerRotation = {{-1, -1}, { 1, -1}, { 1,  1},{-1,  1}};
  vector<vector<int>> edgeRotation   = {{ 0, -1}, { 1,  0}, { 0,  1},{-1,  0}};
  vector<vector<int>> centreRotation = {{ 0,  0}};
  vector<int> thisPoint      = {0, 0};

  // get the two axis' which can be effected
  if(axis == 'X'){ thisPoint = {y, z}; }
  if(axis == 'Y'){ thisPoint = {x, z}; }
  if(axis == 'Z'){ thisPoint = {x, y}; }

  int index = -1;
  vector<vector<int>> listToUse; // The list we want to use

  // Find which list the point is and get the index
  for(unsigned int i = 0; i < cornerRotation.size(); i++)
  {
    if(thisPoint == cornerRotation[i]){ index = i; listToUse = cornerRotation;}
  }

  for(unsigned int i = 0; i < edgeRotation.size(); i++)
  {
    if(thisPoint == edgeRotation[i]){ index = i; listToUse = edgeRotation;}
  }

  if(thisPoint == centreRotation[0]){ index = 0; listToUse = centreRotation;}

  // Find what the new index shold be
  if(axis == 'Y')
  {
    if(prime == 0){ index += 1;} // It's just a normal rotation
    if(prime == 1){ index -= 1;} // It's a prime rotation
  }
  else
  {
    if(prime == 0){ index -= 1;} // It's just a normal rotation
    if(prime == 1){ index += 1;} // It's a prime rotation
  }

  // Get where the point x, y, z should be now, after the cube rotation
  index = index % listToUse.size();

  // Give the updated x, y, z positions
  if(axis == 'X'){ y = listToUse[index][0]; z = listToUse[index][1]; }
  if(axis == 'Y'){ x = listToUse[index][0]; z = listToUse[index][1]; }
  if(axis == 'Z'){ x = listToUse[index][0]; y = listToUse[index][1]; }



  /////////////////////////////////////////////////
  // COLOUR SWAPPING
  /////////////////////////////////////////////////
  int oldFront = front;
  int oldBack = back;
  int oldLeft = left;
  int oldRight = right;
  int oldUp = up;
  int oldDown = down;
  int colourMap = 0;
                                      // We have a different colour map
                                      // for each axis of rotation and both directions
  vector<vector<int>> colourRotation = {{oldRight, oldFront, oldLeft, oldBack, oldUp, oldDown},
                                        {oldLeft, oldBack, oldRight, oldFront, oldUp, oldDown},
                                        {oldDown, oldLeft, oldUp , oldRight, oldFront, oldBack},
                                        {oldUp, oldLeft, oldDown , oldRight, oldBack, oldFront},
                                        {oldFront, oldDown, oldBack, oldUp, oldLeft, oldRight},
                                        {oldFront, oldUp, oldBack, oldDown, oldRight, oldLeft},
                                       };

  // Select correct colour map
  if(axis == 'Y' and prime == 0){colourMap = 0;}
  if(axis == 'Y' and prime == 1){colourMap = 1;}
  if(axis == 'X' and prime == 0){colourMap = 2;}
  if(axis == 'X' and prime == 1){colourMap = 3;}
  if(axis == 'Z' and prime == 0){colourMap = 4;}
  if(axis == 'Z' and prime == 1){colourMap = 5;}

  // Update the colours
  front = colourRotation[colourMap][0];
  left = colourRotation[colourMap][1];
  back = colourRotation[colourMap][2];
  right = colourRotation[colourMap][3];
  up = colourRotation[colourMap][4];
  down = colourRotation[colourMap][5];
}

void Cubie::roundedCorner(float radius, float length)
{
  // Draw a rounded edge
  gluCylinder(corner, radius, radius, length, 10, 10);
}

void Cubie::roundedEdge(float size)
{
  // Draw a rounded corner
  gluSphere(edge, size, 4, 4);
}

void Cubie::draw(float edgeThickness)
{
  // Draws the rounded corners and
  // edges aswell as the faces

  float size = 1 - edgeThickness; // How big each of the flat faces are
  float gap = edgeThickness;  // Gap for rounded corners

  // Each of the translatinos we have to do, so we traverse through all the edges
  vector<vector<int>> edgeCoords = {{1, 1, 1},
                                    {-2, 0, 0},
                                    {0, 0, -2},
                                    {2, 0, 0},
                                    {0, -2, 2},
                                    {-2, 0, 0},
                                    {0, 0, -2},
                                    {2, 0, 0},
                                  };

  // All  the outside edges
  materialStruct* outlineMat = &materials[6];

  glMaterialfv(GL_FRONT, GL_AMBIENT,    outlineMat->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    outlineMat->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   outlineMat->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   outlineMat->shininess);

  glPushMatrix();
  for(int i = 0; i < edgeCoords.size(); i++)
  {
    // get into the right positon
    glTranslatef(size * edgeCoords[i][0],
                 size * edgeCoords[i][1],
                 size * edgeCoords[i][2]);
    // do rounded edge
    this->roundedEdge(gap);
    if(i < 4)
    { // Downward facing edges
      glRotatef(90, 1.0, 0.0, 0.0);
      this->roundedCorner(gap, size * 2); // rounded corner at the bottom
      glRotatef(-90, 1.0, 0.0, 0.0);
    }
    // Do the rotaiton, so the edge is oriented correctly
    glRotatef(-90 * (i + 1), 0.0, 1.0, 0.0);
    this->roundedCorner(gap, size * 2);
    glRotatef(90 * (i + 1), 0.0, 1.0, 0.0);

  }
  glPopMatrix();

  // Faces

  // Here are normals
  GLfloat normals[][7] = { {1., 0. ,0.}, {-1., 0., 0.}, // left right
                           {0., 0., 1.}, {0., 0., -1.}, // front back
                           {0., 1., 0.}, {0., -1., 0.}, // up down
                           {0., 0., 0.}                 // error normal
                          };

  // For each of these, we find the correct material
  // from the class variables, then draw a simple square poly

  // front
  materialStruct* mat = &materials[front + materialsOffset];
  glMaterialfv(GL_FRONT, GL_AMBIENT,    mat->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    mat->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   mat->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   mat->shininess);

  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
  glVertex3f(-size, -size, size + gap);
  glVertex3f( size, -size, size + gap);
  glVertex3f( size,  size, size + gap);
  glVertex3f(-size,  size, size + gap);
  glEnd();


  // // back
  mat = &materials[back + materialsOffset];
  glMaterialfv(GL_FRONT, GL_AMBIENT,    mat->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    mat->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   mat->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   mat->shininess);

  glNormal3fv(normals[3]); // 3
  glBegin(GL_POLYGON);
  glVertex3f(-size, -size, -size - gap);
  glVertex3f( size, -size, -size - gap);
  glVertex3f( size,  size, -size - gap);
  glVertex3f(-size,  size, -size - gap);
  glEnd();


  // // left
  mat = &materials[left + materialsOffset];
  glMaterialfv(GL_FRONT, GL_AMBIENT,    mat->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    mat->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   mat->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   mat->shininess);

  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
  glVertex3f( -size - gap, -size,  size);
  glVertex3f( -size - gap, -size, -size);
  glVertex3f( -size - gap,  size, -size);
  glVertex3f( -size - gap,  size,  size);
  glEnd();


  // // right
  mat = &materials[right + materialsOffset];
  glMaterialfv(GL_FRONT, GL_AMBIENT,    mat->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    mat->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   mat->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   mat->shininess);

  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
  glVertex3f( size + gap, -size, -size);
  glVertex3f( size + gap, -size,  size);
  glVertex3f( size + gap,  size,  size);
  glVertex3f( size + gap,  size, -size);
  glEnd();


  // up
  mat = &materials[up + materialsOffset];
  glMaterialfv(GL_FRONT, GL_AMBIENT,    mat->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    mat->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   mat->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   mat->shininess);

  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
  glVertex3f( size, size + gap, size);
  glVertex3f(-size, size + gap, size);
  glVertex3f(-size, size + gap, -size);
  glVertex3f( size, size + gap, -size);
  glEnd();


  // down
  mat = &materials[down + materialsOffset];
  glMaterialfv(GL_FRONT, GL_AMBIENT,    mat->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    mat->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   mat->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   mat->shininess);

  glNormal3fv(normals[5]);
  glBegin(GL_POLYGON);
  glVertex3f( size,  -size - gap, size);
  glVertex3f(-size, -size - gap, size);
  glVertex3f(-size, -size - gap, -size);
  glVertex3f( size,  -size - gap, -size);
  glEnd();
}
