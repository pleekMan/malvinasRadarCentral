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
#include "ofxAnimatableFloat.h"

#endif /* defined(__malvinasRadarCentral__Ring__) */

class Ring {
    
    
public:
    Ring(){};
    
    void setup(string imagePath, ofPoint _ringCenter, float _radius);
    void update(int mX, int mY);
    void draw();
    
    void setVelocity(float _angularVelocity);
    void setAngle(float degrees);
    bool inside(ofPoint pointer);
    void setDragging(bool _dragging);
    bool isDragging();
    
    ofPoint ringCenter;
    float angle;
    ofxAnimatableFloat angleTweener;
    float angleDragOffset;
    float halfAngularLimit;
    float normalVelocity;
    float velocity;
    float radius;
    ofImage ringImage;
    bool dragging = false;
    
private:
    void drawGizmos();
    float calculateHalfAngularLimit();
    
    
};