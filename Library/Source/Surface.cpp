//***************************************************************************//
// Surface Class Implementation
//
// Created Nov 12, 2005
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

//***************************************************************************//
#include "Surface.hpp"
#include "Material.hpp"
#include "Texture.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  Surface::Surface()
  {
    Create();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Surface::Surface(const Surface& rSource)
  {
    // Uses this class's overloaded assignment operator.
    Create();
    Clone(rSource);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Surface::~Surface()
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
  void Surface::Create()
  {
    this->mpActiveMaterial = NULL;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Surface::Destroy()
  {
    this->mvMaterials.clear();
    this->mvTextures.clear();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Surface::Clone(const Surface& rSource)
  {
    this->mvMaterials.assign(rSource.mvMaterials.begin(), rSource.mvMaterials.end());
    this->mvTextures.assign(rSource.mvTextures.begin(), rSource.mvTextures.end());

    if(this->mvMaterials.size() > 0)
      this->mpActiveMaterial = this->mvMaterials[0];
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Surface::RenderMaterial()
  {
    if(this->mpActiveMaterial)
      this->mpActiveMaterial->Render();
    else if(this->mvMaterials.size() > 0)
    {
      this->mpActiveMaterial = mvMaterials[0];
      this->mpActiveMaterial->Render();
    }
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Surface::RenderTextures()
  {

    for(unsigned long ulIndex = 0UL; ulIndex < this->mvTextures.size(); ulIndex++)
    {
      this->mvTextures[ulIndex]->Render();
    }
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Surface::AddMaterial(class Material* pMaterial)
  {
    bool bReturnValue = false;
    if(pMaterial)
    {
      this->mvMaterials.push_back(pMaterial);
      mpActiveMaterial = pMaterial;
      bReturnValue = true;
    }
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Surface::AddTexture(class Texture* pTexture)
  {
    bool bReturnValue = false;
    if(pTexture)
    {
      this->mvTextures.push_back(pTexture);
      bReturnValue = true;
    }
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Surface::Render()
  {
    this->RenderTextures();
    this->RenderMaterial();
  }
  //-------------------------------------------------------------------------//
} // End of namespace MST
//***************************************************************************//