#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setupVideo(){
    ofSetBackgroundColor(0);
    ofSetVerticalSync(true);
    
    //load media
    introMovie.load("movies/intro.mp4");
    
}


//--------------------------------------------------------------
void ofApp::updateVideo(ofEventArgs & args){
    
    if(game_state == "introVideo"){
        introMovie.play();
        introMovie.update();
        
        
        
        if(introMovie.getPosition() >= 0.99){
            introMovie.stop();
            introMovie.close();
            game_state = "introGame";
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawVideo(ofEventArgs & args){
    ofSetColor(255);
    
    if (game_state == "start") {
        ofDrawBitmapString("screen for video", 100, 50);
        
    }else if (game_state == "introVideo") {
        ofSetColor(255);
        introMovie.draw(0, 0, 1200, 900);
        
    } else if (game_state == "game") {
    
    } else if (game_state == "end") {

    }
}



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel(OF_LOG_ERROR);
    //load media
    introLightmanMovie.load("movies/introLightman.mp4");
    countdownMovie.load("movies/countdown.mp4");
    instructionMovie.load("movies/countdown.mp4");
    
    neutralLightmanMovie.load("movies/neutralLightman.mp4");
    sadLightmanMovie.load("movies/sadLightman.mp4");
    happyLightmanMovie.load("movies/happyLightman.mp4");
    
    arrow.load("images/arrow.png");
    

    

    // connect with arduino
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup(0, baud); //open the first device
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example

    //setup game
    nulPos.x = (ofGetWidth() - width)/2;
    nulPos.y = (ofGetHeight() - height)/2;
    game_state = "start";
    score = 0;
    
    
    
    
    for(int i=0; i<4; i++){
        Player p;
        p.setup(colors[i][0],colors[i][1],colors[i][2], nulPos.x + x_positions[i], 20, i);
        players.push_back(p);
    }
    
    memset(bytesReadString, 0, 9);
    
}



//--------------------------------------------------------------
void ofApp::update(){

    
    nulPos.x = (ofGetWidth() - width)/2;
    nulPos.y = (ofGetHeight() -height)/2;
    
    

    if(serial.available()){
        unsigned char bytesReturned[8];
        
        memset(bytesReadString, 0, 9);
        memset(bytesReturned, 0, 8);
        
        memcpy(bytesReadString, bytesReturned, 8);
        serial.readBytes(bytesReturned, 8);
        string serialData = (char*) bytesReturned;
        positions = serialData;
        
        //firstCharacter= positions.substr(0, 2);
        //secondCharacter = positions.substr(2,2);

        update_players();
        serial.flush();
    }
   

    

    
    if(game_state == "start"){
        
    }else if(game_state=="introVideo"){
        
        
    }else if(game_state=="introGame"){
        introLightmanMovie.play();
        introLightmanMovie.update();
        
        if(introLightmanMovie.getPosition() >= 0.99){
            introLightmanMovie.stop();
            introLightmanMovie.close();
            game_state = "countdown";
            
        }
        
        
    }else if(game_state=="countdown"){
        
        countdownMovie.play();
        countdownMovie.update();
        
        if(countdownMovie.getPosition() >= 0.9){
            countdownMovie.stop();
            countdownMovie.close();
            
            neutralLightmanMovie.play();
            
            game_state = "game";
            
            
            // eerste lichtbol heel traag en animatie bij de bal
            // die geraakt moet worden, zodat duidelijk is
            // wat moet gebeuren
            add_lightbol();
        }


    }else if(game_state == "game") {
        
        update_lightman();
        
        if(catched_lightballs == 0){
            // show arrow at right position
            
        }
        
        
        if(level == 1){
            if(catched_lightballs == 10) {
                // start animation
                
                level == 2;
            }
            
            
        }else if(level == 2){
            float now = ofGetElapsedTimef();
            if(now > nextLightbolSeconds) {
                add_lightbol();
                nextLightbolSeconds = now + speed_nextLightball;
            }
        }else if(level == 3) {
            if(score > 30){
                float now = ofGetElapsedTimef();
                if(now > nextLightbolSeconds) {
                    add_lightbol();
                    nextLightbolSeconds = now + speed_nextLightball;
                }
            }else if(score >= 30){
                // stop all the lightman video's
                
                game_state == "end";
            }
        }
        update_lightbols();
        

    }else if(game_state == "end") {
        
    }
    
    
    
    
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    //ofDrawCircle(150, position, 50);
    ofSetColor(0);
    ofDrawRectangle(nulPos.x, nulPos.y, width, height);
    
    
    for (int i = 0; i < players.size(); i++) {
        players[i].draw();
    }
    
    
    if(game_state=="start"){
        ofDrawBitmapString("Pick your level", 1000, 500);
        
    }else if (game_state == "introGame") {
        ofSetColor(255);
        introLightmanMovie.draw(width/2 + nulPos.x, 0, width/2, width/2);
    }else if (game_state == "countdown") {
        ofSetColor(255);
        
        countdownMovie.draw(width/2 + nulPos.x, nulPos.y, 800, 800);
        
    }else if (game_state == "game") {
        //draw score
        ofDrawBitmapString("Score:",1500, 50);
        ofDrawBitmapString(ofToString(score), 1550, 50);
        ofDrawBitmapString("Catched lightballs:",1500, 70);
        ofDrawBitmapString(ofToString(catched_lightballs),1750, 70);
        ofDrawBitmapString("Level:",1500, 80);
        ofDrawBitmapString(ofToString(level), 1550, 80);
        
        
        //draw lightman
        draw_lightman();
        
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
void ofApp::keyReleased(int key){
    if(game_state == "start"){
        if(key == 'e'){
            game_mode = 1; //easy
            setup_game();
            game_state = "introVideo";
            playVideo = true;
            
        }
        if(key == 'm'){
            game_mode = 2; //medium
            setup_game();
            game_state = "introVideo";
        }
        if(key == 'h'){
            game_mode = 3; // hard
            setup_game();
            game_state = "introVideo";
        }
        
    }else if(game_state == "introVideo"){
        if(key == 's'){
            introMovie.close();
            game_state = "introGame";
        }
    }else if(game_state == "introGame"){
        if(key == 's'){
            introLightmanMovie.close();
            game_state = "countdown";
        }
        
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
        
        if(key == 'a'){
            players[0].pos.y -= 10;
        }
        if(key == 'q'){
            players[0].pos.y += 10;
        }
        if(key == 'z'){
            players[1].pos.y -= 10;
        }
        if(key == 's'){
            players[1].pos.y += 10;
        }
        if(key == 'e'){
            players[2].pos.y -= 10;
        }
        if(key == 'd'){
            players[2].pos.y += 10;
        }
        if(key == 'r'){
            players[3].pos.y -= 10;
        }
        if(key == 'f'){
            players[3].pos.y += 10;
        }
        
        if(key == 'm'){
            reset_game();
            
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::reset_game(){
    score = 0;
    catched_lightballs = 0;
    throwed_lightballs = 0;
    nextLightbolSeconds = 0;
    game_mode = 0;
    state_lightman = "neutral";
    
    
    //load media
    introMovie.load("movies/intro.mp4");
    
    introLightmanMovie.load("movies/introLightman.mp4");
    countdownMovie.load("movies/countdown.mp4");
    instructionMovie.load("movies/countdown.mp4");
    
    neutralLightmanMovie.load("movies/neutralLightman.mp4");
    sadLightmanMovie.load("movies/sadLightman.mp4");
    happyLightmanMovie.load("movies/happyLightman.mp4");
    
    game_state = "start";
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
    int marge = 40;
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
void ofApp::check_lightbols_collision() {
    for (int i = 0; i < lightbols.size(); i++) {
        
        //check borders
        if(lightbols[i].pos.y > nulPos.y + height || lightbols[i].pos.y < nulPos.y){
            lightbols[i].velo.y *= -1;
        }
        
        
        
        //check out of screen
        if(lightbols[i].pos.x < nulPos.x){
            lightbols.erase(lightbols.begin()+ i);
            if(catched_lightballs <= 9){
                add_lightbol();
            }
        }
        
        
        // check hit
        for(int j=0; j< players.size(); j++){
            
            // check if player hits lightball
            //nu wanneer 1/4 van de lichtbal samenvalt met een speler => gevangen!
            if(lightbols[i].pos.x - lightbols[i].radius / 2  < players[j].pos.x + players[j].radius && lightbols[i].pos.x  + lightbols[i].radius / 2 > players[j].pos.x - players[j].radius && lightbols[i].pos.y - lightbols[i].radius / 2< players[j].pos.y + players[j].radius && lightbols[i].pos.y + lightbols[i].radius / 2 > players[j].pos.y - players[j].radius){
                
                
                
                // check if color is equal (YES?: +++; NO?: ---;)
                if(players[j].player_nr == lightbols[i].colorIndex){
                    
                    // set lightman happy
                    state_lightman = "happy";
                    
                    // give positive feedback to player
                    players[j].color.set(0,255,0);
                    
                    //delete lightbol
                    lightbols.erase(lightbols.begin()+i);
                    
                    // add score
                    score ++;
                    catched_lightballs ++;
                    
                    // if still level 1, add lightbol
                    if(catched_lightballs <= 9){
                        add_lightbol();
                    }
                    //add light to ledstrip
                }else {
                    // set lightman sad
                    state_lightman = "sad";
                    
                    // give negative feedback to player
                    players[j].color.set(255,0,0);
                    
                    // delete lighboll
                    lightbols.erase(lightbols.begin()+i);
                    
                    //update score
                    catched_lightballs ++;
                    
                    if(catched_lightballs <= 9){
                        add_lightbol();
                    }
                    
                    //add light to ledstrip
                }
                
                update_level();
                
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
    
    if(catched_lightballs == 0){
        
        Lightbol firstLightbol;
        colorIndex = 0;
        firstLightbol.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,300, 0, nulPos.x + width, (nulPos.y + height)/2, colorIndex);
        lightbols.push_back(firstLightbol);
        
        
    }else if(catched_lightballs <= 5){
        
        l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,300, 0, nulPos.x + width, ofRandom(nulPos.y ,nulPos.y + height), colorIndex);
        lightbols.push_back(l);
        
        
    }else if(catched_lightballs > 5){
        
        l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,300, 1, nulPos.x + width, ofRandom(nulPos.y ,nulPos.y + height), colorIndex);
        lightbols.push_back(l);
    }
}

//--------------------------------------------------------------
void ofApp::setup_game(){
    level = 1;
    if(game_mode == 1){
        // snelheid lichtballen
        
        speed_nextLightball =3;
    }else if(game_mode == 2){
        // snelheid lichtballen
        
        speed_nextLightball = 5;
        
    }else if(game_mode == 3){
        // snelheid lichtballen
        
        speed_nextLightball = 3;
    }
}

//--------------------------------------------------------------
void ofApp::update_level(){
    
    if(catched_lightballs == 10){
        serial.writeByte('a');
        level = 2;
        
    }else if(catched_lightballs == 20){
        serial.writeByte('b');
        level = 3;
        
    }else if(catched_lightballs == 30){
        game_state = "end";
    }
}

//--------------------------------------------------------------

void ofApp::update_lightman(){
    
    if(neutralLightmanMovie.isPlaying()){
        neutralLightmanMovie.update();
    }
    
    if(state_lightman == "happy"){
        
        if(sadLightmanMovie.isPlaying()){
            sadLightmanMovie.setPaused(true);
            sadLightmanMovie.setPosition(0.01);
        }else{
            neutralLightmanMovie.setPaused(true);
            neutralLightmanMovie.setPosition(0.01);
        }
        
        happyLightmanMovie.play();
        state_lightman = "neutral";
    }
    
    if(state_lightman == "sad"){
        
        if(happyLightmanMovie.isPlaying()){
            happyLightmanMovie.setPaused(true);
            happyLightmanMovie.setPosition(0.01);
        }else{
            neutralLightmanMovie.setPaused(true);
            neutralLightmanMovie.setPosition(0.01);
        }
        
        
        
        
        sadLightmanMovie.play();
        state_lightman = "neutral";
    }
    
    if(happyLightmanMovie.isPlaying()){
        happyLightmanMovie.update();
        
        if(happyLightmanMovie.getPosition() >= 0.9){
            happyLightmanMovie.setPosition(0.01);
            happyLightmanMovie.setPaused(true);
            
            neutralLightmanMovie.setPaused(false);
        }
    }
    
    if(sadLightmanMovie.isPlaying()){
        sadLightmanMovie.update();
        
        if(sadLightmanMovie.getPosition() >= 0.9){
            sadLightmanMovie.setPosition(0.01);
            sadLightmanMovie.setPaused(true);
            
            neutralLightmanMovie.setPaused(false);
        }
    }
    
    // if state is changes, stop other lightman video's and play correct state video
    
    /*
    if(state_lightman == "happy"){
        stop_lightmanMovies();
        happyLightmanMovie.play();
    }
    
    if(state_lightman == "sad"){
     stop_lightmanMovies();
     sadLightmanMovie.play();
     }
    
    if(happyLightmanMovie.isPlaying()){
        happyLightmanMovie.update();
        if(happyLightmanMovie.getPosition() >= 0.95){
            happyLightmanMovie.stop();
            happyLightmanMovie.close();
            
            neutralLightmanMovie.play();
        }
    }else if(sadLightmanMovie.isPlaying()){
      sadLightmanMovie.update();
      if(sadLightmanMovie.getPosition() >= 0.95){
      sadLightmanMovie.stop();
      sadLightmanMovie.close();
      
      neutralLightmanMovie.play();
      }
    //}
    else {
        neutralLightmanMovie.update();
    }
    
    state_lightman = "neutral";
      */
}

//--------------------------------------------------------------

void ofApp::draw_lightman(){
    int sizeVideo = 200;
    
    if(neutralLightmanMovie.isPlaying()){
        ofSetColor(255);
        neutralLightmanMovie.draw(width - sizeVideo + nulPos.x, nulPos.y, sizeVideo, sizeVideo);
    }
    
    if(happyLightmanMovie.isPlaying()){
        ofSetColor(255);
        happyLightmanMovie.draw(width - sizeVideo + nulPos.x, nulPos.y, sizeVideo, sizeVideo);
    }
    
    if(sadLightmanMovie.isPlaying()){
        ofSetColor(255);
        sadLightmanMovie.draw(width - sizeVideo + nulPos.x, nulPos.y, sizeVideo, sizeVideo);
    }
    
    /*
    int sizeVideo = 100;
    
    if(neutralLightmanMovie.isPlaying()){
        neutralLightmanMovie.draw(width - sizeVideo + nulPos.x, nulPos.y, sizeVideo, sizeVideo);
        
    }else if(happyLightmanMovie.isPlaying()){
        happyLightmanMovie.draw(width - sizeVideo + nulPos.x, nulPos.y, sizeVideo, sizeVideo);
        
    }else if(sadLightmanMovie.isPlaying()){
        sadLightmanMovie.draw(width - sizeVideo + nulPos.x, nulPos.y, sizeVideo, sizeVideo);
    }
     */
    
}

//--------------------------------------------------------------
void ofApp:: stop_lightmanMovies(){
    if(happyLightmanMovie.isPlaying()){
        happyLightmanMovie.stop();
        happyLightmanMovie.close();
    }
    
    if(sadLightmanMovie.isPlaying()){
        sadLightmanMovie.stop();
        sadLightmanMovie.close();
    }
    
    if(neutralLightmanMovie.isPlaying()){
        neutralLightmanMovie.stop();
        neutralLightmanMovie.close();
    }
}
