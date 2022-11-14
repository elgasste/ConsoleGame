#pragma once

#include <memory>

#include "IConsoleDrawer.h"

namespace ConsoleGame
{
   class GameRenderConfig;
   struct ConsoleBufferInfo;

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
      void Draw( int left, int top, const std::shared_ptr<ConsoleSprite> sprite ) override;

      void FlipDrawBuffer() override;

   private:
      void SetCursorVisibility( bool isVisible );
      unsigned short ConsoleColorsToAttribute( ConsoleColor foregroundColor, ConsoleColor backgroundColor );

   private:
      const std::shared_ptr<GameRenderConfig> _renderConfig;

      std::shared_ptr<ConsoleBufferInfo> _bufferInfo;

      ConsoleColor _defaultForegroundColor;
      ConsoleColor _defaultBackgroundColor;
   };
}
