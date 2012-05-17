#include "Planet.h"
#include "Sphere.h"
#include <iostream>
#include "utils.h"

Object::Object(std::string a_Name)
:	m_Name(a_Name)
,	m_Primary(NULL)
,	m_Theta(0)
,	m_L(0)
,	m_U(0)
,	m_Mass(0)
,	m_Eccentricity(0)
,	m_SemiMajorAxis(0)
,	m_SemiMinorAxis(0)
,	m_OrbitalPeriod(0)
,	m_OrbitalRadius(0)
,	m_EquatorialRadius(0.0)
,	m_OrbitScale(1.0)
,	m_RadiusScale(1.0)
,	m_RealPos(D3DXVECTOR3(0,0,0))
,	m_Speed(0)
,	m_Inclination(0)
{
	m_Position = m_RealPos;
}

bool Object::CreateObject(IDirect3DDevice9* a_pDevice)
{
	m_Radius = m_EquatorialRadius * m_RadiusScale;
	return(Sphere::CreateObject(a_pDevice));
}

void Object::Init()
{
	//setup some constant variables
	double G = 6.674 * pow(10.0,-11.0);														//standard gravitational constant
	//
	m_SemiMinorAxis = m_SemiMajorAxis * sqrt(1-pow(m_Eccentricity,2));						//
	m_U = G * (m_Mass + m_Primary->m_Mass);														//standard gravitational parameter
	//
	m_L = m_SemiMajorAxis * m_SemiMajorAxis / m_SemiMinorAxis;								//semi-latus rectum
	//setup the initial states of some variables
	m_OrbitalRadius = m_SemiMajorAxis * (1 - m_Eccentricity);								//perihelion
	m_RealPos.x = (float)m_OrbitalRadius;															//perihelion
	m_Speed = sqrt( m_U * ( (2 / utils::Vec3Mag(m_RealPos)) - (1 / m_SemiMajorAxis) ) );	//real speed
	m_Position = m_RealPos * (FLOAT)m_OrbitScale;													//draw position
}

void Object::Update(double a_dt, double a_TimePassageRate)
{ 
	//gravitational constant
	double G = 6.674 * pow(10.0,-11.0);
	double PI = 3.1415927;

	//calculate speed
	m_Speed = sqrt( m_U * ( (2 / utils::Vec3Mag(m_RealPos)) - (1 / m_SemiMajorAxis) ) );

	//calculate exact position in polar form
	m_Theta += a_dt * a_TimePassageRate / (m_OrbitalPeriod * m_OrbitalRate);
	if(m_Theta > 2*PI)
		m_Theta -= 2*PI;
	else if(m_Theta < 0)
		m_Theta += 2*PI;

	m_OrbitalRadius = m_L / (1 + m_Eccentricity * cos(m_Theta));

	m_RealPos.z = (float)(m_OrbitalRadius * sin(m_Theta));
	m_RealPos.x = (float)(m_OrbitalRadius * cos(m_Theta));

	m_Position = m_RealPos * (FLOAT)m_OrbitScale;
	m_Position.y = (float)(m_Position.x * tan(m_Inclination));

	/*//circular orbit
	if(m_OrbitalRadius)
	{
		D3DXQUATERNION rotQ;
		D3DXQUATERNION pos(m_Position.x ,m_Position.y, m_Position.z, 0.0f);
		double yaw = (m_OrbitalRadius / m_OrbitalPeriod) * a_dt * a_TimePassageRate;

		//build rotation quaternion around the star
		D3DXQuaternionRotationYawPitchRoll(&rotQ,yaw,0.0f,0.0f);

		//rotate planetary pos by quaternion
		D3DXQuaternionMultiply(&pos,&rotQ,&pos);
		D3DXQuaternionInverse(&rotQ,&rotQ);
		D3DXQuaternionMultiply(&rotQ,&pos,&rotQ);
		m_Position = utils::QuatToVec3(rotQ);
	}
	//*/
}

void Object::Render(float a_dt, float a_TimePassageRate, IDirect3DDevice9* a_pDevice)
{
	if (a_pDevice && m_pMesh)
	{
		a_pDevice->SetMaterial(&m_mat);
		a_pDevice->SetTexture(0, NULL);

		// Create a translation matrix
		D3DXMATRIX translationMat;
		D3DXMatrixTranslation(&translationMat, m_Position.x, m_Position.y, m_Position.z);

		a_pDevice->SetTransform(D3DTS_WORLD, &translationMat);

		// Draw our mesh
		m_pMesh->DrawSubset(0);
		//std::cout << m_Name.c_str() << " rendered" << std::endl;
	}
}
