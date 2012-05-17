#include "Sphere.h"

#include <d3dx9.h>
#include <iostream>

//GAM204 Ass03 - Written by Miles Whiticker from original code by Scott Taylor

Sphere::Sphere()
:	m_Position(D3DXVECTOR3(0.0f,0.0f,0.0f))
,	m_Slices(100)
,	m_Stacks(100)
,	m_pMesh(NULL)
,	m_Radius(1.0)
{
	// Set up our material
	ZeroMemory(&m_mat, sizeof(m_mat));  // Zero out the material (ie. all colours black, power set to zero)
	m_mat.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mat.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}

Sphere::~Sphere()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

//
// Sets up this object with some data
// Returns true if successful
//
bool Sphere::CreateObject(IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		std::cout << "No device found." << std::endl;
		return false;
	}

	// Create a shape in our mesh helper
	HRESULT result = D3DXCreateSphere(a_pDevice, (FLOAT)m_Radius, m_Slices, m_Stacks, &m_pMesh, NULL);

	if (result != D3D_OK)
	{
		std::cout << "Could not create sphere." << std::endl;
		return false;
	}

	return true;
}

void Sphere::SetEmissive(float a_MatVal)
{
	//
	m_mat.Emissive = D3DXCOLOR(a_MatVal,a_MatVal,a_MatVal,1);
}

void Sphere::SetAmbient(float a_MatVal)
{
	//
	m_mat.Ambient = D3DXCOLOR(a_MatVal,a_MatVal,a_MatVal,1);
}

void Sphere::Render(float a_dt, float a_TimePassageRate, IDirect3DDevice9* a_pDevice)
{
	if (a_pDevice && m_pMesh)
	{
		//set material and texture properties
		a_pDevice->SetMaterial(&m_mat);
		a_pDevice->SetTexture(0, NULL);

		//translate to coords
		D3DXMATRIX translationMat;
		D3DXMatrixTranslation(&translationMat, m_Position.x, m_Position.y, m_Position.z);

		a_pDevice->SetTransform(D3DTS_WORLD, &translationMat);

		//draw
		m_pMesh->DrawSubset(0);
	}
}

void Sphere::ResizeMesh(IDirect3DDevice9* a_pDevice,double a_Val)
{
	D3DMATERIAL9 oldMat = m_mat;
	m_pMesh->Release();
	m_Radius *= a_Val;
	CreateObject(a_pDevice);
	m_mat.Ambient = oldMat.Ambient;
	m_mat.Emissive = oldMat.Emissive;
	m_mat.Specular = oldMat.Specular;
	m_mat.Diffuse = oldMat.Diffuse;
	//std::cout << "	Mesh resized from " << m_Radius/a_Val << " to " << m_Radius << std::endl;
}

D3DXVECTOR3 Sphere::GetPos()
{
	return m_Position;
}