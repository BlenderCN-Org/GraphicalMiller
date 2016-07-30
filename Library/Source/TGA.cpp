//***************************************************************************//
// Traga Bitmap Class Implementation
//
// Created March 13, 2011
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
// System Includes
#include <assert.h>
#include <fstream>
#include <string>

// Local Includes
#include "Utility.hpp"
#include "TGA.hpp"
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  TGA::TGA(const std::string& rstrName) : Texture(rstrName)
  {
    meTextureType = TGA_TEXTURE_TYPE;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  TGA::~TGA()
  {

  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool TGA::Deserialize(unsigned char* cpHeader)
  {
    bool bReturnValue = false;

    this->mcID_Length        = cpHeader[0];
    this->mcColourMapType    = cpHeader[1];
    this->mcDataTypeCode     = cpHeader[2];
    memcpy_s(&(this->msColourMapOrigin), sizeof(this->msColourMapOrigin), &(cpHeader[3]), 2);
    memcpy_s(&(this->msColourMapLength), sizeof(this->msColourMapLength), &(cpHeader[5]), 2);
    this->mcColourMapDepth   = cpHeader[7];
    memcpy_s(&(this->msX_Origin),        sizeof(this->msX_Origin), &(cpHeader[8]),  2);
    memcpy_s(&(this->msY_Origin),        sizeof(this->msY_Origin), &(cpHeader[10]), 2);
    memcpy_s(&(this->msWidth),           sizeof(this->msWidth),    &(cpHeader[12]), 2);
    memcpy_s(&(this->msHeight),          sizeof(this->msHeight),   &(cpHeader[14]), 2);
    this->mcBitsPerPixel     = cpHeader[16];
    this->mcImageDescription = cpHeader[17];


    Texture::musWidth  = this->msWidth;					
    Texture::musHeight = this->msHeight;
    Texture::mucDepthInBits	= this->mcBitsPerPixel; 
    Texture::mucDepthInBytes = this->mcBitsPerPixel / 8;

    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool TGA::Load(std::ifstream& ifs)
  {
    bool bReturnValue = false;

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
    string strFileName;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This unsigned short will count the number of camera parameters read in
    // and will be used to verify that the correct number of parameters have 
    // been initialized.
    unsigned short usParameterCount = 0;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    ifs >> strLabel;
    if(strLabel == "File")
    {
      ifs >> strFileName;
      ifstream ifsTGA;
      ifsTGA.open(strFileName.c_str(), ios::binary);
      if(ifsTGA.is_open())
      {
        unsigned char* pucHeader = new unsigned char[18];
        ifsTGA.read(reinterpret_cast<char*>(pucHeader), 18);
        this->Deserialize(pucHeader);

        if(Texture::mpImage)
          delete [] Texture::mpImage;
        Texture::mpImage = new Color<unsigned char>[Texture::musWidth * Texture::musHeight];
        unsigned long ulBytesToRead = Texture::musWidth * Texture::musHeight * Texture::mucDepthInBytes;
        unsigned long ulBytesRead = 0UL;
        unsigned long ulTexelsRead = 0UL;
        Color<unsigned char> oTempColor;
        unsigned long ulIndex = 0;
        while(ulBytesRead < ulBytesToRead)
        {
          char caTemp[3];
          ifsTGA.read(&caTemp[0], Texture::mucDepthInBytes);
          ulBytesRead += Texture::mucDepthInBytes;
          Texture::mpImage[ulIndex].A(0);
          Texture::mpImage[ulIndex].R(caTemp[0]);
          Texture::mpImage[ulIndex].G(caTemp[1]);
          Texture::mpImage[ulIndex].B(caTemp[2]);
          ulIndex++;
        }

        delete [] pucHeader;

        if(ulBytesRead == ulBytesToRead)
          bReturnValue = true;
      }
    }
    //-----------------------------------------------------------------------//

    return bReturnValue;
  }
  //-------------------------------------------------------------------------//
}
//***************************************************************************//