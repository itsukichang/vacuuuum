//
//  menu.h
//  emptyExample
//
//  Created by its on 2014/09/05.
//
//

#ifndef __emptyExample__menu__
#define __emptyExample__menu__

#include <iostream>
#include "ofMain.h"

class menu {
    
public:
    
    menu(string path, string name, ofPoint myPoint);
    
    void setup();
    void update();
    void draw();
    
    void init();
    
    void setParentPoint(ofPoint p, float r);
    
    void updateMyPoint(ofPoint p);
    Boolean getCollisitonState();
    string getMenuName();
    
    
private:
    
    string _imagePath;
    string _name;
    ofImage _menuImage;
    
    
    
    void checkCollisiton();
    void measureTime();
    Boolean _collistionFlag;
    Boolean _preState;
    
    int _startTime;
    int _continueTime;
    
    ofPoint _parentPoint;
    float _parentR;
    
    float _myR;
    ofPoint _myPoint;
    
    Boolean _menuSelected;
    Boolean _menuColorFlag;
};

#endif /* defined(__emptyExample__menu__) */
