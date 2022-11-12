#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IKeyboard.h>

class mock_Keyboard : public ConsoleGame::IKeyboard
{
public:
   MOCK_METHOD( bool, IsKeyDown, ( ConsoleGame::KeyCode ), ( const, override ) );
};
