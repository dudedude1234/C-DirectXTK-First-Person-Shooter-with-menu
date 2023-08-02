
#include "Enemy.h"



Enemy::Enemy(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction, DirectX::SimpleMath::Vector3 radius)
{




	/*Weapon.LoadModel( weapon_model_path );
	Weapon.LoadSkin( weapon_skin_path );


	Weapon.SetAnim( STAND );*/

	mAnimationState = 0;

	died_time = 0;
	this->speedOffset = .05;

	this->m_position.y = 1;

	this->m_ammoSpeed = m_ammoSpeed;
}


void Enemy::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	m_model = Model::CreateFromSDKMESH(device, L"Terrorist.sdkmesh",
		*m_fxFactory,
		ModelLoader_Clockwise | ModelLoader_IncludeBones);


	switch (mAnimationState)
	{

	case 0:
	DX::ThrowIfFailed(
		m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
	break;


	case 1:
	DX::ThrowIfFailed(
		m_animation.Load(L"W1_Stand_Aim_Idle.sdkmesh_anim"));
	break;

	case 2:
	DX::ThrowIfFailed(
		m_animation.Load(L"W1_Stand_Aim_Turn_In_Place_L_Loop.sdkmesh_anim"));
	break;

	case 3:
	DX::ThrowIfFailed(
		m_animation.Load(L"W1_Stand_Aim_Turn_In_Place_R_Loop.sdkmesh_anim"));
	break;

	case 4:
	DX::ThrowIfFailed(
		m_animation.Load(L"W1_Stand_Fire_Single.sdkmesh_anim"));
	break;

	}


	m_animation.Bind(*m_model);

	m_drawBones = ModelBone::MakeArray(m_model->bones.size());

	m_model->UpdateEffects([](IEffect* effect)
		{
			auto lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightingEnabled(true);
				lights->SetPerPixelLighting(true);
				lights->SetLightEnabled(0, true);
				lights->SetLightDiffuseColor(0, Colors::Gold);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}

			auto fog = dynamic_cast<IEffectFog*>(effect);
			if (fog)
			{
				fog->SetFogEnabled(true);
				fog->SetFogColor(Colors::CornflowerBlue);
				fog->SetFogStart(3.f);
				fog->SetFogEnd(4.f);
			}
		});
}

void Enemy::Scale(XMFLOAT3 scale)
{
	this->m_scale = scale;
	//Ogro.ScaleModel( i );
	//Weapon.ScaleModel( i );
}

void Enemy::StepDieTimer()
{
	died_time += .025;
}

void Enemy::Run()
{
	if (died_time > 0)return;

	m_position = m_position + (m_direction * speedOffset);
	SetAnim(1 /*animType_t::RUN */);
}

void Enemy::ApplyGravity()
{
	this->m_position.y -= .98f * .1;
}

void Enemy::Update()
{
	switch (m_hat)
	{
	case 0:
		m_model->meshes.data()
			break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	}

	if (m_top)
	{

	}

	switch (m_bottom)
	{
	case 0:
		
			break;
	case 1:

		break;
	}
}

void Enemy::SetAnim(int i)
{
	mAnimationState = i;
	//Weapon.SetAnim(i);
}

void Enemy::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	size_t nbones = m_model->bones.size();

	if (died_time > 0)
		SetAnim(5 /*animType_t::DEATH_FALLBACKSLOW*/);

	gun->m_position = this->m_position + (this->m_direction * .1) + (this->m_direction(XMFLOAT3(0, 1, 0)) * -.2);
	gun->m_position.y += .25;


	size_t nbones = m_model->bones.size();

	m_animation.Apply(*m_model, nbones, m_drawBones.get());

	m_model->DrawSkinned(context, *m_states, nbones, m_drawBones.get(),
		*m_states, m_world, m_view, m_proj));
}

void Enemy::fire()
{
	create();
}

void Enemy::OnDeviceLost()
{
}
