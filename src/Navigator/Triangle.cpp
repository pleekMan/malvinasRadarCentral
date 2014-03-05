//
//  Triangle.cpp
//  animatableTest
//
//  Created by Wanda on 14/02/14.
//
//

#include "Triangle.h"
void Triangle::setup(){
    
    facing = 0;
    width = height = 30;
    anchor = ofPoint(330, 630);
    alpha.reset(0.);
}

void Triangle::update(float time){
    alpha.update(time);
    if(!(ofGetFrameNum()%10))
        turn90();
}

void Triangle::draw(){
    
    float halfWidth = width * 0.5;
    
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
    
    ofTriangle(-halfWidth, -halfWidth, halfWidth, -halfWidth, -halfWidth, halfWidth);
    
    ofPopMatrix();
    ofPopStyle();
}

void Triangle::turn90(){
    facing++; if (facing > 4){facing = 0;};
}
void Triangle::setAngleCorner(int corner){
    facing = corner;
}

void Triangle::appear(float delay){
    alpha.animateToAfterDelay(1.,delay);
}

void Triangle::disappear(){
    alpha.animateTo(0.);
}
