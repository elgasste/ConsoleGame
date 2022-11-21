#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IThread.h>

class mock_Thread : public ConsoleGame::IThread
{
public:
   MOCK_METHOD( bool, SetThisThreadToHighestPriority, ( ), ( const, override ) );
};
