//Renderer class written by Miles Whiticker from code originally by Scott Taylor

#include "Renderer.h"

#include "Drawable.h"
#include "Light.h"
#include "Timer.h"
#include "utils.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

Renderer::Renderer(IDirect3DDevice9* a_pDevice)
:	m_Yaw(0)
,	m_Pitch(0)
,	m_TimePassageRate(1.0f)
,	m_ApplyViewZoom(0)
,	m_ViewZoomRate(1.0f)
,	m_ApplyViewPitch(0)
,	m_ApplyViewYaw(0)
,	m_ViewRotRate(5.0f)
,	m_ViewRadius(10)
,	m_DefaultFont(NULL)
{
	m_ViewAngle = D3DXVECTOR3(0, 0, m_ViewRadius);
	m_LookAtPos = D3DXVECTOR3(0, 0, 0);

	HRESULT result = D3DXCreateFont( a_pDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_DefaultFont );
	if(result != D3D_OK)
		std::cout << "Failed to create default font, you will not be able to see any text." << std::endl;
}

//
// Adds an object to the renderer
// Returns true if successful
//
bool Renderer::AddObject(Drawable* a_pObject)
{
	if (!a_pObject)
	{
		return false;
	}

	//@TODO: assert() that a_pObject isn't already in the list...
	//       It may be helpful to write your own bool Renderer::HasObject(a_pObject).

	m_drawableObjects.push_back(a_pObject);
	return true;
}

//
// Removes an object from the renderer
// Returns true if successful
//
bool Renderer::RemoveObject(Drawable* a_pObject)
{
	// Look for this object in our list
	for (DrawableObjectList::iterator iter = m_drawableObjects.begin(); iter != m_drawableObjects.end(); ++iter)
	{
		Drawable* pElem = *iter;
		if (pElem == a_pObject)
		{
			// Found the object! Remove it from the list
			m_drawableObjects.erase(iter);
			return true;
		}
	}
	return false;  // Not found
}

//
// Adds a light to the renderer
// Returns true if successful
//
bool Renderer::AddLight(Light* a_pLight)
{
	if (!a_pLight)
		return false;
	m_lights.push_back(a_pLight);
	return true;
}

//
// Removes a light from the renderer
// Returns true if successful
//
bool Renderer::RemoveLight(Light* a_pLight)
{
	// Look for this light in our list
	for (LightList::iterator iter = m_lights.begin(); iter != m_lights.end(); ++iter)
	{
		Light* pElem = *iter;
		if (pElem == a_pLight)
		{
			// Found the light! Remove it from the list
			m_lights.erase(iter);
			return true;
		}
	}
	return false;  // Not found
}

//
// Renders all objects
// Returns true if successful
//
bool Renderer::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		return false;
	}

	// Clear backbuffer
	a_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//work out the rotation Euler angles
	m_Yaw = m_ApplyViewYaw * m_ViewRotRate * a_dt;
	m_ApplyViewYaw = 0;
	m_Pitch = m_ApplyViewPitch * m_ViewRotRate * a_dt;
	m_ApplyViewPitch = 0;

	//apply zoom
	float viewZoomRate = (float)utils::Vec3Mag(m_ViewAngle) * 0.1F;
	if(!viewZoomRate)
		viewZoomRate = 1;
	if(m_ViewRadius + m_ApplyViewZoom * viewZoomRate > 0)
		m_ViewRadius += (float)m_ApplyViewZoom * viewZoomRate;
	D3DXVec3Normalize(&m_ViewAngle,&m_ViewAngle);
	m_ViewAngle *= m_ViewRadius;
	m_ApplyViewZoom = 0;

	//work out mouse rotation
	D3DXQUATERNION rotQ;
	D3DXQUATERNION viewAngleQuat = utils::Vec3ToQuat(m_ViewAngle);

	//build rotation quaternion
	D3DXQuaternionRotationYawPitchRoll(&rotQ,m_Yaw,m_Pitch,0.0f);

	//rotate look-from-pos by quaternion
	D3DXQuaternionMultiply(&viewAngleQuat,&rotQ,&viewAngleQuat);
	D3DXQuaternionInverse(&rotQ,&rotQ);
	D3DXQuaternionMultiply(&rotQ,&viewAngleQuat,&rotQ);
	D3DXVECTOR3 lookFromPos = utils::QuatToVec3(viewAngleQuat);

	//add the view angle vector to the position the view is centred on
	lookFromPos += m_LookAtPos;

	//set m_Viewangle to the new viewing angle
	m_ViewAngle = utils::QuatToVec3(viewAngleQuat);

	// Create our camera (view-space) transform for this frame
	D3DXMATRIX worldToView;
	D3DXVECTOR3 upVec(0, 1, 0);
	D3DXMatrixLookAtLH(&worldToView,&lookFromPos, &m_LookAtPos, &upVec);
	a_pDevice->SetTransform(D3DTS_VIEW, &worldToView);

	// Create our projection matrix for this frame
	D3DXMATRIX viewToScreen;
	D3DXMatrixPerspectiveFovLH(&viewToScreen, 3.14f / 4, 1, 1, 5000);
	a_pDevice->SetTransform(D3DTS_PROJECTION, &viewToScreen);

	// Set up common render states
	a_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	a_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	a_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	a_pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	a_pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1,1,1,1));

	// Begin rendering
	a_pDevice->BeginScene();

	// Set up lights
	int curLightId = 0;
	for (LightList::iterator iter = m_lights.begin(); iter != m_lights.end(); ++iter)
	{
		Light* pElem = *iter;
		HRESULT result = a_pDevice->SetLight(curLightId, &pElem->GetLightData());
		if(result != D3D_OK)	
			return false;
		result = a_pDevice->LightEnable(curLightId, TRUE);
		if(result != D3D_OK)
			return false;
		++curLightId;
	}

	// Render world
	for (DrawableObjectList::iterator iter = m_drawableObjects.begin(); iter != m_drawableObjects.end(); ++iter)
	{
		Drawable* pElem = *iter;
		pElem->Render(a_dt, m_TimePassageRate, a_pDevice);
	}

	//render titles
	for(unsigned short n=0;n<m_Titles.size();n++)
	{
		int len = m_Titles[n]->Text.size()+1;
		wchar_t *wText = new wchar_t[len];
		memset(wText,0,len);
		MultiByteToWideChar(CP_ACP, NULL, m_Titles[n]->Text.c_str(), -1, wText,len );
		m_DefaultFont->DrawTextW(NULL, (LPCTSTR)wText, -1, m_Titles[n]->Rect, 0, D3DCOLOR_XRGB(0,255,0));
	}

	// Finish rendering
	a_pDevice->EndScene();

	// Display the backbuffer
	a_pDevice->Present(NULL, NULL, NULL, NULL);

	return true;
}

RECT* Renderer::GetTitleRect(std::string a_String)
{
	RECT* rect = new RECT;
	rect->top = 0;
	rect->left = 0;
	rect->right = 0;
	rect->bottom = 0;
	int len = a_String.size()+1;
	wchar_t *wText = new wchar_t[len];
	memset(wText,0,len);
	MultiByteToWideChar(CP_ACP, NULL, a_String.c_str(), -1, wText,len );
	m_DefaultFont->DrawTextW(NULL, (LPCTSTR)a_String.c_str(), -1, rect, DT_CALCRECT, D3DCOLOR_XRGB(255,255,255));
	return rect;
}
