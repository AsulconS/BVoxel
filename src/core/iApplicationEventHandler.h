#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "common.h"

class IApplicationEventHandler
{
public:
    IApplicationEventHandler() {}
    virtual ~IApplicationEventHandler() {}
    
    virtual void onKeyDown(uint32 keyCode, bool isRepeat) = 0;
    virtual void onKeyUp(uint32 keyCode, bool isRepeat) = 0;
    virtual void onMouseDown(uint32 mouseButton, uint8 numClicks) = 0;
    virtual void onMouseUp(uint32 mouseButton, uint8 numClicks) = 0;
    virtual void onMouseMove(int32 mousePosX, int32 mousePosY, int32 deltaX, int32 deltaY) = 0;
};

#endif // EVENT_HANDLER_H
