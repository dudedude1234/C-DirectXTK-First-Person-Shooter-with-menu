#include "pch.h"
#include "Gameplay.h"
#include "pch.h"




using namespace concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;

namespace
{
    const XMVECTORF32 START_POSITION = { 0.f, -1.5f, 0.f, 0.f };
    const XMVECTORF32 ROOM_BOUNDS = { 8.f, 6.f, 12.f, 0.f };
    constexpr float ROTATION_GAIN = 0.004f;
    constexpr float MOVEMENT_GAIN = 0.07f;
}

Gameplay::Gameplay(Game* game)  noexcept(false) :
    m_pitch(0),
    m_yaw(0),
    m_cameraPos(m_player->m_position)
{



}

void Gameplay::Initialize()
{

    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif
    m_audEngine = std::make_unique<AudioEngine>(eflags);



    CreateDeviceDependentResources();


    CreateWindowSizeDependentResources();




    //New   ----------------------- 
    m_player = new Player();
    m_player->m_direction(-1, 0, 0, 0);
    m_player->m_position(0, 10.0f, 1, 0);
    m_player->lhw = DirectX::SimpleMath::Vector3(.5, 1.0f, .5f);
    m_player->gun;

    for (int i = 0; i < 1; i++)
    {
        Enemy* m_enemy = new Enemy(DirectX::SimpleMath::Vector3(0.0f, -1.3f, 4.0f), 0.2f);
        m_enemy->Scale(DirectX::SimpleMath::Vector3(.007, .008, .007));
        //enem->pos =  Vector3( i*2,1.f,i);
        m_enemy->m_position = DirectX::SimpleMath::Vector3(i * 2, 1.f, i + 5);
        m_enemies.push_back(m_enemy);
    }


    // Instantiate each of the game levels. The Level class contains methods
   // that initialize the objects in the world for the given level and also
   // define any motion paths for the objects in that level.

    m_level.push_back(ref new Level1);
    m_level.push_back(ref new Level2);
    m_level.push_back(ref new Level3);
    m_level.push_back(ref new Level4);
    m_level.push_back(ref new Level5);
    m_level.push_back(ref new Level6);
    m_levelCount = static_cast<uint32>(m_level.size());



    m_city = new City();


}

void Gameplay::update(const float dt)
{


    if (m_retryAudio)
    {
        m_retryAudio = false;
        if (m_audEngine->Reset())
        {
            // TODO: restart any looped sounds here
        }
    }
    else if (!m_audEngine->Update())
    {
        if (m_audEngine->IsCriticalError())
        {
            m_retryAudio = true;
        }
    }



}

void Gameplay::SaveState()
{
    // Save basic state of the game.
    m_savedState->SaveBool(":GameActive", m_gameActive);
    m_savedState->SaveBool(":LevelActive", m_levelActive);
    m_savedState->SaveInt32(":LevelCompleted", m_currentLevel);
    m_savedState->SaveInt32(":TotalShots", m_totalShots);
    m_savedState->SaveInt32(":TotalHits", m_totalHits);
    m_savedState->SaveXMFLOAT3(":PlayerPosition", m_player->m_position);

    if (m_levelActive)
    {
        // The game is currently in the middle of a level, so save the extended state of
        // the game.
        m_savedState->SaveSingle(":LevelDuration", m_levelDuration);

        m_savedState->SaveInt32(":AmmoCount", m_ammoCount);
        m_savedState->SaveInt32(":AmmoNext", m_ammoNext);

        const int bufferLength = 16;
        char16 str[bufferLength];

  



 

        m_level[m_currentLevel]->SaveState(m_savedState);
    }
}



void Gameplay::StartLevel()
{
    if (m_currentLevel == 0)
    {
        m_gameActive = true;
    }
    m_levelActive = true;
}

void Gameplay::LoadGame()
{


    m_currentLevel = 0;
    m_gameActive = false;
    m_levelActive = false;
}

void Gameplay::CreateDeviceDependentResources()
{


    auto device = m_deviceResources->GetD3DDevice();

    m_font = std::make_unique<SpriteFont>(device, L"myfile.spritefont");

    auto context = m_deviceResources->GetD3DDeviceContext();
    m_spriteBatch = std::make_unique<SpriteBatch>(context);



}

void Gameplay::CreateWindowSizeDependentResources()
{
    auto size = m_deviceResources->GetOutputSize();
    m_fontPos.x = float(size.Width) / 2.f;
    m_fontPos.y = float(size.Height) / 2.f;
}





Gameplay::~Gameplay()
{
    if (m_audEngine)
    {
        m_audEngine->Suspend();
    }
}

void Gameplay::draw(const float dt)
{

    m_spriteBatch->Begin();

    const wchar_t* output = "LPlayer-Health:" + m_player->health;


    m_spriteBatch->Begin();

    DirectX::SimpleMath::Vector2 origin = m_font->MeasureString(output) / 2.f;

    m_font->DrawString(m_spriteBatch.get(), output,
        m_fontPos, Colors::White, 0.f, origin);

    m_spriteBatch->End();

    m_city->Render();

    //player
    m_player->ApplyGravity();

    //Draw gun and bullets
    m_player->gun->SetPosAndDir(DirectX::SimpleMath::Vector3(m_player->m_position.x + (m_player->m_direction.x * .3), m_player->m_direction.y + (m_player->m_direction.y * .3), m_player->m_direction.z + (m_player->m_direction.z * .3)), m_player->m_direction);
    m_player->gun->Draw();
    m_player->gun->StepUpDarts();
    //End
    //	//End



    //Draw MD2 Models
    bool bAnimated = true;
    for (int i = 0; i < m_enemies.size(); i++)
    {
        //If enemy died
        if (m_enemies[i]->died_time > 0)
        {
            m_enemies[i]->StepDieTimer();
            if (m_enemies[i]->died_time >= 1)
            {
                m_enemies.erase(m_enemies.begin() + i);
                i--;
                continue;
            }
        }
        //End

        //enemy StepUp
        m_enemies[i]->m_direction = (m_player->m_position - m_enemies[i]->m_position).Normalize();
        if (m_player->m_position.Distance(m_enemies[i]->m_position) >= 5.0f)
        {
            m_enemies[i]->Run();
        }
        else if (m_enemies[i]->died_time <= 0)
        {
            m_enemies[i]->gun->m_direction = (m_player->m_position - m_enemies[i]->m_position).Normalize();
            m_enemies[i]->gun->fire();
            m_enemies[i]->gun->StepUpBullets();
            m_enemies[i]->gun->Draw();
        }
        m_enemies[i]->ApplyGravity();

        //End

        //player collides with enemy
        if (m_player->m_position.Distance(m_enemies[i]->m_position) <= 1.5)
            m_player->m_position = m_player->m_position - (m_player->m_direction * m_player->speedOffset);
        //End

        //enemy collide with enemy
        for (int j = 0; j < m_enemies.size(); j++)
        {
            if (i == j)continue;
            if ((m_enemies[i]->m_position).Distance(m_enemies[j]->m_position) <= .5)
            {
                DirectX::SimpleMath::Vector3 tDir = m_enemies[i]->m_position - m_enemies[j]->m_position;
                if (m_enemies[i]->m_direction(tDir) < 0.f)
                {
                    m_enemies[i]->m_position = m_enemies[i]->m_position - (m_enemies[i]->m_direction * m_enemies[i]->speedOffset);
                }
            }
        }
        //End


        //player collide with enemy bullets
        for (int k = 0; k < m_enemies[i]->gun->m_ammo.size(); k++)
        {
            float u = 0; bool nearest = 0;
            if (m_enemies[i]->gun->m_ammo[k]->CollideWithModel(DirectX::SimpleMath::Vector3(0, 0, 0) - m_enemies[i]->gun->m_ammo[k]->m_direction, m_player->m_position, .3, u, nearest))
            {
                m_enemies[i]->gun->m_ammo[k]->min_distance_from_objs = u;
                m_player->health -= 10;


                //push the player
                m_player->m_direction = m_player->m_direction + DirectX::SimpleMath::Vector3() * sin(DirectX::SimpleMath::Vector3().x) * .1;
                m_player->m_direction = m_player->m_direction.Normalize();
                m_player->m_position += m_enemies[i]->m_direction * .02;

            }
        }
        //End

        //enemy Bullets removing
        for (int k = 0; k < m_enemies[i]->gun->m_ammo.size(); k++)
        {
            if (m_enemies[i]->gun->m_ammo[k]->min_distance_from_objs < abs(m_enemies[i]->gun->m_ammo[k]->speed / 2))
            {
                //SAFE_DELETE( enems[i]->gun->bullets[k] );
                //enems[i]->gun->bullets.erase( enems[i]->gun->bullets.begin()+k); 
                //k--;

            }
        }
        //End
    };

    //enemy collide with player bullets

        //player bullets collide to wall
    for (int k = 0; k < m_player->gun->m_ammo.size(); k++)
    {
        m_player->gun->m_ammo[k]->CollideWithModel();
    }
    //End

    for (int k = 0; k < m_player->gun->m_ammo.size(); k++)
    {
        int nearest_enem_no = -1;
        for (int i = 0; i < m_enemies.size(); i++)
        {
            DirectX::SimpleMath::Vector3 eDir = m_player->gun->m_ammo[k]->m_direction; eDir.y = 0;
            //((Rect*)(p))->Draw(); 

            float u = 0; bool nearest = false;
            //if( player->gun->bullets[k]->CollideToPlane(  player->gun->bullets[k]->dir.negative()  , enems[i]->pos , .5 , u ,nearest  ) )
            if (m_player->gun->m_ammo[k]->CollideWithModel())
            {
                nearest_enem_no = i;
            }
        }
        if (m_player->gun->m_ammo[k]->stopped == false && nearest_enem_no != -1)
        {
            if (m_enemies[nearest_enem_no]->health <= 0)
            {
                m_enemies[nearest_enem_no]->StepDieTimer();
            }
            else
            {
                m_enemies[nearest_enem_no]->health -= 5;
            }
        }
        if (m_player->gun->m_ammo[k]->min_distance_from_objs < abs(m_player->gun->m_ammo[k]->speed / 2))
        {
            m_player->gun->m_ammo[k]->stop();
            m_player->gun->m_ammo[k]->size = 0.0f;
        }
    }
    //End

}


void Gameplay::PauseGame()
{


}