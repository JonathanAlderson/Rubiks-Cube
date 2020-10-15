#include <vector>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include "materials.h"

using namespace std;
class Cubie
{
  public:
    // Tell us how to draw every side
    // of each individual cubie
    // after any type of rotation
    // all these are updated
    int up;
    int front;
    int left;
    int right;
    int back;
    int down;

    int id;

    // these tell us how to draw each surface
    vector<materialStruct> materials;

    int materialsOffset; // This is for the boolean to change materials


    // the relative position of each cubie
    // compared to the cube, these x, y, z in [-1, 0 1]
    int x;
    int y;
    int z;

    // for rendering
    int size;

    // Constructor
    Cubie(int xIn, int yIn, int zIn, int scaleIn,
               int upIn, int frontIn, int leftIn,
               int rightIn, int backIn, int downIn, int idIn);

    // This is called on each cubie when we do an X, X', Y, Y', Z, Z'
    // or on a subset of cubies after a F, R, L, U, D, B '
    void rotateCube(string rotation);

    // Draws a cubie, called every frame
    void draw(float edgeThickness);

    // Draws the glu sphere as the corner
    void roundedCorner(float radius, float length);

    // Draws the glu cyclinder as the edge
    void roundedEdge(float size);

  private:
    // used for the rounded corners and edges
    GLUquadricObj* edge;
    GLUquadricObj* corner;
};
