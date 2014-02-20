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



#endif /* defined(__malvinasRadarCentral__RingManager__) */

class RingManager {
    
    
public:
    
    RingManager(){};
    
    void setup();
    void draw();
    
    void setRadius(float newRadius);
    void checkRingsDragged(ofPoint pointer);
    
    Ring ring01;
    vector<Ring> rings;
    
private:
    
    void createRings();
    
};