//***************************************************************************//
// Material Class Implementation
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

//***************************************************************************//
// Local Includes
#include "GraphicalMiller.hpp"
#include "Utility.hpp"
#include "Material.hpp"
//***************************************************************************//

//***************************************************************************//
#define NUMBER_OF_MATERIAL_PARAMETERS 3
#define DIFFUSE_COLOR_LABEL  "Diffuse"
#define AMBIENT_FACTOR_LABEL "Ambient"
#define SPECULAR_COLOR_LABEL "Specular"
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  Material::Material(const std::string& rstrName)
  {
    this->mpAmbient = new Color<float>(1.0, 1.0, 1.0, 1.0);
    this->mpDiffuse = new Color<float>(1.0, 1.0, 1.0, 1.0);
    this->mpSpecular = new Color<float>(1.0, 1.0, 1.0, 1.0);
    this->mfSpecularPower = 8.0F;

    assert(rstrName.size());
    if(rstrName.size())
      this->mstrName = rstrName;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Material::~Material()
  {
    delete this->mpAmbient;
    delete this->mpDiffuse;
    delete this->mpSpecular;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  const std::string& Material::Name() const
  {
    return this->mstrName;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Material::Load(std::ifstream& ifs)
  {
    //-----------------------------------------------------------------------//
    // Throw assertion is file streams is not open.
    assert(ifs.is_open() && ifs.good());
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If the file stream is not open return false.
    if(!ifs.is_open() || !ifs.good())
      return false;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This string will hold the label that describes some camera parameter.
    string strLabel;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This unsigned short will count the number of camera parameters read in
    // and will be used to verify that the correct number of parameters have 
    // been initialized.
    unsigned short usParameterCount = 0;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // The for loop will read in data from the file stream and will set 
    // the objects data members accordingly.
    for(unsigned short i = 0; i < NUMBER_OF_MATERIAL_PARAMETERS; i++)
    {
      //---------------------------------------------------------------------//
      // Read in the label
      ifs >> strLabel;
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // Match the label to some predefined token and set the proper data member.
      float fR, fG, fB, fA;
      if(strLabel == DIFFUSE_COLOR_LABEL)
      {
        ifs >> fR;
        ifs >> fG;
        ifs >> fB;
        ifs >> fA;
        this->SetDiffuse(fR, fG, fB);
        usParameterCount++;
      }
      else if(strLabel == AMBIENT_FACTOR_LABEL)
      {
        float fAmbientFactor;
        ifs >> fAmbientFactor;
        this->SetAmbient(this->mpDiffuse->R() * fAmbientFactor, 
                         this->mpDiffuse->G() * fAmbientFactor,
                         this->mpDiffuse->B() * fAmbientFactor);
        usParameterCount++;
      }
      else if(strLabel == SPECULAR_COLOR_LABEL)
      {
        ifs >> fR;
        ifs >> fG;
        ifs >> fB;
        ifs >> fA;
        this->SetSpecular(fR, fG, fB);
        usParameterCount++;
      } // End of if-else chain that matches the read in label 
      // to predefined token.
      //---------------------------------------------------------------------//
    } // End of for(unsigned short i = 0; i < NUMBER_OF_CAMERA_PARAMETERS; i++)
    //-----------------------------------------------------------------------//

    assert(usParameterCount == NUMBER_OF_MATERIAL_PARAMETERS);
    return (usParameterCount == NUMBER_OF_MATERIAL_PARAMETERS);
  }
  //-------------------------------------------------------------------------//


  //*************************************************************************//
  void Material::SetAmbient(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpAmbient->R(fRed);
    mpAmbient->G(fGreen);
    mpAmbient->B(fBlue);
    mpAmbient->A(1.0F);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetAmbient(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetAmbient(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetDiffuse(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpDiffuse->R(fRed);
    mpDiffuse->G(fGreen);
    mpDiffuse->B(fBlue);
    mpDiffuse->A(1.0F);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetDiffuse(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetDiffuse(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetSpecular(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpSpecular->R(fRed);
    mpSpecular->G(fGreen);
    mpSpecular->B(fBlue);
    mpSpecular->A(0.0F);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetSpecular(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetSpecular(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //-------------------------------------------------------------------------//
  void Material::Render()
  {
    glMaterialfv(GL_FRONT, GL_AMBIENT,  this->mpAmbient->Array());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  this->mpDiffuse->Array());
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->mpSpecular->Array());
  }
  //-------------------------------------------------------------------------//
}
//***************************************************************************//

