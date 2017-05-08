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

        float length(const Point b);
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

     vector <GLfloat> secNorm;
     vector <GLfloat> stickNorm;
     vector <GLfloat> slatNorm;
     vector <GLfloat> rivNorm;
     vector <GLfloat> wandNorm;

     Point getPoint(Point center, float radius, float theta, float phi);
protected:
      void genSector();
      void genStick(Point center);
      void genSlat();
      void genRivet(Point center);
      void genWand();
      void initVectors();
      void initNorms();

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

    vector <GLfloat> getSecNormals();
    vector <GLfloat> getStickNormals();
    vector <GLfloat> getRivetNormals();
    vector <GLfloat> getSlatNormals();
    vector <GLfloat> getWandNormals();
};

#endif // UMBRELLA_H
