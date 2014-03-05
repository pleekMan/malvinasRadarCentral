//
//  FunkyRect.cpp
//  animatableTest
//
//  Created by Wanda on 11/02/14.
//
//

#include "FunkyRect.h"


void FunkyRect::setup(bool state, ofPoint _pos, float _width, float _height){
    
    color.setDuration(0.5);
    color.setColor(ofColor(255,0));
    pos.setPosition(_pos);
    width = _width;
    height = _height;
    angle = 0;
    
    rot.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
    rot.setDuration(0.2);
    rot.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
    rot.setCurve(TANH);
    
    isRotating = false;
    
    
}

void FunkyRect::update(float time){
    pos.update(time);
    color.update(time);
    rot.update(time);
}

void FunkyRect::draw(){
    ofPushMatrix();
    ofPushStyle();
    if (isRotating) {
        
    ofTranslate(pos.getCurrentPosition().x, pos.getCurrentPosition().y);
    
    ofRotate(ofRadToDeg(angle));


    ofSetColor(color.getCurrentColor());
    ofFill();
    ofRect(-(width * 0.5), -(height * 0.5), width, height);
    ofSetColor(255,255);
    
        
    } else {
        
        ofSetColor(color.getCurrentColor());
        ofFill();
        
        ofTranslate(pos.getCurrentPosition());
        ofRotateX(rot.getCurrentPosition().x);
        ofRotateY(rot.getCurrentPosition().y);
        ofRotateZ(rot.getCurrentPosition().z);
        
        ofRect(0, 0, width, height);
    }
    ofPopStyle();
    ofPopMatrix();

}

void FunkyRect::moveTo(ofPoint target){
    pos.animateTo(target);
}

void FunkyRect::rotate(float angleRad){
    isRotating = true;
    angle = angleRad;
}

void FunkyRect::disappear(){
    color.animateTo(ofColor(255,0));
}

void FunkyRect::appear(float delay){
    if(delay){
        color.animateToAfterDelay(ofColor(159,54,42,255),delay);
    }
    else{
        color.animateTo(ofColor(159,54,42,255));
        rot.animateTo(ofPoint(-45,0,0));
    }
}