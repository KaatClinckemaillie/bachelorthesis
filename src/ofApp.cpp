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
    
    game_state = "start";
    score = 0;
    
    for(int i=0; i<4; i++){
        Player p;
        p.setup(colors[i][0],colors[i][1],colors[i][2], x_positions[i], (i+1) * 50, i);
        players.push_back(p);
    }
    
    
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
    
    if(game_state == "start"){
        
    }else if(game_state == "game") {
        update_lightbols();
        
    }else if(game_state == "end") {
        
    }
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofDrawCircle(150, position, 50);
    for (int i = 0; i < players.size(); i++) {
        players[i].draw();
    }
    
    if (game_state == "start") {
        
    } else if (game_state == "game") {
        
        for (int i = 0; i < lightbols.size(); i++) {
            lightbols[i].draw();
        }
        
    } else if (game_state == "end") {

    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(game_state == "start"){
        game_state = "game";
    }else if(game_state == "game"){
        // blank for now
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(game_state == "game"){
        if(key == ' '){
            Lightbol l;
            int colorIndex = ofRandom(5)-1;
            l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,1, 550, ofRandom(ofGetHeight()), colorIndex);
            lightbols.push_back(l);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update_lightbols(){
    for (int i = 0; i < lightbols.size(); i++) {
        lightbols[i].update();
    }
    
    check_lightbols_collision();
}

//--------------------------------------------------------------
void ofApp::check_lightbols_collision() {
    for (int i = 0; i < lightbols.size(); i++) {
        if(lightbols[i].pos.x < 0){
            lightbols.erase(lightbols.begin()+ i);
        }
    }
}



