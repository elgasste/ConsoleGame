#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameInputReader.h>

enum class ConsoleGame::GameButton;

class mock_GameInputReader : public ConsoleGame::IGameInputReader
{
public:
   MOCK_METHOD( void, ReadInput, ( ), ( override ) );
   MOCK_METHOD( bool, WasButtonPressed, ( ConsoleGame::GameButton ), ( const, override ) );
   MOCK_METHOD( bool, IsButtonDown, ( ConsoleGame::GameButton ), ( const, override ) );
   MOCK_METHOD( bool, WasAnyButtonPressed, ( ), ( const, override ) );
};
