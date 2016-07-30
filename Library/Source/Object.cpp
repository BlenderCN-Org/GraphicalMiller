//***************************************************************************//
// Object Class Implementation
//
// Created Feb 1, 2007
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

//***************************************************************************//
#include "Object.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  Object::Object(const std::string& rstrName)
  {
    Create(rstrName);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Object::Object(const Object& rSource)
  {
    // Uses this class's overloaded assignment operator.
    Create(rSource.Name());
    Clone(rSource);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Object::Object(const Object& rSource, const std::string& rstrDestinationName)
  {
    Create(rstrDestinationName);
    Clone(rSource);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Object::~Object()
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
  void Object::Create(const std::string& rstrName)
  {
    //-----------------------------------------------------------------------//
    mfPitch = 0.0F;
    mfYaw   = 0.0F;
    mfRoll  = 0.0F;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mPosition.Set     (0.0F, 0.0F, 0.0F); 
    mRightVector.Set  (1.0F, 0.0F, 0.0F);
    mUpVector.Set     (0.0F, 1.0F, 0.0F);
    mForwardVector.Set(0.0F, 0.0F, 1.0F);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mstrName = rstrName;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mTransformMatrix.Identity();
    //-----------------------------------------------------------------------//
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Destroy()
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Clone(const Object& rSource)
  {
    this->mPosition      = rSource.mPosition;
    this->mForwardVector = rSource.mForwardVector;
    this->mRightVector   = rSource.mRightVector;
    this->mUpVector      = rSource.mUpVector;
    
    this->mfPitch = rSource.mfPitch;
    this->mfYaw   = rSource.mfYaw;
    this->mfRoll  = rSource.mfRoll;
    
    this->mTransformMatrix = rSource.mTransformMatrix;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Name(const std::string& rstrName)
  {
    this->mstrName = rstrName;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Position(float fX, float fY, float fZ)
  {
    mPosition.Set(fX, fY, fZ);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Move(float fX, float fY, float fZ)
  {
    mPosition.rX() += fX;
    mPosition.rY() += fY;
    mPosition.rZ() += fZ;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::RelativePitch(float fAngle)
  {
    this->mfPitch += fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::RelativeRoll(float fAngle)
  {
    this->mfRoll += fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::RelativeYaw(float fAngle)
  {
    this->mfYaw += fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::AbsolutePitch(float fAngle)
  {
    this->mfPitch = fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::AbsoluteRoll(float fAngle)
  {
    this->mfRoll = fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::AbsoluteYaw(float fAngle)
  {
    this->mfYaw = fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Strafe(float fDisplacement)
  {
	  this->mPosition.X(this->mPosition.X() + (this->mRightVector.X() * fDisplacement));
	  this->mPosition.Z(this->mPosition.Z() + (this->mRightVector.Z() * fDisplacement));
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Advance(float fDisplacement)
  {
    this->mPosition.X(this->mPosition.X() + (this->mForwardVector.X() * fDisplacement));
	  this->mPosition.Z(this->mPosition.Z() + (this->mForwardVector.Z() * fDisplacement));
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Elevate(float fDisplacement)
  {
    this->mPosition.X(this->mPosition.X() + (this->mUpVector.X() * fDisplacement));
	  this->mPosition.Y(this->mPosition.Y() + (this->mUpVector.Y() * fDisplacement));
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Forward(float fX, float fY, float fZ)
  {
    this->mForwardVector.X(fX);
    this->mForwardVector.Y(fY);
    this->mForwardVector.Z(fZ);
    this->mForwardVector.Normalize();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Up(float fX, float fY, float fZ)
  {
    this->mUpVector.X(fX);
    this->mUpVector.Y(fY);
    this->mUpVector.Z(fZ);
    this->mUpVector.Normalize();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Right(float fX, float fY, float fZ)
  {
    this->mRightVector.X(fX);
    this->mRightVector.Y(fY);
    this->mRightVector.Z(fZ);
    this->mRightVector.Normalize();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::TransformToModelSpace()
  {
    MST::Matrix<float, 4> oTempMatrix;

    this->mRightVector.Set  (1.0, 0.0, 0.0);
    this->mUpVector.Set     (0.0, 1.0, 0.0);
    this->mForwardVector.Set(0.0, 0.0, 1.0);

    if(mfRoll != 0.0F)
    { 
      oTempMatrix.RotateAboutZ(mfRoll);
      this->mRightVector.  Transform(oTempMatrix);
      this->mRightVector.  Normalize();
      this->mUpVector.     Cross(this->mRightVector,    this->mForwardVector);
    }

    if(mfYaw != 0.0F)
    {
      oTempMatrix.RotateAboutY(mfYaw);
      this->mForwardVector.Transform(oTempMatrix);
      this->mForwardVector.Normalize();
      this->mRightVector.  Cross(this->mForwardVector,  this->mUpVector);
    }

    if(mfPitch != 0.0F)
    {

      oTempMatrix.RotateAboutX(mfPitch);
      this->mUpVector.     Transform(oTempMatrix);
      this->mUpVector.     Normalize();
      this->mForwardVector.Cross(this->mUpVector,       this->mRightVector);
    }
    
    this->mTransformMatrix[0][0] = this->mRightVector.X();
    this->mTransformMatrix[1][0] = this->mUpVector.X();
    this->mTransformMatrix[2][0] = this->mForwardVector.X();
    this->mTransformMatrix[3][0] = 0.0F;

    this->mTransformMatrix[0][1] = this->mRightVector.Y();
    this->mTransformMatrix[1][1] = this->mUpVector.Y();
    this->mTransformMatrix[2][1] = this->mForwardVector.Y();
    this->mTransformMatrix[3][1] = 0.0F;

    this->mTransformMatrix[0][2] = this->mRightVector.Z();
    this->mTransformMatrix[1][2] = this->mUpVector.Z();
    this->mTransformMatrix[2][2] = this->mForwardVector.Z();
    this->mTransformMatrix[3][2] = 0.0F;

    this->mTransformMatrix[0][3] = this->mPosition.X();;
    this->mTransformMatrix[1][3] = this->mPosition.Y();; 
    this->mTransformMatrix[2][3] = this->mPosition.Z();;
    this->mTransformMatrix[3][3] = 1.0F;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::TransformToViewSpace()
  {
    MST::Matrix<float, 4> oTempMatrix;

    this->mRightVector.Set  (1.0, 0.0, 0.0);
    this->mUpVector.Set     (0.0, 1.0, 0.0);
    this->mForwardVector.Set(0.0, 0.0, 1.0);

    if(mfRoll != 0.0F)
    { 
      oTempMatrix.RotateAboutZ(mfRoll);
      this->mRightVector.  Transform(oTempMatrix);
      this->mRightVector.  Normalize();
      this->mUpVector.     Cross(this->mRightVector,    this->mForwardVector);
    }

    if(mfYaw != 0.0F)
    {
      oTempMatrix.RotateAboutY(mfYaw);
      this->mForwardVector.Transform(oTempMatrix);
      this->mForwardVector.Normalize();
      this->mRightVector.  Cross(this->mForwardVector,  this->mUpVector);
    }

    if(mfPitch != 0.0F)
    {
      
      oTempMatrix.RotateAboutX(mfPitch);
      this->mUpVector.     Transform(oTempMatrix);
      this->mUpVector.     Normalize();
      this->mForwardVector.Cross(this->mUpVector,       this->mRightVector);
    } 

    this->mTransformMatrix[0][0] = this->mRightVector.X();
    this->mTransformMatrix[1][0] = this->mRightVector.Y();
    this->mTransformMatrix[2][0] = this->mRightVector.Z();
    this->mTransformMatrix[3][0] = -(this->mPosition.Dot(this->mRightVector));

    this->mTransformMatrix[0][1] = this->mUpVector.X();
    this->mTransformMatrix[1][1] = this->mUpVector.Y();
    this->mTransformMatrix[2][1] = this->mUpVector.Z();
    this->mTransformMatrix[3][1] = -(this->mPosition.Dot(this->mUpVector));

    this->mTransformMatrix[0][2] = this->mForwardVector.X();
    this->mTransformMatrix[1][2] = this->mForwardVector.Y();
    this->mTransformMatrix[2][2] = this->mForwardVector.Z();
    this->mTransformMatrix[3][2] = -(this->mPosition.Dot(this->mForwardVector));

    this->mTransformMatrix[0][3] = 0.0F;
    this->mTransformMatrix[1][3] = 0.0F; 
    this->mTransformMatrix[2][3] = 0.0F;
    this->mTransformMatrix[3][3] = 1.0F;

    return;
  }
  //-------------------------------------------------------------------------//
}// End of namespace MST
//***************************************************************************//