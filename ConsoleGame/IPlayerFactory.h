#pragma once

#include <memory>

namespace ConsoleGame
{
   class IPlayer;

   class __declspec( novtable ) IPlayerFactory
   {
   public:
      virtual const std::shared_ptr<IPlayer> CreatePlayer() const = 0;
   };
}
