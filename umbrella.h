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
     vector <Point> wand;

     vector <GLfloat> sectorPts;

     vector <GLfloat> stickPts;
     vector <int> stickIdx;

     vector <GLfloat> slatPts;
     vector <int> slatIdx;

     vector <GLfloat> rivetPts;
     vector <int> rivetIdx;

     vector <GLfloat> wandPts;
     vector <int> wandIdx;

     Point getPoint(Point center, float radius, float theta, float phi);
protected:
      void genSector();
      void genStick(Point center);
      void genSlat();
      void genRivet(Point center);
      void genWand();
public:
    Umbrella(int a);

    vector <GLfloat> getWand();
    vector <int> getWandIdx();

    vector <GLfloat> getSector();

    vector<GLfloat> getStick();
    vector <int> getStickIdx();

    vector <GLfloat> getSlat();
    vector <int> getSlatIdx();

    vector <int> getRivetIdx();
    vector <GLfloat> getRivet();

    void initVectors();
};

#endif // UMBRELLA_H
