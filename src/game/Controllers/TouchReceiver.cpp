#include "Precompiled.h"
#include "TouchReceiver.h"
#include "TouchManager.h"

TouchReceiver::~TouchReceiver()
{
    TouchManager::GetInstance()->removeReceiever(this);
}
