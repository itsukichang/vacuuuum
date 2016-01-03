//
//  menuWindow.h
//  emptyExample
//
//  Created by its on 2014/09/08.
//
//

#ifndef __emptyExample__menuWindow__
#define __emptyExample__menuWindow__

#include <iostream>
#include "ofMain.h"
#include "ofxTweener.h"
#include "menu.h"

class menuWindow {
    
public:
    
    void setup(vector<string> menuImagePath, vector<string> menuNames, string now);
    void update();
    void draw();
    
    string getSelectedMenu();
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

private:
    
    

    //utility
    ofPoint _mousePoint;
    
    //カーソル関係
    ofImage _cursol;
    ofImage _cursolString;
    float _cursolAngle;
    
    //描画メニュー
    int _menuNum;
    vector<menu *> _menus;
    vector<ofPoint> _menuPoint;
    float _selectedScale;
    
    ofImage _titleImage;
    float _titleAlpha;
    ofPoint _titlePoint;
    
    //menu
    vector<string> _menuImagePath;
    vector<string> _menuName;
    string _nowName;
    int _selectNo;
    
    //選択
    string _selectedNow;
    string _selectedPre;
    string _nextWindow;
    
    
    void cheackSelected();
};
#endif /* defined(__emptyExample__menuWindow__) */
