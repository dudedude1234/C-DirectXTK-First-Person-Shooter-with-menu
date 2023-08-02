#include "pch.h"
#include "Bullets.h"



Bullets::Bullets(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 direction, float speed, int texture = 0)
{
	
	this->min_distance_from_objs = 1000000.f;
	this->start_pos = position;

}

void Bullets::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	m_states = std::make_unique<CommonStates>(device);

	m_fxFactory = std::make_unique<EffectFactory>(device);

	m_model = Model::CreateFromCMO(device, L"cup.cmo", *m_fxFactory);
	
}

void Bullets::stop()
{
	this->stopped = true;
}

bool Bullets::CollideWithModel(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_direction)
{
	const Vector3 m_sphereOrgin = m_position + Vector3(0, 2.5f, 0);
	const float m_sphereRadius = 3.0f;
	const float m_sphereRadius2 = m_sphereRadius * m_sphereRadius;
}

void Bullets::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	m_model->Draw(context, *m_states, m_world, m_view, m_proj);
}

void Bullets::OnDeviceLost()
{
}
