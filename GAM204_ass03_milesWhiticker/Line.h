#ifndef LINE_H
#define LINE_H

#include "Drawable.h"

struct VertexData
{
	D3DVECTOR pos;
	D3DCOLOR col;
};

class Line : public Drawable
{
public:
	Line();
	virtual ~Line();
	//
	virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
	virtual void Render(float a_dt, float a_TimePassageRate, IDirect3DDevice9* a_pDevice);
	//
	static const DWORD VERTEX_FORMAT_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	//
	VertexData* v1;
	VertexData* v2;
	D3DXVECTOR3 m_Offset;
	//
	bool m_LightEnabled;
	D3DMATERIAL9 m_Mat;
};

#endif