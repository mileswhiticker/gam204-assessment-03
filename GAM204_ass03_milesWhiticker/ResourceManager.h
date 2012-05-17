#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <list>

class Drawable;
class Sphere;
class Renderer;
class Light;
class Grid;
struct IDirect3DDevice9;

struct tagRECT;
typedef tagRECT RECT;

struct Title;

class ResMgr
{
public:
	static ResMgr& GetInstance()
	{
		static ResMgr* instance = new ResMgr;
		return *instance;
	}
	void Init(Renderer* a_Renderer);
	Grid* GetGrid(IDirect3DDevice9* a_pDevice);
	//
	Title* AddTitle(std::string a_String, short a_RowY = 0, long a_OffSetX = 0);
	void UpdateRect(Title* a_pTitle);
	bool ClearTitle(Title* a_pTitle);
	bool ClearTitle(unsigned short a_Index);
	void ClearAllTitles();
	Light* m_Light;
	//
	Renderer* m_Renderer;
	//
private:
	ResMgr();
	Grid* m_Grid;
	//
	typedef std::list<Drawable*> DrawableObjectList;
	DrawableObjectList m_Visible;
	DrawableObjectList m_Hidden;
};

#endif