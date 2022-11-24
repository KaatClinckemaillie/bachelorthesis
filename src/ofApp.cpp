#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
        
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    
    serial.setup(0, baud); //open the first device
    //serial.setup("COM10", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    //lightbol newLightbol;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //Simple if statement to inform user if Arduino is sending serial messages.
    if (serial.available() < 0) {
        sensorValue = "Arduino Error";
    }
    else {
        //While statement looping through serial messages when serial is being provided.
        while (serial.available() > 0) {
            byteData = serial.readByte();
            //position = byteData * 10;
        }
    }
    cout << position << endl; // output the sensorValue
    
    
    newLightbol.x--;
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofDrawCircle(150, position, 50);
    newLightbol.draw();
}

//--------------------------------------------------------------
lightbol::lightbol() {
    //constructor
    y = ofRandom(ofGetHeight());
    
};

//--------------------------------------------------------------
lightbol::~lightbol() {
    //deconstructor
}

//--------------------------------------------------------------
void lightbol::draw(){
    ofDrawCircle(x, y, radius);
}



