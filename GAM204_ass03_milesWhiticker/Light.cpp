#include "Light.h"

#include <d3dx9.h>
#include <d3dx9math.h>

void Light::InitOmni()
{
	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_POINT;
	m_light.Range = 50.0f;
	m_light.Attenuation1 = 50.0f;
	SetSpecular(255,255,255,255);
	SetDiffuse(255,255,255,255);
}

void Light::SetRange(float a_range)
{
	m_light.Range = a_range;
}

void Light::SetAttenuation(float a_attenuationFactor)
{
	m_light.Attenuation0 = 0.0f;
	m_light.Attenuation1 = a_attenuationFactor;
	m_light.Attenuation2 = 0.0f;
}

void Light::SetPosition(D3DXVECTOR3 a_Pos)
{
	m_light.Position = a_Pos;
}

void Light::SetPosition(float a_x,float a_y,float a_z)
{
	m_light.Position = D3DXVECTOR3(a_x,a_y,a_z);
}

void Light::SetDiffuse(float a, float r, float b, float g)
{
	//
	m_light.Diffuse.a = a;
	m_light.Diffuse.r = r;
	m_light.Diffuse.g = g;
	m_light.Diffuse.b = b;
}

void Light::SetSpecular(float a, float r, float b, float g)
{
	//
	m_light.Specular.a = a;
	m_light.Specular.r = r;
	m_light.Specular.g = g;
	m_light.Specular.b = b;
}
