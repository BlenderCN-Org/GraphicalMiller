//***************************************************************************//
// Texture Class Implementation
//
// Created Mar 06, 2005
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
#include <windows.h>

//***************************************************************************//
// 3rdParty Includes
#include <GL\GL.h>
//***************************************************************************//

#include <assert.h>
#include <stdio.h>

#include <fstream>
#include <sstream>
#include <string>

#include "Texture.hpp"
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
#define DEFAULT_TEXTURE_WIDTH  32  // Pixels
#define DEFAULT_TEXTURE_HEIGHT 32  // Pixels
#define DEFAULT_TEXTURE_DEPTH  4   // Bytes

#define NUMBER_OF_TEXTURE_PARAMETERS 2

#define TEXTURE_TYPE_LABEL     "Type"
#define TEXTURE_FILE_LABEL     "File"
//***************************************************************************//

using namespace std;

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  Texture::Texture(const std::string& rstrName)
  {
    //-----------------------------------------------------------------------//
    mpImage            = NULL;
    musWidth           = DEFAULT_TEXTURE_WIDTH;
    musHeight          = DEFAULT_TEXTURE_HEIGHT;
    mucDepthInBytes    = DEFAULT_TEXTURE_DEPTH;

    meTextureType      = NO_TEXTURE_TYPE;

    this->mstrName = rstrName;

    glGenTextures(1, reinterpret_cast<GLuint*>(&mulTextureBinding));
    //-----------------------------------------------------------------------//
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Texture::~Texture()
  {
    glDeleteTextures(1, reinterpret_cast<GLuint*>(&mulTextureBinding));

    if(this->mpImage)
      delete [] this->mpImage;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Texture::Load(std::ifstream& ifs)
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
    for(unsigned short i = 0; i < NUMBER_OF_TEXTURE_PARAMETERS; i++)
    {
      //---------------------------------------------------------------------//
      // Read in the label
      ifs >> strLabel;
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // Match the label to some predefined token and set the proper data member.
      if(strLabel == TEXTURE_TYPE_LABEL)
      {
        string strType;
        ifs >> strType;
        if(strType == "TGA")
        {
          this->meTextureType = TGA_TEXTURE_TYPE;
        }
        else if(strType == "Target")
        {
          // No file parameter in this case
          usParameterCount++;
        }
        usParameterCount++;
      }
      else if(strLabel == TEXTURE_FILE_LABEL)
      {
        string strFilename;
        ifs >> strFilename;
        usParameterCount++;
      } // End of if-else chain that matches the read in label 
      // to predefined token.
      //---------------------------------------------------------------------//
    } // End of for(unsigned short i = 0; i < NUMBER_OF_CAMERA_PARAMETERS; i++)
    //-----------------------------------------------------------------------//

    assert(usParameterCount == NUMBER_OF_TEXTURE_PARAMETERS);
    return (usParameterCount == NUMBER_OF_TEXTURE_PARAMETERS);
  }
  //-----------------------------------------------------------------------//

  //*************************************************************************//
  void Texture::Bind() const
  {
    glBindTexture(GL_TEXTURE_2D, this->mulTextureBinding);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Texture::Unbind() const
  {
    glBindTexture(GL_TEXTURE_2D, 0UL);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Texture::Initialize()
  {
    this->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, 4, Texture::musWidth, Texture::musHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture::mpImage);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT  );
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT  );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned char Texture::DepthInBytes()   const
  {
    return mucDepthInBytes;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned char Texture::DepthInBits()   const
  {
    return mucDepthInBits;;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned short Texture::Width()   const
  {
    return musWidth;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned short Texture::Height()  const
  {
    return musHeight;
  }
  //*************************************************************************//

  //*************************************************************************//
  Color<unsigned char>* Texture::Image()   const
  {
    return mpImage;
  }
  //*************************************************************************//
}
//***************************************************************************//