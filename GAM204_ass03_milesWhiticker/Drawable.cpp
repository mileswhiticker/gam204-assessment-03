//Drawable class written by Miles Whiticker with code originally by Scott Taylor

#include "Drawable.h"

#include <d3dx9.h>

//
// Constructor
//
Drawable::Drawable()
  : m_pVertexBuf(NULL)
  , m_pIndexBuf(NULL)
{
	//
}

//
// Destructor
//
Drawable::~Drawable()
{
	// Clean up our vertex buffer
	if (m_pVertexBuf)
	{
		//@TODO: Call Release() on our vertex buffer, set to NULL
	}

	// Clean up our index buffer
	if (m_pIndexBuf)
	{
		//@TODO: Call Release() on our index buffer, set to NULL
	}
}
