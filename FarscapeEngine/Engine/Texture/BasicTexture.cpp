//
//  BasicTexture.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "BasicTexture.h"

#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <cstdio>
#include <fstream>
#include <sstream>

#include "../Util/File.h"


// Apple only definition

#include <png.h> // Ability to read png files for textures

#include <cassert>

Farscape::BasicTexture::BasicTexture(const std::string& file)
{
    if(!LoadFromFile(file))
    {
        printf("Can't read texture file!!");
        exit(0);
    }
}

bool Farscape::BasicTexture::LoadFromFile(const std::string& file_name_temp)
{
    Farscape::FilePNGHandler* pngTexture = new Farscape::FilePNGHandler("Res/Textures/" + file_name_temp + ".png");
    printf("%s\n" ,file_name_temp.c_str());
    assert(pngTexture->IsSuccess());
    Farscape::Image i = pngTexture->GetImage();
    GenerateTexture(i.m_width, i.m_height, i.m_format, i.data);
    delete pngTexture;
    return true;
}

void Farscape::BasicTexture::GenerateTexture(GLuint temp_width, GLuint temp_height, GLint format, GLubyte* image_data)
{
    //printf("h: %d, w: %d\n",temp_height,temp_width);
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    
    glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height,
                 0, format, GL_UNSIGNED_BYTE, image_data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Farscape::BasicTexture::~BasicTexture()
{
    glDeleteTextures(1, &m_id);
}

void Farscape::BasicTexture::BindTexture() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
