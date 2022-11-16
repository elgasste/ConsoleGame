#pragma once

#include <string>
#include <memory>

namespace ConsoleGame
{
   enum class ConsoleColor;
   struct ConsoleSprite;

   class __declspec( novtable ) IConsoleDrawer
   {
   public:
      virtual void Initialize() = 0;
      virtual void CleanUp() = 0;

      virtual void SetDefaultForegroundColor( ConsoleColor color ) = 0;
      virtual void SetDefaultBackgroundColor( ConsoleColor color ) = 0;
      virtual void ClearDrawBuffer() = 0;

      virtual void Draw( int left, int top, char buffer ) = 0;
      virtual void Draw( int left, int top, char buffer, ConsoleColor foregroundColor ) = 0;
      virtual void Draw( int left, int top, char buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor ) = 0;
      virtual void Draw( int left, int top, const std::string& buffer ) = 0;
      virtual void Draw( int left, int top, const std::string& buffer, ConsoleColor foregroundColor ) = 0;
      virtual void Draw( int left, int top, const std::string& buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor ) = 0;
      virtual void Draw( int left, int top, const ConsoleSprite& sprite ) = 0;

      virtual void FlipDrawBuffer() = 0;
   };
}
