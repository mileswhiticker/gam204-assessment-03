//Renderer class written by Miles Whiticker from code by Scott Taylor

#if !defined(RENDERER_H)
#define RENDERER_H

#include <list>
#include <vector>
#include <d3d9.h>
#include <d3d9types.h>
#include <D3dx9core.h>

#ifndef S_TITLE
#define S_TITLE

struct Title
{
	std::string Text;
	RECT* Rect;
	long RowY;
	long OffSetX;
};

#endif

class Drawable;
class Light;
class Timer;
struct IDirect3DDevice9;

class Renderer
{
public:
	static Renderer* GetInstance(IDirect3DDevice9* a_pDevice = NULL)
	{
		static Renderer* instance = NULL;
		if(!instance && a_pDevice)
			instance = new Renderer(a_pDevice);
		return instance;
	}
	bool Render(float a_dt, IDirect3DDevice9* a_pDevice);
	///handle modular creation / deletion of objects
	bool AddObject(Drawable* a_pObject);
	bool RemoveObject(Drawable* a_pObject);
	//handle modular creation / deletion of lights
	bool AddLight(Light* a_pLight);
	bool RemoveLight(Light* a_pLight);
	//handle outputting text to screen
	RECT* GetTitleRect(std::string a_String);
	std::vector< Title* > m_Titles;
	LPD3DXFONT m_DefaultFont;
	//these are set by the WndProc when the mouse moves
	//every render call, if any of these are true the view changes accordingly
	short m_ApplyViewPitch;			//positive = over horizon,				negative = under horizon
	short m_ApplyViewYaw;			//positive = clockwise around centre,	negative = anti-clockwise around centre
	short m_ApplyViewZoom;			//positive = zoom out,					negative = zoom in
	//distance (in discrete units) from the origin (currently viewed body)
	float m_ViewRadius;
	//rate of passage of time
	float m_TimePassageRate;
	//view positions in space
	D3DXVECTOR3 m_LookAtPos;		//co-ords of viewing object
	D3DXVECTOR3 m_ViewAngle;		//relative to origin
	//
	float m_Yaw;					//not required
	float m_Pitch;					//not required
	//
	float m_ViewZoomRate;			//rate (discrete units) of change per second
	float m_ViewRotRate;			//rate (rads) of rotation per second, same for vert and horiz
private:
	Renderer(IDirect3DDevice9* a_pDevice);
	//
	typedef std::list<Drawable*> DrawableObjectList;
	DrawableObjectList m_drawableObjects;
	typedef std::list<Light*> LightList;
	LightList m_lights;
};

#endif  // RENDERER_H

