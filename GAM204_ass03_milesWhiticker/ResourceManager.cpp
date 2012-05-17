#include "ResourceManager.h"
#include "WindowManager.h"

#include "Light.h"
//#include "Sphere.h"
#include "Renderer.h"
#include "Grid.h"

#include <iostream>

ResMgr::ResMgr()
:	m_Renderer(NULL)
,	m_Grid(NULL)
{
	//no hacky stuff here that requires rendering will work, use Init() instead
}

void ResMgr::Init(Renderer* a_Renderer)
{
	m_Renderer = a_Renderer;
	//add an omnidirectional light
	/*
	*/
	m_Light = new Light();
	m_Light->InitOmni();
	m_Light->SetPosition(-2,0,-2);
	//m_Light->SetCircling(3.0f);
	m_Renderer->AddLight(m_Light);
}

Grid* ResMgr::GetGrid(IDirect3DDevice9* a_pDevice)
{
	if(!m_Grid && a_pDevice)
	{
		m_Grid = new Grid();
		if(!m_Grid->CreateGrid(a_pDevice))
		{
			delete m_Grid;
			m_Grid = NULL;
		}
	}
	return m_Grid;
}

Title* ResMgr::AddTitle(std::string a_String, short a_RowY, long a_OffSetX)
{
	Title* title = new Title;
	title->Rect = m_Renderer->GetTitleRect(a_String);
	title->Text = a_String;
	title->OffSetX = a_OffSetX;
	title->RowY = a_RowY;
	//
	title->Rect->top += a_RowY*19;
	title->Rect->bottom += a_RowY*19;
	title->Rect->left = a_OffSetX;
	title->Rect->right = a_OffSetX + title->Rect->right;
	/*if(a_OffSetX > 640)
		a_OffSetX = 640;
	if(a_OffSetX < 0)
		a_OffSetX = 0;
	if( (a_OffSetX + title->Rect->right/2) > 640 )
	{
		title->Rect->left = a_OffSetX - title->Rect->right;
		title->Rect->right = a_OffSetX;
	}
	else if( (a_OffSetX - title->Rect->right/2) > 0 )
	{
		title->Rect->left = a_OffSetX - title->Rect->right/2;
		title->Rect->right = a_OffSetX + title->Rect->right/2;
	}
	else
	{
		title->Rect->left = a_OffSetX;
		title->Rect->right = a_OffSetX + title->Rect->right/2;
	}*/
	m_Renderer->m_Titles.push_back(title);
	return title;
}

void ResMgr::UpdateRect(Title* a_pTitle)
{
	delete a_pTitle->Rect;
	a_pTitle->Rect = m_Renderer->GetTitleRect(a_pTitle->Text);
	//
	a_pTitle->Rect->top += a_pTitle->RowY*19;
	a_pTitle->Rect->bottom += a_pTitle->RowY*19;
	a_pTitle->Rect->left = a_pTitle->OffSetX;
	a_pTitle->Rect->right = a_pTitle->OffSetX + a_pTitle->Rect->right;
	/*if( (a_pTitle->OffSetX + a_pTitle->Rect->right/2) > 640 )
	{
		a_pTitle->Rect->left = a_pTitle->OffSetX - a_pTitle->Rect->right;
		a_pTitle->Rect->right = a_pTitle->OffSetX;
	}
	else if( (a_pTitle->OffSetX - a_pTitle->Rect->right/2) > 0 )
	{
		a_pTitle->Rect->left = a_pTitle->OffSetX - a_pTitle->Rect->right/2;
		a_pTitle->Rect->right = a_pTitle->OffSetX + a_pTitle->Rect->right/2;
	}
	else
	{
		a_pTitle->Rect->left = a_pTitle->OffSetX;
		a_pTitle->Rect->right = a_pTitle->OffSetX + a_pTitle->Rect->right/2;
	}*/
	//
	/*std::cout << a_pTitle->Text.c_str() << std::endl;
	std::cout << "rect->left = " << a_pTitle->Rect->left << std::endl;
	std::cout << "rect->right = " << a_pTitle->Rect->right << std::endl;
	std::cout << "rect->top = " << a_pTitle->Rect->top << std::endl;
	std::cout << "rect->bottom = " << a_pTitle->Rect->bottom << std::endl;*/
}

void ResMgr::ClearAllTitles()
{
	while(m_Renderer->m_Titles.size())
	{
		ClearTitle(m_Renderer->m_Titles[0]);
	}
}

bool ResMgr::ClearTitle(Title* a_pTitle)
{
	for(unsigned short n=0;n<m_Renderer->m_Titles.size();n++)
	{
		if( !m_Renderer->m_Titles[n]->Text.compare(a_pTitle->Text) )
		{
			RECT* firstRect = m_Renderer->m_Titles[n]->Rect;
			RECT* secondRect = a_pTitle->Rect;
			if(firstRect->bottom == secondRect->bottom && firstRect->top == secondRect->top && firstRect->left == secondRect->left && firstRect->right == secondRect->right)
			{
				//std::cout << "	title '" << m_Renderer->m_Titles[n]->first.c_str() << "' cleared" << std::endl;
				delete m_Renderer->m_Titles[n]->Rect;
				m_Renderer->m_Titles[n]->Rect = NULL;
				delete m_Renderer->m_Titles[n];
				m_Renderer->m_Titles[n] = NULL;
				m_Renderer->m_Titles.erase(m_Renderer->m_Titles.begin()+n);
				return true;
			}
		}
	}
	return false;
	//
}

bool ResMgr::ClearTitle(unsigned short a_Index)
{
	if(a_Index >= m_Renderer->m_Titles.size())
	{
		//std::cout << "	n too large" << std::endl;
		return false;
	}
	if(!m_Renderer->m_Titles[a_Index])
	{
		//std::cout << "	n nonexistent" << std::endl;
		return false;
	}
	//std::cout << "Clearing title: \"" << m_Renderer->m_Titles[a_Index]->Text.c_str() << "\"" << std::endl;
	delete m_Renderer->m_Titles[a_Index]->Rect;
	m_Renderer->m_Titles[a_Index]->Rect = NULL;
	delete m_Renderer->m_Titles[a_Index];
	m_Renderer->m_Titles[a_Index] = NULL;
	m_Renderer->m_Titles.erase(m_Renderer->m_Titles.begin()+a_Index);
	return true;
}
