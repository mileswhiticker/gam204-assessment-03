#ifndef PLANET_H
#define PLANET_H

#include "Sphere.h"
#include <string>

class Object : public Sphere
{
public:
	virtual void Render(float a_dt, float a_TimePassageRate, IDirect3DDevice9* a_pDevice);
	virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
	Object(std::string a_Name);
	void Init();
	//
	void Jump(D3DXVECTOR3 a_Position);
	void Update(double a_dt,double a_TimePassageRate);
	//
	std::string m_Name;
	double m_OrbitScale;		//difference of magnitude between calculated values and simulation values
	double m_RadiusScale;		//difference of magnitude between actual radius and simulation (display) radius
	double m_OrbitalRate;		//difference of magnitude between actual orbital period and simulation orbital period
	//
	double m_Theta;				//true anomaly (angle with periapsis)
	double m_OrbitalPeriod;		//(constant)
	double m_Eccentricity;		//(constant)
	double m_SemiMajorAxis;		//(constant)
	double m_Mass;				//(constant)
	double m_EquatorialRadius;	//(constant)
	Object* m_Primary;			//(constant)
	double m_Inclination;		//(constant)
	//
	double m_OrbitalRadius;		//
	double m_SemiMinorAxis;		//(constant)
	double m_L;					//Semi latus rectum (constant)
	double m_U;					//standard gravitational parameter (constant)
	double m_Speed;				//real speed
	D3DXVECTOR3 m_RealPos;
	//
};

#endif