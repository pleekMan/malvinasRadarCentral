//
//  RingManager.cpp
//  malvinasRadarCentral
//
//  Created by Wanda on 19/02/14.
//
//

#include "RingManager.h"

#define CENTER ofPoint(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5)
#define RING_COUNT 1 // MAX 10
#define RING_WIDTH 20

void RingManager::setup(){
    
    preLoadNavigatorContent();
    createRings();
    
    //createHotSpots(300);


    
}

void RingManager::update(int mX, int mY){
    
    float t = ofGetElapsedTimef();
    float dt = t - time;
    time = t;
    
    for (int i=0; i < RING_COUNT; i++) {
        
        rings[i].update(mX, mY);
        
        /*
        if(i % 2 == 1){
            avoidPair(i);
        }
        */
    }
    
    /*
    for (int i=0; i < pins.size(); i++) {
        pins[i].update(mX, mY);
    }
     */
    
    // LOADERS
    
    for (int i=0; i < loaders.size(); i++) {
        loaders[i].update();
        
        if (loaders[i].isFinished()) {
            launchNavigator(loaders[i].getNavigatorLink(), loaders[i].getQuadrant());
            loaders[i].disappear();
            loaders.erase(loaders.begin() + i);
        }
        if (loaders[i].hasReturned()) {
            loaders[i].disappear();
            loaders.erase(loaders.begin() + i);
        }
        
        /*
        if (loaders[i].isFinishedAnimating()){
            loaders.erase(loaders.begin() + i);
        }
         */
    }
    
    for (int i=0; i < navigators.size(); i++) {
         if (navigators[i].isVisible()) {
             navigators[i].update(dt);
         }
    }
    
    //cout << "Loader Count: " + ofToString(loaders.size()) << endl;

    
}

void RingManager::draw(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
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
    //int ringModulo = (int)rings[0].angle % 360;
    //ofDrawBitmapString("Angle Modulo: " + ofToString(ringModulo), ofGetAppPtr() -> mouseX, ofGetAppPtr() -> mouseY + 20);
    
    // ANGLE BTW RINGS - END
    
    /*
    // DRAW HotSpots - BEGIN
    ofNoFill();
    for (int i=0; i < navigatorHotSpot.size(); i++) {
        ofBeginShape();
        for (int j=0; j<navigatorHotSpot[i].getVertices().size(); j++) {
            ofVertex(navigatorHotSpot[i].getVertices()[j].x, navigatorHotSpot[i].getVertices()[j].y);
        }
        ofEndShape();
    }
     */
    
    // DRAW HotSpots - END
    
    
    // DRAW PINS
    for (int i=0; i < pins.size(); i++) {
        pins[i].draw();
    }
    
    for (int i=0; i < loaders.size(); i++) {
        loaders[i].draw();
    }

    
    for (int i=0; i < navigators.size(); i++) {
        if (navigators[i].isVisible()) {
            navigators[i].draw();
            cout << "Drawing Nav: " + ofToString(i) << endl;
        }
    }
    
    
}

void RingManager::preLoadNavigatorContent(){
    
    for (int i=0; i<RING_COUNT; i++) {
        Navigator navigator;
        navigators.push_back(navigator);
        
    }
    
    for (int i=0; i<RING_COUNT; i++) {
        navigators[i].setup("Navigator_0");
    }
    
}

void RingManager::createRings(){
    
    float centerBaseOffset = 140;
    float radiusIncrement = 0;
    
    for (int i=0; i < RING_COUNT; i++) {
        Ring currentRing;
        rings.push_back(currentRing);
    }
    
    for (int i=0; i < RING_COUNT; i++) {
        
        string currentPath = "rings/ring_" + ofToString(i);
        
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
    
    /*
    if(pointer.x > (ofGetWidth() * 0.5)){
        pointerStartAtRightSide = true;
    } else {
        pointerStartAtRightSide = false;
    }
     */
    
    for (int i=0; i < RING_COUNT; i++) {
        
        if(rings[i].inside(pointer)){
            
            //cout << "Ring Pressed: " << ofToString(i) << endl;

            if(!rings[i].isDragging()){
                rings[i].setDragging(true);
                
                rings[i].ringImageOn.color.setRepeatType(LOOP_BACK_AND_FORTH);
                rings[i].ringImageOn.color.animateTo(ofColor(255,255));
            }
            
            // PIN SHIT
            /*
            Pin pin;
            pin.setData(i, "Drag ta tha corner, biotch..!!");
            pins.push_back(pin);
            break; // ONLY CHECKING FOR ONE POINTER
             */
            
            
            // LOADERS
            ofPoint pointer = ofPoint(ofGetMouseX(), ofGetMouseY());
            bool loaderCaught = false;
            
            // CHECK IF LOADER AT QUADRANT IS STILL ACTIVE (FADING OUT), AND REVERSE
            for (int i=0; i < loaders.size(); i++) {
                if (loaders[i].getQuadrant() == atQuadrant(pointer)) {
                    loaders[i].toggleProgressDirection();
                    loaderCaught = true;
                } else {
                    loaderCaught = false;
                }
            }
            
            // IF NO ACTIVE LOADERS ARE AT A QUADRANT, CREATE
            if (!loaderCaught) {
                Loader loader;
                loader.setup(ofPoint(ofGetWidth() * 0.5, ofGetWidth() * 0.5), atQuadrant(pointer), i);
                loaders.push_back(loader);
            }
            
            
            //launchNavigator(i, 2);
            
        }
    }
    
    for (int i=0; i < navigators.size(); i++) {
        if (navigators[i].closePressed(pointer.x, pointer.y)) {
            quitNavigator(&navigators[i]);
            //navigators.erase(navigators.begin() + i);
        }
    }
    
    
}

void RingManager::stopDrag(){
    
    for (int i=0; i < RING_COUNT; i++) {
        
        // CHECK IF IT'S BEING DRAGGED AND POINTER IS INSIDE
        if (rings[i].isDragging()){// && rings[i].inside(ofPoint(ofGetMouseX(), ofGetMouseY()))) {
            
            rings[i].setDragging(false);
            //rings[i].setVelocity(rings[i].normalVelocity);
            
            rings[i].ringImageOn.color.setRepeatType(PLAY_ONCE);
            rings[i].ringImageOn.color.animateTo(ofColor(255,0));
            
            for (int j=0; j < loaders.size(); j++) {
                if (loaders[j].getNavigatorLink() == i) {
                    loaders[j].toggleProgressDirection();
                }
            }
            
        }
        
        
    }
    
    
    
    /*
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
     */
    
}


void RingManager::launchNavigator(int navigatorId, int atQuadrant){
    
    
    ofPoint targetPos;
    bool upsideDown = false;

    switch (atQuadrant) {
        case 0:
            //targetPos = ofPoint(720,720); // 720 = WIDTH OF NAVIGATOR (APROX)
            targetPos = ofPoint(50,50);
            upsideDown = true;
            break;
        case 1:
            //targetPos = ofPoint(ofGetWidth() - 10 ,720);
            targetPos = ofPoint(100,50);
            upsideDown = true;
            break;
        case 2:
            //targetPos = ofPoint(ofGetWidth() - 720, ofGetHeight() - 360);
            targetPos = ofPoint(100,100);
            //upsideDown = true;
            break;
        case 3:
            //targetPos = ofPoint(10, ofGetHeight() - 720);
            targetPos = ofPoint(50,100);
            break;
        default:
            break;
    }
    
    
    // USING fbo ALPHA TO CHECK IF THE ANIMATION IS FINISHED
    // WHEN LAUNCHING, PRESET ALPHA TO ONE SO IT IS VISIBLE RIGHT AWAY FOR THE isVisible() INSIDE THIS UPDATE.
    navigators[navigatorId].fbo.color.setAlphaOnly(1);
    
    //navigator.setup("Navigator_0", targetPos, upsideDown, targetPos);
    navigators[navigatorId].fbo.color.setDuration(1.);
    navigators[navigatorId].fbo.setPosition(ofPoint(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
    navigators[navigatorId].fbo.setSize(0.);
    navigators[navigatorId].fbo.size.setCurve(EASE_OUT);
    navigators[navigatorId].setPosition(targetPos);
        
    navigators[navigatorId].fbo.size.animateTo(1.);
    navigators[navigatorId].fbo.position.animateTo(targetPos);
    navigators[navigatorId].fbo.color.animateToAlpha(255);
    navigators[navigatorId].appear(0.);
    
    
    
    //navigators.push_back(navigator);
    
}

void RingManager::quitNavigator(Navigator* navigator){
    
    navigator->fbo.size.animateTo(0.);
    navigator->fbo.position.animateTo(navigator->fbo.position.getCurrentPosition());
    navigator->fbo.color.animateToAlpha(0);
    navigator->disappear();
    //delete(navigator);
}

int RingManager::atQuadrant(ofPoint point){
    if (point.x < ofGetWidth() * 0.5 && point.y < ofGetHeight() * 0.5) {
        return 0;
    } else if (point.x > ofGetWidth() * 0.5 && point.y < ofGetHeight() * 0.5){
        return 1;
    } else if (point.x > ofGetWidth() * 0.5 && point.y > ofGetHeight() * 0.5){
        return 2;
    } else {
        return 3;
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
        //cout << "Dragging Ring A" << endl;
        
        if (angleBetween < (ringA -> halfAngularLimit + ringB -> halfAngularLimit)) {
            //cout << "ON TOP :: TO LEFT" << endl;
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