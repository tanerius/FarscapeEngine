//
//  File.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef File_h
#define File_h

#include "SingletonBase.h"
#include <string>
#include <png.h> // Ability to read png files for textures
#include <GL/glew.h>

namespace Farscape
{
    struct Image
    {
        GLsizei m_width;
        GLsizei m_height;
        GLvoid* data;
    };
    
    class FilePNGHandler
    {
        public:
        FilePNGHandler() = delete;
        FilePNGHandler(const std::string& filename);
        ~FilePNGHandler();
        
        Image GetImage() {
            Image i;
            i.m_height = m_height;
            i.m_width = m_width;
            i.data = image_data;
            return i;
        }
        bool IsSuccess() { return m_isRead; }
        
        private:
        bool ReadPNG(const std::string& filename);
            FILE *fp = nullptr;
            png_uint_32 m_width;
            png_uint_32 m_height;
            GLint format;
            png_byte* image_data = nullptr;
            png_structp png_ptr;
            png_infop info_ptr;
            png_infop end_info;
            png_byte ** row_pointers = nullptr;
            bool m_isRead = false;
    };
    
    
    // A class that can work with files
    class File : public Farscape::SingletonBase<File>
    {
        friend class Farscape::SingletonBase<File>;
    public:
        File() = default;
        // Load string files
        std::string GetFileContents(const std::string& filePath);

        
    };
}

#endif /* File_hpp */
