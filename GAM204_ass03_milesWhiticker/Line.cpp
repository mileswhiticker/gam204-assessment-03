#include "Line.h"
#include <iostream>

Line::Line()
:	m_Offset(D3DXVECTOR3(0,0,0))
,	v1(new VertexData())
,	v2(new VertexData())
{
	m_pVertexBuf = NULL;
	m_pIndexBuf = NULL;
	//
	v1->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	v1->col = D3DCOLOR_ARGB(255, 0, 255, 255);
	v2->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	v2->col = D3DCOLOR_ARGB(255, 0, 255, 255);
}

Line::~Line()
{
	if(m_pVertexBuf)
		m_pVertexBuf->Release();
	if(m_pIndexBuf)
		m_pIndexBuf->Release();
}

bool Line::CreateObject(IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		return false;
	}

	//create vertex buffer
	HRESULT result = a_pDevice->CreateVertexBuffer(sizeof(VertexData) * 2, 0, VERTEX_FORMAT_FVF, D3DPOOL_DEFAULT, &m_pVertexBuf, NULL);
	if (result != D3D_OK)
	{
		return false;
	}

	//create index buffer
	a_pDevice->CreateIndexBuffer(sizeof(short) * 2, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuf, NULL);
	if (result != D3D_OK)
	{
		m_pVertexBuf->Release();
		m_pVertexBuf = NULL;
		return false;
	}

	//setup vertex data
	VertexData verts[2];
	verts[0] = *v1;
	verts[1] = *v2;

	//set up indices
	short indices[2];
	indices[0] = 0;
	indices[1] = 1;

	//copy vertex data into buffer
	void* pLockedData = NULL;
	m_pVertexBuf->Lock(0, sizeof(VertexData) * 2, &pLockedData, 0);
	memcpy(pLockedData, verts, sizeof(VertexData) * 2);
	m_pVertexBuf->Unlock();
	pLockedData = NULL;

	//copy index data into buffer
	m_pIndexBuf->Lock(0, sizeof(short) * 2, &pLockedData, 0);
	memcpy(pLockedData, indices, sizeof(short) * 2);
	m_pIndexBuf->Unlock();
	pLockedData = NULL;

	return true;
}

void Line::Render(float a_dt, float a_TimePassageRate, IDirect3DDevice9* a_pDevice)
{
	if (a_pDevice && m_pVertexBuf && m_pIndexBuf)
	{
		// setup material
		//*
		ZeroMemory(&m_Mat, sizeof(m_Mat));
		m_Mat.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		if(m_LightEnabled)
		{
			//m_Mat.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			m_Mat.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			m_Mat.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		}
		a_pDevice->SetMaterial(&m_Mat);
		//*/
		a_pDevice->SetTexture(0,NULL);

		// center the grid on the origin
		D3DXMATRIX translationMat;
		D3DXMatrixTranslation(&translationMat, m_Offset.x, m_Offset.y, m_Offset.z);

		a_pDevice->SetTransform(D3DTS_WORLD, &translationMat);

		//set vertex data
		a_pDevice->SetStreamSource(0, m_pVertexBuf, 0, sizeof(VertexData));
		a_pDevice->SetFVF(VERTEX_FORMAT_FVF);

		//set index data
		a_pDevice->SetIndices(m_pIndexBuf);

		//draw line
		a_pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, 2, 0, 1);
	}
}
