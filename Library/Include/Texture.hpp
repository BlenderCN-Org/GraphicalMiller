//***************************************************************************//
// Texture Class Interface
//
// Created May 13, 2005
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

#ifndef MST_GRAPHICS_TEXTURE_HPP
#define MST_GRAPHICS_TEXTURE_HPP

//***************************************************************************//
// System Includes
#include <string>
//***************************************************************************//

// Local Includes
#include "Utility.hpp"

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  enum TextureType
  {
    TGA_TEXTURE_TYPE,
    NO_TEXTURE_TYPE
  };
  //*************************************************************************//

  //*************************************************************************//
  class Texture
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // To store texture binding
    unsigned long mulTextureBinding;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    std::string mstrName;
    std::string mstrTextureFileName;
    //-----------------------------------------------------------------------//

    //***********************************************************************//
  protected:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    enum TextureType meTextureType;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Depth of color 
    unsigned char mucDepthInBytes;
    unsigned char mucDepthInBits;
    /// Width of texture
    unsigned short musWidth;
    /// Height of texture
    unsigned short musHeight;

    // Buffer that holds the color map
    Color<unsigned char>* mpImage;
    //-----------------------------------------------------------------------//
    
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Texture(const std::string& rstrName);
    virtual ~Texture();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    const std::string&  Name() const { return this->mstrName; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long  Binding() {return mulTextureBinding;}
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual bool  Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Binds the the current texture to make it active
    void  Bind() const;
    void  Unbind() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Initialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// The below methods are getters for this classes private members
    /// The const keyword is not needed for Width(), Height(), Depth() but 
    /// it signifies that these methods are read only getters
    unsigned char  DepthInBits()    const;
    unsigned char  DepthInBytes()   const;
    unsigned short  Width()   const;
    unsigned short  Height()  const;
    
    /// Returns the a pointer to the image buffer
    Color<unsigned char>*  Image()   const;
    //-----------------------------------------------------------------------//

    void  Render() { this->Bind(); };
    //***********************************************************************//
  }; // End of class Texture : public Surface
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_TEXTURE_HPP
