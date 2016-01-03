//
//  menuWindow.h
//  emptyExample
//
//  Created by its on 2014/09/08.
//
//

#ifndef __emptyExample__garbageSetWindow__
#define __emptyExample__garbageSetWindow__

#include <iostream>
#include "ofMain.h"
#include "ofxGui.h"

class garbageSetWindow {
    
public:
    
    void setup();
    void update();
    void draw();
    void init();
    
    void setMousePoint(ofPoint mp);
    
    //画面遷移
    string getChangeMode();
    
    //default
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    
    float getVacumPower();
    float getGarbageMass();
    
    
private:
    
    //gui
    ofxPanel gui;
    ofxIntSlider _mass;
    ofxFloatSlider _attr;
    
    //utility
    ofPoint _mousePoint;
    
    //選択
    string _nextWindow;
    
};
#endif /* defined(__emptyExample__menuWindow__) */
