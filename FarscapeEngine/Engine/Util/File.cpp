//
//  File.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "File.h"

#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <cstdio>
#include <fstream>
#include <sstream>

#ifdef WINDOWS
#include<windows.h>
#endif

// Apple only definition

#include <png.h> // Ability to read png files for textures

// #include <unistd.h>
// #define GetCurrentDir getcwd

#include <GL/glew.h>
#include <GLFW/glfw3.h>


bool Farscape::FilePNGHandler::ReadPNG(const std::string& file_name)
{
    png_byte header[8];
    
    fp = fopen(file_name.c_str(), "rb");
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
        fp = nullptr;
        return false;
    }
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "ERROR: png_create_read_struct returned 0.\n");
        fclose(fp);
        fp = nullptr;
        return false;
    }
    
    // create png info struct
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return false;
    }
    
    // create png info struct
    end_info = png_create_info_struct(png_ptr);
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
        fclose(fp);
        return false;
    }
    
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
            fclose(fp);
            return false;
    }
    
    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);
    
    // Row size in bytes.
    unsigned long rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    
    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes-1) % 4);
    
    // Allocate the image_data as a big block, to be given to opengl
    image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
    if (image_data == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return false;
    }
    
    // row_pointers is for pointing to image_data for reading the png with libpng
    row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
    if (row_pointers == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        image_data = nullptr;
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
    m_width = temp_width;
    m_height = temp_height;
    m_format = format;
    return true;
}

Farscape::FilePNGHandler::FilePNGHandler(const std::string& file_name)
{
    m_isRead = ReadPNG(file_name);   
}

Farscape::FilePNGHandler::~FilePNGHandler()
{
    // clean up
    if(m_isRead)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        free(row_pointers);
        fclose(fp);
        
    }
    else
    {
        if(image_data != nullptr)
        {
            free(image_data);
        }
        if(row_pointers != nullptr)
        {
            free(row_pointers);
        }
    }
}

std::string Farscape::File::GetFileContents(const std::string& filePath)
{
    /*
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        throw std::runtime_error("Current dir problem: " + filePath);
    }
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    
    printf ("The current working directory is %s", cCurrentPath);
    */
    std::ifstream inFile(filePath);
    if(!inFile.is_open())
    {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
    
    std::stringstream stream;
    
    stream << inFile.rdbuf();
    return stream.str();
}
