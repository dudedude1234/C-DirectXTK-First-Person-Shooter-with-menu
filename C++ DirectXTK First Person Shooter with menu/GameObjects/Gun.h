#include "pch.h"



class Gun
{
public:
	std::vector<Bullets*>m_ammo;
	float bulletSpeed;

	Gun();

	void CreateDeviceDependentResources();

	void SetPosAndDir(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction);

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_direction;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;



	virtual void StepUpBullets();

	virtual void create();

	virtual void Draw();

	virtual void fire();

};