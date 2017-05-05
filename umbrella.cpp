#include "umbrella.h"

#define pi 3.1415926535897

Umbrella::Umbrella(int a){
    step = 20;
    genSector();
    genSlat();
    genWand();
    initVectors();
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
            sector.push_back(getPoint(Point(0,0,0),radius, theta,j));
         }

   int i = 0;
   Point last = sector[1];
   genStick(sector[0]);
   //genRivet(sector[0]);

   while (i<140 && last.x>=0){
       Point nextPoint = Point();
       if (i%2!=0) {
           nextPoint.z=sector[i].z + pow(sector[i-1].x,2)/8.0;
           nextPoint.y=sector[i].y - 0.002;
           nextPoint.x=sector[i].x - 0.0043;

       } else {
           nextPoint.z=sector[i].z + pow(sector[i].x,2)/8.0;
           nextPoint.y=sector[i].y;
           nextPoint.x=sector[i].x - 0.0048;

       }

       sector.push_back(nextPoint);
       i++;
       last = nextPoint;
   }

}


void  Umbrella::genRivet(Point center){
   // center.x=0.006;
    //center.z-=0.003;
    float radius = 0.0025;
    float theta = pi/4.0f;
    rivet.clear();

    for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
        rivet.push_back(getPoint(center,radius, theta, j));
     }

    int i = 0;
    while (i<20){
        Point nextPoint = Point();
        nextPoint.z=rivet[i].z - 0.0052;//pow(rivet[i].x,2)/8.0;
        nextPoint.y=rivet[i].y;
        nextPoint.x=rivet[i].x + 0.0013;

        rivet.push_back(nextPoint);
        i++;
    }
}

void Umbrella::genWand(){
    Point center = Point(0,0,0.53);
    float radius = 0.005;
    float theta = pi/4.0f;
    wand.clear();

    for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
        wand.push_back(getPoint(center,radius, theta, j));
    }

    int i = 0;
    while (wand[wand.size()-1].z>0.37){
        Point nextPoint = Point();
        nextPoint.z=wand[i].z - 0.0052;
        nextPoint.y=wand[i].y;
        nextPoint.x=wand[i].x;

        wand.push_back(nextPoint);
        i++;
    }

//крепление 1
    center = Point(0,0,0.37);
    radius = 0.011;

    for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
        wand.push_back(getPoint(center,radius, theta, j));
    }

    i+=step;
        while (wand[wand.size()-1].z>0.35){
            Point nextPoint = Point();
            nextPoint.z=wand[i].z - 0.0052;
            nextPoint.y=wand[i].y;
            nextPoint.x=wand[i].x;

            wand.push_back(nextPoint);
            i++;
        }
//крепление 2
      center = Point(0,0,0.35);
        radius = 0.008;

        for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
            wand.push_back(getPoint(center,radius, theta, j));
        }

        i+=step;
            while (wand[wand.size()-1].z>0.32){
                Point nextPoint = Point();
                nextPoint.z=wand[i].z - 0.0052;
                nextPoint.y=wand[i].y;
                nextPoint.x=wand[i].x;

                wand.push_back(nextPoint);
                i++;
            }
//палка дальше
            center = Point(0,0,0.32);
            radius = 0.005;

            for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
                wand.push_back(getPoint(center,radius, theta, j));
            }

            i+=step;
                while (wand[wand.size()-1].z>0){
                    Point nextPoint = Point();
                    nextPoint.z=wand[i].z - 0.0052;
                    nextPoint.y=wand[i].y;
                    nextPoint.x=wand[i].x;

                    wand.push_back(nextPoint);
                    i++;
                }


}

void  Umbrella::genStick(Point center){
    center.x-=0.003;
    center.z-=0.003;

    genRivet(center);
    float radius = 0.0025;
    float theta = pi/4.0f;
    stick.clear();

    for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
        stick.push_back(getPoint(center,radius, theta, j));
     }

    int i = 0;
    Point last = stick[1];

    while (last.x>=0){
        Point nextPoint = Point();
        nextPoint.z=stick[i].z + pow(stick[i].x,2)/8.0;
        nextPoint.y=stick[i].y;
        nextPoint.x=stick[i].x - 0.005;

        stick.push_back(nextPoint);
        i++;
        last = nextPoint;
    }
}

void Umbrella::genSlat(){
    Point center = Point (0, 0, 0.37);
    float radius = 0.0025;
    float theta = pi/4.0f;

    for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
        slat.push_back(getPoint(center,radius, theta, j));
     }

    int i = 0;
    while (i<620){
        Point nextPoint = Point();
            nextPoint.z=slat[i].z + 0.002;
            nextPoint.y=slat[i].y;
            nextPoint.x=slat[i].x - 0.005;

        slat.push_back(nextPoint);
        i++;
    }

}


vector <GLfloat> Umbrella::getSector(){return  sectorPts;}
vector<int> Umbrella::getSlatIdx(){  return slatIdx;}
vector <GLfloat> Umbrella::getSlat(){return  slatPts;}
vector <int> Umbrella::getRivetIdx(){ return rivetIdx;}
vector <GLfloat> Umbrella::getRivet(){ return rivetPts;}
vector<GLfloat>  Umbrella::getStick(){  return  stickPts;}
vector <int> Umbrella::getStickIdx(){ return stickIdx;}
vector <GLfloat> Umbrella::getWand(){ return wandPts; }
vector <int> Umbrella::getWandIdx() {return wandIdx;}

void Umbrella::initVectors(){
 //slat
        for (int i = 0; i<(slat.size()-step); i++){
            slatIdx.push_back(i);
            slatIdx.push_back(i+step);
        }

        for (Point p : slat) {
            slatPts.push_back(p.x);
            slatPts.push_back(p.y);
            slatPts.push_back(p.z);
        }
//rivet
        for (int i = 0; i<(rivet.size()-step); i++){
            rivetIdx.push_back(i);
            rivetIdx.push_back(i+step);
        }

        for (Point p : rivet) {
            rivetPts.push_back(p.x);
            rivetPts.push_back(p.y);
            rivetPts.push_back(p.z);
        }
 //stick
        for (Point p : stick) {
            stickPts.push_back(p.x);
            stickPts.push_back(p.y);
            stickPts.push_back(p.z);
        }

        for (int i = 0; i<(stick.size()-step); i++){
            stickIdx.push_back(i);
            stickIdx.push_back(i+step);
        }

//sector
        for (Point p: sector) {
            sectorPts.push_back(p.x);
            sectorPts.push_back(p.y);
            sectorPts.push_back(p.z);
        }
//цфтв
        for (Point p : wand) {
             wandPts.push_back(p.x);
             wandPts.push_back(p.y);
             wandPts.push_back(p.z);
          }

        for (int i = 0; i<(wand.size()-step); i++){
             wandIdx.push_back(i);
             wandIdx.push_back(i+step);
         }

}












