#include <Arduino.h>
#define FRAME_BUFFER_LENGTH 24


extern void frameSequencerCallBack(uint8_t _frm);
extern void frameSequencerDone();

typedef void(*FunctionPtr)();
typedef struct{
	uint8_t frameID;
	uint16_t duration;
}frameInfo;

enum class FrameSequencerEvent {
  SEQUENCE_START,
  FRAME_START,
  FRAME_END,
  SEQUENCE_END
};

typedef void (*OnFrameSequencerEventCallback)();

class FrameSequencer{

	private:
	frameInfo* animationSequence[FRAME_BUFFER_LENGTH];
	// initFrames in constructor();

	bool forward;
	uint8_t framesCount, playHeadPosition;
	unsigned long currentTime, lastTime;
	frameInfo* currentFrame;
	
	frameInfo* newFrame;
	FunctionPtr callback;
	public:
	
	bool running = false;
	FrameSequencer();
	~FrameSequencer();
	void addFrame(uint8_t _frmID, uint16_t _duration);
	void startAnimation();
	void runAnimation();
	void printFrames();
	void initFrames();
	void clearAnimation();
    void animationDone();
};