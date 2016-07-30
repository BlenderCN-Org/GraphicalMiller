//***************************************************************************//
// Traga Bitmap Class Interface
//
// Created March 13, 2011
// By: Jeremy Michael Miller
//
// Copyright (c) 2011-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_TGA_HPP
#define MST_GRAPHICS_TGA_HPP

//***************************************************************************//
// Local Includes
#include "Texture.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
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

    bool  Load(std::ifstream& ifs);
    //***********************************************************************//
  }; // End of class class TGA : public Texture
  //*************************************************************************//

}
//***************************************************************************//

#endif MST_GRAPHICS_TGA_HPP