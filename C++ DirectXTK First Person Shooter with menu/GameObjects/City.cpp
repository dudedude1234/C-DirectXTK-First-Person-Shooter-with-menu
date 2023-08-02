#include "pch.h"
#include "City.h"

void City::CreateDeviceDependentResources()
{

	auto device = m_deviceResources->GetD3DDevice();

	m_states = std::make_unique<CommonStates>(device);

	m_fxFactory = std::make_unique<EffectFactory>(device);

	m_model = Model::CreateFromCMO(device, L"City.cmo", *m_fxFactory);



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

void City::Render()
{

	auto context = m_deviceResources->GetD3DDeviceContext();

	m_model->Draw(context, *m_states, m_world, m_view, m_proj);
}

void City::OnDeviceLost()
{

}
