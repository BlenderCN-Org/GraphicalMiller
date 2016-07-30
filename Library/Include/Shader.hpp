//***************************************************************************//
// Shader Class Interface
//
// Created: April 11, 2011
// By: Jeremy M Miller
//
// Copyright (c) 2011 Jeremy M Miller.  All rights reserved.
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

#ifndef HABU_GRAPHICS_SHADER_HPP
#define HABU_GRAPHICS_SHADER_HPP

//***************************************************************************//
// 3rd Party Includes
#include <glew.h> // Must be called before GL.h
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <string>
#include <map>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  enum ShaderType
  {
    HABU_GRAPHICS_VERTEX_SHADER   = GL_VERTEX_SHADER_ARB,
    HABU_GRAPHICS_FRAGMENT_SHADER = GL_FRAGMENT_SHADER_ARB,
    HABU_GRAPHICS_UNKNOWN_SHADER  = 0xFFFFFFFF
  };
  //*************************************************************************//

  //*************************************************************************//
  class Shader
  {
  private:
    //***********************************************************************//
    std::string mstrName;
    std::string mstrFilename;

    unsigned int muiShaderID;

    enum ShaderType meType;

    std::map<std::string, unsigned int> mmapParametersToLocation;
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Shader(const std::string& rstrName, enum ShaderType eShaderType);
    ~Shader();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    const std::string& Name() const;
    unsigned int ID() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool _cdecl Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool _cdecl Compile();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned int ParameterLocation(const std::string& rstrParameterName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool UpdateParameter(const std::string& rstrParameterName, float fValue);
    void UpdateParemeter(unsigned int uiLocation, float fValue);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  };
  //*************************************************************************//
}
//***************************************************************************//

#endif HABU_GRAPHICS_SHADER_HPP