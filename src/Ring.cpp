//
//  Ring.cpp
//  malvinasRadarCentral
//
//  Created by Wanda on 19/02/14.
//
//

#include "Ring.h"
#define K 30.
#define MASS 1.
#define DAMPING 10.

void Ring::setup(string imagePath, ofPoint _ringCenter, float _radius){
    
    ringImage.loadImage(imagePath);
    ringImage.setAnchorPercent(0.5, 1.);
    
    radius = _radius;
    ringCenter = _ringCenter;
    angle = ofRandom(360);
    angleDragOffset = 0;
    
    angleTweener.setDuration(0.5);
    angleTweener.setCurve(EASE_IN_EASE_OUT);
    
    // INFER THE ANGLE, BASED ON THE IMAGE SIZE
    halfAngularLimit = ofRadToDeg(atan((ringImage.getWidth() * 0.5) / (radius - ringImage.height))) * 0.95;
    //cout << (ringImage.getWidth() * 0.5) / (radius - ringImage.height) << endl;
    //cout << "halfWidth: " << ringImage.getWidth() * 0.5 << " / ringRadius: " << radius - ringImage.height << " / angle Result: " << halfAngularLimit << endl;
    
    setVelocity(ofRandom(-0.3, 0.3));
}

void Ring::update(int mX, int mY){
    
    
    if(!dragging){
        
        /*
        float dt=1./ofGetFrameRate();
        float accel=destination-position;
        accel*=(K/MASS);
        accel-=(DAMPING/MASS)*velocity;
        velocity+=(accel*dt);
        position+=(velocity*dt);
        
        */
        
        angle += velocity;
        
        // CONSTRAIN TO 0 - 360
        if(angle > 360)angle = 0;
        if (angle < 0)angle = 360;
        
       
        
    } else {
        ofVec2f mouseVector = ofVec2f(mX - ringCenter.x, mY - ringCenter.y);
        ofVec2f ringVector = ofVec3f(0, radius);
        
        //float angleDiff =  ringVector.angle(mouseVector) - angle;
        //angle = ringVector.angle(mouseVector);// + angleDragOffset;
        
        
        float mouseAngle = ringVector.angle(mouseVector);
        mouseAngle = (mouseAngle < 0) ? mouseAngle + 360:mouseAngle;
       
        
        
        float dt=1./ofGetFrameRate();
        float accel=mouseAngle - angle;
        accel*=(K/MASS);
        accel-=(DAMPING/MASS) * velocity;
        velocity += (accel*dt);
        angle += (velocity * dt);
        
        
        // CONSTRAIN TO 0 - 360
        angle = (angle > 360)?angle -= 360:angle;
        angle = (angle < 0) ? angle + 360:angle;
        

    }
    
    
    
}

void Ring::draw(){
    
    
    if (dragging) {
        ofSetColor(255, 0, 0);
    } else {
        ofSetColor(255);
    }
     
    
    ofPushMatrix();
    
    ofTranslate(ringCenter);
    ofRotate(angle);
    ofTranslate(0, radius);
    
    //ofEnableAlphaBlending();
    ofSetColor(255);
    ringImage.draw(0,0);
    //ofDisableAlphaBlending();
    
    

    
    ofPopMatrix();
    
    drawGizmos();
    
}

void Ring::setVelocity(float _angularVelocity){
    
    //velocity = _angularVelocity;
    normalVelocity = velocity = _angularVelocity;
}

void Ring::setAngle(float newAngle){
    angle = newAngle;
}

bool Ring::inside(ofPoint pointer){
    
    float pointerDistance = ofDist(pointer.x, pointer.y, ringCenter.x, ringCenter.y);
    
    ofVec2f mouseVector = ofVec2f(pointer.x - ringCenter.x, pointer.y - ringCenter.y);
    ofVec2f ringVector = ofVec2f(0, radius);
    
    float mouseAngle = ringVector.angle(mouseVector);
    mouseAngle = (mouseAngle < 0) ? mouseAngle + 360:mouseAngle;
    
    // CHECK RADIAL DISTANCE
    if (pointerDistance > radius - 20 && pointerDistance < radius){
        
        
        // MOUSE ANGLE CORRECTION 
        if(abs(mouseAngle-angle)>180){
            if((angle-mouseAngle)>0){
                mouseAngle+=360;
            }
            else{
                mouseAngle-=360;
            }
        }
        
        float lowSide = (int)(angle + halfAngularLimit);
        float highSide = (int)(angle - halfAngularLimit);
        
        // CHECK ANGULAR DISTANCE
        if(mouseAngle < lowSide && mouseAngle > highSide) {
            angleDragOffset = angle - ringVector.angle(mouseVector);
            //cout << "Angle Offset: " << ofToString(angleDragOffset) << endl;
            return true;
        } else {
            return false;
        }
        
    } else {
        return false;
    }
}

void Ring::setDragging(bool _dragging){
    dragging = _dragging;
}

bool Ring::isDragging(){
    return dragging;
}


void Ring::drawGizmos(){
    
    ofSetColor(0, 0, 50);
    
    ofPushMatrix();

    ofTranslate(ringCenter);
        ofCircle(0,0, 3);
    
    ofRotate(angle);
    ofLine(ofPoint(0,0), ofPoint(0, radius * 2));
        ofPolyline arcInner, arcOuter;
        arcInner.arc(ofPoint(0,0), radius - 20, radius - 20, 90 - halfAngularLimit, 90 + halfAngularLimit, true);
        arcOuter.arc(ofPoint(0,0), radius, radius, 90 - halfAngularLimit, 90 + halfAngularLimit, true);
        arcInner.draw();
        arcOuter.draw();
    
    ofPushMatrix();
    ofRotate(-halfAngularLimit);
        ofLine(0,0,0,radius);
    ofRotate(halfAngularLimit * 2);
        ofLine(0,0,0,radius);
    ofPopMatrix();
    
        ofLine(0,0,0,radius);
    ofTranslate(0, radius);
        ofRect(0, 0, 5, 5);
        ofSetColor(0, 0, 255);
        ofDrawBitmapString(ofToString(angle), 0,20);
    
    ofPopMatrix();
    
}