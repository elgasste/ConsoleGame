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

      _config->StartVelocityX = 0;
      _config->StartVelocityY = 0;
      _config->MaxVelocityX = 10;
      _config->MaxVelocityY = 10;
      _config->VelocityDeltaX = 2;
      _config->VelocityDeltaY = 2;
      _config->StartDirection = Direction::Left;
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
   _config->StartVelocityX = 1;
   _config->StartVelocityY = 2;
   _config->StartDirection = Direction::Right;
   BuildPlayer();

   EXPECT_EQ( _player->GetVelocityX(), 1 );
   EXPECT_EQ( _player->GetVelocityY(), 2 );
   EXPECT_EQ( _player->GetDirection(), Direction::Right );
}

TEST_F( PlayerTests, Push_Always_SetsDirection )
{
   _config->StartDirection = Direction::Right;
   BuildPlayer();

   _player->Push( Direction::Up );

   EXPECT_EQ( _player->GetDirection(), Direction::Up );
}

TEST_F( PlayerTests, Push_LeftAndVelocityHasNotMaxedOut_DecreasesXVelocity )
{
   BuildPlayer();

   _player->Push( Direction::Left );

   EXPECT_EQ( _player->GetVelocityX(), -2 );
}

TEST_F( PlayerTests, Push_UpLeftAndVelocityHasNotMaxedOut_DecreasesXAndYVelocity )
{
   BuildPlayer();

   _player->Push( Direction::UpLeft );

   EXPECT_EQ( _player->GetVelocityX(), -2 );
   EXPECT_EQ( _player->GetVelocityY(), -2 );
}

TEST_F( PlayerTests, Push_UpAndVelocityHasNotMaxedOut_DecreasesYVelocity )
{
   BuildPlayer();

   _player->Push( Direction::Up );

   EXPECT_EQ( _player->GetVelocityY(), -2 );
}

TEST_F( PlayerTests, Push_UpRightAndVelocityHasNotMaxedOut_IncreasesXVelocityAndDecreasesYVelocity )
{
   BuildPlayer();

   _player->Push( Direction::UpRight );

   EXPECT_EQ( _player->GetVelocityX(), 2 );
   EXPECT_EQ( _player->GetVelocityY(), -2 );
}

TEST_F( PlayerTests, Push_RightAndVelocityHasNotMaxedOut_IncreasesXVelocity )
{
   BuildPlayer();

   _player->Push( Direction::Right );

   EXPECT_EQ( _player->GetVelocityX(), 2 );
}

TEST_F( PlayerTests, Push_DownRightAndVelocityHasNotMaxedOut_IncreasesXAndYVelocity )
{
   BuildPlayer();

   _player->Push( Direction::DownRight );

   EXPECT_EQ( _player->GetVelocityX(), 2 );
   EXPECT_EQ( _player->GetVelocityY(), 2 );
}

TEST_F( PlayerTests, Push_DownAndVelocityHasNotMaxedOut_IncreasesYVelocity )
{
   BuildPlayer();

   _player->Push( Direction::Down );

   EXPECT_EQ( _player->GetVelocityY(), 2 );
}

TEST_F( PlayerTests, Push_DownLeftAndVelocityHasNotMaxedOut_DecreasesXVelocityAndIncreasesYVelocity )
{
   BuildPlayer();

   _player->Push( Direction::DownLeft );

   EXPECT_EQ( _player->GetVelocityX(), -2 );
   EXPECT_EQ( _player->GetVelocityY(), 2 );
}

TEST_F( PlayerTests, Push_LeftAndVelocityHasMaxedOut_ClampsToMaxVelocity )
{
   _config->VelocityDeltaX = 11;
   BuildPlayer();

   _player->Push( Direction::Left );

   EXPECT_EQ( _player->GetVelocityX(), -10 );
}

TEST_F( PlayerTests, Push_RightAndVelocityHasMaxedOut_ClampsToMaxVelocity )
{
   _config->VelocityDeltaX = 11;
   BuildPlayer();

   _player->Push( Direction::Right );

   EXPECT_EQ( _player->GetVelocityX(), 10 );
}

TEST_F( PlayerTests, Push_UpAndVelocityHasMaxedOut_ClampsToMaxVelocity )
{
   _config->VelocityDeltaY = 11;
   BuildPlayer();

   _player->Push( Direction::Up );

   EXPECT_EQ( _player->GetVelocityY(), -10 );
}

TEST_F( PlayerTests, Push_DownAndVelocityHasMaxedOut_ClampsToMaxVelocity )
{
   _config->VelocityDeltaY = 11;
   BuildPlayer();

   _player->Push( Direction::Down );

   EXPECT_EQ( _player->GetVelocityY(), 10 );
}

TEST_F( PlayerTests, ApplyFrictionX_PlayerIsMovingLeftAndHasVelocityToSpare_DoesNotStop )
{
   BuildPlayer();

   _player->Push( Direction::Left );
   _player->Push( Direction::Left );
   _player->ApplyFrictionX();

   EXPECT_EQ( _player->GetVelocityX(), -2 );
}

TEST_F( PlayerTests, ApplyFrictionX_PlayerIsMovingRightAndHasVelocityToSpare_DoesNotStop )
{
   BuildPlayer();

   _player->Push( Direction::Right );
   _player->Push( Direction::Right );
   _player->ApplyFrictionX();

   EXPECT_EQ( _player->GetVelocityX(), 2 );
}

TEST_F( PlayerTests, ApplyFrictionY_PlayerIsMovingUpAndHasVelocityToSpare_DoesNotStop )
{
   BuildPlayer();

   _player->Push( Direction::Up );
   _player->Push( Direction::Up );
   _player->ApplyFrictionY();

   EXPECT_EQ( _player->GetVelocityY(), -2 );
}

TEST_F( PlayerTests, ApplyFrictionY_PlayerIsMovingDownAndHasVelocityToSpare_DoesNotStop )
{
   BuildPlayer();

   _player->Push( Direction::Down );
   _player->Push( Direction::Down );
   _player->ApplyFrictionY();

   EXPECT_EQ( _player->GetVelocityY(), 2 );
}

TEST_F( PlayerTests, ApplyFrictionX_PlayerIsMovingLeftAndHasNoVelocityToSpare_Stops )
{
   _config->StartVelocityX = -1;
   _config->MaxVelocityX = 2;
   BuildPlayer();

   _player->ApplyFrictionX();

   EXPECT_EQ( _player->GetVelocityX(), 0 );
}

TEST_F( PlayerTests, ApplyFrictionX_PlayerIsMovingRightAndHasNoVelocityToSpare_Stops )
{
   _config->StartVelocityX = 1;
   _config->MaxVelocityX = 2;
   BuildPlayer();

   _player->ApplyFrictionX();

   EXPECT_EQ( _player->GetVelocityX(), 0 );
}

TEST_F( PlayerTests, ApplyFrictionY_PlayerIsMovingUpAndHasNoVelocityToSpare_Stops )
{
   _config->StartVelocityY = -1;
   _config->MaxVelocityY = 2;
   BuildPlayer();

   _player->ApplyFrictionY();

   EXPECT_EQ( _player->GetVelocityY(), 0 );
}

TEST_F( PlayerTests, ApplyFrictionY_PlayerIsMovingDownAndHasNoVelocityToSpare_Stops )
{
   _config->StartVelocityY = 1;
   _config->MaxVelocityY = 2;
   BuildPlayer();

   _player->ApplyFrictionY();

   EXPECT_EQ( _player->GetVelocityY(), 0 );
}

TEST_F( PlayerTests, StopX_Always_SetsXVelocityToZero )
{
   BuildPlayer();

   _player->Push( Direction::Right );
   _player->StopX();

   EXPECT_EQ( _player->GetVelocityX(), 0 );
}

TEST_F( PlayerTests, StopY_Always_SetsYVelocityToZero )
{
   BuildPlayer();

   _player->Push( Direction::Up );
   _player->StopY();

   EXPECT_EQ( _player->GetVelocityY(), 0 );
}
