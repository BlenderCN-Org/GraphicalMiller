//***************************************************************************//
// Font Class Implementation
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

//***************************************************************************//
// System Includes
#include <assert.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "GraphicalMiller.hpp"
//***************************************************************************//

#define MAX_LENGTH_OF_STRING 65535 // 2^16 - 1 (for null)

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  Font::Font()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  Font::~Font()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::SetString(const std::string& str)
  {
    assert(str.size() <= MAX_LENGTH_OF_STRING);
    

    if(str.size() > MAX_LENGTH_OF_STRING)
    {
      // get how much to remove 
      // Doing cast of str.size() since no string should 
      // be longer than 2^32 in length.
      std::string strTemp = str;
      assert(str.size() > 0xFFFFFFFF);
      unsigned long ulRemove = (unsigned long)(strTemp.size()) - MAX_LENGTH_OF_STRING;
      strTemp.erase(strTemp.end() - ulRemove, strTemp.end());
      this->mstrText = strTemp;
    }
    else
      this->mstrText = str;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::SetString(char* cpStr, unsigned short usLength)
  {
    assert(usLength <=  MAX_LENGTH_OF_STRING);

    if(this->mstrText.size() > 0)
      this->mstrText.erase(mstrText.begin(), mstrText.end());

    // check for null
    if(strnlen(cpStr, usLength) <= MAX_LENGTH_OF_STRING)
     this->mstrText = cpStr;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::SetPosition(unsigned short usX, unsigned short usY)
  {
    // TODO bound check
    //mRect.top = usY;
    //mRect.left = usX;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::Render()
  {
    //if(mstrText.size() > 0 && mbRender)
    //{
    //  // The below call returns 0 on error.
    //  int iResult = mpFont->DrawText(0, (LPCSTR)this->mstrText.c_str(), -1, (LPRECT)&mRect, DT_NOCLIP, D3DCOLOR_XRGB(255,0,0));
    //  assert(iResult != 0);
    //}
  }
  //*************************************************************************//
}
//***************************************************************************//