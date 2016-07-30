//***************************************************************************//
// Graphical Miller Base Class Interface
//
// Created Jan 01, 2005
// By: Jeremy Michael Miller
//
// Copyright (c) 2005-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.4"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_HPP
#define MST_GRAPHICS_HPP

//***************************************************************************//

//***************************************************************************//
#define DEFAULT_WINDOW_WIDTH  800
#define DEFAULT_WINDOW_HEIGHT 600

#define MST_GRAPHICS_VERSION 0.004F
//***************************************************************************//

//***************************************************************************//
#include <assert.h>
#include <vector>
#include <string>

#include <windows.h>

//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  enum Transforms
  {
    HG_VIEW_TRANSFORM,
    HG_PROJECTION_TRANSFORM
  };
  //*************************************************************************//

  //*************************************************************************//
  // Graphics is the class that enables OpenGL and manages window creation
  class Graphics
  {
  private:
    //***********************************************************************//
    class Scene* mpActiveScene;

    bool mbWireFrame;

    //-----------------------------------------------------------------------//
    static HDC       smhDeviceContext;
    static HGLRC     smhRenderingContext;
    static HWND      smhWindow;
    static HINSTANCE smhInstance;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Maximum number of elements in a vertex buffer
    static unsigned int smuiMaxNumberOfVertexElements;
    static unsigned int smuiMaxNumberOfIndexElements;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long mulWindowWidth;
    unsigned long mulWindowHeight;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This member is used to store the index to the current adapter being used.
    unsigned long mulAdapter;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// This method will check to see if the Device is lost.
    /// Return Value: True if the device is lost otherwise this will return false.
    bool DeviceLost();

    /// The method will reset the device and reallocation and resource allocated
    /// in the D3DPOOL_DEFAULT
    /// Return Value: True if the device was reset otherwise this will return false.
    bool ResetDevice();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// This method will load a configuration file. This configuration file can
    /// used to communicate things such are resolution and anti-aliasing.
    /// Return Value: This method will return true when the configuration file
    ///               loads successfully, otherwise this method will return false.
    bool LoadConfig(const std::string& strFileName);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Graphics();
    ~Graphics();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long  GetNumberOfAdapters();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    static long  Initialize(HWND hWindow, unsigned long ulWidth = DEFAULT_WINDOW_WIDTH, unsigned long ulHeight = DEFAULT_WINDOW_HEIGHT);
    static long  Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  WindowDimensions(unsigned long ulWidth, unsigned long ulHeight);
    unsigned long  WindowWidth() const;
    unsigned long  WindowHeight() const;

    void   NearClipPlane(float fNear);
    float  NearClipPlane() const;
    
    void   FarClipPlane(float fFar);
    float  FarClipPlane() const;
    
    void   FieldOfVeiw(float fDegrees);
    float  FieldOfView() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  SetBackBufferSize(unsigned long ulWidth, unsigned long ulHeight);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long  MaxVertexBufferSize() const;
    unsigned long  MaxIndexBufferSize() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    int  Render();
    void  SwapBuffer();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  ToggleWireFrame();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Scene*  CreateScene(const std::string& rstrName);
    void  DestroyScene(const std::string& rstrName);
    void  DestroyScene(class Scene** ppScene);
    class Scene*  GetScene(const std::string& rstrName);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  };
  //*************************************************************************//
}
//***************************************************************************//

#include "Utility.hpp"
#include "Font.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Cylinder.hpp"
#include "Scene.hpp"

#include "Camera.hpp"
#include "Statistics.hpp"

#endif MST_GRAPHICS_HPP
