#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    nulPos.x = (ofGetWidth() - width)/2;
    nulPos.y = (ofGetHeight()-height)/2;
    
    
    
    //ofSetFrameRate(60);
    
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
        p.setup(colors[i][0],colors[i][1],colors[i][2], nulPos.x + x_positions[i], 20, i);
        players.push_back(p);
    }
    
    memset(bytesReadString, 0, 5);
    
}
//--------------------------------------------------------------
void ofApp::setupVideo(){
    ofSetBackgroundColor(0);
}


//--------------------------------------------------------------
void ofApp::update(){

    
    nulPos.x = (ofGetWidth() - width)/2;
    nulPos.y = (ofGetHeight() -height)/2;
    
    serial.writeByte('a');

    if(serial.available()){
        unsigned char bytesReturned[4];
        
        memset(bytesReadString, 0, 5);
        memset(bytesReturned, 0, 4);
        
        memcpy(bytesReadString, bytesReturned, 4);
        serial.readBytes(bytesReturned, 4);
        string serialData = (char*) bytesReturned;
        positions = serialData;
        
        firstCharacter= positions.substr(0, 2);
        secondCharacter = positions.substr(2,2);

        update_players();
        
        
        
        serial.flush();
        // I think this whole loop is to find the end of the string and stop listening
        // Then when a new one starts in waits for it to finish
        
        
        
    }
   

    

    
    if(game_state == "start"){
        
    }else if(game_state == "game") {
        update_lightbols();
        float now = ofGetElapsedTimef();
        if(now > nextLightbolSeconds) {
            // do something here that should only happen every 5 seconds
            add_lightbol();
            nextLightbolSeconds = now + speed;
        }
        
    }else if(game_state == "end") {
        
    }
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofDrawCircle(150, position, 50);
    ofSetColor(0);
    ofDrawRectangle(nulPos.x, nulPos.y, width, height);
    
    
    
    ofDrawBitmapString(positions, 50, 100);
    ofDrawBitmapString(firstCharacter, 50, 120);
    ofDrawBitmapString(secondCharacter, 50, 130);
    ofDrawBitmapString(players[0].pos.y, 50, 200);
    ofDrawBitmapString(players[1].pos.y, 50, 210);
    
    for (int i = 0; i < players.size(); i++) {
        players[i].draw();
    }
    
    
    
    
   
    
    if (game_state == "intro") {
        
    } else if(game_state=="start"){
        ofDrawBitmapString("Pick your level", 500, 50);
        
    }else if (game_state == "game") {
        //draw score
        ofDrawBitmapString(ofToString(score), 500, 50);
        ofDrawBitmapString(ofToString(level), 500, 500);
        
        for (int i = 0; i < lightbols.size(); i++) {
            lightbols[i].draw();
        }
        
        if(level == 1){
            
        }else if(level == 2){
            
        }else if(level == 3){
            
        }
        
    } else if (game_state == "end") {

    }
}
//--------------------------------------------------------------
void ofApp::drawVideo(ofEventArgs & args){
    if (game_state == "start") {
        ofDrawBitmapString("screen for start video", 100, 50);
    } else if (game_state == "game") {
    
    } else if (game_state == "end") {

    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(game_state == "start"){
        if(key == 'w'){
            level = 1;
            game_state = "game";
        }
        if(key == 'x'){
            level = 2;
            game_state = "game";
        }
        if(key == 'c'){
            level = 3;
            game_state = "game";
        }
        
    }else if(game_state == "game"){
        // blank for now
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(game_state == "game"){
        /*if(key == ' '){
            Lightbol l;
            int colorIndex = ofRandom(5)-1;
            l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,1, 1, nulPos.x + width, ofRandom(nulPos.y ,nulPos.y + height), colorIndex);
            lightbols.push_back(l);
        }*/
        
        if(key== 'a'){
            players[0].pos.y -= 5;
        }
        if(key== 'q'){
            players[0].pos.y += 5;
        }
        if(key== 'z'){
            players[1].pos.y -= 5;
        }
        if(key== 's'){
            players[1].pos.y += 5;
        }
        if(key== 'e'){
            players[2].pos.y -= 5;
        }
        if(key== 'd'){
            players[2].pos.y += 5;
        }
        if(key== 'r'){
            players[3].pos.y -= 5;
        }
        if(key== 'f'){
            players[3].pos.y += 5;
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
void ofApp::update_players(){
    int marge = 20;
    for (int i = 0; i < players.size(); i++) {
        int num = floor((ofToInt(positions.substr(i * 2, 2)) * height)/ float(heightTable));
        
        // check if big difference, yes: change position, no: stay the same
        // to avoid 'flickering'
        if(num > players[i].pos.y + marge || num < players[i].pos.y - marge) {
            players[i].pos.y = num;
        }
        
    }
                                
}

//--------------------------------------------------------------
int ofApp::round_position(float num){
    float dec,numcpy;
    int n,last;
    numcpy=num;
    dec=num-floor(num);
    num=numcpy;
    n=floor(num);
    if(n%10<5)
    {
        n=(n/10)*10;
    }
    else if(n%10==5)
    {
        if(dec>0)
            n=(((n+10)/10)*10);
        else
            n=(n/10)*10;
    }
    else
    {
        n=(((n+10)/10)*10);
    }
    return n;

};

//--------------------------------------------------------------
void ofApp::check_lightbols_collision() {
    for (int i = 0; i < lightbols.size(); i++) {
        
        //check borders
        if(lightbols[i].pos.y > nulPos.y + height || lightbols[i].pos.y < nulPos.y){
            lightbols[i].velo.y *= -1;
        }
        
        
        
        //check out of screen
        if(lightbols[i].pos.x < nulPos.x){
            lightbols.erase(lightbols.begin()+ i);
        }
        
        
        // check hit
        for(int j=0; j< players.size(); j++){
            
            // check if player hits lightball
            //nu wanneer 1/4 van de lichtbal samenvalt met een speler => gevangen!
            if(lightbols[i].pos.x - lightbols[i].radius / 2  < players[j].pos.x + players[j].radius && lightbols[i].pos.x  + lightbols[i].radius / 2 > players[j].pos.x - players[j].radius && lightbols[i].pos.y - lightbols[i].radius / 2< players[j].pos.y + players[j].radius && lightbols[i].pos.y + lightbols[i].radius / 2 > players[j].pos.y - players[j].radius){
                
                
                // check if color is equal (YES?: +++; NO?: ---;)
                if(players[j].player_nr == lightbols[i].colorIndex){
                    players[j].color.set(0,255,0);
                    lightbols.erase(lightbols.begin()+i);
                    score ++;
                    catched_lightballs ++;
                    //add light to ledstrip
                }else {
                    players[j].color.set(255,0,0);
                    lightbols.erase(lightbols.begin()+i);
                    catched_lightballs ++;
                    //add light to ledstrip
                }
                
            }else{
                players[j].color.set(colors[j][0],colors[j][1],colors[j][2]);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

    nulPos.x = (ofGetWidth() - width)/2;
    nulPos.y = (ofGetHeight()-height)/2;
    
    for (int i = 0; i < players.size(); i++) {
        players[i].pos.x = nulPos.x + x_positions[i];
        players[i].pos.y = nulPos.y + (i+1) * 50;
    }
}

//--------------------------------------------------------------
void ofApp::add_lightbol(){
    Lightbol l;
    int colorIndex = ofRandom(5)-1;
    l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,1, 1, nulPos.x + width, ofRandom(nulPos.y ,nulPos.y + height), colorIndex);
    lightbols.push_back(l);
}

