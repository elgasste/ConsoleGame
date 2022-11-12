#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IGameRenderer.h>

class mock_GameRenderer : public ConsoleGame::IGameRenderer
{
public:
   MOCK_METHOD( void, Render, ( ), ( override ) );
};
