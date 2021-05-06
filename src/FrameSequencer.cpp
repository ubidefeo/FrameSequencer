#include "FrameSequencer.h"
FrameSequencer::FrameSequencer(){
	initFrames();
	forward = true;
}
FrameSequencer::~FrameSequencer(){
	clearAnimation();
}

void FrameSequencer::addFrame(uint8_t _frmID, uint16_t _duration){
	if(framesCount < FRAME_BUFFER_LENGTH){
		newFrame = new frameInfo();
		
		newFrame->frameID = _frmID;
		newFrame->duration = _duration;
		animationSequence[framesCount] = newFrame;
		framesCount++;
	}else{
		Serial.println(">>> ERROR: frame buffer FULL <<<");
	}

}
void FrameSequencer::startAnimation(){
	currentTime = lastTime = millis();
	playHeadPosition = 0;
	currentFrame = animationSequence[playHeadPosition];
	frameSequencerCallBack(currentFrame->frameID);
	running = true;
}

void FrameSequencer::runAnimation(){
	if(running){
		unsigned long ms = millis();
		currentFrame = animationSequence[playHeadPosition];
		if(ms - lastTime > currentFrame->duration){
			if(forward){

				if(playHeadPosition == framesCount-1){
					animationDone();
					return;	
				}

				playHeadPosition++;
			}else{
				if(playHeadPosition == 0){
					animationDone();
					return;
				}
				playHeadPosition--;
			}
			currentFrame = animationSequence[playHeadPosition];
			frameSequencerCallBack(currentFrame->frameID);
			lastTime = ms;
		}
		
	}

}

void FrameSequencer::printFrames(){
	frameInfo* curFrm;
	Serial.println("** FRAMES BEGIN**");
	Serial.println(framesCount);
	for(uint8_t frm = 0; frm < framesCount; frm++){
		curFrm = animationSequence[frm];
		Serial.println(curFrm->frameID);
		Serial.println(curFrm->duration);
	}
	Serial.println("** FRAMES END  **");
}

void FrameSequencer::initFrames(){
	for(uint8_t frm = 0; frm < FRAME_BUFFER_LENGTH; frm++){
		if(animationSequence[frm] != NULL){
			animationSequence[frm] = NULL;
		}
	}
	framesCount = 0;
}
void FrameSequencer::clearAnimation(){
	running = false;
	for(uint8_t frm = 0; frm < FRAME_BUFFER_LENGTH; frm++){
		if(animationSequence[frm] != NULL){
			free(animationSequence[frm]);
			animationSequence[frm] = NULL;
		}
	}
	framesCount = 0;
}

void FrameSequencer::animationDone(){
	running = false;
	lastTime = millis();
	//Serial.println("animation done");
	frameSequencerDone();
}