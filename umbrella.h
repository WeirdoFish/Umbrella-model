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
     vector <Point> sector;
     vector <Point> stick;
     vector <Point> slat;
     vector <Point> rivet;

     Point getPoint(Point center, float radius, float theta, float phi);
protected:
      void genSector();
      void genStick(Point center);
      void genSlat();
      void genRivet(Point center);
public:
    Umbrella(int a);

    vector <GLfloat> getSector();
    vector<GLfloat> getStick();
    vector <int> getStickIdx();

    vector <GLfloat> getSlat();
    vector <int> getSlatIdx();

    vector <int> getRivetIdx();
    vector <GLfloat> getRivet();
};

#endif // UMBRELLA_H
