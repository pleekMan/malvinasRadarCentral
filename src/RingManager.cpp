//
//  RingManager.cpp
//  malvinasRadarCentral
//
//  Created by Wanda on 19/02/14.
//
//

#include "RingManager.h"

#define CENTER ofPoint(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5)
#define RING_COUNT 5 // MAX 12
#define RING_WIDTH 20

void RingManager::setup(){
    
    createRings();
    createHotSpots(300);
    

    
}

void RingManager::update(int mX, int mY){
    
    for (int i=0; i < RING_COUNT; i++) {
        
        rings[i].update(mX, mY);
        
        /*
        if(i % 2 == 1){
            avoidPair(i);
        }
        */
    }
    
    for (int i=0; i < pins.size(); i++) {
        pins[i].update(mX, mY);
    }

    
}

void RingManager::draw(){
    
    
    for (int i=0; i < RING_COUNT; i++) {
        rings[i].draw();
    }
    
    // DRAW MOUSE ANGLE - BEGIN
    
    float pointerDistance = ofDist(ofGetAppPtr() -> mouseX,  ofGetAppPtr() -> mouseY, CENTER.x, CENTER.y);
    
    ofVec2f mouseVector = ofVec2f(ofGetAppPtr() -> mouseX - CENTER.x, ofGetAppPtr() -> mouseY - CENTER.y);
    ofVec2f ringVector = ofVec2f(0, 200);
    float mouseAngle = ringVector.angle(mouseVector);
    mouseAngle = (mouseAngle < 0) ? mouseAngle + 360:mouseAngle;
    
    ofSetColor(0, 255, 0);
    ofLine(CENTER.x, CENTER.y, ofGetAppPtr() -> mouseX, ofGetAppPtr() -> mouseY);
    ofLine(CENTER.x, CENTER.y, CENTER.x,  CENTER.y + 300);
    ofDrawBitmapString("Angle: " + ofToString(mouseAngle), ofGetAppPtr() -> mouseX, ofGetAppPtr() -> mouseY);
    
    // DRAW MOUSE ANGLE - END
    
    // ANGLE BTW RINGS - BEGIN
    
     ofDrawBitmapString("Angle BTW Rings: " + ofToString(abs(rings[0].angle - rings[1].angle)), ofGetAppPtr() -> mouseX, ofGetAppPtr() -> mouseY + 20);
    
    // ANGLE BTW RINGS - END
    
    
    // DRAW HotSpots - BEGIN
    ofNoFill();
    for (int i=0; i < navigatorHotSpot.size(); i++) {
        ofBeginShape();
        for (int j=0; j<navigatorHotSpot[i].getVertices().size(); j++) {
            ofVertex(navigatorHotSpot[i].getVertices()[j].x, navigatorHotSpot[i].getVertices()[j].y);
        }
        ofEndShape();
    }
    
    // DRAW HotSpots - END
    
    
    // DRAW PINS
    for (int i=0; i < pins.size(); i++) {
        pins[i].draw();
    }

    
}


void RingManager::createRings(){
    
    float centerBaseOffset = 180;
    float radiusIncrement = 0;
    
    for (int i=0; i < RING_COUNT; i++) {
        Ring currentRing;
        rings.push_back(currentRing);
    }
    
    for (int i=0; i < RING_COUNT; i++) {
        
        string currentPath = "rings/ring_" + ofToString(i) + ".png";
        
        float currentRadius = 0;
        currentRadius = centerBaseOffset + (radiusIncrement);
        
        rings[i].setup(currentPath, CENTER, currentRadius);
        
        // 2 RINGS PER LAYER
        /*
        if (i % 2 == 1) {
            radiusIncrement += RING_WIDTH + 3;
            rings[i].setAngle(rings[i - 1].angle + 180);
            rings[i].setVelocity(rings[i - 1].velocity);
        }
         */
        
        // 1 RING PER LAYER
        radiusIncrement += RING_WIDTH + 3;
        
        
        
    }
}

void RingManager::createHotSpots(int size){
    
    
    ofPolyline area0;
    area0.addVertex(0,0);
    area0.addVertex(size,0);
    area0.addVertex(0,size);
    area0.close();
    navigatorHotSpot.push_back(area0);
    
    ofPolyline area1;
    area1.addVertex(ofGetWidth(),0);
    area1.addVertex(ofGetWidth(),size);
    area1.addVertex(ofGetWidth() - size,0);
    area1.close();
    navigatorHotSpot.push_back(area1);
    
    ofPolyline area2;
    area2.addVertex(ofGetWidth(),ofGetHeight());
    area2.addVertex(ofGetWidth() - size,ofGetHeight());
    area2.addVertex(ofGetWidth(),ofGetHeight() - size);
    area2.close();
    navigatorHotSpot.push_back(area2);
    
    ofPolyline area3;
    area3.addVertex(0,ofGetHeight());
    area3.addVertex(0,ofGetHeight() - size);
    area3.addVertex(size,ofGetHeight());
    area3.close();
    navigatorHotSpot.push_back(area3);

    
}

/*
int RingManager::checkRingsDragged(ofPoint pointer){
    
    int ringInside = -1;
    
    for (int i=0; i < RING_COUNT; i++) {
        
        if(rings[i].inside(pointer)){
            cout << "Ring Pressed: " << ofToString(i) << endl;
            ringInside = i;
           
           if(!rings[i].isDragging()){
               startDrag(i);
           } 
            
        }
    }
    
    return ringInside;
    
}
 */

void RingManager::startDrag(ofPoint pointer){
    

    
    for (int i=0; i < RING_COUNT; i++) {
        
        if(rings[i].inside(pointer)){
            
            cout << "Ring Pressed: " << ofToString(i) << endl;

            if(!rings[i].isDragging()){
                rings[i].setDragging(true);
            }
            
            Pin pin;
            pin.setData(i, "Drag ta tha corner, biotch..!!");
            pins.push_back(pin);
            break; // ONLY CHECKING FOR ONE POINTER
            
        }
    }
    
    
}

void RingManager::stopDrag(){
    
    for (int i=0; i < RING_COUNT; i++) {
        rings[i].setDragging(false);
        rings[i].setVelocity(rings[i].normalVelocity);
    }
    
    //  CHECK PINS INSIDE QUADRANTS
    for (int i=0; i < pins.size(); i++) {
        for (int j=0; j < navigatorHotSpot.size(); j++) {
            if (navigatorHotSpot[j].inside(pins[i].position)) {
                cout << "Trigger Navigator at Quadrant: " << ofToString(j);
                //pins.erase(pins.begin() + i);
            }
        }
        pins.erase(pins.begin() + i);
    }
    
}

/*
bool RingManager::isInsideAnyRing(ofPoint pointer){
    
    for (int i=0; i < RING_COUNT; i++) {
        
        if(rings[i].inside(pointer)){
            return true;
        } else {
            return false;
        }
    }
    
}
*/

bool RingManager::isOnTopOfPair(int currentRing){
    
    Ring ringA = rings[currentRing];
    Ring ringB = rings[currentRing - 1];
    
    if ((ringA.angle - ringA.halfAngularLimit) > (ringB.angle + ringB.halfAngularLimit)) {
        return true;
    } else {
        return false;
    }
    
    
}

void RingManager::avoidPair(int currentRing){
    
    //cout << "Inside Avoid" << endl;
    
    Ring* ringA = &rings[currentRing]; // CURRENT RING (AlWAYS THE 2nd one on the layer)
    Ring* ringB = &rings[currentRing - 1]; // PREVIOUS RING (ON SAME LAYER)
    
    float angleBetween = abs(ringB->angle - ringA->angle);
    
    if (ringA->isDragging()) {
        cout << "Dragging Ring A" << endl;
        
        if (angleBetween < (ringA -> halfAngularLimit + ringB -> halfAngularLimit)) {
            cout << "ON TOP :: TO LEFT" << endl;
            ringB->setAngle(ringB -> angle - ringA->halfAngularLimit);
        }
    }

    
    /*
    if (ringA.isDragging() || ringB.isDragging()) {
        
        if ((ringA.angle - ringA.halfAngularLimit) < (ringB.angle + ringB.halfAngularLimit)) {
            ringB.setAngle(ringA.angle - ringA.halfAngularLimit);
            //ringB.setVelocity(ringB.velocity * -1);
        }
    }
     */
    
    /*
    
    if ((ringA.angle - ringA.halfAngularLimit) > (ringB.angle + ringB.halfAngularLimit)) {
        if (ringA.isDragging()) {
            ringB.setAngle(ringA.angle - ringA.halfAngularLimit);
            ringB.setVelocity(ringB.velocity * -1);
        } else {
            ringA.setAngle(ringB.angle + ringB.halfAngularLimit);
            ringA.setVelocity(ringA.velocity * -1);
        }
    } else if ((ringA.angle + ringA.halfAngularLimit) > (ringB.angle - ringB.halfAngularLimit)){
        if (ringA.isDragging()) {
            ringB.setAngle(ringA.angle + ringA.halfAngularLimit);
            ringB.setVelocity(ringB.velocity * -1);
        } else {
            ringA.setAngle(ringB.angle - ringB.halfAngularLimit);
            ringA.setVelocity(ringA.velocity * -1);
        }
    }
     */
}





void RingManager::setRadius(float newRadius) {
    // SET A GLOBAL radius, AND RE-SET RINGS
}