//***************************************************************************//
// Scene Class Interface
//
// Created Sept 4, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2011 Jeremy M Miller.  All rights reserved.
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

#ifndef HABU_GRAPHICS_SCENE_HPP
#define HABU_GRAPHICS_SCENE_HPP

//***************************************************************************//
// System Includes
#include <fstream>
#include <vector>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
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
    unsigned long _cdecl VertexFreeElements() const;
    unsigned long _cdecl IndexFreeElements() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long _cdecl MaxVertexElements() const;
    unsigned long _cdecl MaxIndexElements() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long _cdecl UsedVertexElements() const;
    unsigned long _cdecl UsedIndexElements() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long _cdecl Allocate(const class Vertex* const pVertices, unsigned long ulVerticesLength,
      const unsigned long* const pIndices, unsigned long ulIndicesLength);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Bind();
    void _cdecl Unbind();
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
    bool _cdecl Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Render();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool _cdecl SetupCamera();
    bool _cdecl SetupLight();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Camera* const _cdecl CreateCamera(const std::string& rstrName);
    bool _cdecl DestroyCamera(const std::string& rstrName);
    bool _cdecl DestroyCamera(class Camera** ppCamera);
    class Camera* const _cdecl GetCamera(const std::string& rstrName);
    class Camera* const _cdecl GetActiveCamera();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Light* const _cdecl CreateLight( const std::string& rstrName, enum LightID eLightID);
    bool _cdecl DestroyLight(const std::string& rstrName);
    bool _cdecl DestroyLight(class Light** ppLight);
    class Light* const _cdecl GetLight(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Material* const _cdecl CreateMaterial( const std::string& rstrName);
    bool _cdecl DestroyMaterial(const std::string& rstrName);
    bool _cdecl DestroyMaterial(class Material** ppMaterial);
    class Material* const _cdecl GetMaterial(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Mesh* const _cdecl CreateMesh(const std::string& rstrName);
    class Mesh* const _cdecl CloneMesh(const std::string& rstrSourceName, const std::string& rstrDestinationName);
    bool _cdecl DestroyMesh(const std::string& rstrName);
    bool _cdecl DestroyMesh(class Mesh** ppMesh);
    class Mesh* const _cdecl GetMesh(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Texture* const _cdecl CreateTexture(const std::string& rstrName, enum TextureType eTextureType);
    bool _cdecl DestroyTexture(const std::string& rstrName);
    bool _cdecl DestroyTexture(class Texture** ppTexture);
    class Texture* const _cdecl GetTexture(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Shader* const _cdecl CreateShader(const std::string& rstrName, enum ShaderType eShaderType);
    bool _cdecl DestroyShader(const std::string& rstrName);
    bool _cdecl DestroyShader(class Shader** ppShader);
    class Shader* const _cdecl GetShader(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class TGA* const _cdecl CreateBitmap(const std::string& rstrName);
    bool _cdecl DestroyBitmap(const std::string& rstrName);
    bool _cdecl DestroyBitmap(class Texture** ppMaterial);
    class TGA* const _cdecl GetBitmap(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Graphics* const _cdecl GetGraphics() const { return mpGraphics; }
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Scene
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_SCENE_HPP