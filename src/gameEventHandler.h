#ifndef GAME_EVENT_HANDLER_H
#define GAME_EVENT_HANDLER_H

#include "common.h"
#include "core/iApplicationEventHandler.h"
#include "inputControl.h"

class GameEventHandler : public IApplicationEventHandler
{
public:
    GameEventHandler() {}
    virtual ~GameEventHandler() {}
    
    virtual void onKeyDown(uint32 keyCode, bool isRepeat);
    virtual void onKeyUp(uint32 keyCode, bool isRepeat);
    virtual void onMouseDown(uint32 mouseButton, uint8 numClicks);
    virtual void onMouseUp(uint32 mouseButton, uint8 numClicks);
    virtual void onMouseMove(int32 mousePosX, int32 mousePosY, int32 deltaX, int32 deltaY);

    void addKeyControl(uint32 keyCode, InputControl& inputControl, float weight = 1.0f);
    void addMouseControl(uint32 mouseButton, InputControl& inputControl, float weight = 1.0f);
};

#endif // GAME_EVENT_HANDLER_H
