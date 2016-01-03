//
//  gameWindow.h
//  emptyExample
//
//  Created by its on 2014/09/08.
//
//

#ifndef __emptyExample__gameWindow__
#define __emptyExample__gameWindow__

#include <iostream>
#include "ofMath.h"
#include "imageSprite.h"
#include "ofxTweener.h"
#include "ofxGui.h"
#include "linework.h"
#include "ofxOsc.h"

#define GAME_TIME 120000

//ボスはゴミの数count以下&& time TIME以下で発動
#define BOSS_TIME 120000
#define BOSS_COUNT 30

//ゲームオーバの条件はGAME_OVER よりゴミの数が多ければ．
#define GAME_OVER 60

class gameWindow {
  
public:
    void setup(string stage, ofSerial ard);
    void update();
    void draw();
    void init(string stage);
    
    void setMousePoint(ofPoint mp);
    void setParam(float vac, float gab);
    
    //image
    vector<imageSprite *> _imgs;
    vector<imageSprite *> _living;
    vector<imageSprite *> _storage;
    vector<imageSprite *> _free;
    
    //画面遷移
    string getChangeMode();
    
    //削除時
    void deleteWindow();
    
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
    
    
    //背景
    ofImage back1;
    
    //gui
    ofxPanel gui;
    ofxIntSlider _mass;
    ofxFloatSlider _attr;
    
    //utility
    ofPoint _mousePoint;
    
    //ゴミ関係
    int _maxGarbageNum;
    ofPoint _mouseOriginalXY;
    float _mouseAngle;
    ofPoint _mouseCollisionXY;
    float _mouseCollisionR;
    Boolean _animationFlag;
    Boolean _preAnimationFlag;
    
    float _vacumPower;
    float _garbageMass;
    
    vector<string> _garbageNames;
    vector<int> _garbageMasses;
    vector<string> _garbageSes;
    
    ofTrueTypeFont font;
    
    ofTrueTypeFont _fontPower;
    ofTrueTypeFont _fontGarbageNum;
    
    //debug
    Boolean _debugMode;
    
    //選択
    string _nextWindow;
    string _stage;
    
    //集中線
    linework lines;
    vector<linework* > _lines;
    
    //表示パラメータ
    float _vacumPowerMeter;
    float _vacumedTotalMass;
    float _vacumedTotal;
    ofImage _message1;
    ofImage _message2;
    int _messageAlpha;
    float _messageAlphaAngle;
    float _addVacumPower;
    
    
    //sound
    ofSoundPlayer _vacumOnSound;
    ofSoundPlayer _vacumOffSound;
    ofSoundPlayer _vacumLoopSound;
    ofSoundPlayer _garbageDeleteSound;
    
    Boolean _soundLoopFlag;
    
    Boolean _garbageFullFlag;
    Boolean _preGarbageFullFlag;
    
    
    //定期的にゴミが増える
    void garbageTimerEvent();
    float _interval;
    float _intervalTime;

    
    //ゲームタイマー
    void gameTimerEvent();
    float _gameInterbal;
    float _gameIntervalTime;
    float _gameTime;
    Boolean _gameEndFlag;
    ofImage _gameClearImage;
    
    //gameover
    
    Boolean _gameOverFlag;
    Boolean _preGameOverFlag;
    ofImage _gameOverImage;
    
    //boss
    Boolean _bossFlag;
    Boolean _preBossFlag;
    
    Boolean _bossAppearFlag;
    Boolean _preBossAppearFlag;
    ofImage _bossCome;
    
    void bossTimerEvent();
    float _bossInterbal;
    float _bossIntervalTime;
    
    //osc
    ofxOscSender _sender;
    void oscSender(string s);
    
    //arduino
    ofSerial _arduinoObj;
    string _pressureString;
    int _pressureValue;
    
    //bgm
    ofSoundPlayer _bgm;
    
    //switch
    Boolean _switch;
    void vacumeOn(Boolean f);
};



#endif /* defined(__emptyExample__gameWindow__) */
