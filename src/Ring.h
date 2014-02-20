//
//  Ring.h
//  malvinasRadarCentral
//
//  Created by Wanda on 19/02/14.
//
//

#ifndef __malvinasRadarCentral__Ring__
#define __malvinasRadarCentral__Ring__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__malvinasRadarCentral__Ring__) */

class Ring {
    
    
public:
    Ring(){};
    
    void setup(string imagePath, ofPoint _ringCenter, float _radius);
    void update();
    void draw();
    
    void setVelocity(float _angularVelocity);
    bool inside(ofPoint pointer);
    void setActive(bool _active);
    bool isActive();
    
    ofPoint ringCenter;
    float angle;
    float halfAngularLimit;
    float velocity;
    float radius;
    ofImage ringImage;
    bool active;
    
private:
    void drawGizmos();
    float calculateHalfAngularLimit();
    
    
};