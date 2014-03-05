//
//  ContentHolder.cpp
//  animatableTest
//
//  Created by Wanda on 10/02/14.
//
//

#include "ContentHolder.h"
#include "ofMain.h"


void ContentHolder::setup(string path, ofPoint pos){

    float thumbHalfSize = 35;
    for(int i=0; ofDirectory::doesDirectoryExist(path + "/Image_" + ofToString(i)); i++){
        thumbs.push_back(ofxAnimatableObject<ofImage>());
        images.push_back(ofxAnimatableObjectMasked<ofImage>());
    }
    
    for(int i=0; i<thumbs.size(); i++){
        thumbs[i].loadImage(path + "/Image_" + ofToString(i) + "/thumb.png");
    }
    for(int i=thumbs.size() - 1; i >= 0; i--){
        thumbs[i].setPosition(pos.x + 560 - ((thumbs.size() - 1 -i) * 50) + thumbHalfSize,pos.y + 505 + thumbHalfSize);
        thumbs[i].setAnchorPercent(0.5, 0.5);
        thumbs[i].setSize(0.0);
        thumbs[i].size.setDuration(0.5);
        thumbs[i].size.setRepeatType(PLAY_ONCE);
        thumbs[i].size.setCurve(TANH);
        thumbs[i].setColor(255,200);
        thumbs[i].color.setDuration(0.5);
        thumbs[i].color.setRepeatType(PLAY_ONCE);
        thumbs[i].color.setCurve(EASE_IN);
    }
    
    for(int i=0; i<images.size(); i++){
        images[i].tex.loadImage(path + "/Image_" + ofToString(i) + "/image.png");
        images[i].allocate();
        images[i].setAnchorPercent(0.,0.);  
        //images[i].setPosition(pos.x,pos.y);
        images[i].setPosition(pos.x + 265,pos.y + 10);
        images[i].setMaskType(DIAGONAL);
        images[i].setMask(1);
        images[i].mask.setDuration(.7);
        images[i].mask.setRepeatType(PLAY_ONCE);
        images[i].setColor(ofColor(255,0));
        images[i].color.setDuration(.5);
    }
        
    textBack.tex.loadImage(path + "/../textBack.png");
    textBack.allocate();
    textBack.setAnchorPercent(0.,0.);
    textBack.setPosition(pos.x,pos.y);
    textBack.setMaskType(HORIZONTAL);
    textBack.setMask(1.);
    textBack.mask.setDuration(0.5);
    textBack.mask.setRepeatType(PLAY_ONCE);
    textBack.setColor(ofColor(255,0));
    textBack.color.setDuration(.5);
    
    text.tex.load(path + "/text.png",textBack.getWidth()*0.96,textBack.getHeight()*0.96,40.);
    text.allocate();
    text.setAnchorPercent(0.5,0.5);
    text.setPosition(pos.x+textBack.getWidth()*0.5,pos.y+textBack.getHeight()*0.5);
    text.setMaskType(HORIZONTAL);
    text.setMask(1.);
    text.mask.setDuration(0.5);
    text.mask.setRepeatType(PLAY_ONCE);
    text.setColor(ofColor(255,0));
    text.color.setDuration(.5);
    
    imageBack.tex.loadImage(path + "/../imageBack.png");
    imageBack.allocate();
    imageBack.setAnchorPercent(0.,0.);
    imageBack.setPosition(pos.x + 255,pos.y);
    imageBack.setMaskType(DIAGONAL);
    imageBack.setMask(0.);
    imageBack.mask.setDuration(0.5);
    imageBack.mask.setRepeatType(PLAY_ONCE);
    imageBack.setColor(ofColor(255,255));
    imageBack.color.setDuration(.5);
    
    dottedLine.loadImage(path + "/../dottedLine.png");
    dottedLine.setAnchorPercent(0.,0.);
    dottedLine.setPosition(pos.x + 422, pos.y + 510);
    dottedLine.setColor(ofColor(255,0));
    dottedLine.color.setDuration(.5);

    currentThumb = nextThumb = 0;
    
}
void ContentHolder::appear(float delay){

    reset();
    
    images[currentThumb].setColor(255,255);
    images[currentThumb].setMask(0.);
    images[currentThumb].mask.animateToAfterDelay(1.0, delay);
    
    imageBack.setColor(255,255);
    imageBack.setMask(0.);
    imageBack.mask.animateToAfterDelay(1.0, delay);
    
    text.color.animateToAfterDelay(ofColor(255,255),delay + 0.4);
    text.setMask(0.);
    text.mask.animateToAfterDelay(1.0, delay + 0.4);
    
    textBack.color.animateToAfterDelay(ofColor(255,255),delay + 0.4);
    textBack.setMask(0.);
    textBack.mask.animateToAfterDelay(1.0, delay + 0.4);
    
    dottedLine.color.animateToAfterDelay(ofColor(255,200),delay + 0.6);

    delay += 0.5;

    for(int i=0; i<thumbs.size(); i++){
        thumbs[i].size.animateToAfterDelay(1.0, delay + i*0.2);
    }
    thumbs[currentThumb].color.animateToAfterDelay(ofColor(255,255),delay + currentThumb*0.2);
}

void ContentHolder::disappear(){

    images[currentThumb].color.animateTo(ofColor(255,0));
    images[currentThumb].mask.animateTo(0.);
    
    text.color.animateTo(ofColor(255,0));
    text.mask.animateTo(0.);
    
    textBack.color.animateTo(ofColor(255,0));
    textBack.mask.animateTo(0.);
    
    imageBack.color.animateTo(ofColor(255,0));
    imageBack.mask.animateTo(0.);
    
    dottedLine.color.animateTo(ofColor(255,0));

    for(int i=0; i<thumbs.size(); i++){
        thumbs[i].size.animateTo(0.0);
        thumbs[i].color.animateTo(ofColor(255,200));
    }

    nextThumb = currentThumb;
}

void ContentHolder::update(float time){

    images[currentThumb].update(time);

    if( currentThumb != nextThumb ){
        images[nextThumb].update(time);
        if( !images[currentThumb].isOrWillBeAnimating() ){
            currentThumb = nextThumb;
        }
    }
    
    text.update(time);
    textBack.update(time);
    imageBack.update(time);
    dottedLine.update(time);

    for(int i=0; i<thumbs.size(); i++){
        thumbs[i].update(time);
    }
    
    text.tex.update();

}

void ContentHolder::draw(){
    textBack.draw();
    imageBack.draw();
    dottedLine.draw();
    text.draw();
        
    images[currentThumb].draw();

    if( currentThumb != nextThumb){
        images[nextThumb].draw();
    }

    for(int i=0; i<thumbs.size(); i++){
        thumbs[i].draw();
    }     
}

void ContentHolder::thumbPressed(int selection){
    if(selection == currentThumb || selection == nextThumb){
        return;
    }
    else{
        if(currentThumb != nextThumb){
           thumbs[nextThumb].color.animateTo(ofColor(255,200));
        }
        images[currentThumb].color.animateToAlpha(0);
        images[currentThumb].mask.animateTo(0.);        
        
        nextThumb = selection;
        
        images[nextThumb].setColor(ofColor(255,255));
        images[nextThumb].setMask(0);
        images[nextThumb].mask.animateTo(1.0);

        thumbs[currentThumb].color.animateTo(ofColor(255,200));
        thumbs[nextThumb].color.animateTo(ofColor(255,255));
    }
}

bool ContentHolder::isOrWillBeAnimating(){

    bool iowba = false;
    iowba |= text.isOrWillBeAnimating();
    iowba |= images[currentThumb].isOrWillBeAnimating();
    if( currentThumb != nextThumb ){
        iowba |= images[nextThumb].isOrWillBeAnimating();
    }

    for(int i=0; i<thumbs.size(); i++){
        iowba |= thumbs[i].isOrWillBeAnimating();
    }

    return iowba;
}

void ContentHolder::reset(){
    
    currentThumb = nextThumb = 0;
    
    for (int i=0; i < images.size(); i++) {
        images[i].setMask(0);
        images[i].setColor(ofColor(255,0));
    }
    
    text.setMask(0);
    text.tex.reset();
    
    for(int i=0; i<thumbs.size(); i++){
        thumbs[i].setSize(0.);
        thumbs[i].setColor(ofColor(255,200));
    }
}
