//***************************************************************************//
// Camera Class Interface
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2011  Jeremy M Miller.  All rights reserved.
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

#ifndef HABU_GRAPHICS_CAMERA_HPP
#define HABU_GRAPHICS_CAMERA_HPP

//***************************************************************************//
// Platform Includes
#include <windows.h>

// System Includes
#include <fstream> // For std namespace in ifstream
#include <string>

// Local Includes
#include "Object.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // This class describes a camera object.  Camera objects are managed in the 
  // CameraManager class
  class Camera : public Object
  {
  private:
    //-----------------------------------------------------------------------//
    HabuTech::Matrix<float, 4> mProjectionMatrix;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Describes the distance for the near and far clip planes.
    /// The near clip plan should never be set closer than 1.0.
    float mfNearClipPlane;
    float mfFarClipPlane;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Describes the vertical field of view
    float mfVerticalFOV;
    //-----------------------------------------------------------------------//

    std::string mstrName;

    class Scene* mpScene;

    void UpdateProjection();
    //-----------------------------------------------------------------------//
  public:
    //-----------------------------------------------------------------------//
    //-----------------------------------------------------------------------//
    /// Constructor sets the camera up as follows.
    /// Up vector parallel to positive y basis vector.
    /// Right vector parallel to positive x basis vector.
    /// Forward vector parallel to positive z basis vector.
    /// Near clip plan at 1.0F.
    /// Far clip plane at 100.0F.
    /// All other orientation and position data is zero.
    Camera(const std::string& strName, class Scene* const pScene);
    // Destructor does nothing.
    ~Camera();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Scene(class Scene* pScene);
    class Scene* const _cdecl Scene() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool _cdecl Load(std::ifstream& ifs);
    bool _cdecl LoadDefaults();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl SetFOV(float fAngle);
    void _cdecl ChangeFOV(float fAngle);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl SetOrientation(float fX, float fY, float fZ);
    void _cdecl SetUp(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    HabuTech::Matrix<float, 4>& _cdecl GetProjectionMatrix()  { return this->mProjectionMatrix; }
    HabuTech::Matrix<float, 4>& _cdecl GetViewMatrix()  { return Object::mTransformMatrix; }
    float _cdecl X() { return Object::mPosition.X(); }
    float _cdecl Y() { return Object::mPosition.Y(); }
    float _cdecl Z() { return Object::mPosition.Z(); }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Render();
    //-----------------------------------------------------------------------//
  }; // End of class Camera : public Object
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_CAMERA_HPP