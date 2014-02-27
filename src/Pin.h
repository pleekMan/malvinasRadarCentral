//
//  Pin.h
//  malvinasRadarCentral
//
//  Created by Zaira on 26/02/14.
//
//

#ifndef __malvinasRadarCentral__Pin__
#define __malvinasRadarCentral__Pin__

#include <iostream>
#include <ofMain.h>

#endif /* defined(__malvinasRadarCentral__Pin__) */

class Pin {
    
    
public:
    Pin(){}
    
    void draw();
    void update(int mX, int mY);
    void setData(int link, string _data);
    int getActiveQuadrant();
    bool isInsideTriggerArea(ofPolyline area);
    
    
    ofPoint position;
    float rotation;
    int linkToRing;
    string data;
    
private:
    int activeQuadrant;
    void updateActiveQuadrant();
    
};