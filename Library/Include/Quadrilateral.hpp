//***************************************************************************//
// Quadrilateral Class Interface
//
// Created: July 27, 2011
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

#ifndef MST_GRAPHICS_QUADRILATERAL_HPP
#define MST_GRAPHICS_QUADRILATERAL_HPP

//***************************************************************************//
// System includes
#include <string>
#include <vector>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Mesh.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{

  //*************************************************************************//
  class Quadrilateral : public Mesh
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  protected:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    void Create(const std::string& rstrName, class Scene* pScene);
    void Clone(const Quadrilateral& rSource);
    void Destroy();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // This constructor sets all member data to zero
    Quadrilateral(const std::string& rstrName, class Scene* const pScene);
    Quadrilateral(const Quadrilateral& rSource);
    Quadrilateral(const Quadrilateral& rSource, const std::string& rstrDestinationName); 
    virtual ~Quadrilateral();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    Quadrilateral& Quadrilateral::operator=(const Quadrilateral& rSource)
    {
      if(this != &rSource)
      {
        Clone(rSource);
      }    
      return *this;
    }
    //-----------------------------------------------------------------------//

    //-------------------------------------------------------------------------//
    void Quadrilateral::SetVertices(const Vertex& rLeft, const Vertex& rRight, const Vertex& rTop, const Vertex& rBottom);
    //-------------------------------------------------------------------------//

    //***********************************************************************//
  }; // End of class Mesh : public Object
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//
#endif MST_GRAPHICS_QUADRILATERAL_HPP