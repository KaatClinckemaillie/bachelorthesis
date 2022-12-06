//
//  Player.cpp
//  bachelor_thesis_JEF
//
//  Created by Kaat Clinckemaillie on 25/11/2022.
//

 
#include "Player.h"

void Player::setup(int r,int g,int b,int x, int y, int nr){
    player_nr = nr;
    color.set(r, g , b);
    pos.x = x;
    pos.y = y;
    ofSetCircleResolution(100);
}

void Player::update(){
    
}

void Player::draw(){
    ofSetColor(color);
    
    ofDrawCircle(pos.x, pos.y, radius);
}
