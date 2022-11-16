#pragma once

#include <gmock/gmock.h>

#include <ConsoleGame/IConsoleDrawer.h>

class mock_ConsoleDrawer : public ConsoleGame::IConsoleDrawer
{
public:
   MOCK_METHOD( void, Initialize, ( ), ( override ) );
   MOCK_METHOD( void, CleanUp, ( ), ( override ) );

   MOCK_METHOD( void, SetDefaultForegroundColor, ( ConsoleGame::ConsoleColor ), ( override ) );
   MOCK_METHOD( void, SetDefaultBackgroundColor, ( ConsoleGame::ConsoleColor ), ( override ) );
   MOCK_METHOD( void, ClearDrawBuffer, ( ), ( override ) );

   MOCK_METHOD( void, Draw, ( int, int, char ), ( override ) );
   MOCK_METHOD( void, Draw, ( int, int, char, ConsoleGame::ConsoleColor ), ( override ) );
   MOCK_METHOD( void, Draw, ( int, int, char, ConsoleGame::ConsoleColor, ConsoleGame::ConsoleColor ), ( override ) );
   MOCK_METHOD( void, Draw, ( int, int, const std::string& ), ( override ) );
   MOCK_METHOD( void, Draw, ( int, int, const std::string&, ConsoleGame::ConsoleColor ), ( override ) );
   MOCK_METHOD( void, Draw, ( int, int, const std::string&, ConsoleGame::ConsoleColor, ConsoleGame::ConsoleColor ), ( override ) );
   MOCK_METHOD( void, Draw, ( int, int, const ConsoleGame::ConsoleSprite& ), ( override ) );

   MOCK_METHOD( void, FlipDrawBuffer, ( ), ( override ) );
};
