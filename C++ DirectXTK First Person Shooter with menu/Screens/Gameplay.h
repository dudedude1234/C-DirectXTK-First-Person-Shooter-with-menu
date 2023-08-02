#pragma once
#include "pch.h"




enum class GameStage
{
    Waiting,
    Active,
    LevelComplete,
    TimeExpired,
    GameComplete,
};

enum class GameInfoOverlayState
{
    Loading,
    GameStats,
    LevelStart,
    LevelCompleted,
    GameOver,
    Pause
};

class Gameplay : public GameState
{
public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    void SaveState();
    virtual void handleInput();
    GameStage RunGame();
    void SetGameInfoOverlay(GameInfoOverlayState state);
    void StartLevel();
    void LoadGame();
    void CreateDeviceDependentResources();

    void CreateWindowSizeDependentResources();

    void Initialize();

    ~Gameplay();

    Gameplay(Game* game) noexcept(false);


    bool GameActive() { return m_gameActive; };
    bool LevelActive() { return m_levelActive; };
    Level^ CurrentLevel() { return m_level[m_currentLevel]; };
    float HealthRemaining() { return m_healthRemaining; };
    int LevelCompleted() { return m_currentLevel; };

    uint32                                      m_ammoCount;
    uint32                                      m_ammoNext;

    PersistentState^ m_savedState;

    bool                                        m_gameActive;
    bool                                        m_levelActive;
    int                                         m_totalHits;
    int                                         m_totalShots;
    float                                       m_levelDuration;
    float                                       m_healthRemaining;
    std::vector<Level^>                         m_level;
    uint32                                      m_levelCount;
    uint32                                      m_currentLevel;

public:

    Gun m_gun;

    Player *m_player;

    std::vector<Enemy*>                        m_enemies;

    Enemy *m_enemy;

    City *m_city;

    float m_pitch;
    float m_yaw;

    DirectX::SimpleMath::Vector2 m_fontPos;
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

    bool m_retryAudio;

    std::unique_ptr<DirectX::SpriteFont> m_font;

};

