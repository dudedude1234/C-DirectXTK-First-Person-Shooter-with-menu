#pragma once

#include "pch.h"




public enum AnimationState
{
	Forward,
	Backward,
	Left,
	Right,
	Shoot,
	Reload
};



class Enemy : public PlayerObject
{


public:

	Enemy(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction, DirectX::SimpleMath::Vector3 radius);
	void CreateDeviceDependentResources();
	void Scale(DirectX::SimpleMath::Vector3 scale);
	void StepDieTimer();
	void Run();
	void ApplyGravity();
	void Update();
	void Render();
	void SetAnim(int i);
	void fire();
	void OnDeviceLost();

	Gun* gun;


	float angle;
	float deltaAngle;
	float deltaMove;

	float speedOffset;
	float health;

	float		    died_time;


	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DX::AnimationSDKMESH m_animation;


	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;








	AnimationState                 mAnimationState;


	int                 mAnimationState;

	float m_radius;


	bool m_hat;
	bool m_top;
	bool m_bottom;


};

