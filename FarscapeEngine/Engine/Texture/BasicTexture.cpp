//
//  BasicTexture.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "BasicTexture.h"
#include "../Util/File.h"

#include <cassert>

Farscape::BasicTexture::BasicTexture(const std::string& file)
{
    LoadFromFile(file);
}

void Farscape::BasicTexture::LoadFromFile(const std::string& file)
{
    
    Farscape::FilePNGHandler pngfile("Res/Textures/" + file + ".png");
    assert(pngfile.IsSuccess());
    if(!pngfile.IsSuccess())
    {
        ///@TODO Throw error
        
    }
    
    Farscape::Image i = pngfile.GetImage();
    
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.m_width, i.m_height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, i.data);
    
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
    glBindTexture(GL_TEXTURE_2D, m_id);
}
