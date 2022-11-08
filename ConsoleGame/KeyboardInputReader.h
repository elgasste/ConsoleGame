#pragma once

#include <memory>
#include <map>

#include "IGameInputReader.h"

namespace ConsoleGame
{
   struct ButtonState
   {
      bool ButtonWasPressed;
      bool ButtonIsDown;
   };

   class GameInputConfig;
   enum class KeyCode;
   enum class GameButton;

   class KeyboardInputReader : public IGameInputReader
   {
   public:
      KeyboardInputReader( const std::shared_ptr<GameInputConfig>& inputConfig );

      void ReadInput() override;
      bool WasButtonPressed( GameButton button ) const override;
      bool IsButtonDown( GameButton button ) const override;
      bool WasAnyButtonPressed() const override;

   private:
      bool IsKeyDown( KeyCode key ) const;

   private:
      const std::shared_ptr<GameInputConfig>& _inputConfig;

      std::map<GameButton, ButtonState> _buttonStates;
   };
}
