#include "app.h"
#include "Light.h"
#include "Sphere.h"
#include "Planet.h"
#include "Grid.h"

#include "WindowManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "utils.h"

App::App(HINSTANCE a_hInst) 
:	dx_manager(DXMgr::GetInstance())
,	window_manager(WndwMgr::GetInstance(a_hInst))
,	res_manager(ResMgr::GetInstance())
,	m_TimePassageRate(1.0f)
,	m_CurViewing(0)
,	m_IsShowingDebug(false)
{
	//dxmanager should have already setup the d3d environment
	//window manager should have already setup the window

	//setup renderer
	m_Renderer = Renderer::GetInstance(dx_manager.GetDevice());
	res_manager.m_Renderer = m_Renderer;
	
	//setup viewfocus output text
	res_manager.AddTitle("the Solar System",0,320);

	res_manager.AddTitle("Solar body: ",0);
	res_manager.AddTitle("Distance to system centre: ",1);
	res_manager.AddTitle("Orbital period: ",2);
	res_manager.AddTitle("Orbital radius: ",3);
	res_manager.AddTitle("Equatorial radius: ",4);
	res_manager.AddTitle("X: ",5);
	res_manager.AddTitle("Y: ",6);
	res_manager.AddTitle("Z: ",7);
	res_manager.AddTitle("Mass: ",8);
	res_manager.AddTitle("Inclination: ",9);
	
	//initialise planetary bodies
	//1 AU = 149 597 870.7 km
	double orbitScale = 0.000000075;
	double radiusScale = 0.00001;
	double orbitalRate = 0.01;

	//Sun
	//equatorial radius = 696 000 km = 0.004 AU
	//orbital radius = 0 km = 0 AU
	m_pObjects.push_back(new Object("Sun"));
	m_pObjects.back()->SetEmissive(1.0f);
	m_pObjects.back()->m_RadiusScale = 0.000005;
	//
	m_pObjects.back()->m_Mass = 1.9891f * pow(10.0f,33.0f);
	m_pObjects.back()->m_EquatorialRadius = 6.955f*pow(10.0f,5.0f);

	m_Renderer->m_ViewRadius = (float)(m_pObjects.back()->m_EquatorialRadius * m_pObjects.back()->m_RadiusScale * 10);

	//Mercury
	//equatorial radius = ? = 0.00001528 AU
	//orbital radius = ? km = 0.39 AU
	m_pObjects.push_back(new Object("Mercury"));
	//
	m_pObjects.back()->m_Mass = 3.3022f*pow(10.0,23.0);
	m_pObjects.back()->m_EquatorialRadius = 2439.7;
	m_pObjects.back()->m_Eccentricity = 0.205630;
	m_pObjects.back()->m_SemiMajorAxis = 57909100;
	m_pObjects.back()->m_OrbitalPeriod = 87.969;
	m_pObjects.back()->m_Inclination = 0.12229522;

	//Venus
	//equatorial radius = ? = 0.00003796 AU
	//orbital radius = ? km = 0.72 AU
	m_pObjects.push_back(new Object("Venus"));
	//
	m_pObjects.back()->m_Mass = 4.8685f*pow(10.0f,24.0f);
	m_pObjects.back()->m_EquatorialRadius = 6051.8;
	m_pObjects.back()->m_Eccentricity = 0.0068;
	m_pObjects.back()->m_SemiMajorAxis = 108208930;
	m_pObjects.back()->m_OrbitalPeriod = 224.70069;
	m_pObjects.back()->m_Inclination = 0.05924886665;

	//Earth
	//equatorial radius = 6378.1 = 0.00004 AU
	//orbital radius = ? km = 1 AU
	m_pObjects.push_back(new Object("Earth"));
	//
	m_pObjects.back()->m_Mass = 5.9736f*pow(10.0f,24.0f);
	m_pObjects.back()->m_EquatorialRadius = 6371;
	m_pObjects.back()->m_Eccentricity = 0.0167;
	m_pObjects.back()->m_SemiMajorAxis = 149598261;
	m_pObjects.back()->m_OrbitalPeriod = 365.256;
	m_pObjects.back()->m_Inclination = 0.1248783;

	//Mars
	//equatorial radius = 6378.1 = 0.00002128 AU
	//orbital radius = ? km = 1.52 AU
	m_pObjects.push_back(new Object("Mars"));
	//
	m_pObjects.back()->m_Mass = 6.4185f*pow(10.0f,23.0f);
	m_pObjects.back()->m_EquatorialRadius = 3396.2;
	m_pObjects.back()->m_Eccentricity = 0.093315;
	m_pObjects.back()->m_SemiMajorAxis = 227939100;
	m_pObjects.back()->m_OrbitalPeriod = 686.971;
	m_pObjects.back()->m_Inclination = 0.03228859;

	//Jupiter
	//equatorial radius = 6378.1 = 0.00044836 AU
	//orbital radius = ? km = 5.2 AU
	m_pObjects.push_back(new Object("Jupiter"));
	//
	m_pObjects.back()->m_Mass = 1.8986f*pow(10.0f,27.0f);
	m_pObjects.back()->m_EquatorialRadius = 71492;
	m_pObjects.back()->m_Eccentricity = 0.048775;
	m_pObjects.back()->m_SemiMajorAxis = 778547200;
	m_pObjects.back()->m_OrbitalPeriod = 4332.59;
	m_pObjects.back()->m_Inclination = 0.0227765467;

	//Saturn
	//equatorial radius = 6378.1 = 0.00037796 AU
	//orbital radius = ? km = 9.54 AU
	m_pObjects.push_back(new Object("Saturn"));
	//
	m_pObjects.back()->m_Mass = 5.6846f*pow(10.0f,26.0f);
	m_pObjects.back()->m_EquatorialRadius = 60268;
	m_pObjects.back()->m_Eccentricity = 0.055723219;
	m_pObjects.back()->m_SemiMajorAxis = 1433449370;
	m_pObjects.back()->m_OrbitalPeriod = 10759.22;
	m_pObjects.back()->m_Inclination = 0.04337562;

	//Uranus
	//equatorial radius = 6378.1 = 0.00016028 AU
	//orbital radius = ? km = 19.22 AU
	m_pObjects.push_back(new Object("Uranus"));
	//
	m_pObjects.back()->m_Mass = 8.6810f*pow(10.0f,25.0f);
	m_pObjects.back()->m_EquatorialRadius = 25559;
	m_pObjects.back()->m_Eccentricity = 0.044405586;
	m_pObjects.back()->m_SemiMajorAxis = 2876679082;
	m_pObjects.back()->m_OrbitalPeriod = 30799.095;
	m_pObjects.back()->m_Inclination = 0.013483645856;

	//Neptune
	//equatorial radius = 6378.1 = 0.00015532 AU
	//orbital radius = ? km = 30.06 AU
	m_pObjects.push_back(new Object("Neptune"));
	//
	m_pObjects.back()->m_Mass = 1.0243*pow(10.0,26.0);
	m_pObjects.back()->m_EquatorialRadius = 24764;
	m_pObjects.back()->m_Eccentricity = 0.011214269;
	m_pObjects.back()->m_SemiMajorAxis = 4503443661;
	m_pObjects.back()->m_OrbitalPeriod = 60190;
	m_pObjects.back()->m_Inclination = 0.030856984;
	//*/

	//set up planets
	for(unsigned short n=1;n<m_pObjects.size();n++)
	{
		Object* current = m_pObjects.at(n);
		current->m_Primary = m_pObjects.front();
		current->m_OrbitScale = orbitScale;
		current->m_RadiusScale = radiusScale;
		current->m_OrbitalRate = orbitalRate;
		//
		current->m_mat.Ambient.r = 0.1f;
		current->m_mat.Ambient.g = 0.1f;
		current->m_mat.Ambient.b = 0.1f;
		//
		current->Init();
	}
	//create render objects
	for(unsigned short n=0;n<m_pObjects.size();n++)
	{
		Object* current = m_pObjects.at(n);
		//
		current->CreateObject(dx_manager.GetDevice());
		m_Renderer->AddObject(current);
	}

	//initialize viewfocus to sun
	SetViewFocus(0);

	//setup grid
	m_Grid = res_manager.GetGrid(dx_manager.GetDevice());

	//add an omnidirectional light
	Light* omni = new Light();
	omni->InitOmni();
	omni->SetPosition(0,0,0);
	omni->SetRange(400.0f);
	omni->SetAttenuation(1.0f);
	m_Renderer->AddLight(omni);
}

// this function updates the different elements of the program, then calls the renders function
bool App::Update(float a_dt)
{
	//update planets
	for(unsigned short n=1;n<m_pObjects.size();n++)
	{
		m_pObjects.at(n)->Update(a_dt,m_TimePassageRate);
	}

	//update text
	Object* pPlanet = m_pObjects.at(m_CurViewing);
	m_Renderer->m_Titles.at(1)->Text = "Solar body: ";
	m_Renderer->m_Titles.at(1)->Text.append(pPlanet->m_Name);
	res_manager.UpdateRect(m_Renderer->m_Titles.at(1));
	m_Renderer->m_Titles.at(2)->Text = "Simulated distance to Sun: ";
	m_Renderer->m_Titles.at(2)->Text.append(utils::dtos(pPlanet->m_OrbitalRadius * pPlanet->m_OrbitScale));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(2));
	m_Renderer->m_Titles.at(3)->Text = "Real distance to Sun: ";
	m_Renderer->m_Titles.at(3)->Text.append(utils::dtos(pPlanet->m_OrbitalRadius));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(3));
	m_Renderer->m_Titles.at(4)->Text = "Simulated radius: ";
	m_Renderer->m_Titles.at(4)->Text.append(utils::dtos(pPlanet->m_Radius));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(4));
	m_Renderer->m_Titles.at(5)->Text = "Real radius: ";
	m_Renderer->m_Titles.at(5)->Text.append(utils::dtos(pPlanet->m_EquatorialRadius));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(6));
	m_Renderer->m_Titles.at(6)->Text = "Simulated X: ";
	m_Renderer->m_Titles.at(6)->Text.append(utils::dtos(pPlanet->m_Position.x));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(6));
	m_Renderer->m_Titles.at(7)->Text = "Simulated Y: ";
	m_Renderer->m_Titles.at(7)->Text.append(utils::dtos(pPlanet->m_Position.y));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(7));
	m_Renderer->m_Titles.at(8)->Text = "Simulated Z: ";
	m_Renderer->m_Titles.at(8)->Text.append(utils::dtos(pPlanet->m_Position.z));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(8));
	m_Renderer->m_Titles.at(7)->Text = "Mass: ";
	m_Renderer->m_Titles.at(7)->Text.append(utils::dtos(pPlanet->m_Mass));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(9));
	m_Renderer->m_Titles.at(8)->Text = "Inclination: ";
	m_Renderer->m_Titles.at(8)->Text.append(utils::dtos(pPlanet->m_Inclination));
	res_manager.UpdateRect(m_Renderer->m_Titles.at(10));
	//
	if(m_IsShowingDebug)
	{
		m_Renderer->m_Titles.at(9)->Text = "Camera X: ";
		m_Renderer->m_Titles.at(9)->Text.append(utils::dtos(m_Renderer->m_ViewAngle.x));
		res_manager.UpdateRect(m_Renderer->m_Titles.at(11));
		//
		m_Renderer->m_Titles.at(10)->Text = "Camera Y: ";
		m_Renderer->m_Titles.at(10)->Text.append(utils::dtos(m_Renderer->m_ViewAngle.y));
		res_manager.UpdateRect(m_Renderer->m_Titles.at(12));
		//
		m_Renderer->m_Titles.at(11)->Text = "Camera Z: ";
		m_Renderer->m_Titles.at(11)->Text.append(utils::dtos(m_Renderer->m_ViewAngle.z));
		res_manager.UpdateRect(m_Renderer->m_Titles.at(13));
		//
		m_Renderer->m_Titles.at(12)->Text = "Time Passage Rate: ";
		m_Renderer->m_Titles.at(12)->Text.append(utils::dtos(m_TimePassageRate));
		res_manager.UpdateRect(m_Renderer->m_Titles.at(14));
		//
		m_Renderer->m_Titles.at(13)->Text = "View Radius: ";
		m_Renderer->m_Titles.at(13)->Text.append(utils::dtos(m_Renderer->m_ViewRadius));
		res_manager.UpdateRect(m_Renderer->m_Titles.at(15));
		//
		m_Renderer->m_Titles.at(14)->Text = "Zoom Rate: ";
		m_Renderer->m_Titles.at(14)->Text.append(utils::dtos(m_Renderer->m_ViewZoomRate));
		res_manager.UpdateRect(m_Renderer->m_Titles.at(16));
		//
		m_Renderer->m_Titles.at(15)->Text = "Rotation Rate: ";
		m_Renderer->m_Titles.at(15)->Text.append(utils::dtos(m_Renderer->m_ViewRotRate));
		res_manager.UpdateRect(m_Renderer->m_Titles.at(17));
	}

	//update viewpos
	m_Renderer->m_LookAtPos = m_pObjects.at(m_CurViewing)->GetPos();

	//render everything
	return m_Renderer->Render(a_dt,dx_manager.GetDevice());
}

void App::cleanUp()
{
	window_manager.cleanUp();
}

void App::ResizeBodies(float a_Amount)
{
	if(a_Amount)
	{
		//std::cout << "Resizing meshes..." << std::endl;
		IDirect3DDevice9* device = dx_manager.GetDevice();
		for(unsigned short n=0;n<m_pObjects.size();n++)
		{
			m_pObjects.at(n)->ResizeMesh(device,a_Amount);
		}
	}
}

void App::ModifyOrbitalRadius(float a_Amount)
{
	Object* target = m_pObjects.at(m_CurViewing);
	if(target->m_OrbitalRadius + a_Amount > 0)
	{
		target->m_OrbitalRadius += a_Amount;
		double dif = target->m_OrbitalRadius / utils::Vec3Mag(target->m_Position);
		target->m_Position *= (FLOAT)dif;
	}
}

void App::ModifyOrbitalPeriod(float a_Amount)
{
	//
	if(m_pObjects.at(m_CurViewing)->m_OrbitalPeriod + a_Amount > 0)
		m_pObjects.at(m_CurViewing)->m_OrbitalPeriod += a_Amount;
}

void App::IncrPlanetaryFocus()
{
	if(++m_CurViewing >= m_pObjects.size())
		m_CurViewing = 0;
	//std::cout << "IncrPlanetaryFocus(), m_CurViewing: " << m_CurViewing << std::endl;
	SetViewFocus(m_CurViewing);
}

void App::DecrPlanetaryFocus()
{
	if(--m_CurViewing == 65535)
		m_CurViewing = m_pObjects.size() - 1;
	//std::cout << "DecrPlanetaryFocus(), m_CurViewing: " << m_CurViewing << std::endl;
	SetViewFocus(m_CurViewing);
}

void App::SetViewFocus(unsigned short a_PlanetNum)
{
	if(a_PlanetNum < m_pObjects.size() && a_PlanetNum > -1)
	{
		m_CurViewing = a_PlanetNum;
	}
	else
	{
		m_CurViewing = 0;
	}
	//std::cout << "now viewing object: " << m_CurViewing << " / " << m_pObjects.size() - 1  << std::endl;
	Object* target = m_pObjects.at(m_CurViewing);
	//
	m_Renderer->m_LookAtPos = target->GetPos();
	//m_Renderer->m_ViewRadius = (long)target->m_Radius * 4;
	//std::cout << "viewrad: " << m_Renderer->m_ViewRadius << std::endl;
	//m_Renderer->m_ViewZoomRate = target->m_Radius;
	//m_Renderer->m_ViewRotRate = target->m_Radius;
}

void App::ToggleDebugInfo()
{
	if(m_IsShowingDebug)
	{
		//clear debug text
		while(res_manager.ClearTitle(11)){}
		m_IsShowingDebug = false;
	}
	else
	{
		//setup debug output text
		res_manager.AddTitle("X: ",1,320);
		res_manager.AddTitle("Y: ",2,320);
		res_manager.AddTitle("Z: ",3,320);
		res_manager.AddTitle("Time Pass Rate: ",4,320);
		res_manager.AddTitle("ViewRad: ",5,320);
		res_manager.AddTitle("Zoom Rate: ",6,320);
		res_manager.AddTitle("Rotation Rate: ",7,320);
		m_IsShowingDebug = true;
	}
}
