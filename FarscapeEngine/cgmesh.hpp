//
//  cgmesh.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/22/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgmesh_hpp
#define cgmesh_hpp
#include "cgcore.hpp"
#include <vector>

#ifdef WINDOWS
#include<windows.h>
#endif

#ifdef USE_GLM
#include <glm/glm.hpp>
#endif

#include <GL/glew.h>

namespace CGCore
{
    
    enum class E_BUFFER_POSITION : unsigned char
    {
        E_POSITION,
        E_TEXCOORD,
        E_NORMAL,
        E_INDEX
    };

    
    class Vertex : public Object
    {
    private:
        glm::vec3* Pos = nullptr;
        glm::vec2* TexCoord = nullptr;
        glm::vec3* Normal = nullptr;
    public:
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
        {
            this->Pos = new glm::vec3(pos);
            this->TexCoord = new glm::vec2(texCoord);
            this->Normal = new glm::vec3(normal);
        }
        ~Vertex();
        glm::vec3* GetPos() const { return Pos; }
        glm::vec2* GetTexCoord() const { return TexCoord; }
        glm::vec3* GetNormal() const { return Normal; }
        
        virtual std::string ToString() const override;
    };
    
    
    
    class IndexedModel
    {
    public:
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;
        
        void CalcNormals();
    };
    
    
    
    class Mesh
    {
    public:
        Mesh(const std::string& fileName)
        {
            assert(false); // DONT USE NOW
        }
        Mesh(
             Vertex* vertices,
             unsigned int numVertices,
             unsigned int* indices,
             unsigned int numIndices
             );
        
        void Draw();
        virtual ~Mesh();
    protected:
    private:
        static const unsigned int NUM_BUFFERS = 4;
        void operator=(const Mesh& mesh) {}
        Mesh(const Mesh& mesh) {}
        
        void InitMesh(const IndexedModel& model);
        
        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];
        unsigned int m_numIndices;
    };
}

#endif /* cgmesh_hpp */
