#include "app.h"
#include "guicon.h"
#include "Timer.h"
#include <iostream>

//application entry point
int WINAPI WinMain(HINSTANCE a_hInst, HINSTANCE a_hPrevInst, LPSTR a_pCmdLine, int a_nCmdShow)
{
	//setup console window
	RedirectIOToConsole();

	//instantiate application class
	App* app = App::GetInstance(a_hInst);

	//setup timer
	Timer time;
	float curT = time.GetTime();
	for(short n=0;n<10;n++){/*delay to make a nonzero dt*/}
	float prevT = time.GetTime();

	//message pump
	bool hasQuit = false;
	while (!hasQuit)
	{
		//work out dt
		prevT = curT;
		curT = time.GetTime();
		float dt = curT - prevT;
		// Process all messages queued up for our window
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		// Let Windows perform some processing on our msg
			DispatchMessage(&msg);		// Send the message to our window procedure
			if (msg.message == WM_QUIT)
			{
				hasQuit = true;
			}
		}
		if(!app->Update(dt))
			return 0;
	}
	// clean up DirectX, COM and DXMgr
	app->cleanUp();
	return 0;
}
