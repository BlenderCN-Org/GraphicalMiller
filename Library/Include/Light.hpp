//***************************************************************************//
// Light Class Interface
//
// Created July 08, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2011  Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
// Usage of HabuGraphics is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available.
//                 
// HabuGraphics is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuGraphics is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuGraphics.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

#ifndef HABU_GRAPHICS_LIGHT_HPP
#define HABU_GRAPHICS_LIGHT_HPP

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
namespace HabuTech
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
    void _cdecl Initialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool _cdecl Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Position(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Move(float fX, float fY, float fZ);
    /// Moves the light left or right relative to its current orientation
    void _cdecl Strafe(float fX);
    /// Moves the light forward or backwards relative to its current orientation
    void _cdecl Advance(float fZ);
    /// Moves the light up or down relative to its current orientation
    void _cdecl Elevate(float fY);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Forward(float fX, float fY, float fZ);
    void _cdecl Up(float fX, float fY, float fZ);
    void _cdecl Right(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl SetAmbient(float fRed, float fGreen, float fBlue);
    void _cdecl SetAmbient(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl SetDiffuse(float fRed, float fGreen, float fBlue);
    void _cdecl SetDiffuse(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl SetSpecular(float fRed, float fGreen, float fBlue);
    void _cdecl SetSpecular(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl TurnLightOn();
    void _cdecl TurnLightOff();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Light : public Object
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_LIGHT_HPP