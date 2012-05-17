#ifndef APP_H
#define APP_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <vector>

class WndwMgr;
class ResMgr;
class Renderer;
class DXMgr;
class Object;
class Grid;

class App
{
public:
	static App* GetInstance(HINSTANCE a_hInst = NULL)
	{
		static App* instance = NULL;
		if(!instance && a_hInst)
			instance = new App(a_hInst);
		return instance;
	}
	bool Update(float a_dt);
	void cleanUp();
	//
	void SetViewFocus(unsigned short a_PlanetNum = 0);
	void IncrPlanetaryFocus();
	void DecrPlanetaryFocus();
	void ResizeBodies(float a_Amount);
	void ModifyOrbitalRadius(float a_Amount);
	void ModifyOrbitalPeriod(float a_Amount);
	//
	float m_TimePassageRate;
	//
	void ToggleDebugInfo();
private:
	App(HINSTANCE a_hInst);
	void initD3D(HWND hWnd);
	bool m_IsShowingDebug;
	//
	DXMgr& dx_manager;
	WndwMgr& window_manager;
	ResMgr& res_manager;
	Renderer* m_Renderer;
	//grid aligned to the plane running out of the sun's equator
	Grid* m_Grid;
	std::vector<Object*> m_pObjects;
	unsigned short m_CurViewing;
	//
};

#endif APP_H