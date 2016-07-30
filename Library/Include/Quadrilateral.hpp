//***************************************************************************//
// Quadrilateral Class Interface
//
// Created: July 27, 2011
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

#ifndef HABU_GRAPHICS_QUADRILATERAL_HPP
#define HABU_GRAPHICS_QUADRILATERAL_HPP

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
namespace HabuTech
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
} // End of namespace HabuTech
//***************************************************************************//
#endif HABU_GRAPHICS_QUADRILATERAL_HPP