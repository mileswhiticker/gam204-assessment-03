//light class written by Miles Whiticker fromcode by Scott Tayloe

#if !defined(LIGHT_H)
#define LIGHT_H

#include <d3d9.h>
#include <d3d9types.h>
#include "D3dx9math.h"

struct D3DXCOLOR;

class Light
{
public:
	void InitOmni();
	//
	void SetPosition(D3DXVECTOR3 a_Pos);
	void SetPosition(float a_x,float a_y,float a_z);
	void SetRange(float a_Range);
	void SetAttenuation(float a_attenuationFactor);
	void SetCone(float a_theta, float a_phi);
	void SetDiffuse(float a, float r, float b, float g);
	void SetSpecular(float a, float r, float b, float g);
	//
	const D3DLIGHT9& GetLightData() { return m_light; }
protected:
	D3DLIGHT9 m_light;
};

#endif  // LIGHT_H
