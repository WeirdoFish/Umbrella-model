#ifndef UMBRELLA_H
#define UMBRELLA_H

#include <GL/gl.h>
#include <math.h>
#include <vector>
using std::vector;

class Umbrella
{
    struct Point{
        float x;
        float y;
        float z;
        Point(){

        }

        Point (float a, float b, float c){
            x=a;
            y=b;
            z=c;
        }
    };
     int step;
     vector <Point> sectorPts;
     vector <GLfloat>  sector;

     vector <Point> stickPts;
     vector <GLfloat> stick;

     vector <Point> slatPts;
     vector <GLfloat> slat;

     Point getPoint(Point center, float radius, float theta, float phi);
protected:
      void genSector();
      void genStick(Point center);
      void genSlat();
public:
    Umbrella(int a);

    vector <int> getStickIdx();
    vector <GLfloat> getSector();
    vector<GLfloat> getStick();
    vector <GLfloat> getSlat();
    vector <int> getSlatIdx();
};

#endif // UMBRELLA_H
