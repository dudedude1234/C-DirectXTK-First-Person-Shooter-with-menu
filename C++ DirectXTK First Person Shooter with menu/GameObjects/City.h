#pragma once
class City
{

	City(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction, float speed);
	void CreateDeviceDependentResources();
	void Render();

	void OnDeviceLost();

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;



};

