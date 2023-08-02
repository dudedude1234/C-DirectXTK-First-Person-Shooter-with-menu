#include "pch.h"
#include "StartScreen.h"
#include <Game.h>
#include <Common/DirectXHelper.h>





StartScreen::StartScreen(Game* game)
{





    //Since it's only 3 text its fine to just manually set each...
    buttons[0] = L"Play Game";
    buttons[1] = L"Options";
    buttons[2] = L"Quit";



    this->game = game;
}

void StartScreen::Initialize(IUnknown* window)
{


    m_keyboard = std::make_unique<Keyboard>();
    m_mouse = std::make_unique<Mouse>();
    m_mouse->SetWindow(reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(window));
    


    CreateDeviceDependentResources();


    CreateWindowSizeDependentResources();
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif
   

}

void StartScreen::draw(const float dt)
{
    m_spriteBatch->Begin();

    //set positions of things
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        XMVECTOR origin = m_font->MeasureString(buttons[i]) / 2.f;

        m_font->DrawString(m_spriteBatch.get(), buttons[i],
            m_fontPos, Colors::White, 0.f, origin);
    }

    m_spriteBatch->End();


}

void StartScreen::update(const float dt)
{
    switch (m_SelectedMenu)
    {
    case 0:
        m_font->DrawString(m_spriteBatch.get(), buttons[0], Colors::Blue);
        break;
    case 1:
        m_font->DrawString(m_spriteBatch.get(), buttons[1], Colors::Blue);
        break;
    case 2:
        m_font->DrawString(m_spriteBatch.get(), buttons[2], Colors::Blue);
        break;
    }
}

void StartScreen::handleInput()
{
    auto pad = m_gamePad->GetState(0);
    if (pad.IsConnected())
    {

        if (pad.IsLeftThumbStickDown())
        {
            m_SelectedMenu += 1;
        }
        if (pad.IsLeftThumbStickUp())
        {
            m_SelectedMenu -= 1;
        }

        if (pad.buttons.a)
        {
            switch (m_SelectedMenu)
            {
            case 0:
                loadgame(game);
                break;
            case 1:

                break;
            case 2:

                break;
            }
        }


    }
}

void StartScreen::CreateWindowSizeDependentResources()
{
}



void StartScreen::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, L"canstockphoto6782999.jpg", nullptr,
            m_background.ReleaseAndGetAddressOf()));
}



bool StartScreen::isTextClicked(IUnknown* window)
{
    auto state = m_mouse->Get().GetState();

    RECT rect =
    {
        state.x, state.y, static_cast<long>(m_fontPos.x), static_cast<long>(m_fontPos.y)
    };


    if (reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(window))
        return true;

    //Otherwise, don't do anything
    return false;

}

void StartScreen::loadgame(Game* game)
{

    game->pushState(new Gameplay(game));


}

