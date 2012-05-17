#ifndef GRID_H
#define GRID_H

#include "Drawable.h"
#include <vector>

class Line;

class Grid
{
public:
	Grid(D3DXVECTOR3 a_GridWidth = D3DXVECTOR3(10.0f,0.0f,10.0f), float a_CellSize = 40.0f, D3DXVECTOR3 a_Origin = D3DXVECTOR3(0,0,0));
	bool CreateGrid(IDirect3DDevice9* a_pDevice);
	~Grid();
	//
	D3DXVECTOR3 m_GridMax;
	float m_CellSize;
	D3DXVECTOR3 m_Origin;
	//
	bool m_DiscreteCells;
	bool m_LightEnabled;
	//
private:
	std::vector<Line*> m_Lines;
	//
};

#endif