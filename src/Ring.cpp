//
//  Ring.cpp
//  malvinasRadarCentral
//
//  Created by Wanda on 19/02/14.
//
//

#include "Ring.h"

void Ring::setup(string imagePath, ofPoint _ringCenter, float _radius){
    
    ringImage.loadImage(imagePath);
    ringImage.setAnchorPercent(0.5, 1.);
    
    radius = _radius;
    ringCenter = _ringCenter;
    angle = 0.;
    
    halfAngularLimit = ofRadToDeg(atan((ringImage.getWidth() * 0.5) / (radius - ringImage.height))) * 0.95;
    cout << (ringImage.getWidth() * 0.5) / (radius - ringImage.height) << endl;
    cout << "halfWidth: " << ringImage.getWidth() * 0.5 << " / ringRadius: " << radius - ringImage.height << " / angle Result: " << halfAngularLimit << endl;
    
    setVelocity(ofRandom(-0.5, 0.5));
}

void Ring::update(){
    
    angle += velocity;
    
    
}

void Ring::draw(){
    
    ofPushMatrix();
    
    ofTranslate(ringCenter);
    ofRotate(angle);
    ofTranslate(0, radius);
    
    ringImage.draw(0,0);
    ofRect(0,0,5, 5);
    
    
    ofPopMatrix();
    
    drawGizmos();
    
}

void Ring::setVelocity(float _angularVelocity){
    
    velocity = _angularVelocity;
}

bool Ring::inside(ofPoint pointer){
    return true;
}

void Ring::setActive(bool _active){
    
}
bool Ring::isActive(){
    return active;
}


void Ring::drawGizmos(){
    
    
    ofPushMatrix();
    ofTranslate(ringCenter);
        ofCircle(0,0, 3);
    ofRotate(angle);
    
    ofPushMatrix();
    ofRotate(-halfAngularLimit);
        ofLine(0,0,0,radius);
    ofRotate(halfAngularLimit * 2);
        ofLine(0,0,0,radius);
    ofPopMatrix();
    
        ofLine(0,0,0,radius);
    ofTranslate(0, radius);
        ofRect(0, 0, 5, 5);
    ringImage.draw(0,0);
    
    ofPopMatrix();
    
}