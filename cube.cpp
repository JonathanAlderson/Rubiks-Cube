#include <iostream>
#include <list>
#include "cube.h"
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;


Cube::Cube()
{
  // This data is the intial colour scheme
  // of the whole cube. Each cubie is
  // given colour info for the
  // up, down, left, right, front, back faces
  faceData.push_back({0, 6, 4, 6, 3, 6});  // top layer
  faceData.push_back({0, 6, 6, 6, 3, 6});
  faceData.push_back({0, 6, 6, 2, 3, 6});
  faceData.push_back({0, 6, 4, 6, 6, 6});
  faceData.push_back({0, 6, 6, 6, 6, 6});
  faceData.push_back({0, 6, 6, 2, 6, 6});
  faceData.push_back({0, 1, 4, 6, 6, 6});
  faceData.push_back({0, 1, 6, 6, 6, 6});
  faceData.push_back({0, 1, 6, 2, 6, 6});


  faceData.push_back({6, 6, 4, 6, 3, 6});  // middle layer
  faceData.push_back({6, 6, 6, 6, 3, 6});
  faceData.push_back({6, 6, 6, 2, 3, 6});
  faceData.push_back({6, 6, 4, 6, 6, 6});
  faceData.push_back({6, 6, 6, 6, 6, 6});
  faceData.push_back({6, 6, 6, 2, 6, 6});
  faceData.push_back({6, 1, 4, 6, 6, 6});
  faceData.push_back({6, 1, 6, 6, 6, 6});
  faceData.push_back({6, 1, 6, 2, 6, 6});


  faceData.push_back({6, 6, 4, 6, 3, 5});  // bottom layer
  faceData.push_back({6, 6, 6, 6, 3, 5});
  faceData.push_back({6, 6, 6, 2, 3, 5});
  faceData.push_back({6, 6, 4, 6, 6, 5});
  faceData.push_back({6, 6, 6, 6, 6, 5});
  faceData.push_back({6, 6, 6, 2, 6, 5});
  faceData.push_back({6, 1, 4, 6, 6, 5});
  faceData.push_back({6, 1, 6, 6, 6, 5});
  faceData.push_back({6, 1, 6, 2, 6, 5});

  // Logical layout for cubie
  // positions to line up with the face data
  vector<int> xList = {-1, 0, 1};
  vector<int> yList = { 1, 0,-1};
  vector<int> zList = {-1, 0, 1};

  // Controllers for the animation
  // basic premise is to check if any are not 0
  // then move them till they are
  cubeRotations = {0, 0, 0};
  remainingCubeRotations = {0, 0, 0};
  cubiesToRotate = {-1};
                         // F, B, L, R, U, D
  faceRotations =          {0, 0, 0, 0, 0, 0};
  remainingFaceRotations = {0, 0, 0, 0, 0, 0};

  // for counting the cubie id
  int counter = 0;

  // updated rotate speed
  // since we have to wait until a move is
  // done before we update or we get multiple errors
  rotateSpeed = 5;
  updatedRotateSpeed = 5;

  // initial variables
  // before they get changed by sliders
  space = 2.09;
  edgeThickness = 0.2;
  stretchFactor = 0.0;

  // Scrambling variables
  // We have these updates checked in the mainloop
  solvingCube = 0;
  scramblingCube = 0;
  movesInAScramble = 20;
  remainingScrambleMoves = 0;

  doingRotation = 0;
  finishedRotation = 0;

  // The string input of the next move
  currentRotation = "None";


  // Initalise every cubie, with the correct
  // x, y, z position and colour scheme
  for (unsigned int y = 0; y < yList.size(); y++)
  {
    for (unsigned int z = 0; z < zList.size(); z++)
    {
      for (unsigned int x = 0; x < xList.size(); x++)
      {
        Cubie thisOne(xList[x], yList[y], zList[z], 1, faceData[counter][0], faceData[counter][1],
          faceData[counter][2], faceData[counter][3],
          faceData[counter][4], faceData[counter][5], counter);
          cubies.push_back(thisOne);
          counter += 1;
        }
      }
    }

}

void Cube::startSolve()
{
  // Will start the solving, unless we already
  // are, or if it's being scrambled
  // we need these checks or it will be solving and scrambling
  // at the same time
  if(this->solvingCube == 0 and this->scramblingCube == 0)
  {
    this->solvingCube = 1;
  }
}

void Cube::solveCube()
{
  // Pop the stack of moves
  // and carry out a single one
  string nextMove;
  string prime = "'";
  if(!allMoves.empty()) // if there's any more moves to do
  {
    nextMove = allMoves.top();
    allMoves.pop();

    // Invert the move
    if(nextMove.length() == 2){ nextMove = nextMove[0];}
    else                      { nextMove = nextMove + prime;}
    this->rotate(nextMove);
    allMoves.pop(); // Remove what we just did, since it doesn't matter
                    // otherwise, we just get stuck in a loop
  }
  else
  {
    // we have finished solving, and can resume keyboard input
    // as normal
    this->solvingCube = 0;
  }
}

void Cube::startScramble(vector<string> &randomMoves)
{
  // check we arn't already scrambling or solving
  if(this->solvingCube == 0 and this->scramblingCube == 0)
  {
    // reset how many moves left, and the list of
    // which moves to do
    this->remainingScrambleMoves = this->movesInAScramble;
    this->scramblingCube = 1;
    this->scrambleMoves = randomMoves;
  }
}

void Cube::scrambleCube()
{
  // Performs a single move of the
  // scramble. And let's user input
  // continue if we have reached the end
  if(this->remainingScrambleMoves > 0)
  {
    this->rotate(this->scrambleMoves[this->remainingScrambleMoves - 1]);
    this->remainingScrambleMoves -= 1;
  }
  else
  {
    // Finish the scramble
    this->scramblingCube = 0;
  }
}

int Cube::rotate(string rot)
{
  // Takes keyboard input
  // and turns it into a move

  int rotateAmount = 90; // well.. if it wasn't 90 how could you do a full turn
  int thisRotateAmount;

  // If we arn't currently doing a move
  if(this->doingRotation == 0)
  {
    currentRotation = rot;                // so the cubies know what to do after a move
    this->allMoves.push(currentRotation); // add move to the stack
    thisRotateAmount = rotateAmount;      // have a new var, so we can invert if there is a prime move

    // If we are doing a 'prime' move, it needs to be backwards
    // so we inverse the rotation amount to perform a move
    // in the opposite direction
    if(rot[1] == '\'') { thisRotateAmount = -rotateAmount; }

    ////////////////////////////////
    // All Rotation Moves
    ///////////////////////////////
    // I know there's a lot of cases here

    // Whole Cube X
    if(rot[0] == 'X'){this->remainingCubeRotations[0] = -thisRotateAmount;}

    // Whole Cube Y
    else if(rot[0] == 'Y'){this->remainingCubeRotations[1] = -thisRotateAmount;}

    // Whole Cube Z
    else if(rot[0] == 'Z'){this->remainingCubeRotations[2] = -thisRotateAmount;}

    // Front Face
    else if(rot[0] == 'f'){this->remainingFaceRotations[0] = -thisRotateAmount;
                           cubiesToRotate = this->getCubies(-2, -2, 1);}

    // Back Face
    else if(rot[0] == 'b'){this->remainingFaceRotations[1] = thisRotateAmount;
                           cubiesToRotate = this->getCubies(-2, -2, -1);}

    // Left Face
    else if(rot[0] == 'l'){this->remainingFaceRotations[2] = thisRotateAmount;
                           cubiesToRotate = this->getCubies(-1, -2, -2);}

    // Right Face
    else if(rot[0] == 'r'){this->remainingFaceRotations[3] = -thisRotateAmount;
                          cubiesToRotate = this->getCubies(1, -2, -2);}

    // Up Face
    else if(rot[0] == 'u'){this->remainingFaceRotations[4] = -thisRotateAmount;
                           cubiesToRotate = this->getCubies(-2, 1, -2);}

    // Down Face
    else if(rot[0] == 'd'){this->remainingFaceRotations[5] = thisRotateAmount;
                           cubiesToRotate = this->getCubies(-2, -1, -2);}

    this->doingRotation = 1; // now we can't take any more moves
    return 0;                // no errors
    }
  else
  {
    // Move cannot complete, because one is currently
    // being executed
    return 1; // Error
  }

}

void Cube::doAnimation()
{
  // Animate the whole cube rotations
  // and the face rotations
  // then check if we are done

  // Whole cube rotations
  for(unsigned int i = 0; i < this->cubeRotations.size(); i++)
  {
    // If we have any whole cube animations in progress
    // then do a step of them
    if(this->remainingCubeRotations[i] != 0)
    {
      if(this->remainingCubeRotations[i] > 0){this->remainingCubeRotations[i] -= this->rotateSpeed; this->cubeRotations[i] += this->rotateSpeed;}
      else                                   {this->remainingCubeRotations[i] += this->rotateSpeed; this->cubeRotations[i] -= this->rotateSpeed;}
    }
  }

  // face rotations
  for(unsigned int i = 0; i < this->faceRotations.size(); i++)
  {
    // If we have any face animations in progress
    // then do a step of them
    if(this->remainingFaceRotations[i] != 0)
    {
      if(this->remainingFaceRotations[i] > 0){this->remainingFaceRotations[i] -= this->rotateSpeed; this->faceRotations[i] += this->rotateSpeed;}
      else                                   {this->remainingFaceRotations[i] += this->rotateSpeed; this->faceRotations[i] -= this->rotateSpeed;}
    }
  }

  // Check to see if the rotation
  // has been finished
  if(this->doingRotation == 1)
  {
    // Because we are working with ints we don't get any
    // 0.0000000001 errors, they're the worst!
    if(this->remainingCubeRotations == vector<int> {0, 0, 0} and
       this->remainingFaceRotations == vector<int> {0, 0, 0, 0, 0, 0})
    {
      // This function performs all the colour swapping
      // and the position updating
      this->finishAnimation();
    }
  }
}

void Cube::finishAnimation()
{
  // This function is called when the cube has
  // finsihed any type of rotation
  // we must now update all the postiions
  // and colours of the cubies and return the rotations
  // back to normal
  this->finishedRotation = 0;                  // so now we can do another input
  this->doingRotation = 0;                     // ^^
  this->cubeRotations = vector<int> {0, 0, 0}; // reset cube rotaions


  // if cubies to rotate has length of 1
  // when a whole cube rotation has been carried out
  // since we never 'got' the ones on the face we need
  // and just did it on all of them
  if(this->cubiesToRotate.size() == 1)
  {
    for( unsigned int i = 0; i < cubies.size(); i ++)
    {
      // each cubie is responsible for what happends
      // after a rotation, so we call their function
      cubies[i].rotateCube(this->currentRotation);
    }
  }
  // this is when only one face has been rotated
  // so update the colours and positions of those ones
  else
  {
    // Only do the updates on the cubies which belong to the face
    // that just rotated
    for( unsigned int i = 0; i < cubiesToRotate.size(); i ++)
    {
      cubies[cubiesToRotate[i]].rotateCube(this->currentRotation);
    }
  }
  // reset which cubies are involved in roatations
  this->cubiesToRotate = {-1};
  // rest every face rotation so we can do the next
  this->faceRotations = {0, 0, 0, 0, 0, 0};
}

void Cube::update()
{
  // this function carries out the
  // rotation speed,
  // sovling, scrambling and drawing

  // Check if we should make the rotate speed faster this frame
  if(this->doingRotation == 0)
  {
    if(this->updatedRotateSpeed != this->rotateSpeed)
    {
      this->rotateSpeed = this->updatedRotateSpeed;
    }
  }

  // Check if we should do a scramble step this frame
  if(this->scramblingCube == 1 and this->solvingCube == 0)
  {
    // If the previous scramble move has finished
    if(this->doingRotation == 0)
    {
      // input the next move to solve the cube
      this->scrambleCube();
    }
  }

  // Check if we should do a solve step this frame
  if(this->solvingCube == 1 and this->scramblingCube == 0)
  {
    // If the rotation has finished
    if(this->doingRotation == 0)
    {
      // input the next move to solve the cube
      this->solveCube();
    }
  }

  // Update the cubes rotations
  this->doAnimation();
}

void Cube::draw()
{
  // This function draws all the cubies
  // in their correct positions and rotations


  float exaggerateMove; // for use when we have the slider in use


  glPushMatrix();
  // Whole cube rotations
  glRotatef(this->cubeRotations[0], 1.0, 0.0, 0.0);
  glRotatef(this->cubeRotations[1], 0.0, 1.0, 0.0);
  glRotatef(this->cubeRotations[2], 0.0, 0.0, 1.0);

  // Draw each cubie
  for(unsigned int i = 0; i < cubies.size(); i++)
  {
    glPushMatrix();

    // If this cubie is under a complex rotation
    if(std::find(this->cubiesToRotate.begin(), this->cubiesToRotate.end(), i) != this->cubiesToRotate.end())
    {
      // Look at rotation value of each face
      for(unsigned int j = 0; j < this->faceRotations.size(); j++)
      {
        // If we have a cubie under a rotation and we have the angle
        // that this specifc face is under
        if(this->faceRotations[j] != 0)
        {
          // This makes our rotations have a stretch effect based on the slider
          exaggerateMove = this->stretchFactor * sin(abs(this->faceRotations[j])* 3.14159/90) + space;

          // rotate around the relevent axis with the included exaggerate
          // we only perform the exaggerated move on the axises that the rotation
          // is happening on, or else the pieces look like they fly off from the
          // cube
          if(j == 0 or j == 1){glRotatef(this->faceRotations[j], 0.0, 0.0, 1.0);
                                         glTranslatef(exaggerateMove * cubies[i].x, exaggerateMove * cubies[i].y, space * cubies[i].z);}
          if(j == 2 or j == 3){glRotatef(this->faceRotations[j], 1.0, 0.0, 0.0);
                                         glTranslatef(space * cubies[i].x, exaggerateMove * cubies[i].y, exaggerateMove * cubies[i].z);}
          if(j == 4 or j == 5){glRotatef(this->faceRotations[j], 0.0, 1.0, 0.0);
                                         glTranslatef(exaggerateMove * cubies[i].x, space * cubies[i].y, exaggerateMove * cubies[i].z);}
        }
      }
    }
    // The cubie isn't doing a rotation
    else
    {
      // Put it in it's place by looking at the cubies x, y, z coords
      glTranslatef(space * cubies[i].x, space * cubies[i].y, space * cubies[i].z);
    }

    // Now we have the position sorted
    // draw it, making sure to pass the edge thickness
    cubies[i].draw(this->edgeThickness);
    glPopMatrix();
  }
  glPopMatrix();
}

vector<int> Cube::getCubies(int x, int y, int z)
{
  // This function is for finding which
  // cubie objects should be involved when we
  // press 'f' for example. Any time we want the
  // front face moving, then we want all cubies with
  // a Z position of +1. And likewise for any face.

  // Only using integer ID's, less messy than
  // returning object references
  vector<int> toReturn;

  for(unsigned int i = 0; i < cubies.size(); i++)
  {
    if(cubies[i].x == x || x == -2)
    {
      if(cubies[i].y == y || y == -2)
      {
        if(cubies[i].z == z || z == -2)
        {
          toReturn.push_back(cubies[i].id);
        }
      }
    }
  }
  return toReturn;
}
