//***************************************************************************//
// Shader Class Implementation
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

//***************************************************************************//
// Local Includes
#include "Shader.hpp"
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <assert.h>
#include <fstream>
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
#define FILE_LABEL "File"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //-----------------------------------------------------------------------//
  Shader::Shader(const std::string& rstrName, enum ShaderType eShaderType)
  {
    assert(rstrName.size());
    muiShaderID = 0;
    this->mstrName = rstrName;
    this->meType   = eShaderType;
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  Shader::~Shader()
  {
    try
    {
      if(glIsShader(muiShaderID))
      {
        glDeleteShader(muiShaderID);
        this->muiShaderID = 0;
      }
    }
    catch(...)
    {
    }
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  const std::string& Shader::Name() const
  {
    return this->mstrName;
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  unsigned int Shader::ID() const
  {
    return this->muiShaderID;
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  bool Shader::Load(std::ifstream& ifs)
  {
    bool bReturnValue = false;

    //---------------------------------------------------------------------//
    // Read in the label
    string strLabel;
    ifs >> strLabel;
    //---------------------------------------------------------------------//

    //---------------------------------------------------------------------//
    if(strLabel == FILE_LABEL)
    {
      string strFilename;
      ifs >> strFilename;
      if(strFilename.size())
      {
        this->mstrFilename = strFilename;
        /// \todo see if file actually exists.
        bReturnValue = true;
      }
    }
    //---------------------------------------------------------------------//

    return bReturnValue;
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  bool Shader::Compile()
  {
    bool bReturnValue = false;
    muiShaderID = glCreateShader(this->meType);
    if(muiShaderID != 0)
    {
      string strShader;
      ifstream ifs;
      ifs.open(mstrFilename.c_str());
      char buffer;
      if(ifs.is_open())
      {
        while(!ifs.eof())
        {
          ifs.read(&buffer, 1);
          if(ifs.good())
            strShader += buffer;
        }
        ifs.close();
      }
      const char* cp = strShader.c_str();

      glShaderSourceARB(muiShaderID, 1, &cp, NULL);
      assert(GL_NO_ERROR == glGetError());
      glCompileShaderARB(muiShaderID);
      GLint bCompiled;
      glGetShaderiv(muiShaderID, GL_COMPILE_STATUS, &bCompiled);

      if(bCompiled)
        bReturnValue = true;
      else
      {
        int iMaxLength    = 0;
        int iActualLength = 0;

        if(glIsShader(muiShaderID))
          glGetShaderiv(muiShaderID, GL_INFO_LOG_LENGTH, &iMaxLength);

        char* infoLog = new char[iMaxLength];
        glGetShaderInfoLog(muiShaderID, iMaxLength, &iActualLength, infoLog);
        delete [] infoLog;

        glDeleteShader(muiShaderID);
        muiShaderID = 0;
      }
    }

    return bReturnValue;
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  unsigned int Shader::ParameterLocation(const std::string& rstrParameterName)
  {
    unsigned int uiReturnValue = 0xFFFFFFFF;
    map<string, unsigned int >::const_iterator itr = this->mmapParametersToLocation.find(rstrParameterName);
    if(itr != this->mmapParametersToLocation.end())
      uiReturnValue = itr->second;
    return uiReturnValue;
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  bool Shader::UpdateParameter(const std::string& rstrParameterName, float fValue)
  {
    bool bReturnValue = false;
    map<string, unsigned int >::const_iterator itr = this->mmapParametersToLocation.find(rstrParameterName);
    if(itr != this->mmapParametersToLocation.end())
    {
      bReturnValue = true;
      glUniform1f(itr->second, fValue);
      assert(GL_NO_ERROR == glGetError());
    }
    return bReturnValue;
  }
  //-----------------------------------------------------------------------//

  //-----------------------------------------------------------------------//
  void Shader::UpdateParemeter(unsigned int uiLocation, float fValue)
  {
    glUniform1f(uiLocation, fValue);
    assert(GL_NO_ERROR == glGetError());
  }
  //-----------------------------------------------------------------------//
}
//***************************************************************************//