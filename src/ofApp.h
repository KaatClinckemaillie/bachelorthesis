#pragma once

#include "ofMain.h"
#include "Lightbol.h"
#include "Player.h"



class ofApp : public ofBaseApp{

	
public:
    void setup();
    void setupVideo();
    void update();
    void updateVideo(ofEventArgs & args);
    void draw();
    void drawVideo(ofEventArgs & args);
    
    void keyReleased(int key);
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);
    void update_lightbols();
    void check_lightbols_collision();
    void add_lightbol();
    void update_players();
    int round_position(float num);
    void setup_game();
    void update_level();

    
    
    //technical setup
    int heightTable = 40;
    
    
    //game setup
    int width = 1220;
    int height = 680;
    ofPoint nulPos;
    string game_state; // start introVideo introGame instructions game end outro restart
    
    int score = 0;
    int speed_nextLightball;
    int catched_lightballs = 0;
    int throwed_lightballs = 0;
    float nextLightbolSeconds = 0;
    int level;
    int game_mode; //easy medium hard
    
    //media
    //video
    bool playVideo = false;
    ofVideoPlayer introMovie;
    ofVideoPlayer countdownMovie;
    ofVideoPlayer introLightmanMovie;
    ofVideoPlayer instructionMovie;
    //img
    ofImage arrow;

    
    
    
    // arduino
    ofSerial serial;

    char  bytesRead[8];  // data from serial, we will be trying to read 8
    char bytesReadString[9]; // a string needs a null terminator, so we need 8 + 1 bytes
    std::string positions;
    std::string prev_positions;
    std::string firstCharacter;
    std::string secondCharacter;
    
    

            
    
    //char byteData[4];
    int position = 50;
    
    vector <int> bytesData;
    
    vector <Lightbol> lightbols;
    vector <Player> players;
    
    // colors of the sticks and bolls
    // yellow , green, blue, pink
    int colors[4][3] = {{245, 215, 64},{1, 157, 89},{20, 37, 234},{253, 175, 221}};
    
    // hangt van de stokken van de tafel af
    int x_positions[4] = {50, 250, 450, 650};
    
    
        
};
