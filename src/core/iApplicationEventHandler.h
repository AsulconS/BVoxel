#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "common.h"

class IApplicationEventHandler
{
public:
    IApplicationEventHandler() {}
    virtual ~IApplicationEventHandler() {}
    
    virtual void onKeyDown(uint32 keyCode, bool isRepeat) {}
    virtual void onKeyUp(uint32 keyCode, bool isRepeat) {}
    virtual void onMouseDown(uint32 mouseButton, uint8 numClicks) {}
    virtual void onMouseUp(uint32 mouseButton, uint8 numClicks) {}
    virtual void onMouseMove(int32 mousePosX, int32 mousePosY, int32 deltaX, int32 deltaY) {}
};

#endif // EVENT_HANDLER_H
