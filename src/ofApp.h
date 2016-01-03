#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#include "imageSprite.h"
#include "menu.h"
#include "ofxTweener.h"

#include "menuWindow.h"
#include "gameWindow.h"
#include "garbageSetWindow.h"
#include "calibration.h"

#define PORT 8000

enum AnimeStatus {
    VISIBLE,
    FORWARD,
    INVISIBLE,
    BACKWARD,
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    float vacumPower;
    float garbageMass;
    
    


//gui

    ofxPanel gui;
    ofxIntSlider _mass;
    ofxFloatSlider _attr;

//animetion関係
    AnimeStatus status;
    imageSprite *img;
    vector<imageSprite *> imgs;
    
private:
    
    //////////キャリブレーション関係////////
    calibration _cali;
    
    //キャリブレーションフラグ
    Boolean calibrationFlag;
    
    //動画から色取得
    int _targetR;
    int _targetG;
    int _targetB;
	
	//カメラの幅と高さ
	int _camWidth = 640;
	int _camHeight = 320;
	
    ////カメラ系
	//もともとの映像情報
	ofxCvColorImage _inputImage;   //入力
    ofxCvColorImage _outputImage;  //出力
    
    //カメラ
	ofVideoGrabber _vidGrabber;
    int mode = 0; //mode0 検出色の指定 mode1 キャリブレーション用の4点指定モード（左上から時計回りに）
    int count = 0;
    ofPoint leftH,leftL,rightH,rightL;
    
    ///////////////////////
    
    ofPoint _vacuumPoint;
    
    int _maxGarbageNum;
    ofPoint _mouseOriginalXY;
    float _mouseAngle;

    ofPoint _mouseCollisionXY;
    float _mouseCollisionR;
    Boolean _debugMode;


    //menukankei
    ofImage _cursol;
    ofImage _cursolString;
    float _cursolAngle;
   // menu testMenu;
    
    
    //window
    string _nowWindow;
    string _preWindow;
    
    menuWindow _menuW;
    menuWindow _gameMenuW;
    
    gameWindow _gameW;
    garbageSetWindow _gSetW;
    
    //osc
    ofxOscReceiver  _receiver;
    
    //arduino
    void serialDataUpdate();
    ofSerial _arduino;
    string _pressureString;
    int _pressureValue;
    

    
};
