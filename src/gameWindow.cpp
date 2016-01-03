//
//  gameWindow.cpp
//  emptyExample
//
//  Created by its on 2014/09/08.
//
//

#include "gameWindow.h"

void gameWindow::deleteWindow() {
    for (int i = 0; i < _imgs.size(); i++) {
        _imgs[i]->imageReset();
    }
}

void gameWindow::setup(string stage, ofSerial ard) {
    _arduinoObj = ard;
    _switch = false;
    
    _arduinoObj.setup("/dev/cu.usbmodem1421",9600);
    _pressureString = "";
    _pressureValue = 0;
    
    
    //gui
   /*
    gui.setup();
    gui.add(_mass.setup( "objMass", 50, 50, 300 ));
    gui.add(_attr.setup( "attractiveForce",100,50,300));
    */
    
    
    _stage = stage;
    //ゴミのパラメータ
    //ゴミの名前
    _garbageNames.push_back("garbage1");    //ほこり
    _garbageNames.push_back("garbage2");    //土
    _garbageNames.push_back("garbage3");    //ちり紙1
    _garbageNames.push_back("garbage4");    //ちり紙2
    _garbageNames.push_back("garbage5");    //ペットボトル
    _garbageNames.push_back("garbage6");    //新聞紙
    _garbageNames.push_back("garbage7");    //ダンボール
    
    _garbageNames.push_back("garbage8");    //金槌
    _garbageNames.push_back("garbage9");    //缶
    _garbageNames.push_back("garbage10");    //ねじ
    _garbageNames.push_back("garbage11");   //スイカ
    
    //ゴミの質量
    _garbageMasses.push_back(30);   //ほこり
    _garbageMasses.push_back(30);   //土
    _garbageMasses.push_back(40);   //ちり紙1
    _garbageMasses.push_back(40);   //ちり紙2
    _garbageMasses.push_back(70);   //ペットボトル
    _garbageMasses.push_back(100);   //新聞紙
    _garbageMasses.push_back(150);   //段ボール
    _garbageMasses.push_back(160);   //金槌
    _garbageMasses.push_back(70);   //缶
    _garbageMasses.push_back(60);   //ねじ
    _garbageMasses.push_back(200);   //スイカ
    
    
    //ゴミのse
    _garbageSes.push_back("garbage/se1.mp3");   //ほこり
    _garbageSes.push_back("garbage/se6.mp3");   //土
    _garbageSes.push_back("garbage/se2.mp3");   //ちり紙1
    _garbageSes.push_back("garbage/se2.mp3");   //ちり紙2
    _garbageSes.push_back("garbage/se3.mp3");   //ペットボトル
    _garbageSes.push_back("garbage/se5.mp3");   //新聞紙
    _garbageSes.push_back("garbage/se2.mp3");   //ダンボール
    
    _garbageSes.push_back("garbage/se3.mp3");   //金槌
    _garbageSes.push_back("garbage/se3.mp3");   //缶
    _garbageSes.push_back("garbage/se3.mp3");   //ねじ
    _garbageSes.push_back("garbage/se2.mp3");   //スイカ
    
    
    //掃除機とゴミのパラメータ
    _vacumPower = 75;
    _garbageMass = 50;
    
    //paramInit
    _mouseCollisionR = _vacumPower;
    _debugMode = false;
    _mouseOriginalXY = ofPoint(0,0);
    _mouseAngle = 270.0;
    _mousePoint = ofPoint(0,0);
    
    
    _nextWindow = "gameWindow";
    
    
    
    int miniGarbage;
    int normalGarbage;
    int bigGarbage;
    
    
    ///////////////////////リビング//////////////////////
    miniGarbage = 20;
    normalGarbage = 20;
    bigGarbage = 0;
    
    //ほこりとかの雑魚
    _maxGarbageNum = miniGarbage + normalGarbage + bigGarbage;
    for (int i = 0; i < miniGarbage; i++) {
        ofPoint pxy = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        
        int imgNo = floor(ofRandom(1,5));
        string imgPath = "garbage/garbage"+ofToString(imgNo) + ".png";
        _living.push_back(new imageSprite(imgPath,            //画像url
                                        _garbageSes[imgNo-1],         //効果音url
                                        _garbageNames[imgNo-1],             //名前
                                       pxy,                 //pXY
                                       ofPoint(0,0),        //toXY
                                       ofPoint(0.1,0.3),    //toScaleXY
                                       0,                   //toAlpha
                                       ofRandom(540,1080),  //toAngle
                                       true,                //動き回るか
                                       _garbageMasses[imgNo-1]                   //質量
                                        ));
    }
    
    //ビン，新聞紙，段ボール
    float maxW = ofGetWidth() - 50;
    float gY = 50;
    
    for (int i = 0; i < normalGarbage; i++) {
        
        int imgNo = floor(ofRandom(5,9));
        if (imgNo == 8) imgNo = 11;
        string imgPath = "garbage/garbage"+ofToString(imgNo) + ".png";
        
        ofPoint p;
        if (maxW > 100) {
            p = ofPoint(maxW,gY);
            maxW -= 100;
        } else {
            p = ofPoint(maxW,gY);
            gY += ofRandom(80,120);
        }
        _living.push_back(new imageSprite(imgPath,            //画像url
                                        _garbageSes[imgNo-1],         //効果音url
                                        _garbageNames[imgNo-1],             //名前
                                        p,                 //pXY
                                        ofPoint(0,0),        //toXY
                                        ofPoint(0.1,0.3),    //toScaleXY
                                        0,                   //toAlpha
                                        ofRandom(540,1080),  //toAngle
                                        false,                //動き回るか
                                        _garbageMasses[imgNo-1]                    //質量
                                        ));
    }
    
    
    ///////////////////////倉庫//////////////////////
    miniGarbage = 30;
    normalGarbage =20;
    bigGarbage = 0;
    //ほこりとかの雑魚
    _maxGarbageNum = miniGarbage + normalGarbage + bigGarbage;
    for (int i = 0; i < miniGarbage; i++) {
        ofPoint pxy = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        
        int imgNo = floor(ofRandom(1,5));
        string imgPath = "garbage/garbage"+ofToString(imgNo) + ".png";
        _storage.push_back(new imageSprite(imgPath,            //画像url
                                          _garbageSes[imgNo-1],         //効果音url
                                          _garbageNames[imgNo-1],             //名前
                                          pxy,                 //pXY
                                          ofPoint(0,0),        //toXY
                                          ofPoint(0.1,0.3),    //toScaleXY
                                          0,                   //toAlpha
                                          ofRandom(540,1080),  //toAngle
                                          true,                //動き回るか
                                          _garbageMasses[imgNo-1]                   //質量
                                          ));
    }
    
    //ビン，新聞紙，段ボール
    maxW = 50;
    gY = 50;
    
    for (int i = 0; i < normalGarbage; i++) {
        
        int imgNo = floor(ofRandom(7,11));
        string imgPath = "garbage/garbage"+ofToString(imgNo) + ".png";
        
        ofPoint p;
        if (gY < ofGetHeight() - 50) {
            p = ofPoint(maxW,gY);
            gY += ofRandom(80,120);
        } else {
            p = ofPoint(maxW,gY);
            gY = ofRandom(40,80);
            maxW += ofRandom(80,120);
        }
        _storage.push_back(new imageSprite(imgPath,            //画像url
                                          _garbageSes[imgNo-1],         //効果音url
                                          _garbageNames[imgNo-1],             //名前
                                          p,                 //pXY
                                          ofPoint(0,0),        //toXY
                                          ofPoint(0.1,0.3),    //toScaleXY
                                          0,                   //toAlpha
                                          ofRandom(540,1080),  //toAngle
                                          false,                //動き回るか
                                          _garbageMasses[imgNo-1]                    //質量
                                          ));
    }
    
    
    
    ///////////////////////フリー//////////////////////
    
    
    maxW = 50;
    gY = 50;
    for (int i = 1; i < _garbageMasses.size() + 1; i++) {
        ofPoint pxy = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        int imgNo = i;
        
        string imgPath = "garbage/garbage"+ofToString(imgNo) + ".png";
        
        ofPoint p;
        if (i % 4 == 0) {
            gY += 300;
            maxW =  300;
        } else {
            maxW += 300;
        }
        p = ofPoint(maxW,gY);
        _free.push_back(new imageSprite(imgPath,            //画像url
                                           _garbageSes[imgNo-1],         //効果音url
                                           _garbageNames[imgNo-1],             //名前
                                           p,                 //pXY
                                           ofPoint(0,0),        //toXY
                                           ofPoint(0.1,0.3),    //toScaleXY
                                           0,                   //toAlpha
                                           ofRandom(540,1080),  //toAngle
                                           false,                //動き回るか
                                           _garbageMasses[imgNo-1]                   //質量
                                           ));
    }
    
    
    //初期設定リビング
    
    if (stage == "living") {
        _imgs = _living;
        _nextWindow = "stage1";
        back1.loadImage("back1.jpg");
    } else if (stage == "storage"){
        _imgs = _storage;
        _nextWindow = "stage2";
        back1.loadImage("back3.jpg");
    } else if (stage == "free"){
        _imgs = _free;
        _nextWindow = "stage3";
        back1.loadImage("back3.jpg");
    }
    
    
    //集中線
    for (int i = 0; i < 30; i++) {
        _lines.push_back(new linework());
        _lines[i]->setup();
    }
    
    //吸い込んでいる状態か否か
    _animationFlag = false;
    _preAnimationFlag = false;
    
    //文字
    font.loadFont("ヒラギノ角ゴ StdN W8.otf",24);
    _fontPower.loadFont("ヒラギノ角ゴ StdN W8.otf",20);
    _fontGarbageNum.loadFont("ヒラギノ角ゴ StdN W8.otf",20);
    //背景
    back1.loadImage("back1.jpg");
    
    
    //サウンド
    _vacumOnSound.loadSound("vacuum-cleaner-on1.mp3");
    _vacumOnSound.setVolume(0.5);
    _vacumOffSound.loadSound("vacuum-cleaner-off1.mp3");
    _vacumOffSound.setVolume(0.5);
    _vacumLoopSound.loadSound("vacuum-cleaner-operation1.mp3");
    _vacumLoopSound.setVolume(0.5);
    
    
    _garbageDeleteSound.loadSound("se_maoudamashii_magical28.mp3");
    _garbageDeleteSound.setVolume(0.5);
    
    
    _soundLoopFlag = false;
    
    
    //表示パラメータ
    _vacumPowerMeter = 0;
    _vacumedTotalMass = 0;
    _vacumedTotal = 0;
    
    _addVacumPower = 0;
    _message1.loadImage("message1.png");
    _message2.loadImage("message2.png");
    
    _messageAlpha = 0;
    _messageAlphaAngle = 0;

    //osc
    
    string kawabata = "192.168.1.101";
    
    _sender.setup("localhost",8000);
    //_sender.setup(kawabata,8000);
    oscSender("reset");
    
    
    //TimerEvent
    _interval = ofGetElapsedTimeMillis();
    _intervalTime = ofRandom(300, 2500);
    
    //gameTimerEvent
    _gameInterbal = ofGetElapsedTimeMillis();
    _gameIntervalTime = 100;
    _gameTime = GAME_TIME;
    _gameClearImage.loadImage("gameClear.png");
    //gameover
    _gameOverFlag = false;
    _preGameOverFlag = false;
    _gameOverImage.loadImage("gameover.png");
    
    //boss
    _bossFlag = false;
    _preBossFlag = false;
    _bossInterbal = 0;
    _bossIntervalTime = 3000;
    _bossAppearFlag = false;
    _preBossAppearFlag = false;
    _bossCome.loadImage("bossCome.png");
    
    _gameEndFlag = false;
    
    //ゴミ満タン
    _garbageFullFlag = false;
    _preGarbageFullFlag = false;
    
    //bgm
    
    _bgm.loadSound("bgm1.mp3");
    _bgm.setLoop(true);
    _bgm.setVolume(0.5);
}


void gameWindow::init(string stage) {
    
    _switch = false;
    
     _bgm.play();
    _stage = stage;
    _pressureString = "";
    _pressureValue = 0;
    
    
    
    if (stage == "living") {
        _imgs = _living;
        _nextWindow = "stage1";
        back1.loadImage("back1.jpg");
    } else if (stage == "storage"){
        _imgs = _storage;
        _nextWindow = "stage2";
        back1.loadImage("back3.jpg");
    } else if (stage == "free"){
        _imgs = _free;
        _nextWindow = "stage3";
        back1.loadImage("back3.jpg");
    }
    
    
    //_nextWindow = "gameWindow";
    for (int i = 0; i < _imgs.size(); i++) {
        _imgs[i]->imageReset();
        _imgs[i]->appear();
    }
    
    _vacumPowerMeter = 0;
    _vacumedTotalMass = 0;
    _vacumedTotal = 0;
    
    _vacumPower = 75;
    _garbageMass = 50;
    _addVacumPower = 0;
    _messageAlpha = 0;
    _messageAlphaAngle = 0;
    
    _vacumOnSound.setVolume(0.5);
    _vacumOffSound.setVolume(0.5);
    _vacumLoopSound.setVolume(0.5);
    oscSender("reset");
    
    
    //timerEvent;
    _interval = ofGetElapsedTimeMillis();
    _intervalTime = ofRandom(300, 2500);
    
    _gameInterbal = ofGetElapsedTimeMillis();
    _gameIntervalTime = 100;
    _gameTime= GAME_TIME;
    
    
    if (_stage == "living") {
        _imgs = _living;
        _nextWindow = "stage1";
        back1.loadImage("back1.jpg");
    } else if (_stage == "storage"){
        _imgs = _storage;
        _nextWindow = "stage2";
        back1.loadImage("back3.jpg");
    } else if (_stage == "free"){
        _imgs = _free;
        _nextWindow = "stage3";
        back1.loadImage("back3.jpg");
    }
    
    //gameover
    _gameOverFlag = false;
    _preGameOverFlag = false;
    
    //boss
    _bossFlag = false;
    _preBossFlag = false;
    _bossAppearFlag = false;
    _preBossAppearFlag = false;
    _bossInterbal = 0;
    _bossIntervalTime = 3000;
    
    _gameEndFlag = false;
    
    //ゴミ満タン
    _garbageFullFlag = false;
    _preGarbageFullFlag = false;
}



void gameWindow::update() {
    
    //bgm
   
    vacumeOn(_switch);
    
    //arduino
    
    for (int i = 0; i < 30; i++ ) {
        while (_arduinoObj.available() > 0) {
            char byte = _arduinoObj.readByte();
            
            if (byte == '\n') {
                cout << "<-ここまで\n";
                std::string ss = _pressureString;
                
                //圧力検知
                string keyword ="press:";
                //int tmp = ss.find(keyword);
                if (ss.find(keyword) != std::string::npos) {
                    //cout <<  "検出位置 : " << tmp << "\n";
                    cout <<  "検出内容 : " << ss.substr(keyword.length());
                    _pressureValue = ofToInt(ss.substr(keyword.length()));
                    
                }
                
                
                //加速度検知
                if (ss.find("garbage:delete") != std::string::npos) {
                    _garbageDeleteSound.play();
                    _vacumedTotalMass = 0;
                    oscSender("reset");
                }
                cout << "arduino string : " + _pressureString + "\n";
                _pressureString = "";
                
                if (ss.find("switchOn") != std::string::npos) {
                    _switch  = true;
                }
                
                if (ss.find("switchOff") != std::string::npos) {
                    _switch  = false;
                    
                    unsigned char buf[5] = {'c','l','e','a','r'};
                    _arduinoObj.writeBytes(&buf[0], 5);
                }
                
                
            } else {
                _pressureString += byte;
            }
        }
    }
    cout << "int : " << _pressureValue << "\n";
    
    
        if(_pressureValue > 340) {
        
        int mag = 3;
        setParam(75*mag*0.5, 50);
    } else {
        setParam(75, 50);
    }
    
    
    
    
    
    
    
    
    
    //sound
    if (_preAnimationFlag == false && _animationFlag == true) {
        cout << "off - >on \n";
        _vacumOnSound.play();
        _vacumOffSound.stop();
    } else if(_preAnimationFlag == true && _animationFlag == false) {
        cout << "on -> off\n";
        _vacumOnSound.stop();
        _vacumLoopSound.stop();
        
        _vacumOffSound.play();
        _soundLoopFlag = false;
    }
    
    if (_animationFlag == true && _vacumOnSound.getPosition() > 0.5) {
        _soundLoopFlag = true;
        _vacumLoopSound.setLoop(true);
        _vacumLoopSound.play();
        _vacumOnSound.stop();
    }
    
    
    float volume = (_vacumPower - 50) / 100.0 / 2 + 0.3;
    
    _vacumOnSound.setVolume(volume);
    _vacumLoopSound.setVolume(volume);
    
    //cout << "sound volume : " << _vacumOnSound.getVolume() << "\n";
    //cout << "v power : " << _vacumPower << "\n";
    
    //////////////////////////////////////////////////////////
    
    _preAnimationFlag = _animationFlag;
    
    _mouseCollisionR = _vacumPower+_addVacumPower ;
    _mouseOriginalXY = ofPoint(_mousePoint.x, _mousePoint.y);
    
    float rad = _mouseAngle / 180.0 * PI;
    
    _mouseCollisionXY = ofPoint(_mouseOriginalXY.x+cos(rad)*_mouseCollisionR,
                                _mouseOriginalXY.y+sin(rad)*_mouseCollisionR+_mouseCollisionR);
    Tweener.update();
    
    _soundLoopFlag = false;
    
    if (_stage != "free") {
        if (_gameTime > 0) {
            gameTimerEvent();
            garbageTimerEvent();
        } else {
            _gameEndFlag = true;
            _addVacumPower = -150;
            _garbageMass = 1000;
            
        }
    }
}


void gameWindow::draw() {
    
    cout << "stage: " << _stage << "\n";
    back1.draw(0,0);

    gui.draw();
    if (_debugMode) {
        ofSetColor(0,255,0,128);
        ofCircle(_mouseOriginalXY.x, _mouseOriginalXY.y, _mouseCollisionR);
        ofSetColor(0, 0, 255, 128);
        ofCircle(_mouseCollisionXY.x, _mouseCollisionXY.y, _mouseCollisionR);
    }
    
    int count = 0;
    for (int i = 0; i < _imgs.size(); i++) {
        _imgs[i]->update();
        _imgs[i]->draw();
        _imgs[i]->setToXY(ofPoint(_mousePoint.x, _mousePoint.y));
        _imgs[i]->setVacumePower(_vacumPower);
        _imgs[i]->setVibCount(_garbageMass);
        if (_imgs[i]->getVacumued()) {
            count++;
        }
        if (_animationFlag) {
            _imgs[i]->toAnimation();
        }
        
        if (_imgs[i]->getVacumued() == true && _imgs[i]->getPreVacumed() == false) {
            cout << _imgs[i]->getGarbageName() << "が吸い込まれました\n";
            _vacumedTotalMass += _imgs[i]->getGarbageMass();
            _vacumedTotal += _imgs[i]->getGarbageMass();
            
            oscSender(_imgs[i]->getGarbageName());
            
            
            
            ////arduino
            //吸い込んだゴミによって送るデータを変更
            
            if (_switch) {
                if (_imgs[i]->getGarbageName() == "garbage7") {
                    unsigned char buf[3] = {'s','q','u'};
                    _arduinoObj.writeBytes(&buf[0], 3);
                } else if (_imgs[i]->getGarbageName() == "garbage11") {
                    unsigned char buf[3] = {'b','a','l'};
                    _arduinoObj.writeBytes(&buf[0], 3);
                } else if (_imgs[i]->getGarbageName() == "garbage5" || _imgs[i]->getGarbageName() == "garbage8" ||
                           _imgs[i]->getGarbageName() == "garbage9" || _imgs[i]->getGarbageName() == "garbage10" ||
                           _imgs[i]->getGarbageName() == "garbage6") {
                    unsigned char buf[3] = {'b','i','g'};
                    _arduinoObj.writeBytes(&buf[0], 3);
                } else {
                    unsigned char buf[3] = {'s','m','a'};
                    _arduinoObj.writeBytes(&buf[0], 3);
                }
            }
            
            //freeモードなら復活
            if (_stage == "free") {
                
            }
        }
    }
    
    
    //集中線
    /*
    float testX = _mousePoint.x + 100;
    float testY = _mousePoint.y - 100;
    float angle = atan2(testX - _mousePoint.x, testY - _mousePoint.y);
    float toY = -10;
    float toX = toY / tan(angle);
    toY += _mousePoint.y;
    toX += _mousePoint.x;
    ofLine(testX, testY, toX, toY);
    */
    
    if (_animationFlag) {
        for (int i = 0; i < 20; i++) {
            _lines[i]->setLength(_mouseCollisionR*1.5);
            _lines[i]->setMousePoint(_mousePoint);
            _lines[i]->setParentAngle(_mouseAngle);
            _lines[i]->update();
            _lines[i]->draw();
        }
    }
    
    
    //cout << "vp : " <<_vacumPower << "\n";
    if (_animationFlag) {
        _vacumPowerMeter = (_vacumPower + _addVacumPower) * 4 + ofRandom(20,30);
    } else {
        _vacumPowerMeter += (0-_vacumPowerMeter) / 16;
    }

    
    ofSetColor(0,0,0,128);
    ofRect(0, ofGetHeight()-90, ofGetWidth()/2+200, 45);
    ofSetColor(0,0,255);
    ofRect(0, ofGetHeight()-90, _vacumPowerMeter, 45);
    
    ofSetColor(0,0,0,128);
    ofRect(0, ofGetHeight()-45, ofGetWidth()/2+200, 45);
    ofSetColor(0,255,0);
    ofRect(0, ofGetHeight()-45, _vacumedTotalMass/5, 45);
    ofSetColor(255,255,255);
    
    //font.drawString("GARBAGE NUM : " + ofToString(_imgs.size()-count) , ofGetWidth()-500,ofGetHeight()-50);
    
    if (_gameEndFlag == false) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()-300,ofGetHeight()-150);
        ofRotate(-90);
        ofSetColor(0,0,0);
    
        font.drawString("last : " + ofToString(_gameTime/1000) + "\nGARBAGE NUM : " + ofToString(_imgs.size()- count) , 0,0);
    } else {
        _gameClearImage.draw((ofGetWidth() - _gameClearImage.width) / 2, (ofGetHeight() - _gameClearImage.height) / 2);
        ofPushMatrix();
        ofTranslate(ofGetWidth()-300,ofGetHeight()-150);
        ofRotate(-90);
        ofSetColor(0,0,0);
        font.drawString("RESULT : \nVACUMED GARBAGE : " + ofToString(count) + "\nSCORE : " +  ofToString(_vacumedTotal), 0,0);
        
        
    }
    ofSetColor(255,255,255);
    ofPopMatrix();
    
    
    _fontPower.drawString("POWER", ofGetWidth()/2+30,ofGetHeight()-60);
    _fontPower.drawString("CAPACITY", ofGetWidth()/2+30,ofGetHeight()-15);
    
    
    cout << "total mass : " << _vacumedTotalMass/5 << "\n";
    
    //float rad = _messageAlphaAngle / 180 * PI;
    
    _preGarbageFullFlag = _garbageFullFlag;
    
    _messageAlpha = 128 * (sin(_messageAlphaAngle)+1);
    _messageAlphaAngle += 0.05;
    
    
    if (_vacumPower > 100 && _vacumPower < 130) {
        _garbageMass = 30;
    } else if (_vacumPower > 130) {
        _garbageMass = 10;
    }
    
    _garbageFullFlag = false;
    cout << "messageAlpha : " << _messageAlpha << "\n";
    if (_vacumedTotalMass / 5 > 600 && _vacumedTotalMass / 5 < 800) {
        ofSetColor(255,255,255,_messageAlpha);
        _garbageMass = 75;
        _addVacumPower = -30;
        _message2.draw(300, 20);
        ofSetColor(255,255,255,255);
    } else if (_vacumedTotalMass / 5 > 800 ) {
        ofSetColor(255,255,255,_messageAlpha);
        _garbageMass = 200;
        _addVacumPower = -100;
        _message1.draw(300, 20);
        ofSetColor(255,255,255,255);
        
        _garbageFullFlag = true;
    } else {
        _garbageMass = 50;
        _addVacumPower = 0;
    }
    
    if (_preGarbageFullFlag == true && _garbageFullFlag == false) {
        cout << "空になりました！！！！！\n";
        _garbageDeleteSound.play();
    }
    
    //ofDrawBitmapString("吸い込み数 : " + ofToString(count),100,100);
    
    
    ////////////GAMEOVER処理
    _preGameOverFlag = _gameOverFlag;
    if (_imgs.size()- count > GAME_OVER) {
        _gameOverFlag = true;
    }
    
    if (_preGameOverFlag == false && _gameOverFlag == true) {
        for (int i = 0; i < 100; i++) {
            ofPoint pxy = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0,ofGetHeight()));
            
            
            int imgNo = floor(ofRandom(1,5));
            string imgPath = "garbage/garbage"+ofToString(imgNo) + ".png";
            _imgs.push_back(new imageSprite(imgPath,            //画像url
                                              _garbageSes[imgNo-1],         //効果音url
                                              _garbageNames[imgNo-1],             //名前
                                              pxy,                 //pXY
                                              ofPoint(0,0),        //toXY
                                              ofPoint(0.1,0.3),    //toScaleXY
                                              0,                   //toAlpha
                                              ofRandom(540,1080),  //toAngle
                                              true,                //動き回るか
                                              _garbageMasses[imgNo-1]                   //質量
                                              ));
            _imgs[_imgs.size()-1]->appear();
        }
    }
    if (_gameOverFlag) {
        cout << "gameover\n";
        _gameOverImage.draw((ofGetWidth() - _gameOverImage.width) / 2, (ofGetHeight() - _gameOverImage.height) / 2);
        _addVacumPower = -150;
        _garbageMass = 1000;
    }
    ////////////////////////////////////////////////
    
    
    ////////BOSS処理
    _preBossFlag = _bossFlag;
    if (_gameEndFlag == false) {
        _preBossAppearFlag =_bossAppearFlag;
        if (_imgs.size()- count < BOSS_COUNT && _gameTime < BOSS_TIME) {
            _bossFlag  = true;
        }
        
        if ( _preBossFlag == false && _bossFlag == true) {
            _bossInterbal = ofGetElapsedTimeMillis();
        }
        
        if (_bossFlag == true && _bossAppearFlag == false) {
            _bossCome.draw((ofGetWidth() - _bossCome.width) / 2, (ofGetHeight() - _bossCome.height) / 2);
        }
        
        if (_bossFlag) {
            bossTimerEvent();
        }
        if (_preBossAppearFlag == false && _bossAppearFlag == true) {
            int imgNo = 11;
            string imgPath = "garbage/boss1.png";
            ofPoint pxy = ofPoint(ofGetWidth() / 2, ofGetHeight()/2);
            _imgs.push_back(new imageSprite(imgPath,            //画像url
                                            "garbage/seBoss.wav",         //効果音url
                                            "boss1",             //名前
                                            pxy,                 //pXY
                                            ofPoint(0,0),        //toXY
                                            ofPoint(0.1,0.3),    //toScaleXY
                                            0,                   //toAlpha
                                            ofRandom(540,1080),  //toAngle
                                            true,                //動き回るか
                                            500                   //質量
                                            ));
            _imgs[_imgs.size()-1]->appear();
        }

    }
    /////////////////////////////////////////////////
    
}

//boss
void gameWindow::bossTimerEvent() {
    if (_bossFlag) {
        if (ofGetElapsedTimeMillis() - _bossInterbal > _bossIntervalTime) {
            _bossAppearFlag = true;
            
        }
    }
}


//時間計測
void gameWindow::gameTimerEvent() {
    if (ofGetElapsedTimeMillis() - _gameInterbal > _gameIntervalTime) {
        _gameInterbal = ofGetElapsedTimeMillis();
        if (_gameTime > 0)
        _gameTime -= 100;
        
    }
}

//ゴミの増加
void gameWindow::garbageTimerEvent() {
    if (ofGetElapsedTimeMillis() - _interval > _intervalTime) {
        _interval = ofGetElapsedTimeMillis();
        _intervalTime = ofRandom(300, 2500);
        
        cout << "garbage+++++++++\n";
        
        
        int imgNo;
        Boolean moveFlag;
        
        if (_stage == "living") {
            if (ofRandom(0,1) > 0.7) {
                imgNo = floor(ofRandom(1,5));
            } else {
                imgNo = floor(ofRandom(5,9));
                if (imgNo == 8) imgNo = 11;
            }
        } else if (_stage == "storage"){
            
            if (ofRandom(0,1) > 0.7) {
                imgNo = floor(ofRandom(1,5));
            } else {
                imgNo = floor(ofRandom(7,11));
            }
        }
        
        if (imgNo >= 5) {
            moveFlag = false;
        } else {
            moveFlag = true;
        }

        
        ofPoint pxy = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        string imgPath = "garbage/garbage"+ofToString(imgNo) + ".png";
        _imgs.push_back(new imageSprite(imgPath,            //画像url
                                           _garbageSes[imgNo-1],         //効果音url
                                           _garbageNames[imgNo-1],             //名前
                                           pxy,                 //pXY
                                           ofPoint(0,0),        //toXY
                                           ofPoint(0.1,0.3),    //toScaleXY
                                           0,                   //toAlpha
                                           ofRandom(540,1080),  //toAngle
                                           moveFlag,                //動き回るか
                                           _garbageMasses[imgNo-1]                   //質量
                                           ));
        _imgs[_imgs.size()-1]->appear();
    }
}

void gameWindow::oscSender(string s) {
    ofxOscMessage m;
    m.setAddress("/vacuum/garbageName");
    m.addStringArg(s);
    _sender.sendMessage(m);
}

void gameWindow::setMousePoint(ofPoint mp) {
    _mousePoint = mp;
}

void gameWindow::setParam(float vac, float gab) {
    _vacumPower = vac;
    
    cout << "power : " << _vacumPower << "\n";
    _garbageMass = gab;
}

string gameWindow::getChangeMode() {
    return _nextWindow;
}


void gameWindow::vacumeOn(Boolean f) {
    
    if (f) {
        _animationFlag = true;
        for (int i = 0; i < _imgs.size(); i++) {
            ofPoint targetXY = _imgs[i]->getCollisionXY();
            float targetR = _imgs[i]->getCollisionR();
            float diffR = targetR + _mouseCollisionR;
            
            float diffValue = sqrt(
                                   (targetXY.x - _mouseCollisionXY.x)*(targetXY.x - _mouseCollisionXY.x)+
                                   (targetXY.y - _mouseCollisionXY.y)*(targetXY.y - _mouseCollisionXY.y));
            if (diffValue < diffR) {
                _imgs[i]->setAnimeFlag(true);
            } else {
                //imgs[i]->setAnimeFlag(false);
            }
            
            if (_imgs[i]->getAnimeFlag() && diffValue > diffR*2.5) {
                _imgs[i]->setAnimeFlag(false);
            }
        }
    } else {
        _animationFlag = false;
    }
}


//以下keyやmouseイベント

//--------------------------------------------------------------
void gameWindow::keyPressed(int key){
    
    if (key == 'a') {
        _nextWindow = "menuWindow";
    }
    
    
    if(key == OF_KEY_RETURN || key == 'k' || key == 'j') {
        _animationFlag = true;
        for (int i = 0; i < _imgs.size(); i++) {
            ofPoint targetXY = _imgs[i]->getCollisionXY();
            float targetR = _imgs[i]->getCollisionR();
            float diffR = targetR + _mouseCollisionR;
            
            float diffValue = sqrt(
                                   (targetXY.x - _mouseCollisionXY.x)*(targetXY.x - _mouseCollisionXY.x)+
                                   (targetXY.y - _mouseCollisionXY.y)*(targetXY.y - _mouseCollisionXY.y));
            if (diffValue < diffR) {
                _imgs[i]->setAnimeFlag(true);
            } else {
                //imgs[i]->setAnimeFlag(false);
            }
            
            if (_imgs[i]->getAnimeFlag() && diffValue > diffR*2.5) {
                _imgs[i]->setAnimeFlag(false);
            }
        }
    }
    if(key == ' ') {
        for (int i = 0; i < _imgs.size(); i++) {
            _imgs[i]->imageReset();
            _imgs[i]->appear();
            oscSender("reset");
            _vacumPowerMeter = 0;
            _vacumedTotalMass = 0;
            
            _addVacumPower = 0;
            _vacumPower = 75;
        }
        
        init(_stage);
    }
    
    if(key == 'd') {
        _debugMode = !_debugMode;
        
        for (int i = 0; i < _imgs.size(); i++) {
            _imgs[i]->setDebugMode(_debugMode);
        }
    }
    
    if (key == 'j') {
        _mouseAngle += 5;
    } else if (key == 'k') {
        _mouseAngle -=5;
    }
    
    
    
    if (key == '1') {
        
        _imgs = _living;
        for (int i = 0; i < _imgs.size(); i++) {
            _imgs[i]->imageReset();
            _imgs[i]->appear();
        }
        back1.loadImage("back1.jpg");
    }
    
    if (key == '2') {
        _imgs = _storage;
        for (int i = 0; i < _imgs.size(); i++) {
            _imgs[i]->imageReset();
            _imgs[i]->appear();
        }
        back1.loadImage("back3.jpg");
    }
}

//--------------------------------------------------------------
void gameWindow::keyReleased(int key){
    if(key == OF_KEY_RETURN) {
        _animationFlag = false;
    }
    
}

//--------------------------------------------------------------
void gameWindow::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void gameWindow::mouseDragged(int x, int y, int button){
    
}


//--------------------------------------------------------------
void gameWindow::mousePressed(int x, int y, int button){
  
}

//--------------------------------------------------------------
void gameWindow::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------
void gameWindow::windowResized(int w, int h){
    
}


//--------------------------------------------------------------
void gameWindow::dragEvent(ofDragInfo dragInfo){
    
}
