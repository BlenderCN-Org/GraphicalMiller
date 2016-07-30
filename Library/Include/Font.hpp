//***************************************************************************//
// Font Class Interface
//
// Created Aug 17, 2006
// By: Jeremy Michael Miller
//
// Copyright (c) 2006-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_FONT_HPP
#define MST_GRAPHICS_FONT_HPP

//***************************************************************************//
// System Includes
#include <string>
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  class Font
  {
  private:
    //***********************************************************************//
    float mfaPosition[2];
    std::string mstrText;

    bool mbRender;
    //***********************************************************************//
  public:
    //***********************************************************************//
    Font();
    ~Font();

    void SetString(const std::string& str);
    void SetString(char* cpStr, unsigned short usLength);

    void SetPosition(unsigned short usX, unsigned short usY);

    void Render();
    //***********************************************************************//
  }; // End of class Font
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_FONT_HPP