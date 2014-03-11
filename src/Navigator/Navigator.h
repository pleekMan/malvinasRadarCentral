//
//  Navigator.h
//  animatableTest
//
//  Created by Wanda on 07/02/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAnimatableObject.h"
#include "ofxAnimatableObjectMasked.h"
#include "ContentHolder.h"
#include "FunkyRect.h"
#include "Wave.h"
#include "TriangleBlast.h"
#include "Stripper.h"

class Navigator{

    public:
        Navigator(){};
        ~Navigator(){};

        void setup(string p, ofPoint initPos, bool _upsideDown, ofPoint _initialScreenOffset);
        void setup(string p);

        void appear(float delay);
        void disappear();
        void update(float time);
        void draw();
        void setPosition(ofPoint pos);
        void drawMisc();

        void checkClick(int mx, int my);
        void optionPressed(int selection); // type: SECTION or THUMB,
    bool closePressed(int mx, int my);
    bool isVisible();

    string path;
    int width, height;
    bool visible;
    bool upsideDown;

    ofxAnimatableObject<ofFbo> fbo;

    ofxAnimatableObject<ofImage> titulo;
    ofxAnimatableObject<ofImage> close;

    vector< ofxAnimatableObject<ofImage> > buttons;
    vector <ofPoint> buttonBackPos;
    vector <FunkyRect> buttonsBackG;
    

    int currentContent;
    int nextContent;
    
    vector <ContentHolder> contents;

    //Wave wave;
    //FunkyRect swizzer;
    //vector <FunkyRect> beepers;
    ofxAnimatableObject<ofImage> triangle;
    //TriangleBlast triangle;
    //Stripper stripper;
    
    ofPoint initialScreenOffset;
    ofPoint position;

};
