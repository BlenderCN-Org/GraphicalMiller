//***************************************************************************//
// Miller Graphics Base Class Implementation
//
// Created Jan 01, 2005
// By: Jeremy Michael Miller
//
// Copyright (c) 2007-2016 Jeremy Michael Miller. 
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
// System Includes
#include <assert.h>
//***************************************************************************//

//***************************************************************************//
// 3rd Party Includes
#include <glew.h> // Must be called before GL.h
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Utility.hpp"
#include <GraphicalMiller.hpp>
//***************************************************************************//

//***************************************************************************//
#define CLEAR_COLOR 0xFFEEEEEE
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  HDC          Graphics::smhDeviceContext = nullptr;
  HGLRC        Graphics::smhRenderingContext = nullptr;
  HWND         Graphics::smhWindow = nullptr;
  HINSTANCE    Graphics::smhInstance = nullptr;
  unsigned int Graphics::smuiMaxNumberOfVertexElements = 0UL;
  unsigned int Graphics::smuiMaxNumberOfIndexElements = 0UL;
  //*************************************************************************//

  //*************************************************************************//
  // Start of class Graphics implementation
  //-------------------------------------------------------------------------//
  Graphics::Graphics()
  {
    //-----------------------------------------------------------------------//
    this->mpActiveScene        = nullptr;
    this->mulWindowHeight      = DEFAULT_WINDOW_HEIGHT;
    this->mulWindowWidth       = DEFAULT_WINDOW_WIDTH;
    //-----------------------------------------------------------------------//

    this->mbWireFrame = false;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Graphics::~Graphics()
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Graphics::SetMultiSample(unsigned long ulSamples)
  {
    // This bool is for returning to the callee the success or failure
    // or trying to set the given multi-sample type.
    bool bReturnValue = false;

    // Return either success or failure.
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  long Graphics::Initialize(HWND hWindow, unsigned long ulWidth, unsigned long ulHeight)										
  {
    //-----------------------------------------------------------------------//
    // Create a data member to hold the result of this method. In this method's
    // case it will hold any error codes. By default set to 1 to signal no error. 
    long lResultCode = 1;
    //-----------------------------------------------------------------------//

    smhWindow = hWindow;

    static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
    {
      sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
      1,											// Version Number
      PFD_DRAW_TO_WINDOW |						// Format Must Support Window
      PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
      PFD_DOUBLEBUFFER,							// Must Support Double Buffering
      PFD_TYPE_RGBA,								// Request An RGBA Format
      32,										// Select Our Color Depth
      0, 0, 0, 0, 0, 0,							// Color Bits Ignored
      0,											// No Alpha Buffer
      0,											// Shift Bit Ignored
      0,											// No Accumulation Buffer
      0, 0, 0, 0,									// Accumulation Bits Ignored
      16,											// 16Bit Z-Buffer (Depth Buffer)  
      0,											// No Stencil Buffer
      0,											// No Auxiliary Buffer
      PFD_MAIN_PLANE,								// Main Drawing Layer
      0,											// Reserved
      0, 0, 0										// Layer Masks Ignored
    };

    GLuint		PixelFormat;
    if(!(smhDeviceContext = GetDC(hWindow)))
    {
      lResultCode = -1;
      smhDeviceContext = NULL;
    }

    if(lResultCode > 0 && !(PixelFormat = ChoosePixelFormat(smhDeviceContext, &pfd)))	// Did Windows Find A Matching Pixel Format?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !SetPixelFormat(smhDeviceContext, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !(smhRenderingContext = wglCreateContext(smhDeviceContext)))				// Are We Able To Get A Rendering Context?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !wglMakeCurrent(smhDeviceContext, smhRenderingContext))					// Try To Activate The Rendering Context
    {
      lResultCode = -1;
    }

    if(lResultCode > 0)
    {
      // Check Required Extensions
      GLenum err = glewInit();
      if(err == GLEW_OK)
      {
        if(GLEW_VERSION_2_0 && GLEW_ARB_vertex_buffer_object)
        {
          glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
          glClearDepth(1.0f);									// Depth Buffer Setup
          glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
          glEnable(GL_LIGHTING) ;
          glEnable(GL_TEXTURE_2D);
          glShadeModel(GL_SMOOTH);

          glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
          glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
          glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

          glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, reinterpret_cast<GLint*>(&(smuiMaxNumberOfVertexElements)));
          glGetIntegerv(GL_MAX_ELEMENTS_INDICES, reinterpret_cast<GLint*>(&(smuiMaxNumberOfIndexElements)));
        }
        else
        {
          lResultCode = -1;
        }
      }
      else
      {
        glewGetErrorString(err);
        lResultCode = -1;
        /// \TODO do something with error.
      }
    }

    //-----------------------------------------------------------------------//
    // Return result/error code
    return lResultCode;
    //-----------------------------------------------------------------------//
  } // End of long Graphics::Initialize(HWND hWindow)	
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  long Graphics::Uninitialize()
  {
    long lReturnCode = 1;
    if(smhRenderingContext)											// Do We Have A Rendering Context?
    {
      if(!wglMakeCurrent(nullptr, nullptr))					// Are We Able To Release The DC And RC Contexts?
      {
        MessageBox(nullptr, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        lReturnCode = -1;
      }

      if(!wglDeleteContext(smhRenderingContext))						// Are We Able To Delete The RC?
      {
        MessageBox(nullptr, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        lReturnCode = -1;
      }
      smhRenderingContext = nullptr;										// Set RC To NULL
    }
    if(smhDeviceContext && !ReleaseDC(smhWindow, smhDeviceContext))					// Are We Able To Release The DC
    {
      MessageBox(nullptr, L"Release Device Context Failed.", L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
      smhDeviceContext = nullptr;										// Set DC To NULL
      lReturnCode = -1;
    }

    return lReturnCode;
  } // End of long Graphics::Uninitialize()
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Graphics::WindowDimensions(unsigned long ulWidth, unsigned long ulHeight)
  {
    this->mulWindowWidth  = ulWidth;
    this->mulWindowHeight = ulHeight;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  unsigned long Graphics::WindowWidth() const
  {
    return this->mulWindowWidth;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  unsigned long Graphics::WindowHeight() const
  {
    return this->mulWindowHeight;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Base::RenderScene() clears the depth and color buffer and starts
  // rendering the scene
  int Graphics::Render()									
  {
    if(this->mpActiveScene)
      this->mpActiveScene->Render();

    return 0;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Base::SwapBuffers 
  void Graphics::SwapBuffer()
  {
    SwapBuffers(smhDeviceContext);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Graphics::ToggleWireFrame()
  {
    if(!this->mbWireFrame)
    {
      glDisable(GL_LIGHTING);
      glDisable(GL_TEXTURE_2D);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      this->mbWireFrame = true;
    }
    else
    {
      glEnable(GL_LIGHTING);
      glEnable(GL_TEXTURE_2D);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      this->mbWireFrame = false;
    }
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  class Scene* Graphics::CreateScene(const std::string& rstrName)
  {
    this->mpActiveScene = new Scene(this);
    return this->mpActiveScene;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Graphics::LoadConfig(const std::string& strFileName)
  {
    return false;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  unsigned long Graphics::GetNumberOfAdapters()
  {
    return 0;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Graphics::DeviceLost()
  {
    bool bReturnValue = false;
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Graphics::SetBackBufferSize(unsigned long ulWidth, unsigned long ulHeight)
  {
    this->ResetDevice();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  unsigned long  Graphics::MaxVertexBufferSize() const
  {
    return this->smuiMaxNumberOfVertexElements;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  unsigned long  Graphics::MaxIndexBufferSize() const
  {
    return this->smuiMaxNumberOfIndexElements;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Graphics::ResetDevice()
  {
    bool bReturnValue = true;
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//
  // End of class Graphics implementation
  //*************************************************************************//
}
//***************************************************************************//
