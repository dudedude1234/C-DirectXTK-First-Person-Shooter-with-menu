#include "pch.h"
#include "Player.h"
#include <Common/DirectXHelper.h>
#include <Screens/Gameplay.cpp>




Player::Player()
{
	this->speedOffset = .1;
	this->deltaAngle = 0.f;
	this->deltaMove = 0.f;
	this->angle = 0.0f;
	this->m_position.y = 1;
}

Player::Player(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction, DirectX::SimpleMath::Vector3 radius)
{
	Player();
	this->m_position = m_position;
	this->m_direction = m_direction;
}

void Player::CreateDeviceDependentResources()
{

	m_keyboard = std::make_unique<Keyboard>();
	m_keyboard->SetWindow(reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(window));

	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(window));

	auto device = m_deviceResources->GetD3DDevice();

	m_model = Model::CreateFromSDKMESH(device, L".sdkmesh",
		*m_fxFactory,
		ModelLoader_Clockwise | ModelLoader_IncludeBones);


	DX::ThrowIfFailed(
		CreateWICTextureFromFile(device, L".png", nullptr,
			m_texture.ReleaseAndGetAddressOf()));



	if (m_armed = true)
	{
		DX::ThrowIfFailed(
			m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
	}
	else
	{

	}
	
	
	m_animation.Bind(*m_model);

	m_drawBones = ModelBone::MakeArray(m_model->bones.size());

	m_model->UpdateEffects([&](IEffect* effect)
		{
			auto skin = dynamic_cast<SkinnedEffect*>(effect);
			if (skin)
			{
				skin->SetPerPixelLighting(true);
			}
		});

	m_world = Matrix::Identity;

}

void Player::Update()
{
	auto mouse = m_mouse->GetState();
	auto kb = m_keyboard->GetState();
	auto pad = m_gamePad->GetState(0);

	if (kb.Left || kb.A)
	{
		DirectX::SimpleMath::Vector3 v = m_direction.Cross(DirectX::SimpleMath::Vector3(0, 1, 0));
		m_position.x += (v.x * speedOffset);
		m_position.z += (v.z * speedOffset);
		//pos.y += (v.y* speedOffset);





	}

	if (kb.Right || kb.D)
	{
		DirectX::SimpleMath::Vector3 v = m_direction.Cross(DirectX::SimpleMath::Vector3(0, 1, 0));
		m_position.x -= (v.x * speedOffset);
		m_position.z -= (v.z * speedOffset);
		//pos.y -= (v.y* speedOffset);



	}
	if (kb.Up || kb.W)
	{
		m_position.x += (m_direction.x * speedOffset);
		m_position.z += (m_direction.z * speedOffset);
		//pos.y += (dir.y* speedOffset);

		if (m_armed = true)
		{
			DX::ThrowIfFailed(
				m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
		}
		else
		{
			DX::ThrowIfFailed(
				m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
		}

	}
	if (kb.Down || kb.S)
	{
		m_position.x -= (m_direction.x * speedOffset);
		m_position.z -= (m_direction.z * speedOffset);
		//pos.y -= (dir.y* speedOffset);



	}

	if (mouse.positionMode == Mouse::MODE_RELATIVE)
	{
		DirectX::SimpleMath::Vector3 delta = DirectX::SimpleMath::Vector3(float(mouse.x), float(mouse.y), 0.f)
			* ROTATION_GAIN;

		m_pitch -= delta.y;
		m_yaw -= delta.x;
	}

	m_mouse->SetMode(mouse.leftButton
		? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE);

	if (pad.IsConnected())
	{
		

		if (pad.IsRightTriggerPressed())
		{
			DX::ThrowIfFailed(
				m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
			taser->create();
		}

		if (pad.IsLeftTriggerPressed())
		{
			DX::ThrowIfFailed(
				m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
		}

		if (pad.IsLeftThumbStickLeft())
		{
			DirectX::SimpleMath::Vector3 v = m_direction.Cross(DirectX::SimpleMath::Vector3(0, 1, 0));
			m_position.x += (v.x * speedOffset);
			m_position.z += (v.z * speedOffset);
			//pos.y += (v.y* speedOffset);



		}

		if (pad.IsLeftThumbStickRight())
		{
			DirectX::SimpleMath::Vector3 v = m_direction.Cross(DirectX::SimpleMath::Vector3(0, 1, 0));
			m_position.x -= (v.x * speedOffset);
			m_position.z -= (v.z * speedOffset);
			//pos.y -= (v.y* speedOffset);



		}
		if (pad.IsLeftThumbStickUp())
		{
			m_position.x += (m_direction.x * speedOffset);
			m_position.z += (m_direction.z * speedOffset);
			//pos.y += (dir.y* speedOffset);

			if (m_armed = true)
			{
				DX::ThrowIfFailed(
					m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
				if (pad.IsLeftTriggerPressed())
				{
					DX::ThrowIfFailed(
						m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
				}
			}
			else
			{
				DX::ThrowIfFailed(
					m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
			}

		}
		if (pad.IsLeftThumbStickDown())
		{
			m_position.x -= (m_direction.x * speedOffset);
			m_position.z -= (m_direction.z * speedOffset);
			//pos.y -= (dir.y* speedOffset);



		}

	}

};

void Player::ApplyGravity()
{
	this->m_position.y -= .98f * .1;
}

void Player::StepUpBullets()
{
}

void Player::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	size_t nbones = m_model->bones.size();

	m_animation.Apply(*m_model, nbones, m_drawBones.get());

	m_model->DrawSkinned(context, *m_states, nbones, m_drawBones.get(),
		m_world, m_view, m_proj);
}

void Player::OnDeviceLost()
{
	m_states.reset();
	m_fxFactory.reset();
	m_model.reset();
	m_texture.Reset();
}
