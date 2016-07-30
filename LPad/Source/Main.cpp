//***************************************************************************//
// Miller Graphics Pad
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
//***************************************************************************//

//***************************************************************************//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, char* cpCmdLine, int nCmdShow)			
{
  App::Instance(hInstance);

  App::Instance()->EnableCrashingOnAllCrashes();

  if(App::Instance()->Initialize(cpCmdLine))
    App::Instance()->Run();
  App::Instance()->End();

  return 0;
}
//***************************************************************************//