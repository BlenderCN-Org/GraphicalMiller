//***************************************************************************//
// Traga Bitmap Class Interface
//
// Created March 13, 2011
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

#ifndef HABU_GRAPHICS_TGA_HPP
#define HABU_GRAPHICS_TGA_HPP

//***************************************************************************//
// Local Includes
#include "Texture.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  class TGA : public Texture
  {
  private:
    //***********************************************************************//
    char  mcID_Length;
    char  mcColourMapType;
    char  mcDataTypeCode;
    short msColourMapOrigin;
    short msColourMapLength;
    char  mcColourMapDepth;
    short msX_Origin;
    short msY_Origin;
    short msWidth;
    short msHeight;
    char  mcBitsPerPixel;
    char  mcImageDescription;


    bool Deserialize(unsigned char* cpHeader);
    //***********************************************************************//
  public:
    //***********************************************************************//
    TGA(const std::string& rstrName);
    ~TGA();

    bool _cdecl Load(std::ifstream& ifs);
    //***********************************************************************//
  }; // End of class class TGA : public Texture
  //*************************************************************************//

}
//***************************************************************************//

#endif HABU_GRAPHICS_TGA_HPP