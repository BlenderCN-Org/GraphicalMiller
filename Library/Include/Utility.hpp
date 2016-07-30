//***************************************************************************//
// Utility Classes Interfaces
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2011 Jeremy M Miller.  All rights reserved.
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

#ifndef HABU_GRAPHICS_UTILITY_HPP
#define HABU_GRAPHICS_UTILITY_HPP

//***************************************************************************//
// System Includes
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <GL\GL.h>
//***************************************************************************//

//***************************************************************************//
// BlueHabu Technologies Includes
#include <HabuMath.hpp>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
#pragma pack(push, 1)
  template <class T>
  class Color
  {
  private:
    //***********************************************************************//
    /// This data member stores information about the current color
    T mtColors[4];
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    /// Constructor sets all the colors to zero or black
    Color() { memset(this->mtColors, 0UL, 4 * sizeof(T)); }
    Color(T tAlpha, float tRed, T tGreen, T tBlue) 
    { mtColors[3] = tAlpha; mtColors[0] = tRed; mtColors[1] = tGreen; mtColors[2] = tBlue; }
    /// Destructor does nothing
    ~Color() {}
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// These methods return the value of the color
    T _cdecl A() const { return this->mtColors[3]; }
    T _cdecl R() const { return this->mtColors[0]; }
    T _cdecl G() const { return this->mtColors[1]; }
    T _cdecl B() const { return this->mtColors[2]; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// These methods set the value of the color
    void _cdecl A(T tAlpha) { this->mtColors[3] = tAlpha; }
    void _cdecl R(T tRed)   { this->mtColors[0] = tRed; }
    void _cdecl G(T tGreen) { this->mtColors[1] = tGreen; }
    void _cdecl B(T tBlue)  { this->mtColors[2] = tBlue;}
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    T* _cdecl Array() { return this->mtColors; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Overloaded '=" operator so assignment of one color to another can be managed
    /// Current this method does nothing more than the non-overloaded '=' operator
    class Color& _cdecl operator=(const class Color& rhs)
    {
      //---------------------------------------------------------------------//
      memcpy(this->mtColors, rhs.mtColors, 4 * sizeof(T));
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      return *this; // return address of data just copied
      //---------------------------------------------------------------------//
    } // End of class Color& operator=(const class Color& rhs)
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Color
#pragma pack(pop)
  //*************************************************************************//

  //*************************************************************************//
#pragma pack(push, 1)
  class Vertex
  {
  private:
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Vertex() { mPosition[0] = 0.0F; mPosition[1] = 0.0F; mPosition[2] = 0.0F; 
    mNormal[0] = 0.0F; mNormal[1] = 0.0F; mNormal[2] = 0.0F; }
    Vertex(float fX, float fY, float fZ) {mPosition[0] = fX; mPosition[1] = fY; mPosition[2] = fZ;
    mNormal[0] = 0.0F; mNormal[1] = 0.0F; mNormal[2] = 0.0F; }
    ~Vertex() {} 
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    HabuTech::Point <float, 3>  mPosition;
    HabuTech::Vector<float, 3>  mNormal;
    float mTextureUV[2];
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    static void DeclareVertex()
    {
      #define BUFFER_OFFSET(i) ((char *)NULL + (i))
      glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
      glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
      glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
    }
    //-----------------------------------------------------------------------//
  }; // End of class Vertex
#pragma pack(pop)
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_UTILITY_HPP
