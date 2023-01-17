#pragma once

#include "IFrameRateProvider.h"

namespace ConsoleGame
{
   class __declspec( novtable ) IGameClock : public IFrameRateProvider
   {
   public:
      virtual void StartFrame() = 0;
      virtual void EndFrame() = 0;
   };
}
