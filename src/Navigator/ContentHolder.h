//
//  ContentHolder.h
//  animatableTest
//
//  Created by Wanda on 10/02/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAnimatableObject.h"
#include "ofxAnimatableObjectMasked.h"
#include "ofxScrollable.h"

class ContentHolder{

public:

    ContentHolder(){};
    ~ContentHolder(){};

    void setup(string path,ofPoint pos);
    void appear(float delay);
    void disappear();
    void update(float time);
    void draw();

    void thumbPressed(int selection);
    //void textPressed(bool forwardDirection);
    
    bool isOrWillBeAnimating();

    vector < ofxAnimatableObject<ofImage> > thumbs;
    vector < ofxAnimatableObjectMasked<ofImage> > images;

    ofxAnimatableObjectMasked<ofxScrollable> text;
    ofxAnimatableObjectMasked<ofImage> textBack;
    ofxAnimatableObjectMasked<ofImage> imageBack;
    ofxAnimatableObject<ofImage> dottedLine;

    int currentThumb;
    int nextThumb;
    
    string path;
    
private:
    void reset();

};
