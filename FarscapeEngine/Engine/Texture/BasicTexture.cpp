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
    png_byte header[8];
    std::string file_name = "Res/Textures/" + file_name_temp + ".png";
    FILE *fp = fopen(file_name.c_str(), "rb");
    if (fp == 0)
    {
        perror(file_name.c_str());
        return false;
    }
    
    // read the header
    fread(header, 1, 8, fp);
    
    if (png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "ERROR: %s is not a PNG.\n", file_name.c_str());
        fclose(fp);
        return false;
    }
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "ERROR: png_create_read_struct returned 0.\n");
        fclose(fp);
        return false;
    }
    
    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return false;
    }
    
    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return false;
    }
    
    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return false;
    }
    
    // init png reading
    png_init_io(png_ptr, fp);
    
    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);
    
    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);
    
    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;
    
    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
                 NULL, NULL, NULL);
    
    // No need to store the data now enable if needed
    //Width = temp_width;
    //Height = temp_height;
    
    //printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);
    
    if (bit_depth != 8)
    {
        fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name.c_str(), bit_depth);
        return false;
    }
    
    GLint format;
    switch(color_type)
    {
        case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name.c_str(), color_type);
            return false;
    }
    
    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);
    
    // Row size in bytes.
    unsigned long rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    
    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes-1) % 4);
    
    // Allocate the image_data as a big block, to be given to opengl
    png_byte * image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
    if (image_data == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return false;
    }
    
    // row_pointers is for pointing to image_data for reading the png with libpng
    png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
    if (row_pointers == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(fp);
        return false;
    }
    
    // set the individual row_pointers to point at the correct offsets of image_data
    for (unsigned int i = 0; i < temp_height; i++)
    {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }
    
    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);
    
    // Generate the OpenGL texture object
    GenerateTexture(temp_width, temp_height, format, image_data);
    
    // clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(fp);
    return true;
}

void Farscape::BasicTexture::GenerateTexture(GLuint temp_width, GLuint temp_height, GLint format, GLubyte* image_data)
{
    printf("h: %d, w: %d\n",temp_height,temp_width);
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
