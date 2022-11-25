//
//  Player.h
//  bachelor_thesis_JEF
//
//  Created by Kaat Clinckemaillie on 25/11/2022.
//

#pragma once
#include "ofMain.h"


class Player {
public:
    int radius = 20;
    ofPoint pos;
    ofColor color;
    int player_nr;
    
    void draw();
    void update();
    void setup(int r,int g,int b,int x, int y, int nr);
};
