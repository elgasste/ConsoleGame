#pragma once

namespace ConsoleGame
{
   enum class GameCommand;

   class _declspec( novtable ) IGameCommandExecutor
   {
   public:
      virtual void ExecuteCommand( GameCommand command ) = 0;
   };
}
