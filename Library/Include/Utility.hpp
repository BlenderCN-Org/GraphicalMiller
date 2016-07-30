//***************************************************************************//
// Utility Classes Interfaces
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

#ifndef MST_GRAPHICS_UTILITY_HPP
#define MST_GRAPHICS_UTILITY_HPP

//***************************************************************************//
// System Includes
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <GL\GL.h>
//***************************************************************************//

//***************************************************************************//
// MST Includes
#include <MathmaticalMiller.hpp>
//***************************************************************************//

//***************************************************************************//
namespace MST
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
    T  A() const { return this->mtColors[3]; }
    T  R() const { return this->mtColors[0]; }
    T  G() const { return this->mtColors[1]; }
    T  B() const { return this->mtColors[2]; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// These methods set the value of the color
    void  A(T tAlpha) { this->mtColors[3] = tAlpha; }
    void  R(T tRed)   { this->mtColors[0] = tRed; }
    void  G(T tGreen) { this->mtColors[1] = tGreen; }
    void  B(T tBlue)  { this->mtColors[2] = tBlue;}
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    T*  Array() { return this->mtColors; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Overloaded '=" operator so assignment of one color to another can be managed
    /// Current this method does nothing more than the non-overloaded '=' operator
    class Color&  operator=(const class Color& rhs)
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
    MST::Point <float, 3>  mPosition;
    MST::Vector<float, 3>  mNormal;
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
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_UTILITY_HPP
