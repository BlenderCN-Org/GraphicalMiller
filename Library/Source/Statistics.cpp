//***************************************************************************//
// Statistics Class Implementation
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
#include <sstream>
#include <string>

#include "Font.hpp"
#include "Statistics.hpp"
#include "GraphicalMiller.hpp"
//***************************************************************************//

//***************************************************************************//
#define TIME_BETWEEN_UPDATES 1.0F
#define X_PIXEL_POSITION 5
#define Y_PIXEL_POSITION 5
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  Statistics::Statistics(class Graphics* pGraphics)
  {
    //-----------------------------------------------------------------------//
    mpFont = NULL;
    mpFont->SetPosition(X_PIXEL_POSITION, Y_PIXEL_POSITION);
    mpFont->SetString("", 0L);
    //-----------------------------------------------------------------------//
    
    //-----------------------------------------------------------------------//
    fET = 0.0F;
    fDT_sum = 0.0F;
    faDT[0] = 0.0F;
    faDT[1] = 0.0F;
    faDT[2] = 0.0F;
    faDT[3] = 0.0F;
    faDT[4] = 0.0F;
    //-----------------------------------------------------------------------//
  } // End of Statistics::Statistics()
  //*************************************************************************//

  //*************************************************************************//
  Statistics::~Statistics()
  {
    if(mpFont)
      delete mpFont;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Statistics::Display(float fDT)
  {
    fET += fDT;

    if(mpFont)
    {
      if(fET > TIME_BETWEEN_UPDATES)
      {
        fDT_sum -= faDT[4];
        faDT[4] = faDT[3];
        faDT[3] = faDT[2];
        faDT[2] = faDT[1];
        faDT[1] = faDT[0];
        faDT[0] = fDT;
        fDT_sum += fDT;

        fET = 0.0F;
        stringstream sstmFPS;
        sstmFPS << "Frames Per Second: ";
        sstmFPS << 1.0F/(fDT_sum/5.0F);
        mpFont->SetString(sstmFPS.str());
      }
    }
    return;
  } // End of void Statistics::Display(float fDT)
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//