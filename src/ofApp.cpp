#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setupVideo(){
    ofSetBackgroundColor(0);
    ofSetVerticalSync(true);
    
    //load media
    introMovie.load("movies/intro.mp4");
    flicker1Movie.load("movies/flicker1.mp4");
    flicker2Movie.load("movies/flicker2.mp4");
    outroMovie.load("movies/outro.mp4");
    
    font.load("BebasNeue-Regular.ttf", 180);
    
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
            serial.writeByte('c');
            
            
        }
     }else if(game_state == "flicker"){
        if(level == 2){
            flicker1Movie.play();
            flicker1Movie.update();
            
            if(flicker1Movie.getPosition() >= 0.95){
                flicker1Movie.stop();
                game_state = "game";
            }
        }
        
        if(level == 3){
            flicker1Movie.close();

            flicker2Movie.play();
            flicker2Movie.update();
            
            if(flicker2Movie.getPosition() >= 0.95){
                flicker2Movie.stop();
                game_state = "game";
            }
        }
     }else if(game_state == "outro" || game_state == "score"){
         
         // video outro
         outroMovie.play();
         outroMovie.update();
         
         if(outroMovie.getPosition() >= 0.51){
             game_state = "score";
             endScore = ofToString(score) + "/30";
         }
         
         if(outroMovie.getPosition() >= 0.95){
             outroMovie.stop();
             outroMovie.close();
             
             reset_game();
         }
     }
        
    
}

//--------------------------------------------------------------
void ofApp::drawVideo(ofEventArgs & args){
    
    if (game_state == "start") {
        ofDrawBitmapString("screen for video", 100, 50);
        
    }else if (game_state == "introVideo") {
        ofSetColor(255);
        introMovie.draw(0, 0, ofGetWidth(), ofGetWidth() * 9 / 16);
        
    } else if (game_state == "flicker" || game_state == "game") {
        ofSetColor(255);
        
        if(level == 2){
            flicker1Movie.draw(0, 0, ofGetWidth(), ofGetWidth() * 9 / 16);
        }
        if(level == 3){
            flicker2Movie.draw(0, 0, ofGetWidth(), ofGetWidth() * 9 / 16);
        }
    
    } else if (game_state == "outro" || game_state == "score") {
        ofSetColor(255);
        outroMovie.draw(0, 0, ofGetWidth(), ofGetWidth() * 9 / 16);
    }
    
    if(game_state == "score"){
        ofSetColor(255);
        font.drawString(endScore, ofGetWidth()/2 - font.stringWidth(endScore)/2, ofGetHeight()/2 + font.stringHeight(endScore)/2);
    }
}



//--------------------------------------------------------------
void ofApp::setup(){

    //load media
    introLightmanMovie.load("movies/introLightman.mp4");
    countdownMovie.load("movies/countdown.mp4");
    instructionMovie.load("movies/countdown.mp4");
    
    neutralLightmanMovie.load("movies/neutralLightman.mp4");
    sadLightmanMovie.load("movies/sadLightman.mp4");
    happyLightmanMovie.load("movies/happyLightman.mp4");
    
    scoreMovie.load("movies/score.mp4");
    loseMovie.load("movies/lose.mp4");
    
    
    pickLevelMovie.load("movies/pickLevel.mp4");
    levelUpMovie.load("movies/levelUp.mp4");
    
    endMovie.load("movies/end.mp4");
    
    
    //endscoreProjectionMovie.load("movies/endscoreProjection.mp4");
    

    

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
    
    

    if(serial.available() < 0){
        
    }else {
        
        while(serial.available() > 0){
            unsigned char bytesReturned[8];
            
            memset(bytesReadString, 0, 9);
            memset(bytesReturned, 0, 8);
            
            memcpy(bytesReadString, bytesReturned, 8);
            serial.readBytes(bytesReturned, 8);
            string serialData = (char*) bytesReturned;
            positions = serialData;
            
            test ++;
            update_players();
            
            firstCharacter= positions.substr(0, 2);
            secondCharacter = positions.substr(2,2);
            serial.flush();
        }
    }
   

    

    
    if(game_state == "start"){
        pickLevelMovie.play();
        pickLevelMovie.update();
        
    }else if(game_state =="introVideo"){
        pickLevelMovie.stop();
        pickLevelMovie.close();
        
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
            serial.writeByte('d');
            
            
            // eerste lichtbol heel traag en animatie bij de bal
            // die geraakt moet worden, zodat duidelijk is
            // wat moet gebeuren
            add_lightball();
        }


    }else if(game_state == "game") {
        
        update_feedbackMovies();
        update_lightman();
        
        if(catched_lightballs == 0){
            // show arrow at right position
            
        }
        
        if(level == 1){

        }else if(level == 2){
            float now = ofGetElapsedTimef();
            if(now > nextLightballSeconds) {
                add_lightball();
                nextLightballSeconds = now + speed_nextLightball;
            }
            
            
        }else if(level == 3) {
            if(catched_lightballs < 30){
                float now = ofGetElapsedTimef();
                if(now > nextLightballSeconds) {
                    add_lightball();
                    nextLightballSeconds = now + speed_nextLightball;
                }
                update_opacity();
            
            
            }else if(catched_lightballs >= 30){
                opacity = 0;
                // stop all the lightman video's
            
            }
            
            
        }
        update_lightballs();
        

    }else if(game_state == "levelUp"){
        
        levelUpMovie.update();
        
        if(levelUpMovie.getPosition() >= 0.95){
            levelUpMovie.setPaused(true);
            game_state = "flicker";
        }
        
    }else if(game_state == "end") {
        
        endMovie.play();
        endMovie.update();
        
        if(endMovie.getPosition() >= 0.9){
            endMovie.setPaused(true);
            game_state = "outro";
        }
        
        
    }else if(game_state == "score"){
        // display score for 10 sec
        
        //restart
    }
    
    
    
    
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    //ofDrawCircle(150, position, 50);
    ofSetColor(0);
    ofDrawRectangle(nulPos.x, nulPos.y, width, height);
    
    ofSetColor(255);
    ofDrawBitmapString(loseMovie.getPosition(), 50, 100);
    ofDrawBitmapString(scoreMovie.getPosition(), 50, 150);
    ofDrawBitmapString(game_state, 50, 200);
    //ofDrawBitmapString(secondCharacter, 50, 130);
    //ofDrawBitmapString(ofToString(test), 50, 150);
    //ofDrawBitmapString(players[0].pos.y, 50, 200);
    //ofDrawBitmapString(players[1].pos.y, 50, 210);
    
    
    
    
    if(game_state=="start"){
        //ofDrawBitmapString("Pick your level", 1000, 500);
        ofSetColor(255);
        pickLevelMovie.draw(nulPos.x + width - sizeVideoWidth , nulPos.y + height/2 - sizeVideoHeight/2, sizeVideoWidth, sizeVideoHeight);
        
    }else if (game_state == "introGame") {
        ofSetColor(255);
        introLightmanMovie.draw(width/2 + nulPos.x, 0 + nulPos.y, 800, 800);
    }else if (game_state == "countdown") {
        ofSetColor(255);
        countdownMovie.draw(nulPos.x + width - sizeVideoWidth , nulPos.y + height/2 - sizeVideoHeight/2, sizeVideoWidth, sizeVideoHeight);
        
    }else if (game_state == "game") {

        
        for (int i = 0; i < lightballs.size(); i++) {
            lightballs[i].draw();
        }
        
        if(level == 1){
            
            
        }else if(level == 2){
            
        }else if(level == 3){
            ofEnableAlphaBlending();
            ofSetColor(0,0,0,opacity);
            ofDrawRectangle(nulPos.x, nulPos.y, width, height);
            ofDisableAlphaBlending();
        }
        
        
        //draw lightman
        draw_lightman();
        draw_feedbackMovies();
        
        
    } else if (game_state == "levelUp" || game_state == "flicker") {
        ofSetColor(255);
        int size_x = 782;
        int size_y = 1080;
        levelUpMovie.draw(nulPos.x + width - sizeVideoWidth , nulPos.y + height/2 - sizeVideoHeight/2, sizeVideoWidth, sizeVideoHeight);
    }
    
    for (int i = 0; i < players.size(); i++) {
        players[i].draw();
    }
    
    if(game_state == "end" || game_state == "outro"){
        endMovie.draw(nulPos.x, nulPos.y, width, height);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(game_state == "start"){
        if(key == 'e'){
            game_mode = 1; //easy
            setup_game();
            game_state = "introVideo";
            serial.writeByte('b');
            playVideo = true;
            
        }
        if(key == 'i'){
            game_mode = 2; //medium
            setup_game();
            game_state = "introVideo";
            serial.writeByte('b');
            playVideo = true;
        }
        if(key == 'h'){
            game_mode = 3; // hard
            setup_game();
            game_state = "introVideo";
            serial.writeByte('b');
            playVideo = true;
        }
        
    }else if(game_state == "introVideo"){
        if(key == 's'){
            introMovie.close();
            game_state = "introGame";
            serial.writeByte('c');
        }
    }else if(game_state == "introGame"){
        if(key == 's'){
            introLightmanMovie.close();
            game_state = "countdown";
        }
        
    }else if(game_state == "score"){
        outroMovie.stop();
        outroMovie.close();
        reset_game();
    }
    

    if(game_state == "game"){
        /*if(key == ' '){
            lightball l;
            int colorIndex = ofRandom(5)-1;
            l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,1, 1, nulPos.x + width, ofRandom(nulPos.y ,nulPos.y + height), colorIndex);
            lightballs.push_back(l);
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
        if(key == 'n'){
            reset_game();
            
            
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
void ofApp::reset_game(){
    serial.writeByte('r');
    score = 0;
    catched_lightballs = 0;
    throwed_lightballs = 0;
    nextLightballSeconds = 0;
    game_mode = 0;
    state_lightman = "neutral";
    lightballs.clear();
    
    
    //load media
    introMovie.load("movies/intro.mp4");
    flicker1Movie.load("movies/flicker1.mp4");
    endscoreMovie.load("movies/endscoreScreen.mp4");
    
    introLightmanMovie.load("movies/introLightman.mp4");
    countdownMovie.load("movies/countdown.mp4");
    instructionMovie.load("movies/countdown.mp4");
    
    neutralLightmanMovie.load("movies/neutralLightman.mp4");
    sadLightmanMovie.load("movies/sadLightman.mp4");
    happyLightmanMovie.load("movies/happyLightman.mp4");
    
    pickLevelMovie.load("movies/pickLevel.mp4");
    
    
    
    game_state = "start";
}

//--------------------------------------------------------------
void ofApp::update_lightballs(){
    for (int i = 0; i < lightballs.size(); i++) {
        lightballs[i].update();
    }
    
    check_lightballs_collision();
}

//--------------------------------------------------------------
void ofApp::add_lightball(){
    Lightball l;
    int colorIndex = ofRandom(5)-1;
    int marge = 50;
    
    // first ball with instructions
    if(catched_lightballs == 0){
        
        Lightball firstlightball;
        colorIndex = 0;
        firstlightball.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,speed_lightballs, 0, nulPos.x + width, (nulPos.y + height)/2, colorIndex);
        lightballs.push_back(firstlightball);
        
        
    }else if(catched_lightballs < 5){
        
        l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,speed_lightballs, 0, nulPos.x + width, ofRandom(nulPos.y +  marge ,nulPos.y + height - marge), colorIndex);
        lightballs.push_back(l);
        
        
    }else if(catched_lightballs >= 5){
        
        l.setup(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2] ,speed_lightballs,ofRandom(150), nulPos.x + width, ofRandom(nulPos.y +  marge ,nulPos.y + height - marge), colorIndex);
        lightballs.push_back(l);
    }
}

//--------------------------------------------------------------
void ofApp::update_players(){
    int marge = 50;
    
    for (int i = 0; i < players.size(); i++) {
        
        // substract de numbers from string + mirror
        int getPosition = maxPosSensor + minPosSensor - ofToInt(positions.substr(i * 2, 2));
        
        // correct ratio
        int num = floor((getPosition * height)/ float(maxPosSensor));
        
        
        if(num < minPosSensor){
            num = minPosSensor + players[i].radius;
        }else if(num > maxPosSensor){
            num = maxPosSensor - players[i].radius;
        }
        
        
        
        
        // check if big difference, yes: change position, no: stay the same
        // to avoid 'flickering'
        if(num > players[i].pos.y + marge || num < players[i].pos.y - marge) {
            
            
            int newPosition = num + nulPos.y;
            
            if(newPosition + players[i].radius > nulPos.y + height ){
                players[i].pos.y = nulPos.y + height - players[i].radius;
            }else if(newPosition - players[i].radius < nulPos.y){
                players[i].pos.y = nulPos.y + players[i].radius;
            }else{
                players[i].pos.y = newPosition;
            }
            
        }
        
    }
                                
}


//--------------------------------------------------------------
void ofApp::check_lightballs_collision() {
    for (int i = 0; i < lightballs.size(); i++) {
        
        //check borders
        if(lightballs[i].pos.y + lightballs[i].radius > nulPos.y + height || lightballs[i].pos.y - lightballs[i].radius < nulPos.y){
            lightballs[i].velo.y *= -1;
        }
        
        
        
        //check out of screen
        if(lightballs[i].pos.x < nulPos.x){
            lightballs.erase(lightballs.begin()+ i);
            if(catched_lightballs <= 9){
                add_lightball();
            }
        }
        
        
        // check hit
        for(int j=0; j< players.size(); j++){
            
            // check if player hits lightball
            //nu wanneer 1/4 van de lichtbal samenvalt met een speler => gevangen!
            if(lightballs[i].pos.x - lightballs[i].radius / 2  < players[j].pos.x + players[j].radius && lightballs[i].pos.x  + lightballs[i].radius / 2 > players[j].pos.x - players[j].radius && lightballs[i].pos.y - lightballs[i].radius / 2< players[j].pos.y + players[j].radius && lightballs[i].pos.y + lightballs[i].radius / 2 > players[j].pos.y - players[j].radius){
                
                update_score(j, i);
                update_level();
                
            }else{
                players[j].color.set(colors[j][0],colors[j][1],colors[j][2]);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update_score(int indexPlayer, int indexLightball){
    // check if color is equal (YES?: +++; NO?: ---;)
    if(players[indexPlayer].player_nr == lightballs[indexLightball].colorIndex){
        
        // set lightman happy
        state_lightman = "happy";
        
        // give positive feedback to player
        positionHit.x = players[indexPlayer].pos.x;
        positionHit.y = players[indexPlayer].pos.y;
        scoreMovie.play();
        
        //delete lightball
        lightballs.erase(lightballs.begin()+indexLightball);
        
        // add score
        score ++;
        catched_lightballs ++;
        
        //add light to ledstrip
        serial.writeByte('e');
        
        // if still level 1, add lightball
        if(catched_lightballs <= 9){
            add_lightball();
        }
        
        
    }else {
        // set lightman sad
        state_lightman = "sad";
        
        // give negative feedback to player
        positionHit.x = players[indexPlayer].pos.x;
        positionHit.y = players[indexPlayer].pos.y;
        loseMovie.play();
        
        // delete lighboll
        lightballs.erase(lightballs.begin()+indexLightball);
        
        //update score
        catched_lightballs ++;
        
        //add light to ledstrip
        serial.writeByte('f');
        
        
        if(catched_lightballs <= 9){
            add_lightball();
        }
        
        
    }
}


//--------------------------------------------------------------
void ofApp::setup_game(){
    level = 1;
    if(game_mode == 1){
        // snelheid lichtballen
        speed_lightballs = 300;

        speed_nextLightball =4;
    }else if(game_mode == 2){
        // snelheid lichtballen
        speed_lightballs = 400;
        speed_nextLightball = 2;

    }else if(game_mode == 3){
        // snelheid lichtballen
        speed_lightballs = 500;
        speed_nextLightball = 1;
    }
}

//--------------------------------------------------------------
void ofApp::update_level(){
    
    if(catched_lightballs == 10){
        serial.writeByte('a');
        level = 2;
        game_state = "levelUp";
        
        scoreMovie.setPaused(true);
        scoreMovie.setPosition(0.1);
        
        loseMovie.setPaused(true);
        loseMovie.setPosition(0.1);
        
        levelUpMovie.setPosition(0.1);
        levelUpMovie.play();

        
    }else if(catched_lightballs == 20){
        serial.writeByte('b');
        level = 3;
        game_state = "levelUp";
        
        scoreMovie.setPaused(true);
        scoreMovie.setPosition(0.1);
        
        loseMovie.setPaused(true);
        loseMovie.setPosition(0.1);
        
        levelUpMovie.setPosition(0.1);
        levelUpMovie.play();
    
        
    }else if(catched_lightballs == 30){
        game_state = "end";
        
        scoreMovie.close();
        loseMovie.close();
        
    }
}

//--------------------------------------------------------------

void ofApp::update_lightman(){
    
    if(neutralLightmanMovie.isPlaying()){
        neutralLightmanMovie.update();
    }
    
    if(state_lightman == "happy"){
        
        stop_lightmanMovies();
        
        happyLightmanMovie.play();
        state_lightman = "neutral";
    }
    
    if(state_lightman == "sad"){
        
        stop_lightmanMovies();
        
        
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

    
}

//--------------------------------------------------------------
void ofApp:: stop_lightmanMovies(){
    if(sadLightmanMovie.isPlaying()){
        sadLightmanMovie.setPaused(true);
        sadLightmanMovie.setPosition(0.01);
    }else if(happyLightmanMovie.isPlaying()){
        happyLightmanMovie.setPaused(true);
        happyLightmanMovie.setPosition(0.01);
    }else{
        neutralLightmanMovie.setPaused(true);
        neutralLightmanMovie.setPosition(0.01);
    }
}


//--------------------------------------------------------------
void ofApp:: update_opacity(){
    if(increaseOpacity){
        opacity += 1;
    }else{
        opacity -= 1;
    }
    
    if(opacity == 255 || opacity == 0){
        increaseOpacity = !increaseOpacity;
    }
}


//--------------------------------------------------------------
void ofApp:: draw_feedbackMovies(){
    
    int sizeVideo = 500;
    
    if(scoreMovie.isPlaying()){
        ofSetColor(255);
        scoreMovie.draw(positionHit.x - sizeVideo/2, positionHit.y-sizeVideo/2, sizeVideo, sizeVideo);
    }
    
    if(loseMovie.isPlaying()){
        ofSetColor(255);
        loseMovie.draw(positionHit.x - sizeVideo/2, positionHit.y-sizeVideo/2, sizeVideo, sizeVideo);
    }
}

//--------------------------------------------------------------
void ofApp:: update_feedbackMovies(){
    

        if(scoreMovie.isPlaying()){
            scoreMovie.update();
            
            if(scoreMovie.getPosition() >= 0.8 || game_state != "game"){
                scoreMovie.setPaused(true);
                scoreMovie.setPosition(0.01);
            }
        }
        
        if(loseMovie.isPlaying()){
            loseMovie.update();
            
            if(loseMovie.getPosition() >= 0.8 || game_state != "game"){
                loseMovie.setPaused(true);
                loseMovie.setPosition(0.01);
            }
        }
    
}
