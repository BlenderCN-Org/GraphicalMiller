//***************************************************************************//
// Camera Class Interface
//
// Created Jan 01, 2005
// By: Jeremy Michael Miller
//
// Copyright (c) 2015-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//


#ifndef MST_GRAPHICS_CAMERA_HPP
#define MST_GRAPHICS_CAMERA_HPP

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
namespace MST
{
  //*************************************************************************//
  // This class describes a camera object.  Camera objects are managed in the 
  // CameraManager class
  class Camera : public Object
  {
  private:
    //-----------------------------------------------------------------------//
    MST::Matrix<float, 4> mProjectionMatrix;
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
    void Scene(class Scene* pScene);
    class Scene* const  Scene() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool Load(std::ifstream& ifs);
    bool LoadDefaults();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  SetFOV(float fAngle);
    void  ChangeFOV(float fAngle);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void SetOrientation(float fX, float fY, float fZ);
    void SetUp(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    MST::Matrix<float, 4>&  GetProjectionMatrix()  { return this->mProjectionMatrix; }
    MST::Matrix<float, 4>&  GetViewMatrix()  { return Object::mTransformMatrix; }
    float  X() { return Object::mPosition.X(); }
    float  Y() { return Object::mPosition.Y(); }
    float  Z() { return Object::mPosition.Z(); }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Render();
    //-----------------------------------------------------------------------//
  }; // End of class Camera : public Object
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_CAMERA_HPP