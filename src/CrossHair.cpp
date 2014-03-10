//
//  CrossHair.cpp
//  malvinasRadarCentral
//
//  Created by Zaira on 07/03/14.
//
//

#include "CrossHair.h"

void CrossHair::setup(ofPoint _center){
    
    center = _center;
    
    distance = 300;
    
    lineLength = 30;
    animOffset = 0;
    
    lineCount = 64;
    angle = 360 / lineCount;
    
    active = true;
    
}

void CrossHair::draw(){
    
    if(active){
        ofPushMatrix();
        ofTranslate(center);
        
        ofSetColor(255, 200 - (200 * animOffset));
        for (int i=0; i < lineCount; i++) {
        
            ofPushMatrix();
            ofRotate(angle * i);
            
            //ofEllipse(0, (distance * animOffset), 30, 30);
            ofLine(0, (distance * animOffset), 0, (distance * animOffset) + lineLength);
            ofPopMatrix();
        }
        ofPopMatrix();
    
        animOffset += 0.015;
        //cout << ofToString(distance * animOffset) << endl;
    
        if (animOffset > 1) {
            //cout << "Inside the Max checker" << endl;
            active = false;
        }
    }
    
}

bool CrossHair::isFinished() {
    return !active;
}

void CrossHair::reset(){
    active = true;
    animOffset = 0;
}

