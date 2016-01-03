#include "ofApp.h"


/*
setup() -> update() -> draw() ->update() ->draw()...
*/

float imageWidth,imageHeight;
//--------------------------------------------------------------
void ofApp::setup(){
    
    //osc関係
    _receiver.setup( PORT );
    
    //arduino関係
   
    /*
    _arduino.setup("/dev/cu.usbserial-A6008kUC",9600);
    _pressureString = "";
    _pressureValue = 0;
    */
    
    
    
    
    //キャリブレーション関係////////////
    /*
    _vacuumPoint = ofPoint(0,0);
    _camWidth = 1280;
    _camHeight = 1024;
    _inputImage.allocate(_camWidth, _camHeight);//入力
	_outputImage.allocate(_camWidth, _camHeight);//出力
    
    //Grabberのデバイスidと大きさ設定
	_vidGrabber.setVerbose(true);
    _vidGrabber.setDeviceID(0);
	_vidGrabber.initGrabber(_camWidth, _camHeight);
    
    calibrationFlag = false;
    _targetR = 0;
    _targetG = 0;
    _targetB = 0;
    
    leftH = ofPoint(0,0);
    leftL = ofPoint(0,0);
    rightH = ofPoint(0,0);
    rightL = ofPoint(0,0);
    
    _cali.menuInit();
    _cali.initViewSize(_camWidth, _camHeight);
    */
    //////////////////////
    
    
    //param
    vacumPower = 75;
    garbageMass = 50;
    
    
    //ofInit
    ofEnableAlphaBlending();
    ofSetCircleResolution(64);
    ofSetFrameRate(60);
    ofBackground(0,0,0);
    
    //windownames = menuWindow, gameWindow, garbageSetWindow  ...
    _preWindow = "";
    _nowWindow = "menuWindow";
    
    vector<string> menuImagePath;
    vector<string> menuName;
    
    menuImagePath.push_back("menu1.png");
    menuImagePath.push_back("menu2.png");
    menuName.push_back("gameSelectWindow");
    menuName.push_back("garbageSetWindow");
    
    vector<string> gameMenuImagePath;
    vector<string> gameMenuName;
    
    gameMenuImagePath.push_back("stage1.png");
    gameMenuImagePath.push_back("stage2.png");
    gameMenuImagePath.push_back("stage3.png");
    gameMenuName.push_back("stage1");
    gameMenuName.push_back("stage2");
    gameMenuName.push_back("stage3");
    
    
    //各windowの初期化
    _gameW.setup("living", _arduino);
    _menuW.setup(menuImagePath, menuName, "menuWindow");
    _gameMenuW.setup(gameMenuImagePath,gameMenuName,"gameSelectWindow");
    
    _gSetW.setup();
    
    
    
}
//--------------------------------------------------------------


float toX = 0, toY = 0;
float ar = 4;
int cnt = 0;

float imageAngle = 0;
float imageX = 0;
float imageY = 0;
float alpha = 255;

float scaleX = 1;
float scaleY = 1;

Boolean animationFlag = false;


void ofApp::update(){
    
    //キャリブレーション関係
    /*
    _vidGrabber.update();
    //ofPixels &pixels =_vidGrabber.getPixelsRef();
    _inputImage.setFromPixels(_vidGrabber.getPixels(), _camWidth, _camHeight);
    
    _cali.setimg(_inputImage);
    
    _outputImage = _cali.getTransformedImage();
    
    if (_nowWindow == "calibration") {
        
    }
     */
    
    //arduinoの値取得
    
    serialDataUpdate();
    
    while( _receiver.hasWaitingMessages() )
    {
        //次のメッセージを取得
        ofxOscMessage m;
        _receiver.getNextMessage( &m );
        
        //マウスの位置を取得
        if (m.getAddress() == "/vacuum/position") {
            int vx = m.getArgAsInt32( 0 );
            int vy = m.getArgAsInt32( 1 );
            _vacuumPoint = ofPoint(vx,vy);
            cout << "x,y = " << vx << "," << vy << endl;
        }
    }
    
    if (_nowWindow == "menuWindow") {
        //_menuW.setMousePoint(ofPoint(mouseX,mouseY));
        _menuW.setMousePoint(_vacuumPoint);
        _menuW.update();
        _nowWindow = _menuW.getChangeMode();
    } else if(_nowWindow == "gameSelectWindow") {
        //_gameMenuW.setMousePoint(ofPoint(mouseX,mouseY));
        _gameMenuW.setMousePoint(_vacuumPoint);
        _gameMenuW.update();
        _nowWindow = _gameMenuW.getChangeMode();
    } else if (_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        //_gameW.setMousePoint(ofPoint(mouseX,mouseY));
        _gameW.setMousePoint(_vacuumPoint);
        _gameW.update();
        /*if(_pressureValue > 370) {
            int mag = 375 - _pressureValue;
            mag = 5 - mag;
            _gameW.setParam(vacumPower*mag*0.5, garbageMass);
        } else {
            _gameW.setParam(vacumPower, garbageMass);
        }*/
        _nowWindow = _gameW.getChangeMode();
    } else if(_nowWindow == "garbageSetWindow") {
        //_gSetW.setMousePoint(ofPoint(mouseX,mouseY));
        _gSetW.setMousePoint(_vacuumPoint);
        _gSetW.update();
        vacumPower = _gSetW.getVacumPower();
        garbageMass = _gSetW.getGarbageMass();
        _nowWindow = _gSetW.getChangeMode();
    }
    
    
    
    if (_preWindow != _nowWindow) {
        cout << "windowsがきりかわりました\n";
        
        if (_nowWindow == "menuWindow") {
            //選択したものの初期化
            _menuW.init();
            
            //その他のものの削除
            _gameW.deleteWindow();
            
        } else if(_nowWindow == "gameSelectWindow") {
            //選択したものの初期化
            _gameMenuW.init();
            
            //その他のものの削除
             _gameW.deleteWindow();
        } else if(_nowWindow == "stage1") {
            _gameW.init("living");
        } else if(_nowWindow == "stage2") {
            _gameW.init("storage");
        } else if(_nowWindow == "stage3") {
            _gameW.init("free");
            cout <<"freeeeeeeeeeeeeee\n";
        } else if(_nowWindow == "garbageSetWindow") {
            _gSetW.init();
            
            _gameW.deleteWindow();
        }
    }
    
    _preWindow = _nowWindow;
    
   
}

void ofApp::serialDataUpdate() {
    
    /*
    unsigned char buf[3] = {'o','f','!'};
    _arduino.writeBytes(&buf[0], 3);
    */
   // _arduino.writeByte('o');
    
    /*
    while (_arduino.available() > 0) {
        char byte = _arduino.readByte();
        
        if (byte == '\n') {
            cout << "<-ここまで\n";
            std::string ss = _pressureString;
            
            string keyword ="atsuryoku:";
            int tmp = ss.find(keyword);
            if (ss.find(keyword) != std::string::npos) {
                //cout <<  "検出位置 : " << tmp << "\n";
                cout <<  "検出内容 : " << ss.substr(keyword.length());
                _pressureValue = ofToInt(ss.substr(keyword.length()));
                
            }
            cout << "string : " + _pressureString + "\n";
            _pressureString = "";
        } else {
            _pressureString += byte;
        }
    }
    cout << "int : " << _pressureValue << "\n";
     */
}


//--------------------------------------------------------------


float px = 0;

float angle = 0;
void ofApp::draw(){
    
    //キャリブレーション関係
    /*
     
    if (_nowWindow == "calibration") {
        if (calibrationFlag) {
            //元映像を表示
            _vidGrabber.draw(0, 0);
            ofLine(0.0, 0.0, 300.0, 0.0);
            
            unsigned char* pixels = _vidGrabber.getPixels();
            _targetR = pixels[mouseY * 3 * _camWidth + mouseX*3];
            _targetG = pixels[mouseY * 3 * _camWidth + mouseX*3+1];
            _targetB = pixels[mouseY * 3 * _camWidth + mouseX*3+2];
            
            //キャリブレーションの枠
            ofLine(leftH.x, leftH.y, rightH.x, rightH.y);
            ofLine(rightH.x, rightH.y, rightL.x, rightL.y);
            ofLine(leftL.x, leftL.y, rightL.x, rightL.y);
            ofLine(leftH.x, leftH.y, leftL.x, leftL.y);
            ofSetColor(_targetR, _targetG, _targetB);
            ofRect(mouseX, mouseY, 50, 50);
            ofSetColor(255, 255, 255);
            
        } else {
            
            //黄色で重心を描画
            cvCircle (_outputImage.getCvImage(), cvPoint (_cali.getPx(), _cali.getPy()), 10, CV_RGB (0, 255, 255), -1, 8, 0);
            
            _outputImage.draw(0, 0);
            
            unsigned char* pixels = _outputImage.getPixels();
            _targetR = pixels[mouseY * 3 * _camWidth + mouseX*3];
            _targetG = pixels[mouseY * 3 * _camWidth + mouseX*3+1];
            _targetB = pixels[mouseY * 3 * _camWidth + mouseX*3+2];
            ofSetColor(_targetR, _targetG, _targetB);
            ofRect(mouseX, mouseY, 50, 50);
            ofSetColor(255, 255, 255);
        }
        _cali.menuDraw();
    }
     
    
    _vacuumPoint.x = _cali.getPx();
    _vacuumPoint.y = _cali.getPy();
    
    */
    
    if (_nowWindow == "menuWindow") {
        _menuW.draw();
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.draw();
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.draw();
    } else if(_nowWindow == "garbageSetWindow") {
        _gSetW.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    /*
    if (key == '0') {
        _nowWindow = "calibration";
    } else if (key == 'p') {
        _nowWindow = "menuWindow";
    }
     */
    
    /*
    if (_nowWindow == "calibration") {
        _cali.keyPressed(key);
        
        if (key == ' ') {
            calibrationFlag = true;
        }
        if (key == 'c') {
            _cali.setTargetColor(_targetR, _targetG, _targetB);
        }
    }
     */
    
    
    if (_nowWindow == "menuWindow") {
        _menuW.keyPressed(key);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.keyPressed(key);
    } else if(_nowWindow == "garbageSetWindow") {
        _gSetW.keyPressed(key);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.keyPressed(key);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (_nowWindow == "menuWindow") {
        _menuW.keyReleased(key);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.keyReleased(key);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.keyReleased(key);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    if (_nowWindow == "menuWindow") {
        _menuW.mouseMoved(x,y);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.mouseMoved(x,y);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.mouseMoved(x,y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (_nowWindow == "menuWindow") {
        _menuW.mouseDragged(x,y,button);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.mouseDragged(x,y,button);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.mouseDragged(x,y,button);
    }
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){
    /*
    
    if (_nowWindow == "calibration") {
        if (calibrationFlag) {
            switch (count) {
                case 0:
                    leftH.x = x;
                    leftH.y = y;
                    count = 1;
                    break;
                case 1:
                    rightH.x = x;
                    rightH.y = y;
                    count= 2;
                    break;
                case 2:
                    rightL.x = x;
                    rightL.y = y;
                    count = 3;
                    break;
                case 3:
                    leftL.x = x;
                    leftL.y = y;
                    count = 0;
                    calibrationFlag = false;
                    break;
                default:
                    break;
            }
            _cali.setpoint(leftH.x , leftH.y , rightH.x , rightH.y , rightL.x , rightL.y , leftL.x , leftL.y);
        }
    }
    */
    
    if (_nowWindow == "menuWindow") {
        _menuW.mousePressed(x,y,button);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.mousePressed(x,y,button);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.mousePressed(x,y,button);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (_nowWindow == "menuWindow") {
        _menuW.mouseReleased(x,y,button);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.mouseReleased(x,y,button);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.mouseReleased(x,y,button);
    }

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

    if (_nowWindow == "menuWindow") {
        _menuW.windowResized(w,h);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.windowResized(w,h);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.windowResized(w,h);
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    if (_nowWindow == "menuWindow") {
        _menuW.dragEvent(dragInfo);
    } else if(_nowWindow == "gameSelectWindow") {
        _gameMenuW.dragEvent(dragInfo);
    } else if(_nowWindow == "stage1" || _nowWindow == "stage2" || _nowWindow == "stage3") {
        _gameW.dragEvent(dragInfo);
    }

}