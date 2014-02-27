//
//  RingManager.h
//  malvinasRadarCentral
//
//  Created by Wanda on 19/02/14.
//
//

#ifndef __malvinasRadarCentral__RingManager__
#define __malvinasRadarCentral__RingManager__

#include <iostream>
#include "ofMain.h"
#include "Ring.h"
#include "Pin.h"



#endif /* defined(__malvinasRadarCentral__RingManager__) */

class RingManager {
    
    
public:
    
    RingManager(){};
    
    void setup();
    void update(int mX, int mY);
    void draw();
    
    void setRadius(float newRadius);
    int checkRingsDragged(ofPoint pointer);
    //void startDrag(int _ring);
    void startDrag(ofPoint pointer);
    void stopDrag();
    
    Ring ring01;
    vector<Ring> rings;
    vector <Pin> pins;
    vector <ofPolyline> navigatorHotSpot;
    
private:
    
    void createRings();
    void createHotSpots(int size);
    bool isOnTopOfPair(int currentRing);
    void avoidPair(int currentRing);
    
    
};