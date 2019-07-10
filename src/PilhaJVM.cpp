#include "PilhaJVM.h"



PilhaJVM::PilhaJVM() {
    
}

PilhaJVM::~PilhaJVM() {
    
}

void PilhaJVM::addFrame(Frame *frame) {
    // Verifica se a stack está cheia
//    if (_frameStack.size() >= FRAME_MAX_SIZE) {
//        cerr << "StackOverflowError" << endl;
//        exit(1);
//    }
    
    _frameStack.push(frame);
}

Frame* PilhaJVM::getTopFrame() {
    if (_frameStack.size() == 0) {
        return NULL;
    }
    
    return _frameStack.top();
}

bool PilhaJVM::destroyTopFrame() {
    if (_frameStack.size() == 0) {
        return false;
    }
    
    Frame *frame = _frameStack.top();
    _frameStack.pop();
    delete frame;
    
    return true;
}

uint32_t PilhaJVM::size() {
    return _frameStack.size();
}
