#ifndef SPHERE_H
#define SPHERE_H

#include "Drawable.h"

//#include <d3d9.h>
//#include <d3d9types.h>

struct IDirect3DDevice9;
struct ID3DXMesh;

struct lVec3
{
	long x;
	long y;
	long z;
};

class Sphere : public Drawable
{
public:
	Sphere();
	virtual ~Sphere();
	//
	virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
	virtual void Render(float a_dt, float a_TimePassageRate, IDirect3DDevice9* a_pDevice);
	//
	void SetEmissive(float a_MatVal);
	void SetAmbient(float a_MatVal);
	//
	void ResizeMesh(IDirect3DDevice9* a_pDevice,double a_Val);
	//
	D3DXVECTOR3 GetPos();
	double m_Radius;
	D3DXVECTOR3 m_Position;
	D3DMATERIAL9 m_mat;
protected:
	//
	int m_Slices;
	int m_Stacks;
	//
	ID3DXMesh* m_pMesh;
};

#endif