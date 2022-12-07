#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    
    //size of laptop/beamer screen
    //beamer: 1980 x 1080
    settings.setSize(1024, 768);
    settings.setPosition(glm::vec2(300,0));
    settings.resizable = true;
    auto mainWindow = ofCreateWindow(settings);
    
    settings.setSize(1024,768);
    settings.setPosition(glm::vec2(0,0));
    settings.resizable = true;
    
    auto videoWindow = ofCreateWindow(settings);
    videoWindow->setVerticalSync(false);
    
    auto mainApp = make_shared<ofApp>();
    mainApp-> setupVideo();
    ofAddListener(videoWindow->events().draw, mainApp.get(), &ofApp::drawVideo);
    ofAddListener(videoWindow->events().update,mainApp.get(), &ofApp::updateVideo);
    
    //ofAddListener(guiWindow->events().draw,mainApp.get(),&ofApp::drawGui);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
	//ofSetupOpenGL(600,300,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());

}
