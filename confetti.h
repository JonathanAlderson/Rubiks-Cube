#include <stdlib.h>
#include <QGLWidget>

class Confetti
{
  public:
    // position
    float x;
    float y;
    float z;

    // we need these for respawning the confetti
    int yMax;

    float size;

    // animation
    int frame;
    float xRot;
    float zRot;
    float speed;
    float chaos;
    float rotateSpeed;

    // colour
    float r;
    float g;
    float b;

    // Only for the money stuff
    float moneySize;    // Just for the money
    int rainingMoney; // Changes the shape and the RGB

    Confetti(int xMin, int xMax,
             int yMin, int yMax,
             int zMin, int zMax,
             float speedIn);

    float randFloat(float a, float b); // Random float between range

    void draw();   // Renders a single piece of confetti

    void update(); // Computes movement for the confetti


};
