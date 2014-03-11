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
    
    ringImage.loadImage(imagePath + ".png");
    ringImage.setAnchorPercent(0.5, 1.);
    
    ringImageOn.loadImage(imagePath + "_On.png");
    ringImageOn.setAnchorPercent(0.5, 1);
    ringImageOn.setColor(ofColor(255,0));
    ringImageOn.color.setDuration(.5);
    ringImageOn.color.setRepeatType(LOOP_BACK_AND_FORTH);
    
    
    //navigatorLink = _navigatorLink;
    
    radius = _radius;
    ringCenter = _ringCenter;
    angle = ofRandom(360, 360 * 10);
    angleDragOffset = 0;
    dragging = false;
    
    angleTweener.setDuration(0.5);
    angleTweener.setCurve(EASE_IN_EASE_OUT);
    
    // INFER THE ANGLE, BASED ON THE IMAGE SIZE
    halfAngularLimit = ofRadToDeg(atan((ringImage.getWidth() * 0.5) / (radius - ringImage.height))) * 0.95;
    //cout << (ringImage.getWidth() * 0.5) / (radius - ringImage.height) << endl;
    //cout << "halfWidth: " << ringImage.getWidth() * 0.5 << " / ringRadius: " << radius - ringImage.height << " / angle Result: " << halfAngularLimit << endl;
    
    setVelocity(ofRandom(-8, 8));
    
    
    time = 0;
}

void Ring::update(int mX, int mY){
    
    ringImageOn.update(1./ofGetFrameRate());
    
    if(!dragging){
        
        /*
        float 
        float accel=destination-position;
        accel*=(K/MASS);
        accel-=(DAMPING/MASS)*velocity;
        velocity+=(accel*dt);
        position+=(velocity*dt);
        
        */
        
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        float impulse=normalVelocity-velocity;
        impulse*=(K/MASS);
        impulse-=(DAMPING/MASS)*dvelocity;
        dvelocity+=(impulse*dt);
        velocity+=(dvelocity*dt);
        
        angle += velocity * (dt);
        
        // CONSTRAIN TO 0 - 360
        //if(angle > 360)angle = 0;
        //if (angle < 0)angle = 360;
        
        // RESET ANGLE WHEN GONE TOO FAR
        if(angle > (360 * 1000) || angle < (-360 * 1000)){
            angle = 0;
        }
        

        
    } else {
        ofVec2f mouseVector = ofVec2f(mX - ringCenter.x, mY - ringCenter.y);
        ofVec2f ringVector = ofVec3f(0, radius);
        
        //float angleDiff =  ringVector.angle(mouseVector) - angle;
        //angle = ringVector.angle(mouseVector);// + angleDragOffset;
        
        
        float mouseAngle = ringVector.angle(mouseVector);
        mouseAngle = (mouseAngle < 0) ? mouseAngle + 360:mouseAngle;
        
        
        // ADAPT MOUSEANGLE TO ANGLE
        mouseAngle += int((angle - mouseAngle) / 360) * 360;
        
        if((mouseAngle - angle) > 180){
            mouseAngle -= 360;
        } else if((mouseAngle - angle) < -180) {
            mouseAngle += 360;
        }

        
        //cout << "M A: " << mouseAngle << endl;
        
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        float accel = mouseAngle - (angle);
        //float accel = mouseAngle - angle;
        accel*=(K/MASS);
        accel-=(DAMPING/MASS) * velocity;
        velocity += (accel*dt);
        angle += (velocity * dt);
        
        
        // CONSTRAIN TO 0 - 360
        //angle = (angle > 360)?angle -= 360:angle;
        //angle = (angle < 0) ? angle + 360:angle;
        

    }
    
    
    
}

void Ring::draw(){
    
    /*
    if (dragging) {
        ofSetColor(255, 255);
    } else {
        ofSetColor(255,200);
    }
     */
    

     
    ofSetColor(255,255);
    
    ofPushMatrix();
    
    ofTranslate(ringCenter);
    ofRotate(angle);
    ofTranslate(0, radius);

    ringImage.draw(0,0);
    ringImageOn.draw();
    
    
    ofPopMatrix();
    
    drawGizmos();
    
}

void Ring::setVelocity(float _angularVelocity){
    
    //velocity = _angularVelocity;
    dvelocity = 0;
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
    //mouseAngle = (mouseAngle < 0) ? mouseAngle + 360:mouseAngle;
    
    // ADAPT MOUSEANGLE TO ANGLE
    mouseAngle += int((angle - mouseAngle) /360) * 360;
    
    if((mouseAngle - angle) > 180){
        mouseAngle -= 360;
    } else if((mouseAngle - angle) < -180) {
        mouseAngle += 360;
    }
    
    // CHECK RADIAL DISTANCE
    if (pointerDistance > radius - 20 && pointerDistance < radius){
        
        
        
        // MOUSE ANGLE CORRECTION
        
        /*
        if(abs(mouseAngle-angle)>180){
            if((angle-mouseAngle)>0){
                mouseAngle+=360;
            }
            else{
                mouseAngle-=360;
            }
        }
         */
        
        
         
        
        float lowSide = (int)(angle + halfAngularLimit);
        float highSide = (int)(angle - halfAngularLimit);
        
        // CHECK ANGULAR DISTANCE
        if(mouseAngle < lowSide && mouseAngle > highSide) {
            //angleDragOffset = angle - ringVector.angle(mouseVector);
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

string Ring::getNavigatorLink(){
    return navigatorLink;
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
        ofSetColor(255, 0, 0);
        ofDrawBitmapString(ofToString(angle), 0,20);
        int ringModulo = (int)angle % 360;
        ofDrawBitmapString("Angle %: " + ofToString(ringModulo), 0, 40);

    
    ofPopMatrix();
    
    //ofSetColor(255, 0, 0);
    //ofLine(ringCenter,ofPoint(ofGetMouseX(), ofGetMouseY()));
    
}