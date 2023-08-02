#pragma once

#include "pch.h"
#include <random>



class StartScreen : public GameState
{
public:

    void Initialize(IUnknown* window);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    void CreateWindowSizeDependentResources();

    void CreateDeviceDependentResources();

    bool isTextClicked(IUnknown* window);

    StartScreen(Game* game);

    void loadgame(Game* game);





private:
    
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
    DirectX::SimpleMath::Vector2 m_fontPos;
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
    DirectX::SimpleMath::Vector2 m_screenPos;
    DirectX::SimpleMath::Vector2 m_origin;
    std::unique_ptr<DirectX::SpriteFont> m_font;
    const int NUM_BUTTONS = 3;

    std::unique_ptr<DirectX::GamePad> m_gamePad;

    RECT m_fullscreenRect;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;

    int m_SelectedMenu;
    std::vector<const wchar_t*> buttons;

    std::unique_ptr<DirectX::SoundEffect> m_explode;
    std::unique_ptr<DirectX::SoundEffect> m_ambient;

    std::unique_ptr<std::mt19937> m_random;
    float explodeDelay;

};

