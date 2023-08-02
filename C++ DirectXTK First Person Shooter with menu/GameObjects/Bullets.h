#pragma once

#include "pch.h"


public class Bullets
{


public:

	std::vector<Bullets*>m_ammo;

	Bullets(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 direction, float speed, int texture = 0);
	void CreateDeviceDependentResources();
	void stop();
	void StepUpBullets();
	void Render();

	bool CollideWithModel(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction);

	void OnDeviceLost();

	BoundingSphere m_sphere;

	DirectX::SimpleMath::Vector3 start_pos;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_direction;

	float age;
	float size;
	float speed;
	bool stopped;
	int counter;

	float mpSize;

	float min_distance_from_objs;
	DirectX::SimpleMath::Vector3 intersectPoint_Real;
	DirectX::SimpleMath::Vector3 intersectPoint_Ideal;
	DirectX::SimpleMath::Vector3 intersectPointNormal;


};

