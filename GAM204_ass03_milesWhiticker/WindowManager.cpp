#include "WindowManager.h"

#include <iostream>

typedef void(*fncptr_keydown_space);

//int (*pt2Function)(float, char, char) = NULL;   
namespace utils
{
	#ifndef KEYPRESS_HANDLER
	#define KEYPRESS_HANDLER
	//
	int prevMouseX;
	int prevMouseY;
	//
	bool spaceDown = false;
	bool tabDown = false;
	//default window procedure, can be overwritten later
	LRESULT CALLBACK WndProc(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
	{
		switch (a_msg)
		{
		case(WM_MOUSEWHEEL):
			{
				//the mousewheel was moved
				if(a_wParam & MK_CONTROL)
				{
					if(GET_WHEEL_DELTA_WPARAM(a_wParam) > 0)
						utils::zoom_view_in();
					else
						utils::zoom_view_out();
				}
				else if(a_wParam & MK_SHIFT)
				{
					if(GET_WHEEL_DELTA_WPARAM(a_wParam) > 0)
						utils::increase_time_passage_rate();
					else
						utils::decrease_time_passage_rate();
				}
				else if(spaceDown)
				{
					if(GET_WHEEL_DELTA_WPARAM(a_wParam) > 0)
						utils::increase_object_size();
					else
						utils::decrease_object_size();
				}
				else if(tabDown)
				{
					if(GET_WHEEL_DELTA_WPARAM(a_wParam) > 0)
						utils::increment_planet_viewing();
					else
						utils::decrement_planet_viewing();
				}
				break;
			}
		case(WM_MOUSEMOVE):
			{
				if(a_wParam & MK_RBUTTON)
				{
					//the mouse moved, rotate the view accordingly
					int newX = GET_X_LPARAM(a_lParam);
					int newY = GET_Y_LPARAM(a_lParam);
					if(newX < prevMouseX)
						utils::rotate_view_left(newX,newY);
					else if(newX > prevMouseX)
						utils::rotate_view_right(newX,newY);
					prevMouseX = newX;
					if(newY < prevMouseY)
						utils::rotate_view_up(newX,newY);
					else if(newY > prevMouseY)
						utils::rotate_view_down(newX,newY);
					prevMouseY = newY;
				}
				break;
			}
		case(WM_CHAR):
			{
				//WM_CHAR chCharCode = (TCHAR) wParam;
				//lKeyData = lParam;
				//setup letter keypress callback funcs
				switch(a_wParam)
				{
				case('q'):
					{
						utils::keypress_q();
						break;
					}
				case('a'):
					{
						utils::keypress_a();
						break;
					}
				case('w'):
					{
						utils::keypress_w();
						break;
					}
				case('s'):
					{
						utils::keypress_s();
						break;
					}
				case('e'):
					{
						utils::keypress_e();
						break;
					}
				case('d'):
					{
						utils::keypress_d();
						break;
					}
				case('r'):
					{
						utils::keypress_r();
						break;
					}
				case('t'):
					{
						utils::keypress_t();
						break;
					}
				case('1'):
					{
						utils::keypress_1();
						break;
					}
				case('2'):
					{
						utils::keypress_2();
						break;
					}
				}
				break;
			}
		case WM_KEYUP:
			{
				if(a_wParam == VK_SPACE)
				{
					spaceDown = false;
					break;
				}
				if(a_wParam == VK_TAB)
				{
					tabDown = false;
					break;
				}
			}
		case WM_KEYDOWN:
			{
				//setup special keypress callback funcs
				if(a_wParam == VK_SPACE)
				{
					utils::keypress_space();
					spaceDown = true;
					break;
				}
				if(a_wParam == VK_TAB)
				{
					utils::keypress_tab();
					tabDown = true;
					break;
				}
				if(a_wParam == VK_CONTROL)
				{
					utils::keypress_ctrl();
					break;
				}
				if(a_wParam == VK_SHIFT)
				{
					utils::keypress_shift();
					break;
				}
				if(a_wParam == VK_UP)
				{
					utils::keypress_up();
					break;
				}
				if(a_wParam == VK_DOWN)
				{
					utils::keypress_down();
					break;
				}
				if(a_wParam == VK_LEFT)
				{
					utils::keypress_left();
					break;
				}
				if(a_wParam == VK_RIGHT)
				{
					utils::keypress_right();
					break;
				}

				//
				if(a_wParam != VK_ESCAPE)
					break;
			}
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);  // Posts a WM_QUIT message to our application
			return 0;
		default:
			break;
		}

		// We didn't handle this msg; pass it to the default window procedure
		return DefWindowProc(a_hWnd, a_msg, a_wParam, a_lParam);
	}
	#endif
}

WndwMgr::WndwMgr(HINSTANCE a_hInst)
:	dx_manager(DXMgr::GetInstance())
{
	m_WindowClass.cbClsExtra = NULL;
	m_WindowClass.cbWndExtra = NULL;
	m_WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WindowClass.hInstance = a_hInst;
	m_WindowClass.lpfnWndProc = utils::WndProc;
	m_WindowClass.lpszClassName = L"window";	//WINDOW_CLASS_NAME;
	m_WindowClass.lpszMenuName = NULL;
	m_WindowClass.style = CS_CLASSDC;			// Try putting CS_DROPSHADOW here!

	//register window class
	RegisterClass(&m_WindowClass);

	//create window
	HWND handle = CreateWindowW(L"window",L"GAM204 Ass03 - Solarium, Miles Whiticker",WS_BORDER|WS_MINIMIZEBOX|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,640,640,NULL,NULL,a_hInst,NULL);

	// Draw the window
	UpdateWindow(handle);

	// Set window as visible
	ShowWindow(handle, SW_SHOW);

	//init DXMgr
	dx_manager.Init(handle);

	//set up d3d
	initD3D(handle);
}

// this function initializes and prepares Direct3D for use
void WndwMgr::initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);		// create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;				// create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));			// clear out the struct for use
    d3dpp.Windowed = TRUE;						// program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// discard old frames
    d3dpp.hDeviceWindow = hWnd;					// set the window to be used by Direct3D

    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

// this is the function that cleans up Direct3D and COM
void WndwMgr::cleanUp()
{
    d3ddev->Release();			// close and release the 3D device
    d3d->Release();				// close and release Direct3D
	dx_manager.Shutdown();		// shutdown DXMgr
}

DXMgr& WndwMgr::GetDxMgr()
{
	return dx_manager;
}
