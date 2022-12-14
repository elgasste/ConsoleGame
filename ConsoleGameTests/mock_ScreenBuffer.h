#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IScreenBuffer.h>

class mock_ScreenBuffer : public ConsoleGame::IScreenBuffer
{
public:
   MOCK_METHOD( void, LoadRenderDefs, ( const std::shared_ptr<ConsoleGame::IGameRenderDefs> ), ( override ) );
   MOCK_METHOD( void, CleanUp, ( ), ( override ) );
   MOCK_METHOD( void, Clear, ( ), ( override ) );
   MOCK_METHOD( void, Flip, ( ), ( override ) );
};
