#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>

#include "IConsoleDrawer.h"

namespace ConsoleGame
{
   class GameRenderConfig;
   enum class ConsoleColor;

   class ConsoleDrawer : public IConsoleDrawer
   {
   public:
      ConsoleDrawer( const std::shared_ptr<GameRenderConfig> renderConfig );
      ~ConsoleDrawer();

      void Initialize() override;
      void CleanUp() override;

      void SetDefaultForegroundColor( ConsoleColor color ) override;
      void SetDefaultBackgroundColor( ConsoleColor color ) override;
      void ClearDrawBuffer() override;

      void Draw( int left, int top, char buffer ) override;
      void Draw( int left, int top, char buffer, ConsoleColor foregroundColor ) override;
      void Draw( int left, int top, char buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor ) override;
      void Draw( int left, int top, const std::string& buffer ) override;
      void Draw( int left, int top, const std::string& buffer, ConsoleColor foregroundColor ) override;
      void Draw( int left, int top, const std::string& buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor ) override;

      void FlipDrawBuffer() override;

   private:
      void SetCursorVisibility( bool isVisible );
      unsigned short ConsoleColorsToAttribute( ConsoleColor foregroundColor, ConsoleColor backgroundColor );

   private:
      const std::shared_ptr<GameRenderConfig> _renderConfig;

      HANDLE _outputHandle;
      COORD _consoleSize;
      int _drawBufferSize;
      CHAR_INFO* _drawBuffer;
      SMALL_RECT _outputRect;
      COORD _zeroCoordinate = { 0, 0 };

      ConsoleColor _defaultForegroundColor;
      ConsoleColor _defaultBackgroundColor;
   };
}
