//
//  TriangleBlast.cpp
//  animatableTest
//
//  Created by Wanda on 12/02/  14.
//
//

#include "TriangleBlast.h"

void TriangleBlast::setup(){
    
    facing = 0;
    width = height = 10;
    anchor = ofPoint(328, 640);
    alpha.reset(0.);
}

void TriangleBlast::update(float time){
    alpha.update(time);
    if(!(ofGetFrameNum()%10))
        turn90();
}

void TriangleBlast::draw(){
    
    
    float halfWidth = width * 0.5;
    
    /*
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(anchor);
    
    ofFill();
    ofSetColor(160,54,42,255*alpha.val());
    float daddyMultiplier = 2.;
    ofTriangle(halfWidth * daddyMultiplier, halfWidth * daddyMultiplier, halfWidth * daddyMultiplier, -halfWidth * daddyMultiplier, -halfWidth * daddyMultiplier, halfWidth * daddyMultiplier);
    
    ofTranslate(halfWidth, halfWidth);
    ofRotate(90 * facing);
    
    ofSetColor(255,100*alpha.val());
    ofFill();
     */

    ofTriangle(-halfWidth, -halfWidth, halfWidth, -halfWidth, -halfWidth, halfWidth);
    
    /*
    ofPopMatrix();
    ofPopStyle();
     */
}

void TriangleBlast::turn90(){
    facing++; if (facing > 4){facing = 0;};
}
void TriangleBlast::setAngleCorner(int corner){
    facing = corner;
}

void TriangleBlast::appear(float delay){
    alpha.animateToAfterDelay(1.,delay);
}

void TriangleBlast::disappear(){
    alpha.animateTo(0.);
}
