#pragma once

#include <memory>
#include <map>
#include <vector>

#include "IGameInputReader.h"

namespace ConsoleGame
{
   struct ButtonState
   {
      bool ButtonWasPressed;
      bool ButtonIsDown;
   };

   class KeyboardInputDefs;
   class IKeyboard;
   enum class KeyCode;
   enum class GameButton;

   class KeyboardInputReader : public IGameInputReader
   {
   public:
      KeyboardInputReader( const std::shared_ptr<KeyboardInputDefs> inputDefs,
                           const std::shared_ptr<IKeyboard> keyboard );

      void ReadInput() override;
      bool WasButtonPressed( GameButton button ) const override;
      bool IsButtonDown( GameButton button ) const override;
      bool WasAnyButtonPressed() const override;

   private:
      std::shared_ptr<IKeyboard> _keyboard;

      std::map<GameButton, ButtonState> _buttonStates;
      std::map<GameButton, std::vector<KeyCode>> _buttonKeyBindings;
   };
}
