//
//  menuWindow.cpp
//  emptyExample
//
//  Created by its on 2014/09/08.
//
//

#include "menuWindow.h"

void menuWindow::setup(vector<string> menuImagePath, vector<string> menuNames, string now) {
    
    
    //menu
    
    _menuImagePath = menuImagePath;
    _menuName = menuNames;
    _nowName = now;
    _selectNo = -1;
    
    
    //タイトル
    _titleImage.loadImage("title.png");
    _titlePoint = ofPoint((ofGetWidth() - _titleImage.width) / 2, 200);
    _titleAlpha = 0;
    
    
    //各メニュー
    _selectedScale = 1.0;
    /*
    _menuNum = 2;
    string menuPath[2] = {"menu1.png","menu2.png"};
    string menuName[2] = {"menu1","menu2"};
    */
    
    _menuNum = _menuImagePath.size();
    
    
    
    for (int i = 0; i < _menuNum; i++) {
        float px = ofGetWidth() / (_menuNum+1) * (i+1);
        _menuPoint.push_back(ofPoint(px,ofGetHeight() + 500));
        _menus.push_back(new menu(_menuImagePath[i],_menuName[i],_menuPoint[i]));
        _menus[i]->setup();
    }
    
    //カーソル
    _cursol.loadImage("cursol1.png");
    _cursolString.loadImage("cursol2.png");
    _cursolAngle = 0;
    
    _mousePoint = ofPoint(0,0);
    
    //選択
    _selectedNow = "";
    _selectedPre = "";
    _nextWindow = _nowName;
    
    Tweener.addTween(_titleAlpha, 255, 2);
    
    for (int i = 0; i < _menuNum; i++) {
        Tweener.addTween(_menuPoint[i].y, ofGetHeight() / 2, 2, &ofxTransitions::easeOutElastic, 0.5+i*0.5);
    }
    
}
void menuWindow::init() {
    
    _selectNo = -1;
    
    _cursolAngle = 0;
    _selectedNow = "";
    _selectedPre = "";
    _nextWindow = _nowName;
    
    _titleAlpha = 0;
    for (int i = 0; i < _menuNum; i++) {
        float px = ofGetWidth() / (_menuNum+1) * (i+1);
        _menus[i]->init();
        _menus[i]->updateMyPoint(_menuPoint[i]);
        _menus[i]->setParentPoint(_mousePoint, _cursol.getWidth()/2);
        _menuPoint[i] = ofPoint(px,ofGetHeight() + 500);
    }
    
    Tweener.addTween(_titleAlpha, 255, 2);
    
    for (int i = 0; i < _menuNum; i++) {
        float px = ofGetWidth() / (_menuNum+1) * (i+1);
        Tweener.addTween(_menuPoint[i].y, ofGetHeight() / 2, 2, &ofxTransitions::easeOutElastic, 0.5+i*0.5);
    }
}



void menuWindow::update() {
    Tweener.update();
}

void menuWindow::draw() {
    
    _selectedPre = _selectedNow;
    //タイトル
    ofSetColor(255, 255, 255, _titleAlpha);
    _titleImage.draw(_titlePoint.x, _titlePoint.y);
    ofSetColor(255, 255, 255, 255);
    
    //カーソル
    ofPushMatrix();
    ofTranslate(_mousePoint.x, _mousePoint.y-_cursol.getHeight()/2);
    ofRotate(_cursolAngle);
    _cursol.draw(-_cursol.getWidth()/2, -_cursol.getHeight()/2);
    ofPopMatrix();
    _cursolAngle += 2;
    _cursolString.draw(_mousePoint.x-_cursolString.getWidth()/2,_mousePoint.y-_cursolString.getHeight()*3);
    
    
    
    //menu
    for (int i = 0; i < _menuNum; i++) {
        _menus[i]->draw();
        _menus[i]->updateMyPoint(_menuPoint[i]);
        
        /*
        ofSetColor(255, 0, 0, 128);
        ofCircle(_mousePoint.x, _mousePoint.y - _cursol.getWidth()/2, _cursol.getWidth()/2);
        ofSetColor(255, 255, 255, 255);
        */
        ofPoint p = ofPoint(_mousePoint.x, _mousePoint.y - _cursol.getWidth()/2);
        _menus[i]->setParentPoint(p, _cursol.getWidth()/2);
        
        if (_menus[i]->getCollisitonState()) {
            _selectedNow = _menus[i]->getMenuName();
        }
    }
    
    cheackSelected();
}

void menuWindow::cheackSelected() {
    
    /*
    if (_selectedPre == "" && _selectedNow == "menu1") {
        cout << "menu1が選択されました\n";
        Tweener.addTween(_titleAlpha, 0, 2);
        Tweener.addTween(_menuPoint[1].y, ofGetHeight() + 500, 2, &ofxTransitions::easeOutElastic,0.5);
        
    } else if(_selectedPre == "" && _selectedNow == "menu2") {
        cout << "menu2が選択されました\n";
        Tweener.addTween(_titleAlpha, 0, 2);
        Tweener.addTween(_menuPoint[0].y, ofGetHeight() + 500, 2, &ofxTransitions::easeOutElastic, 0.5);
    }
     */
    
    
    for (int i = 0; i < _menuName.size(); i++) {
        if (_selectedPre == "" && _selectedNow == _menuName[i]) {
            cout << _menuName[i] + "が選択されました\n";
            Tweener.addTween(_titleAlpha, 0, 2);
            _selectNo = i;
        }
    }
    
    if (_selectNo != -1) {
        for (int i = 0; i < _menuName.size(); i++) {
            if (_selectNo != i && _selectedPre == "") {
                Tweener.addTween(_menuPoint[i].y, ofGetHeight() + 500, 2, &ofxTransitions::easeOutElastic, 0.5);
                cout << "残りのメニュー削除\n";
            }
        }
    }
    
    
    
    if (_titleAlpha == 0) {
        //cout << "alpha \n";
        
        for (int i = 0; i < _menuName.size(); i++) {
            if (_selectedNow == _menuName[i]) {
                _nextWindow = _menuName[i];
            }
        }
    }
}
string menuWindow::getChangeMode() {
    return _nextWindow;
}

void menuWindow::setMousePoint(ofPoint mp) {
    _mousePoint = mp;
}

//以下keyやmouseイベント

//--------------------------------------------------------------
void menuWindow::keyPressed(int key){
    if (key == ' ') {
       // cout << "key\n";
       // init();
        
    }
    if (key == 'a') {
        _nextWindow = "menuWindow";
    }
}

//--------------------------------------------------------------
void menuWindow::keyReleased(int key){
}

//--------------------------------------------------------------
void menuWindow::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void menuWindow::mouseDragged(int x, int y, int button){
    
}


//--------------------------------------------------------------
void menuWindow::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void menuWindow::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------
void menuWindow::windowResized(int w, int h){
    
}


//--------------------------------------------------------------
void menuWindow::dragEvent(ofDragInfo dragInfo){
    
}