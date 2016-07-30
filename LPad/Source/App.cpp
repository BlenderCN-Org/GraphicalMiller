//***************************************************************************//
// App Object Implementation
//
// Created Jan 01, 2005
// By: Jeremy Michael Miller
//
// Copyright (c) 2005-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//


//***************************************************************************//
#include "App.hpp"

#include "Timer.hpp"

#include <assert.h>
#include <string>
//***************************************************************************//

//***************************************************************************//
using namespace MST;
using namespace std;
//***************************************************************************//

#define APP_TITLE              L"LPad"
#define APP_MUTEX_NAME         L"Global\\" APP_TITLE "_APP_MUTEX_"
#define APP_WINDOW_NAME        L"GraphicalMillerWindow"
#define APP_SLEEP_TIME         25
#define APP_VERSION            0.050F


HINSTANCE  App::smhInstance;
HANDLE     App::mhAppMutex;

WNDCLASS   App::smMainWcl;
HWND       App::smhWindow             = nullptr;
RECT       App::smMainWindowRect;

bool       App::smbWindowActive        = false;
bool       App::smbHasFocus            = true;
bool       App::smbWindowOpen          = true;
bool       App::smbWindowed            = true;

class App* App::mpInstance = nullptr;
//***************************************************************************//
App::App(HINSTANCE hInstance)
{
  mpGraphics = nullptr;
  this->smhInstance = hInstance;
  smbHasFocus = false;
}
//***************************************************************************//

//***************************************************************************//
App::~App()
{
}
//***************************************************************************//

//***************************************************************************//
bool App::Initialize(char* cpCommandLine)
{
  if(cpCommandLine)
    this->mstrCommandLine = static_cast<string>(cpCommandLine);

  bool bReturnValue = false;
  mpGraphics = new Graphics();
  const unsigned long ulWidth = 1024;
  const unsigned long ulHeigth = 768;
  if(this->SpawnWindow(ulWidth, ulHeigth, true) && mpGraphics->Initialize(this->smhWindow, ulWidth, ulHeigth) >= 0)
  {
    mpGraphics->WindowDimensions(ulWidth, ulHeigth);
    Input::Instance()->Initialize(this->smhInstance, this->smhWindow);
    bReturnValue = true;
  }
  return bReturnValue;
}
//***************************************************************************//

//***************************************************************************//
long App::Run() 
{  
  bool bEscapePressed = false;
  MST::Timer oTimer;
  MST::Random<float> oRandom;
  Scene*  pScene   = this->mpGraphics->CreateScene(static_cast<string>("DEFAULT_SCENE"));

  Mesh*   pMesh     = nullptr;
  Camera* pCamera   = nullptr;
  Light*  pLight    = nullptr;

  // Load the scene if we can find one.
  ifstream ifsSceneFile;
  ifsSceneFile.open(this->mstrCommandLine.c_str());
  if(ifsSceneFile.is_open())
  {
    pScene->Load(ifsSceneFile);
    pCamera = pScene->GetActiveCamera();
    pMesh = pScene->GetMesh("Cone");

    pLight = pScene->GetLight(static_cast<string>("Default"));
    if(pLight)
      pLight->TurnLightOn();

    float fHeight = 0.0F;

    if(pMesh)
    {
      pMesh->Position(0.0, 0.0, 0.0);
      pMesh->Elevate(pMesh->BoundVolume()->Height()/2.0F);
	  
      Mesh* pGround = pScene->GetMesh("Ground");
      float fWidth = 100.0F;
      float fDepth = 100.0F;
      if(pGround)
      {
        fWidth = pGround->BoundVolume()->Width();
        fDepth = pGround->BoundVolume()->Depth();
      }
      for(unsigned long ulIndex = 0; ulIndex < 512; ulIndex++)
      {
        stringstream sstmNewName;
        sstmNewName << pMesh->Name();
        sstmNewName << ulIndex;
        Mesh* pNewClone = pScene->CloneMesh(pMesh->Name(), sstmNewName.str());
        float height = pNewClone->BoundVolume()->Height();
        pNewClone->Position(oRandom.Generate(-fWidth/2.0F, fWidth/2.0F), height/2.0F, oRandom.Generate(-fDepth/2.0F, fDepth/2.0F) );

      }
    }

    unsigned long ulLOD = 0;
    bool bWireFrame = false;
    bool upkeydown = false;
    bool downkeydown = false;
    bool xkeydown = false;
    double timer = 0.0;

    float rX = 0.0F;
    float rY = 0.0F;
    float rZ = 0.0F;

    while(smbWindowOpen && !bEscapePressed)
    {
      float fDT = static_cast<float>(oTimer.DT(TIMER_1));

      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_V) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->ChangeFOV(0.001F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_V) && 
        Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->ChangeFOV(-0.001F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_D) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Strafe(2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_A) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Strafe(-2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_S) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Advance(2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_W) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Advance(-2.0F * fDT);
      }

      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_Q) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Elevate(2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_Z) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Elevate(-2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_ESCAPE))
      {
        bEscapePressed = true;
      }

      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_G))
      {
        if(pMesh)
          pMesh->RelativeYaw(fDT * -0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_J))
      {
        if(pMesh)
          pMesh->RelativeYaw(fDT * 0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_Y))
      {
        if(pMesh)
          pMesh->RelativePitch(fDT * -0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_H))
      {
        if(pMesh)
          pMesh->RelativePitch(fDT * 0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_B))
      {
        if(pMesh)
          pMesh->Elevate(fDT * -0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_T))
      {
        if(pMesh)
          pMesh->Elevate(fDT * 0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_P))
      {
        this->mpGraphics->ToggleWireFrame();
      }

      pCamera->RelativePitch(Input::Instance()->GetMouse()->Direct_DY() * .0005f);
      pCamera->RelativeYaw  (Input::Instance()->GetMouse()->Direct_DX() * .0005f);


      Input::Instance()->Poll();

      this->MessageLoop();

      mpGraphics->Render();
      mpGraphics->SwapBuffer();
    }
  }
  return 0;
}
//***************************************************************************//

//***************************************************************************//
void App::End()
{
  mpGraphics->Uninitialize();
  this->KillWindow();
  delete mpGraphics;
}
//***************************************************************************//


//***************************************************************************//
LRESULT CALLBACK App::WindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  static bool unPauseAfterRestore = false;
  long ret = 0;

  switch (message)
  {
  case WM_ERASEBKGND:
    ret = 1;
    break;

  case WM_SETFOCUS:
    smbHasFocus = true;
    ret = 1;
    break;

  case WM_KILLFOCUS:
    smbHasFocus = false;
    ret = 1;
    break;

  case WM_ACTIVATE:
    if (LOWORD( wParam ) == WA_INACTIVE)
    {
      if (smbWindowActive)
      {
        smbWindowActive = false;
        ShowWindow( smhWindow, SW_MINIMIZE );
      }
    }
    else
    {
      if (!smbWindowActive)
      {
        smbWindowActive = true;
        SetForegroundWindow( smhWindow );
        ShowWindow( smhWindow, SW_RESTORE );
      }
    }  
    ret = 1;
    break;

  case WM_MOVE:
  case WM_SIZE:
    UpdateWindowRect();
    break;

  case WM_CLOSE:
    smbWindowOpen = false;
    break;

  case WM_DESTROY:
    ShowWindow (hwnd, SW_HIDE);
    PostQuitMessage(0);
    ret = 0;
    break;

  case WM_SETCURSOR:
    // set cursor to proper state
    //Input::Instance()->GetMouse()->SetCursor();
    //ret = 1;
    break;

  case WM_SYSCOMMAND:
    // low order nibble used by internally by windows
    switch (wParam & 0xFFF0)
    {
      // no suspension or screen saver while this app is running
    case SC_MONITORPOWER:
    case SC_SCREENSAVE:
      ret = FALSE;
      break;

      // don't allow window menu activations by a keypress (really annoying in windowed mode)
    case SC_KEYMENU:
      ret = FALSE;
      break;

    default: return (DefWindowProc( hwnd, message, wParam, lParam ));
    }
    break;

  default:
    return (DefWindowProc( hwnd, message, wParam, lParam ));
    // return before break
  }


  return (ret);
}
//***************************************************************************//

//***************************************************************************//
void App::MessageLoop()
{
  MSG msg;

  while (PeekMessage( &msg, smhWindow, 0, 0, PM_NOREMOVE ))
  {
    if (!GetMessage( &msg, smhWindow, 0, 0 ))
      return;

    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  // If the app isn't the active app, throw in a small Sleep() call 
  // to give other apps a chance to do processing.
  if (!smbWindowActive)
    Sleep(APP_SLEEP_TIME);
}
//***************************************************************************//

//***************************************************************************//
bool App::EnableCrashingOnAllCrashes()
{ 
  BOOL bResult = 0;
  typedef BOOL (WINAPI *tGetPolicy)(LPDWORD lpFlags); 
  typedef BOOL (WINAPI *tSetPolicy)(DWORD dwFlags); 
 

  HMODULE kernel32 = LoadLibraryA("kernel32.dll"); 
  tGetPolicy pGetPolicy = reinterpret_cast<tGetPolicy>(GetProcAddress(kernel32, 
                                                                      "GetProcessUserModeExceptionPolicy")); 
  tSetPolicy pSetPolicy = reinterpret_cast<tSetPolicy>(GetProcAddress(kernel32, 
                                                                      "SetProcessUserModeExceptionPolicy")); 
  if(pGetPolicy && pSetPolicy) 
  { 
    DWORD dwFlags; 
    if(pGetPolicy(&dwFlags)) 
    { 
      const DWORD EXCEPTION_SWALLOWING = 0x1;
      bResult = pSetPolicy(dwFlags & ~EXCEPTION_SWALLOWING); 
    } 
  }
  return bResult != 0 ? true : false;
}
//***************************************************************************//

//***************************************************************************//
bool App::SpawnWindow(long lWidth, long lHeight, bool bWindowed)
{
  bool bErrorOccured = false;
  smbWindowed = bWindowed;
  
  smMainWcl.hInstance     = smhInstance;
  smMainWcl.lpszClassName = APP_WINDOW_NAME;
  smMainWcl.lpfnWndProc   = WindowProc;
  smMainWcl.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  smMainWcl.hIcon         = LoadIcon(nullptr, IDI_WINLOGO);
  smMainWcl.hCursor       = LoadCursor(nullptr, IDC_ARROW);
  smMainWcl.lpszMenuName  = nullptr;
  smMainWcl.cbClsExtra    = 0;
  smMainWcl.cbWndExtra    = 0;
  smMainWcl.hbrBackground = static_cast<HBRUSH>(GetStockObject( NULL_BRUSH ));
  DWORD dwExStyle;
  DWORD dwStyle;
  smMainWindowRect.left   = 0; // Set Left Value To 0
  smMainWindowRect.right  = lWidth;
  smMainWindowRect.top    = 0;			// Set Top Value To 0
  smMainWindowRect.bottom = lHeight;

  if (!RegisterClass(&smMainWcl))
    bErrorOccured = true;

  if(!bErrorOccured)
  {
    // Set window title
    wchar_t caAppTitle[64];
    wsprintf (caAppTitle, L"%s v%0.3f", APP_TITLE, APP_VERSION);

    if(!smbWindowed)												// Attempt Fullscreen Mode?
    {
      DEVMODE dmScreenSettings;								// Device Mode
      memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
      dmScreenSettings.dmSize       = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
      dmScreenSettings.dmPelsWidth	= lWidth;				// Selected Screen Width
      dmScreenSettings.dmPelsHeight	= lHeight;				// Selected Screen Height
      dmScreenSettings.dmBitsPerPel	= 32;					// Selected Bits Per Pixel
      dmScreenSettings.dmFields     = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

      // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
      if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
      {
        // If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
        if (MessageBox(nullptr, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", L"Graphical Miller" , MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
        {
          smbWindowed = true;		// Windowed Mode Selected.
        }
        else
        {
          // Pop Up A Message Box Letting User Know The Program Is Closing.
          MessageBox(nullptr, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
          bErrorOccured = true;
        }
      }
    }

    if(!bErrorOccured)
    {
      if(!smbWindowed)												// Are We Still In Fullscreen Mode?
      {
        dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
        dwStyle   = WS_POPUP;										// Windows Style
        ShowCursor(FALSE);										// Hide Mouse Pointer
      }
      else
      {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
        dwStyle   = WS_OVERLAPPEDWINDOW;							// Windows Style
      }

      long sx;
      long sy;
      if(smbWindowed)
      {
        RECT vp_rect;
        GetClientRect( GetDesktopWindow(), &vp_rect );
        sx = max (0, ((vp_rect.right-vp_rect.left) >> 1) - (lWidth >> 1));
        sy = max (0, ((vp_rect.bottom-vp_rect.top) >> 1) - (lHeight >> 1));
      }
      else
      {
        sx = 0;
        sy = 0;
      }

      AdjustWindowRectEx(&smMainWindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

      // Create The Window
      if (!(smhWindow = CreateWindowEx(	dwExStyle,							// Extended Style For The Window
        APP_WINDOW_NAME,							// Class Name
        caAppTitle,								// Window Title
        dwStyle |							// Defined Window Style
        WS_CLIPSIBLINGS |					// Required Window Style
        WS_CLIPCHILDREN,					// Required Window Style
        sx, sy,								// Window Position
        smMainWindowRect.right  - smMainWindowRect.left,	// Calculate Window Width
        smMainWindowRect.bottom - smMainWindowRect.top,	// Calculate Window Height
        nullptr,								// No Parent Window
        nullptr,								// No Menu
        smhInstance,							// Instance
        nullptr)))								// Dont Pass Anything To WM_CREATE
      {
        App::KillWindow();								// Reset The Display
        MessageBox(nullptr, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
      }

      ShowWindow(smhWindow,SW_SHOW);						// Show The Window
      SetForegroundWindow(smhWindow);						// Slightly Higher Priority
      SetFocus(smhWindow);									// Sets Keyboard Focus To The Window

      smbWindowActive = true;
      UpdateWindowRect();     // Fill in our window rect structure.
    }
    else// bErrorOccured == true
    {
    }

  }
  else // bErrorOccured == true
  {
    //unsigned long ulError = GetLastError();
  }

  return !bErrorOccured;
}
//***************************************************************************//

//***************************************************************************//
void App::KillWindow()
{
  if(!smbWindowed)										// Are We In Fullscreen Mode?
  {
    ChangeDisplaySettings(nullptr,0);					// If So Switch Back To The Desktop
    ShowCursor(TRUE);								// Show Mouse Pointer
  }

  if (smhWindow && !DestroyWindow(smhWindow))					// Are We Able To Destroy The Window?
  {
    MessageBox(nullptr, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    smhWindow = nullptr;										// Set hWnd To NULL
  }

  if (!UnregisterClass(APP_WINDOW_NAME,smhInstance))			// Are We Able To Unregister Class
  {
    MessageBox(nullptr, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    smhInstance = nullptr;									// Set hInstance To NULL
  }

  ClipCursor(nullptr);
}
//***************************************************************************//
