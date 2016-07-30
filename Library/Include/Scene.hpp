//***************************************************************************//
// Scene Class Interface
//
// Created Sept 4, 2005
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

#ifndef MST_GRAPHICS_SCENE_HPP
#define MST_GRAPHICS_SCENE_HPP

//***************************************************************************//
// System Includes
#include <fstream>
#include <vector>
//***************************************************************************//

//***************************************************************************//
namespace MST
{

  //*************************************************************************//
  class GeometryBuffer
  {
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    const class Graphics* mpGraphics;
    //-----------------------------------------------------------------------//
    
    //-----------------------------------------------------------------------//
    unsigned int muiVertexBufferID;
    unsigned int muiIndexBufferID;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long mulVertexFreeElements;
    unsigned long mulIndexFreeElements;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned int muiMaxVertexSize;
    unsigned int muiMaxIndexSize;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void Create(const class Graphics* const pGraphics);
    void Clone(const GeometryBuffer& rSource);
    void Destroy();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    GeometryBuffer(const class Graphics* const pGraphics);
    GeometryBuffer(const GeometryBuffer& rSource);
    ~GeometryBuffer();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long  VertexFreeElements() const;
    unsigned long  IndexFreeElements() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long  MaxVertexElements() const;
    unsigned long  MaxIndexElements() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long  UsedVertexElements() const;
    unsigned long  UsedIndexElements() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long  Allocate(const class Vertex* const pVertices, unsigned long ulVerticesLength,
      const unsigned long* const pIndices, unsigned long ulIndicesLength);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Bind();
    void  Unbind();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  };
  //*************************************************************************//

  //*************************************************************************//
  class Scene
  {
  private:
    //***********************************************************************//
    std::string mstrSceneName;
    class Graphics* mpGraphics;

    unsigned int muiShaderProgram;

    std::vector<GeometryBuffer*>   mvGeometryBuffers;

    std::vector<class Mesh*>     mvMeshes;
    std::vector<class Light*>    mvLights;
    std::vector<class Camera*>   mvCameras;
    std::vector<class Material*> mvMaterials;
    std::vector<class Texture*>  mvTextures;
    std::vector<class Shader*>   mvShaders;

    class Camera* mpActiveCamera;
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Scene(class Graphics* const pGraphics);
    ~Scene();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool  Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void  Render();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool  SetupCamera();
    bool  SetupLight();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Camera* const  CreateCamera(const std::string& rstrName);
    bool  DestroyCamera(const std::string& rstrName);
    bool  DestroyCamera(class Camera** ppCamera);
    class Camera* const  GetCamera(const std::string& rstrName);
    class Camera* const  GetActiveCamera();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Light* const  CreateLight( const std::string& rstrName, enum LightID eLightID);
    bool  DestroyLight(const std::string& rstrName);
    bool  DestroyLight(class Light** ppLight);
    class Light* const  GetLight(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Material* const  CreateMaterial( const std::string& rstrName);
    bool  DestroyMaterial(const std::string& rstrName);
    bool  DestroyMaterial(class Material** ppMaterial);
    class Material* const  GetMaterial(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Mesh* const  CreateMesh(const std::string& rstrName);
    class Mesh* const  CloneMesh(const std::string& rstrSourceName, const std::string& rstrDestinationName);
    bool  DestroyMesh(const std::string& rstrName);
    bool  DestroyMesh(class Mesh** ppMesh);
    class Mesh* const  GetMesh(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Texture* const  CreateTexture(const std::string& rstrName, enum TextureType eTextureType);
    bool  DestroyTexture(const std::string& rstrName);
    bool  DestroyTexture(class Texture** ppTexture);
    class Texture* const  GetTexture(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Shader* const  CreateShader(const std::string& rstrName, enum ShaderType eShaderType);
    bool  DestroyShader(const std::string& rstrName);
    bool  DestroyShader(class Shader** ppShader);
    class Shader* const  GetShader(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class TGA* const  CreateBitmap(const std::string& rstrName);
    bool  DestroyBitmap(const std::string& rstrName);
    bool  DestroyBitmap(class Texture** ppMaterial);
    class TGA* const  GetBitmap(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Graphics* const  GetGraphics() const { return mpGraphics; }
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Scene
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_GRAPHICS_SCENE_HPP
