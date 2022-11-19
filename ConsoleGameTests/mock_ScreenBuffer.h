#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IScreenBuffer.h>

class mock_ScreenBuffer : public ConsoleGame::IScreenBuffer
{
public:
   MOCK_METHOD( void, Initialize, ( ), ( override ) );
   MOCK_METHOD( void, CleanUp, ( ), ( override ) );
   MOCK_METHOD( void, Clear, ( ), ( override ) );
   MOCK_METHOD( void, Flip, ( ), ( override ) );
};