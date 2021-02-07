//
//  Model.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Model_h
#define Model_h

#include <GL/glew.h>
#include <vector>

#include "../Util/NoCopy.h"
#include "../Core/Mesh.h"

namespace Farscape {
    class Model : public NoCopy
    {
        public:
            Model() = default;
            Model(const Mesh& mesh);
            ~Model();
        
        
        
            void AddData(const Mesh& mesh);
            void DeleteData();
        
            void AddVBO(int dimensions, const std::vector<GLfloat>& data);
            void BindVAO() const;
        
            int GetIndicesCount() const;
        
        private:
            void AddEBO(const std::vector<GLuint>& indices);
        
            GLuint m_vao = 0;
            int m_vboCount = 0;
            int m_indicesCount = 0;
            std::vector<GLuint> m_buffers;
    };

}
#endif /* Model_h */