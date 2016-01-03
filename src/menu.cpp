//
//  menu.cpp
//  emptyExample
//
//  Created by its on 2014/09/05.
//
// menuなどで使えるボタンのようなものです．マウスオーバーが一定秒数保たれると，選択していると判定します．
// 使い方: newした後，setup()して，draw -> setParentPoint(ofPoint(mouseX,mouseY), 当たり判定R)を繰り返す
// 座標を変化させるならupdateMyPoint()へ座標を.

#include "menu.h"


menu::menu(string path, string name, ofPoint myPoint) {
    _imagePath = path;  //読み込み画像のパス
    _name = name;       //menuの名前
    _myPoint = myPoint; //配置座標
}


void menu::setup() {
    _menuImage.loadImage(_imagePath);
    _myR = _menuImage.getWidth()/2;
    
    _collistionFlag = false;
    _preState = false;
    _menuSelected = false;
    _menuColorFlag = false;
    _startTime = 0;
}

void menu::init() {
    _collistionFlag = false;
    _preState = false;
    _menuSelected = false;
    _menuColorFlag = false;
    _startTime = 0;
}

void menu::update() {
    
    
}

void menu::draw() {
    
    
    //menuがN秒選択(mouseOver)されていた場合の処理
    if (_continueTime > 1500) {
        ofSetColor(255,255,255,255);
        _menuSelected = true;
        _menuColorFlag = true;
    } else {
        ofSetColor(255,255,255,128);
        _menuSelected = false;
    }
    
    if (_menuColorFlag) {
        ofSetColor(255,255,255,255);
    }
    _menuImage.draw(_myPoint.x-_menuImage.width/2, _myPoint.y-_menuImage.height/2);
    ofSetColor(255,255,255,255);
}


void menu::setParentPoint(ofPoint p, float r) {
    _parentPoint = p;
    _parentR = r;
    
    checkCollisiton();
}

void menu::checkCollisiton() {
   // cout << "check \n";
    
    
    _preState = _collistionFlag;
    
    float diffR = _parentR + _myR;
    
    /*
    cout << "diffR:";
    cout << diffR;
    cout << "px,py,mx,my:";
    cout << _parentPoint.x;
    cout << ", ";
    cout << _parentPoint.y;
    cout << ", ";
    cout << _myPoint.x;
    cout << ", ";
    cout << _myPoint.y;
    cout << "\n ";
    */
    
    float diffValue = sqrt(
                           (_parentPoint.x - _myPoint.x)*(_parentPoint.x - _myPoint.x)+
                           (_parentPoint.y - _myPoint.y)*(_parentPoint.y - _myPoint.y));
    if (diffValue < diffR) {
        _collistionFlag = true;
        if (_preState == false) {
            _startTime = ofGetElapsedTimeMillis();
        }
    } else {
        _collistionFlag = false;
        _menuSelected = false;
        _startTime = 0;
        _continueTime = 0;
    }
    
    measureTime();
}

void menu::measureTime() {
    if (_collistionFlag && _preState) {
        _continueTime = ofGetElapsedTimeMillis() - _startTime;
       /*
        cout << "経過時間 : ";
        cout << _continueTime;
        cout << "\n";
        */
    }
}

//getter, setter
Boolean menu::getCollisitonState() {
    
    return _menuSelected;
}

//
void menu::updateMyPoint(ofPoint p) {
    _myPoint = p;
}

string menu::getMenuName() {
    return _name;
}