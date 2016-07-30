//***************************************************************************//
// Light Class Interface
//
// Created July 08, 2005
// By: Jeremy Michael Miller
//
// Copyright (c) 2015-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_LIGHT_HPP
#define MST_GRAPHICS_LIGHT_HPP

//***************************************************************************//
// 3rdParty Includes
#include <GL\GL.h>
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <windows.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Object.hpp"
#include "Utility.hpp"
//***************************************************************************//
	
//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  enum LightID
  {
    LIGHT_ID_0 = GL_LIGHT0,
    LIGHT_ID_1 = GL_LIGHT1,
    LIGHT_ID_2 = GL_LIGHT2,
    LIGHT_ID_3 = GL_LIGHT3,
    LIGHT_ID_4 = GL_LIGHT4,
    LIGHT_ID_5 = GL_LIGHT5,
    LIGHT_ID_6 = GL_LIGHT6,
    LIGHT_ID_7 = GL_LIGHT7,
    LIGHT_ID_COUNT = 8
  };
  //*************************************************************************//

  //*************************************************************************//
  enum LightType
  {
    OMNI_LIGHT_TYPE,
    SPOT_LIGHT_TYPE,
    UNKNOWN_LIGHT_TYPE
  };
  //*************************************************************************//

  //*************************************************************************//
  class Light : public Object
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    /// Describes the ambient of the light
    Color<float>* mpAmbient;
    /// Describes the diffuse value of the light
    Color<float>* mpDiffuse;
    /// Describes the specular value of the light
    Color<float>* mpSpecular;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    enum LightID meLightID;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    enum LightType meLightType;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Signifies if the light will be enabled or not
    bool mbLightOn;
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    /// This constructors initializes all light parameters to zero and has the light
    /// turned off by calling the member method Initialize
    Light(const std::string& rstrName, enum LightID eLightID);
    /// Does nothing.
    ~Light();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Sets all member data to zero and has light turned off
    void  Initialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool  Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Position(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Move(float fX, float fY, float fZ);
    /// Moves the light left or right relative to its current orientation
    void  Strafe(float fX);
    /// Moves the light forward or backwards relative to its current orientation
    void  Advance(float fZ);
    /// Moves the light up or down relative to its current orientation
    void  Elevate(float fY);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Forward(float fX, float fY, float fZ);
    void  Up(float fX, float fY, float fZ);
    void  Right(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  SetAmbient(float fRed, float fGreen, float fBlue);
    void  SetAmbient(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  SetDiffuse(float fRed, float fGreen, float fBlue);
    void  SetDiffuse(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  SetSpecular(float fRed, float fGreen, float fBlue);
    void  SetSpecular(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  TurnLightOn();
    void  TurnLightOff();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Light : public Object
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_LIGHT_HPP