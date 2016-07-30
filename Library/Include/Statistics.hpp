//***************************************************************************//
// Statistics Class Interface
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

#ifndef MST_GRAPHICS_STATISTICS_HPP
#define MST_GRAPHICS_STATISTICS_HPP

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  class Font;
  //*************************************************************************//

  //*************************************************************************//
  class Statistics
  {
  private:
    //***********************************************************************//
    class Font* mpFont;

    float fET;
    float faDT[5];
    float fDT_sum;
    //***********************************************************************//
  public:
    //***********************************************************************//
    Statistics(class Graphics* pGraphics);
    ~Statistics();

    void  Display(float fDT);
    float  AverageFPS() { return fDT_sum/5.0F; }
    //***********************************************************************//
  }; // End of class Statistics
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_STATISTICS_HPP
