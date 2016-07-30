//***************************************************************************//
// Surface Class Interface
//
// Created Dec 10, 2005
// By: Jeremy Michael Miller
//
// Copyright (c) 2005-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_SURFACE_HPP
#define MST_GRAPHICS_SURFACE_HPP

//***************************************************************************//
// System Includes
#include <vector>
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  // Base classes for all surfaces. I call anything that "fills" any polygon
  // a surface
  class Surface
  {
  private:
    //***********************************************************************//
    // No private members
    //***********************************************************************//
  protected:
    //***********************************************************************//
    class Material* mpActiveMaterial;

    std::vector<class Material*> mvMaterials;
    std::vector<class Texture*>  mvTextures;

    void RenderMaterial();
    void RenderTextures();

    //-----------------------------------------------------------------------//
    void Create();
    void Clone(const Surface& rSource);
    void Destroy();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    /// Both the constructor and the destructor do nothing
    Surface();
    Surface(const Surface& rSource);
    virtual ~Surface();

    //-----------------------------------------------------------------------//
    bool  AddMaterial(class Material* pMaterial);
    bool  AddTexture(class Texture* pTexture);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Render();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Surface
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_SURFACE_HPP
