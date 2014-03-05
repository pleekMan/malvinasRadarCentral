//
//  Triangle.h
//  animatableTest
//
//  Created by Wanda on 14/02/14.
//
//

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"

class Triangle {
    
    
public:
    Triangle(){};
    
    void setup();
    void update(float time);
    void draw();
    
    void appear(float delay);
    void disappear();
    
    float width, height;
    ofPoint vertex[3];
    
    ofxAnimatableFloat alpha;
    ofxAnimatableOfPoint position;
};