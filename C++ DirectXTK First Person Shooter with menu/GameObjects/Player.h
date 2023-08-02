#pragma once

#include "pch.h"


public enum AnimationState
{
	Walk,
	Shoot,
	Crouch,
	Reload,
	AimWalk,
	LeftTurn,
	RightTurn,
	StandShoot

};


class Player : public PlayerObject
{

public:

	Player();

	Player(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction, DirectX::SimpleMath::Vector3 radius);
	void CreateDeviceDependentResources();
	void Update();
	void ApplyGravity();
    void StepUpBullets();
	void Render();
	void OnDeviceLost();

	Taser*                          taser;

	float angle;
	float deltaAngle;
	float deltaMove;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::ModelBone::TransformArray m_drawBones;

	DX::AnimationSDKMESH m_animation;



	bool m_armed;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	






	AnimationState                 mAnimationState;

	float m_pitch;
	float m_yaw;



	

};






