#include <string>
#include <stack>
#include <cmath>
#include "cubie.h"

using namespace std;
class Cube
{
  // Cube class, there is only one of these
  // it represents the whole Rubiks cube
  // we have 4 instances for the helper cubes aswell
  public:
    vector<Cubie> cubies;
    vector<vector<int>> faceData;

    // Rotation Stuff
    vector<int> cubeRotations;
    vector<int> remainingCubeRotations;
    vector<int> faceRotations;
    vector<int> remainingFaceRotations;
    vector<int> cubiesToRotate;



    // Cube and face rotations
    int rotateSpeed;
    int updatedRotateSpeed;
    int doingRotation;
    int finishedRotation;

    // Scrambling and Solving
    int solvingCube;
    int scramblingCube;
    int movesInAScramble;
    int remainingScrambleMoves;
    vector<string> scrambleMoves;
    stack<string> allMoves;
    string currentRotation; // The last successfully inputted move



    // Variables for rendering the cube
    float edgeThickness;                // how thick the black edges are
    float space;                        // how far apart each cubie is
    float stretchFactor;                // How animated each rotation is


    // Functions
    Cube();
    void draw();            // Draw all of the cubes children cubies
    void update();          // The main loop, calls everything else we need
    int rotate(string rot); // The main input to set off a rotation
    void doAnimation();     // Called every frame to draw turning animations
    void finishAnimation(); // Called when a move is finished to update positions and colours
    void startSolve();      // Called by the button, to set off the solve
    void solveCube();       // Inputs the right moves to solve the cube
    void scrambleCube();    // Scrambles the cube
    void startScramble(vector<string> &randomMoves); // gets passed a vector of the moves in the scramble
    vector<int> getCubies(int x, int y, int z);      // Gets cubie ID's on a specific face
};
