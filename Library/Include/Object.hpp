//***************************************************************************//
// Object Class Interface
//
// Created: February 1, 2007
// By: Jeremy Michael Miller
//
// Copyright (c) 2007-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2005-2016, Graphical Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_GRAPHICS_OBJECT_HPP
#define MST_GRAPHICS_OBJECT_HPP

//***************************************************************************//
// MST Includes
#include <MathmaticalMiller.hpp>
#include <string>

//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  // Object is the base class for all objects in a 3D scene
  class Object
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    void Create(const std::string& rstrName);
    void Clone(const Object& rSource);
    void Destroy();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  protected:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Describes the position of the object.
    MST::Vector<float, 4> mPosition; // Position is a vector so we can use MathmaticalMiller's Dot function
    MST::Vector<float, 4> mForwardVector;
    MST::Vector<float, 4> mRightVector;
    MST::Vector<float, 4> mUpVector;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    float mfPitch;
    float mfYaw;
    float mfRoll;

    // For accessing parameters in shader when using the the programmable 
    // pipeline
    unsigned int muiPositionAttributeLocation;
    unsigned int muiColorAttributeLocation;
    unsigned int muiRotationAngleUniformLocation;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    MST::Matrix<float, 4> mTransformMatrix;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void TransformToModelSpace();
    void TransformToViewSpace();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Name of object
    std::string mstrName;
    //-----------------------------------------------------------------------//


    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Object(const std::string& rstrName);
    Object(const Object& rSource);
    Object(const Object& rSource, const std::string& rstrDestinationName); 
    virtual ~Object();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    Object& Object::operator=(const Object& rSource)
    {
      if(this != &rSource)
      {
        Clone(rSource);
      }    
      return *this;
    }
    //-----------------------------------------------------------------------//
    
    //-----------------------------------------------------------------------//
    const std::string&  Name() const { return mstrName; } 
    void  Name(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void RelativePitch(float fAngle);
    virtual void RelativeRoll(float fAngle);
    virtual void RelativeYaw(float fAngle);

    virtual void AbsolutePitch(float fAngle);
    virtual void AbsoluteRoll(float fAngle);
    virtual void AbsoluteYaw(float fAngle);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void Position(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void Move(float fX, float fY, float fZ);
    /// Moves the object left or right relative to its current orientation
    virtual void Strafe(float fDisplacement);
    /// Moves the object forward or backwards relative to its current orientation
    virtual void Advance(float fDisplacement);
    /// Moves the object up or down relative to its current orientation
    virtual void Elevate(float fDisplacement);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void Forward(float fX, float fY, float fZ);
    virtual void Up(float fX, float fY, float fZ);
    virtual void Right(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Object
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_OBJECT_HPP