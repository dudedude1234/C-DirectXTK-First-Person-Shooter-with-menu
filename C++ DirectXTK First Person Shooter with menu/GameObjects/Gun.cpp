#include "Gun.h"





Gun::Gun()
{
	
}


void Gun::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	auto device = m_deviceResources->GetD3DDevice();

	m_states = std::make_unique<CommonStates>(device);

	m_fxFactory = std::make_unique<EffectFactory>(device);

	m_model = Model::CreateFromCMO(device, L"cup.cmo", *m_fxFactory);

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

void Gun::SetPosAndDir(DirectX::SimpleMath::Vector3 m_position, DirectX::SimpleMath::Vector3 m_directionn)
{
	this->m_position = m_position;
	this->m_direction = m_direction;
}

virtual void Gun::create()
{
	if (bullets.size() != 0 && bullets[bullets.size() - 1]->age < 5) return;

	Bullets* bullet = new Bullets(this->position, this->direction, bulletSpeed);
	bullets.push_back(bullet);
}

virtual void Gun::Draw()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i]->stopped)
			bullets[i]->Render();
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	m_model->Draw(context, *m_states, m_world, m_view, m_proj);

}

virtual void Gun::fire()
{
	create();
}



