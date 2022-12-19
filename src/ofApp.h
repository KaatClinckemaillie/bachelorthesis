#pragma once

#include "ofMain.h"
#include "Lightball.h"
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
    
    void update_lightballs();
    void check_lightballs_collision();
    void add_lightball();
    void update_players();
    int round_position(float num);
    void setup_game();
    void update_level();
    void draw_lightman();
    void update_lightman();
    void stop_lightmanMovies();
    void reset_game();
    void check_position_lightballs();
    void update_score(int indexPlayer, int indexLightball);
    void update_opacity();
    void draw_feedbackMovies();
    void update_feedbackMovies();
    
    int test = 0;
    
    //technical setup
    int heightTable = 38;
    
    
    //game setup
    int width = 1920;
    int height = 1080;
    ofPoint nulPos;
    string game_state; // start introVideo introGame countdown game levelUp end outro score
    
    int score = 0;
    int speed_nextLightball;
    int speed_lightballs;
    int catched_lightballs = 0;
    int throwed_lightballs = 0;
    float nextLightballSeconds = 0;
    int level;
    int game_mode; //easy medium hard
    string state_lightman = "neutral"; // neutral happy sad;

    int opacity = 255;
    bool increaseOpacity = false;
    
    
    int playerIndex; // index of player that scored/missed
    ofPoint positionHit;
    
    //media
    //video
    bool playVideo = false;
    ofVideoPlayer introMovie;
    ofVideoPlayer countdownMovie;
    ofVideoPlayer introLightmanMovie;
    ofVideoPlayer instructionMovie;
    ofVideoPlayer happyLightmanMovie;
    ofVideoPlayer sadLightmanMovie;
    ofVideoPlayer neutralLightmanMovie;
    ofVideoPlayer flicker1Movie;
    ofVideoPlayer scoreMovie;
    ofVideoPlayer loseMovie;
    ofVideoPlayer pickLevelMovie;
    ofVideoPlayer endscoreProjectionMovie;
    ofVideoPlayer endscoreMovie;
    //img
    ofImage pickLevelImg;
    ofImage levelUpImg;

    
    
    
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
    
    vector <Lightball> lightballs;
    vector <Player> players;
    
    // colors of the sticks and bolls
    // yellow , green, blue, pink
    int colors[4][3] = {{245, 215, 63},{1, 157, 89},{20, 37, 234},{253, 175, 221}};
    
    // hangt van de stokken van de tafel af
    int x_positions[4] = {151, 453, 755, 1057};
    
    
        
};
