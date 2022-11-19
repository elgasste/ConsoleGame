#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/Player.h>
#include <ConsoleGame/PlayerConfig.h>

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class PlayerTests : public Test
{
public:
   void SetUp() override
   {
      _config.reset( new PlayerConfig );
   }

   void BuildPlayer()
   {
      _player.reset( new Player( _config ) );
   }

protected:
   shared_ptr<PlayerConfig> _config;

   shared_ptr<Player> _player;
};

TEST_F( PlayerTests, Constructor_Always_SetsDefaultPropertiesFromConfig )
{
   _config->StartPositionX = 1;
   _config->StartPositionY = 2;
   _config->StartVelocityX = 3;
   _config->StartVelocityY = 4;
   _config->StartDirection = Direction::Right;

   BuildPlayer();

   EXPECT_EQ( _player->GetPositionX(), 1 );
   EXPECT_EQ( _player->GetPositionY(), 2 );
   EXPECT_EQ( _player->GetVelocityX(), 3 );
   EXPECT_EQ( _player->GetVelocityY(), 4 );
   EXPECT_EQ( _player->GetDirection(), Direction::Right );
}
