//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <wrl.h>
#include <wrl/client.h>
#include <dxgi1_4.h>
#include <d3d11_3.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include <concrt.h>
#include <codecvt>
#include <locale>
#include <winsdkver.h>
#define _WIN32_WINNT 0x0A00
#include <sdkddkver.h>

#include "Audio.h"
#include "Animation.h"
#include "BufferHelpers.h"
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"

#include "GameState.h"
#include <Common/DirectXHelper.h>
#include "Common/DeviceResources.h"
#include "Level/Level1.h"
#include "Level/Level2.h"
#include "Level/Level3.h"
#include "Level/Level4.h"
#include "Level/Level5.h"
#include "Level/Level6.h"
#include "Level/Level.h"
#include <GameObjects/City.h>
#include <GameObjects/Bullets.h>
#include <GameObjects/Gun.h>
#include "GameObjects/Enemy.h"
#include "GameObjects/Player.h"
#include "Screens/StartScreen.h"
#include "Screens/Gameplay.h"
#include "Game.h"
#include <GameObjects/Dart.h>
#include <GameObjects/Taser.h>


using namespace concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Storage;
using namespace Windows::UI::Core;

namespace
{
	constexpr float ROTATION_GAIN = 0.004f;
	constexpr float MOVEMENT_GAIN = 0.07f;
}

using BoundingSphere = DirectX::BoundingSphere;
using BoundingOrientedBox = DirectX::BoundingOrientedBox;
using BoundingBox = DirectX::BoundingBox;
using BoundingFrustum = DirectX::BoundingFrustum;
using ContainmentType = DirectX::ContainmentType;
using Vector3 = DirectX::SimpleMath::Vector3;


struct CollisionSphere
{
	BoundingSphere sphere;
	ContainmentType collision;
};

struct CollisionBox
{
	BoundingOrientedBox obox;
	ContainmentType collision;
};

struct CollisionAABox
{
	BoundingBox aabox;
	ContainmentType collision;
};

struct CollisionRay
{
	DirectX::SimpleMath::Vector3 origin;
	DirectX::SimpleMath::Vector3 direction;
};

float m_pitch;
float m_yaw;

// Cached pointer to device resources.
std::shared_ptr<DX::DeviceResources> m_deviceResources;


DirectX::SimpleMath::Vector3 m_cameraPos;

std::unique_ptr<DirectX::Keyboard> m_keyboard;
std::unique_ptr<DirectX::Mouse> m_mouse;
std::unique_ptr<DirectX::GamePad> m_gamePad;

std::unique_ptr<DirectX::AudioEngine> m_audEngine;


class PlayerObject
{
public:
	DirectX::SimpleMath::Vector3 m_position, m_radius, m_direction, last_pos, lhw;
	float speedOffset;
	float health;


	PlayerObject()
	{
		health = 100;
	}

	PlayerObject(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 direction)
		:m_position(position), m_direction(direction), health(100)
	{
	}

	void ApplyGravity()
	{
		this->m_position.y -= .98f * .1;
	}



};
