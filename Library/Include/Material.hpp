//***************************************************************************//
// Material Class Interface
//
// Created July 06, 2008
// By: Jeremy Michael Miller
//
// Copyright (c) 2008-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_MATERIAL_HPP
#define MST_GRAPHICS_MATERIAL_HPP

//***************************************************************************//
// Local Includes
#include "Utility.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  class Material
  {
  private:
    //***********************************************************************//
    Color<float>* mpAmbient;
    Color<float>* mpDiffuse;
    Color<float>* mpSpecular;

    float mfSpecularPower;

    std::string mstrName;

    //***********************************************************************//
  public:
    //***********************************************************************//
    Material(const std::string& rstrName);
    ~Material();


    //***********************************************************************//
    const std::string&  Name() const;

    //-----------------------------------------------------------------------//
    bool  Load(std::ifstream& ifs);
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
    
    void  Render();
  }; // End of class Material
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_MATERIAL_HPP

