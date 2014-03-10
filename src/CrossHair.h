//
//  CrossHair.h
//  malvinasRadarCentral
//
//  Created by Zaira on 07/03/14.
//
//

#ifndef __malvinasRadarCentral__CrossHair__
#define __malvinasRadarCentral__CrossHair__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__malvinasRadarCentral__CrossHair__) */

class CrossHair {
    
public:
    CrossHair(){};
    
    void setup(ofPoint _center);
    void draw();
    bool isFinished();
    void reset();
    
    //-----------
    
    ofPoint center;
    int lineResolution;
    
    float distance;
    float lineLength;
    float animOffset;
    
    float angle;
    int lineCount;
    
    bool active;
};