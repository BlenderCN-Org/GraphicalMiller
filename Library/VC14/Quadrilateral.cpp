//***************************************************************************//
// Quadrilateral Class Implementation
//
// Created July 27, 2011
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

//***************************************************************************//
// Local Includes
#include "Quadrilateral.hpp"
//***************************************************************************//

//***************************************************************************//
#define QUADRILATERAL_SIDES 4
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
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