//***************************************************************************//
// Cylinder Class Interface
//
// Created: May 24, 2006
// By: Jeremy Michael Miller
//
// Copyright (c) 2016-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_CYLINDER_HPP
#define MST_GRAPHICS_CYLINDER_HPP

//***************************************************************************//
// Local Includes
#include "Mesh.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  class Cylinder : public Mesh
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  public:
    //***********************************************************************//
    Cylinder(const std::string& strName, class Scene* const pScene);
    ~Cylinder();

    void  Render();
    //***********************************************************************//
  }; // End of class Cylinder : public Mesh
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//
#endif MST_GRAPHICS_CYLINDER_HPP