#include "umbrella.h"
#include <QVector2D>
#include <iostream>

#define pi 3.1415926535897

Umbrella::Umbrella(int a){
    step = 20;
    genSector();
    genSlat();
    genWand();
    initVectors();
    initNorms();
}

float Umbrella::Point::length(const Point b){
    return sqrt(pow(this->x-b.x,2) + pow(this->y-b.y,2) + pow(this->z-b.z,2));
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
                while (wand[wand.size()-1].z>0.06){
                    Point nextPoint = Point();
                    nextPoint.z=wand[i].z - 0.0052;
                    nextPoint.y=wand[i].y;
                    nextPoint.x=wand[i].x;

                    wand.push_back(nextPoint);
                    i++;
                }

//ещё палка
                center = Point(0,0,0.06);
                radius = 0.008;

                for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
                    wand.push_back(getPoint(center,radius, theta, j));
                }

                i+=step;
                    while (wand[wand.size()-1].z>0.052){
                        Point nextPoint = Point();
                        nextPoint.z=wand[i].z - 0.0052;
                        nextPoint.y=wand[i].y;
                        nextPoint.x=wand[i].x;

                        wand.push_back(nextPoint);
                        i++;
                    }
//ручка
                  center = Point(0,0,0.052);
                  radius = 0.011;
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
                  wand.pop_back();
                  i--;
//ручка2

                center = Point (-0.03, 0, 0);
                radius = 0.211;

                for (float j = 2.0*pi; j>pi; j-=pi/10){
                    for (int k = 0; k<step; k++){
                      Point nextPoint = Point();

                        radius = center.length(wand[i]);
                        nextPoint.x= center.x +radius*cos(j);
                        nextPoint.z= center.z +radius*sin(j);
                      /*if ( j<pi){
                          nextPoint.x= wand[i].x + center.x +radius*cos(j);
                          nextPoint.z= wand[i].z - center.z +radius*sin(j);
                      }
                      else {
                          nextPoint.x= wand[i].x + center.x +radius*cos(j);
                          nextPoint.z= wand[i].z + center.z +radius*sin(j);
                      }*/
                      nextPoint.y = wand[i].y;
                      wand.push_back(nextPoint);
                      i++;
                    }
                }
/*
                 while (wand[wand.size()-1].z>-0.02){
                      Point nextPoint = Point();
                      nextPoint.z= wand[i].z - pow(wand[i].x,2);
                      nextPoint.y=wand[i].y;
                      nextPoint.x=wand[i].x + 0.004;

                      wand.push_back(nextPoint);
                      i++;
                }

                          /*
                       center = Point(0,-0.025,0);
                       for (float j = 0; j< 2.0f*pi; j+=2.0f*pi/(float)step){
                           wand.push_back(getPoint(center,radius, theta, j));
                       }

                       int c = i;
                       while (i<c+100){
                           for (int j = 0; j<step; j++){
                               Point nextPoint = Point();
                               nextPoint.z=wand[i].z - 0.0052;
                               nextPoint.y=wand[i].y;
                               nextPoint.x=wand[i].x;

                               wand.push_back(nextPoint);

                               wand[i].x = cos(10)*wand[i].x + sin(10)*wand[i].z;
                               wand[i].z = sin(10)*wand[i].x + cos(10)*wand[i].y;
                              // wand[i].y+=0.025;
                               i++;
                           }
                       }
                       */
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
vector <GLfloat> Umbrella::getSecNormals() { return secNorm; }
vector <GLfloat> Umbrella::getSlatNormals() { return slatNorm; }
vector <GLfloat> Umbrella::getRivetNormals() { return rivNorm; }
vector <GLfloat> Umbrella::getWandNormals() { return wandNorm; }

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

void Umbrella::initNorms(){
    for (int i = 1; i< sector.size()-1; i++){
         Point a,b;
        if (i%2==0){
            a = Point (sector[i].x-sector[i-1].x, sector[i].y-sector[i-1].y, sector[i].z-sector[i-1].z);
            b = Point (sector[i].x-sector[i+1].x, sector[i].y-sector[i+1].y, sector[i].z-sector[i+1].z);
        } else {
            a = Point (sector[i].x-sector[i-1].x, sector[i].y-sector[i-1].y, sector[i].z-sector[i-1].z);
            b = Point (sector[i+1].x-sector[i].x, sector[i+1].y-sector[i].y, sector[i+1].z-sector[i].z);
        }
        Point n = Point (a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
        float length = sqrt(pow(n.x,2)+pow(n.y,2) + pow(n.z,2));
        n.x /= length;
        n.y /= length;
        n.z /= length;
        secNorm.push_back(n.x);
        secNorm.push_back(n.y);
        secNorm.push_back(n.z);
       // std::cout << n.x << ":" << n.y << ":" << n.z << "\n";
    }

    for (int i = 0; i< stickIdx.size()-1; i+=2){
        Point a,b;
        int cur = stickIdx[i];

        a = Point (stick[cur].x-stick[cur+1].x, stick[cur].y-stick[cur+1].y, stick[cur].z-stick[cur+1].z);
        b = Point (stick[cur].x-stick[cur+2].x, stick[cur].y-stick[cur+2].y, stick[cur].z-stick[cur+2].z);

        Point n = Point (a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
        float length = sqrt(pow(n.x,2)+pow(n.y,2) + pow(n.z,2));
        n.x /= length;
        n.y /= length;
        n.z /= length;
        stickNorm.push_back(n.x);
        stickNorm.push_back(n.y);
        stickNorm.push_back(n.z);
       // std::cout << n.x << ":" << n.y << ":" << n.z << "\n";
    }
    int k = stickNorm.size();
    for (int i = k  - step*3; i<k; i++){
         stickNorm.push_back(stickNorm[i]);
    }

std::cout <<"";
}












