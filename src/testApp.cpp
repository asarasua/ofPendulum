#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    pendulum = new DoublePendulumItem();
    
    pendulum->setDt(0.005);
    pendulum->setG(9.81);
    
    pendulum->upper().theta = 0.8;
    pendulum->upper().omega = 0.0;
    pendulum->upper().m = 1.0;
    pendulum->upper().l = 1.0;
    
    pendulum->lower().theta = 0.5;
    pendulum->lower().omega = 0.0;
    pendulum->lower().m = 0.3;
    pendulum->lower().l = 0.6;
    
    pendulum->start();
    
    receiver.setup(3002);
    
    sender.setup("192.168.1.157", 2002);
    
    ofxOscMessage hello;
    hello.setAddress("/blo/hub/ext/gest/0");
    hello.addFloatArg(1.0);
    bundle.addMessage(hello);
    sender.sendBundle(bundle);
}

//--------------------------------------------------------------
void testApp::update(){
    pendulum->updateTime(ofGetElapsedTimeMillis());
    
    //process received messages
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        // check for mouse moved message
		if(m.getAddress() == "/blo/hub/ext/gest"){
            pendulum-> updateMass(m.getArgAsFloat(0), m.getArgAsFloat(1));
        }
    }
    
    //send messages
    bundle.clear();
    ofxOscMessage msg1;
    msg1.setAddress("/blo/hub/ext/gest/0");
    msg1.addFloatArg(pendulum->upper().m);
    bundle.addMessage(msg1);
    
    ofxOscMessage msg2;
    msg2.setAddress("/blo/hub/ext/gest/1");
    msg2.addFloatArg(pendulum->lower().m);
    bundle.addMessage(msg2);
    
    sender.sendBundle(bundle);
}

//--------------------------------------------------------------
void testApp::draw(){
    pendulum->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}