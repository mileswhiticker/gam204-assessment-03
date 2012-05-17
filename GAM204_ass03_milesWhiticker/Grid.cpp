#include "Grid.h"
#include "Line.h"
#include <d3dx9.h>
#include <d3d9types.h>
#include "Renderer.h"

Grid::Grid(D3DXVECTOR3 a_GridWidth, float a_CellSize, D3DXVECTOR3 a_Origin)
:	m_GridMax(a_GridWidth)
,	m_CellSize(a_CellSize)
,	m_Origin(a_Origin)
	//
,	m_DiscreteCells(true)
,	m_LightEnabled(false)
{
	//
}

Grid::~Grid()
{
	while(m_Lines.size())
	{
		delete m_Lines.back();
		m_Lines.pop_back();
	}
}

bool Grid::CreateGrid(IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		return false;
	}
	Renderer* renderer = Renderer::GetInstance();

	//grab grid sizes
	short numVertices = (((short)m_GridMax.x)*2 + 1) * (((short)m_GridMax.y)*2 + 1) * (((short)m_GridMax.z)*2 + 1);

	//create lines along the z axis
	for(short i = -(short)m_GridMax.x; i < m_GridMax.x + 1; i++)
	{
		for(short j = -(short)m_GridMax.y; j < m_GridMax.y + 1; j++)
		{
			for(short k = -(short)m_GridMax.z;  k < m_GridMax.z; k++)
			{
				//define a new line of the grid
				m_Lines.push_back(new Line());
				m_Lines.back()->m_LightEnabled = m_LightEnabled;
				//setup the two vertices of the line
				m_Lines.back()->v1->pos = D3DXVECTOR3(i*m_CellSize + m_Origin.x, j*m_CellSize + m_Origin.y, k*m_CellSize + m_Origin.z);
				m_Lines.back()->v1->col = D3DCOLOR_ARGB(255,0,255,255);
				//k++;
				m_Lines.back()->v2->pos = D3DXVECTOR3(i*m_CellSize + m_Origin.x, j*m_CellSize + m_Origin.y, (k+1)*m_CellSize + m_Origin.z);
				m_Lines.back()->v2->col = D3DCOLOR_ARGB(255,0,255,255);
				//create object
				m_Lines.back()->CreateObject(a_pDevice);
				renderer->AddObject(m_Lines.back());
			}
		}
	}

	//create lines along the y axis
	for(short i = -(short)m_GridMax.x; i < m_GridMax.x + 1; i++)
	{
		for(short k = -(short)m_GridMax.z;  k < m_GridMax.z + 1; k++)
		{
			for(short j = -(short)m_GridMax.y; j < m_GridMax.y; j++)
			{
				//define a new line of the grid
				m_Lines.push_back(new Line());
				m_Lines.back()->m_LightEnabled = m_LightEnabled;
				//setup the two vertices of the line
				m_Lines.back()->v1->pos = D3DXVECTOR3(i*m_CellSize + m_Origin.x, j*m_CellSize + m_Origin.y, k*m_CellSize + m_Origin.z);
				m_Lines.back()->v1->col = D3DCOLOR_ARGB(255,0,255,255);
				//j++;
				m_Lines.back()->v2->pos = D3DXVECTOR3(i*m_CellSize + m_Origin.x, (j+1)*m_CellSize + m_Origin.y, k*m_CellSize + m_Origin.z);
				m_Lines.back()->v2->col = D3DCOLOR_ARGB(255,0,255,255);
				//create object
				m_Lines.back()->CreateObject(a_pDevice);
				renderer->AddObject(m_Lines.back());
			}
		}
	}

	//create lines along the x axis
	for(short j = -(short)m_GridMax.y; j < m_GridMax.y + 1; j++)
	{
		for(short k = -(short)m_GridMax.z;  k < m_GridMax.z + 1; k++)
		{
			for(short i = -(short)m_GridMax.x; i < m_GridMax.x; i++)
			{
				//define a new line of the grid
				m_Lines.push_back(new Line());
				m_Lines.back()->m_LightEnabled = m_LightEnabled;
				//setup the two vertices of the line
				m_Lines.back()->v1->pos = D3DXVECTOR3(i*m_CellSize + m_Origin.x, j*m_CellSize + m_Origin.y, k*m_CellSize + m_Origin.z);
				m_Lines.back()->v1->col = D3DCOLOR_ARGB(255,0,255,255);
				//i++;
				m_Lines.back()->v2->pos = D3DXVECTOR3((i+1)*m_CellSize + m_Origin.x, j*m_CellSize + m_Origin.y, k*m_CellSize + m_Origin.z);
				m_Lines.back()->v2->col = D3DCOLOR_ARGB(255,0,255,255);
				//create object
				m_Lines.back()->CreateObject(a_pDevice);
				renderer->AddObject(m_Lines.back());
			}
		}
	}

	return true;
}
