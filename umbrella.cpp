#include "umbrella.h"

#define pi 3.1415926535897

Umbrella::Umbrella(int a){
    step = 20;
    genSector();
}

Umbrella::Point  Umbrella::getPoint(Point center, float radius, float theta, float phi){
    float px = center.x + radius*sin(theta)*cos(phi);
    float py = center.y + radius*sin(theta)*sin(phi);
    float pz = center.z + radius*cos(theta);

    return Point(px,py,pz);
}

void Umbrella::genSector(){
     sector.clear();
     float theta = pi/4.0f;
     float radius = 0.4;

        for (float j = 0; j<2.0f*pi/14.0+0.2; j+=2.0f*pi/14.0){
            sectorPts.push_back(getPoint(Point(0,0,0),radius, theta,j));
         }

   int i = 0;
   Point last = sectorPts[1];
   genStick(sectorPts[0]);

   while (i<140 && last.x>=0){
       Point nextPoint = Point();
       if (i%2!=0) {
           nextPoint.z=sectorPts[i].z + pow(sectorPts[i-1].x,2)/8.0;
           nextPoint.y=sectorPts[i].y - 0.002;
           nextPoint.x=sectorPts[i].x - 0.0043;

       } else {
           nextPoint.z=sectorPts[i].z + pow(sectorPts[i].x,2)/8.0;
           nextPoint.y=sectorPts[i].y;
           nextPoint.x=sectorPts[i].x - 0.0048;

       }

       sectorPts.push_back(nextPoint);
       i++;
       last = nextPoint;
   }

}


void  Umbrella::genStick(Point center){
    center.x-=0.003;
    center.z-=0.003;
    float radius = 0.0025;
    float theta = pi/4.0f;
    stickPts.clear();

    for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
        stickPts.push_back(getPoint(center,radius, theta, j));
     }

    int i = 0;
    Point last = stickPts[1];

    while ( last.x>=0){
        Point nextPoint = Point();
        if (i%2!=0) {
            nextPoint.z=stickPts[i].z + pow(stickPts[i-1].x,2)/8.0;
            nextPoint.y=stickPts[i].y;
            nextPoint.x=stickPts[i].x - 0.005;

       } else {
            nextPoint.z=stickPts[i].z + pow(stickPts[i].x,2)/8.0;
            nextPoint.y=stickPts[i].y;
            nextPoint.x=stickPts[i].x - 0.005;

        }

        stickPts.push_back(nextPoint);
        i++;
        last = nextPoint;
    }
}

void Umbrella::genSlat(){
    Point center = Point (0, 0, 0.3);
    float radius = 0.0025;
    float theta = pi/4.0f;

    for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
        slatPts.push_back(getPoint(center,radius, theta, j));
     }

    int i = 0;
    Point last = slatPts[1];

    while ( last.x>=0){
        Point nextPoint = Point();
            nextPoint.z=slatPts[i].z + 0.005;
            nextPoint.y=slatPts[i].y;
            nextPoint.x=slatPts[i].x - 0.005;

        slatPts.push_back(nextPoint);
        i++;
        last = nextPoint;
    }
}

vector <GLfloat> Umbrella::getSlat(){
    slat.clear();
    for (Point p : slatPts) {
        slat.push_back(p.x);
        slat.push_back(p.y);
        slat.push_back(p.z);
    }
    return slat;
}

vector<int> Umbrella::getSlatIdx(){
    vector<int> idx;
        for (int i = 0; i<(slatPts.size()-step); i++){
            idx.push_back(i);
            idx.push_back(i+step);
        }
    return idx;
}

vector <int> Umbrella::getStickIdx(){
    vector<int> idx;
        for (int i = 0; i<(stickPts.size()-step); i++){
            idx.push_back(i);
            idx.push_back(i+step);
        }
    return idx;
}

vector<GLfloat>  Umbrella::getStick(){
    stick.clear();
    for (Point p : stickPts) {
        stick.push_back(p.x);
        stick.push_back(p.y);
        stick.push_back(p.z);
    }
    return stick;
}

vector <GLfloat> Umbrella::getSector(){
    sector.clear();
    for (Point p: sectorPts) {
        sector.push_back(p.x);
        sector.push_back(p.y);
        sector.push_back(p.z);
    }
    return sector;
}
