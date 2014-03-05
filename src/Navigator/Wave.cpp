//
//  Wave.cpp
//  animatableTest
//
//  Created by Wanda on 12/02/14.
//
//

#include "Wave.h"
#include "ofMain.h"


void Wave::setup(){

    size = 1.5;
    pos = ofPoint(390,230);
    height = 25;
    width = 280;

}

void Wave::draw(){
    
    x = y = offset = 0;
    
    for (int i=0; i < ELEMENTS; i++) {
        
        offset = (TWO_PI/ELEMENTS) * i * 3;
        x = pos.x + (width / ELEMENTS) * i;
        y = ofMap(sin(theta+offset), -1, 1, -height, height);
        
        //x += pos.x;
        y += pos.y;
        
        ofSetColor(255, 255, 255);
        ofFill();
        ofEllipse(x, y, size, size);
        
        
    }
    
    theta += 0.05;
    
    //ofNoFill();
    //ofRect(pos, width, height);
    
}