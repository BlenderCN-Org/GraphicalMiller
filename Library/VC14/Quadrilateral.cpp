//***************************************************************************//
// Quadrilateral Class Implementation
//
// Created July 27, 2011
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

//***************************************************************************//
// Local Includes
#include "Quadrilateral.hpp"
//***************************************************************************//

//***************************************************************************//
#define QUADRILATERAL_SIDES 4
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  Quadrilateral::Quadrilateral(const std::string& rstrName, class Scene* pScene) : Mesh(rstrName, pScene)
  {
    Create(rstrName, pScene);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Quadrilateral::Quadrilateral(const Quadrilateral& rSource) : Mesh(rSource)
  {
    // Uses this class's overloaded assignment operator.
    Create(rSource.Name(), rSource.mpScene);
    Clone(rSource);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Quadrilateral::Quadrilateral(const Quadrilateral& rSource, const std::string& rstrDestinationName) : Mesh(rSource, rstrDestinationName)
  {
    Create(rstrDestinationName, rSource.mpScene);
    Clone(rSource);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Quadrilateral::~Quadrilateral()
  {
    try
    {
      Destroy();
    }
    catch(...)
    {
    }
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Quadrilateral::Create(const std::string& rstrName, class Scene* pScene)
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Quadrilateral::Destroy()
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Quadrilateral::Clone(const Quadrilateral& rSource)
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Quadrilateral::SetVertices(const Vertex& rLeft, const Vertex& rRight, const Vertex& rTop, const Vertex& rBottom)
  {
    
  }
  //-------------------------------------------------------------------------//
}
//***************************************************************************//