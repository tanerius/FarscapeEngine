//
//  cgobj.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/29/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgobj.hpp"
#include "cgmesh.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

static bool CompareOBJIndexPtr(const CGCore::OBJIndex* a, const CGCore::OBJIndex* b);
static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token);
static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end);
static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end);
static inline std::vector<std::string> SplitString(const std::string &s, char delim);

CGCore::OBJModel::OBJModel(const std::string& fileName)
{
    hasUVs = false;
    hasNormals = false;
    std::ifstream file;
    file.open(fileName.c_str());
    
    std::string line;
    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            
            unsigned long lineLength = line.length();
            
            if(lineLength < 2)
                continue;
            
            const char* lineCStr = line.c_str();
            
            switch(lineCStr[0])
            {
                case 'v':
                    if(lineCStr[1] == 't')
                        this->uvs.push_back(ParseOBJVec2(line));
                    else if(lineCStr[1] == 'n')
                        this->normals.push_back(ParseOBJVec3(line));
                    else if(lineCStr[1] == ' ' || lineCStr[1] == '\t')
                        this->vertices.push_back(ParseOBJVec3(line));
                    break;
                case 'f':
                    CreateOBJFace(line);
                    break;
                default: break;
            };
        }
    }
    else
    {
        std::cerr << "Unable to load mesh: " << fileName << std::endl;
    }
}

CGCore::IndexedModel CGCore::OBJModel::ToIndexedModel()
{
    CGCore::IndexedModel result;
    CGCore::IndexedModel normalModel;
    
    unsigned int numIndices = (unsigned int)OBJIndices.size();
    
    std::vector<OBJIndex*> indexLookup;
    
    for(unsigned int i = 0; i < numIndices; i++)
        indexLookup.push_back(&OBJIndices[i]);
    
    std::sort(indexLookup.begin(), indexLookup.end(), CompareOBJIndexPtr);
    
    std::map<OBJIndex, unsigned int> normalModelIndexMap;
    std::map<unsigned int, unsigned int> indexMap;
    
    for(unsigned int i = 0; i < numIndices; i++)
    {
        OBJIndex* currentIndex = &OBJIndices[i];
        
        glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
        glm::vec2 currentTexCoord;
        glm::vec3 currentNormal;
        
        if(hasUVs)
            currentTexCoord = uvs[currentIndex->uvIndex];
        else
            currentTexCoord = glm::vec2(0,0);
        
        if(hasNormals)
            currentNormal = normals[currentIndex->normalIndex];
        else
            currentNormal = glm::vec3(0,0,0);
        
        unsigned int normalModelIndex;
        unsigned int resultModelIndex;
        
        //Create model to properly generate normals on
        std::map<OBJIndex, unsigned int>::iterator it = normalModelIndexMap.find(*currentIndex);
        if(it == normalModelIndexMap.end())
        {
            normalModelIndex = (unsigned int)normalModel.Positions.size();
            
            normalModelIndexMap.insert(std::pair<OBJIndex, unsigned int>(*currentIndex, normalModelIndex));
            normalModel.Positions.push_back(currentPosition);
            normalModel.TexCoords.push_back(currentTexCoord);
            normalModel.Normals.push_back(currentNormal);
        }
        else
            normalModelIndex = it->second;
        
        //Create model which properly separates texture coordinates
        unsigned int previousVertexLocation = FindLastVertexIndex(indexLookup, currentIndex, result);
        
        if(previousVertexLocation == (unsigned int)-1)
        {
            resultModelIndex = (unsigned int)result.Positions.size();
            
            result.Positions.push_back(currentPosition);
            result.TexCoords.push_back(currentTexCoord);
            result.Normals.push_back(currentNormal);
        }
        else
            resultModelIndex = previousVertexLocation;
        
        normalModel.Indices.push_back(normalModelIndex);
        result.Indices.push_back(resultModelIndex);
        indexMap.insert(std::pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
    }
    
    if(!hasNormals)
    {
        normalModel.CalcNormals();
        
        for(unsigned int i = 0; i < result.Positions.size(); i++)
            result.Normals[i] = normalModel.Normals[indexMap[i]];
    }
    
    return result;
};

unsigned int CGCore::OBJModel::FindLastVertexIndex(const std::vector<CGCore::OBJIndex*>& indexLookup, const CGCore::OBJIndex* currentIndex, const CGCore::IndexedModel& result)
{
    unsigned int start = 0;
    unsigned int end = (unsigned int)indexLookup.size();
    unsigned int current = (end - start) / 2 + start;
    unsigned int previous = start;
    
    while(current != previous)
    {
        CGCore::OBJIndex* testIndex = indexLookup[current];
        
        if(testIndex->vertexIndex == currentIndex->vertexIndex)
        {
            unsigned int countStart = current;
            
            for(unsigned int i = 0; i < current; i++)
            {
                OBJIndex* possibleIndex = indexLookup[current - i];
                
                if(possibleIndex == currentIndex)
                    continue;
                
                if(possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;
                
                countStart--;
            }
            
            for(unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
            {
                OBJIndex* possibleIndex = indexLookup[current + i];
                
                if(possibleIndex == currentIndex)
                    continue;
                
                if(possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;
                else if((!hasUVs || possibleIndex->uvIndex == currentIndex->uvIndex)
                        && (!hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
                {
                    glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
                    glm::vec2 currentTexCoord;
                    glm::vec3 currentNormal;
                    
                    if(hasUVs)
                        currentTexCoord = uvs[currentIndex->uvIndex];
                    else
                        currentTexCoord = glm::vec2(0,0);
                    
                    if(hasNormals)
                        currentNormal = normals[currentIndex->normalIndex];
                    else
                        currentNormal = glm::vec3(0,0,0);
                    
                    for(unsigned int j = 0; j < result.Positions.size(); j++)
                    {
                        if(currentPosition == result.Positions[j]
                           && ((!hasUVs || currentTexCoord == result.TexCoords[j])
                               && (!hasNormals || currentNormal == result.Normals[j])))
                        {
                            return j;
                        }
                    }
                }
            }
            
            return -1;
        }
        else
        {
            if(testIndex->vertexIndex < currentIndex->vertexIndex)
                start = current;
            else
                end = current;
        }
        
        previous = current;
        current = (end - start) / 2 + start;
    }
    
    return -1;
}

void CGCore::OBJModel::CreateOBJFace(const std::string& line)
{
    std::vector<std::string> tokens = SplitString(line, ' ');
    
    this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(ParseOBJIndex(tokens[2], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));
    
    if((int)tokens.size() > 4)
    {
        this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(ParseOBJIndex(tokens[4], &this->hasUVs, &this->hasNormals));
    }
}

CGCore::OBJIndex CGCore::OBJModel::ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals)
{
    unsigned int tokenLength = (unsigned int)token.length();
    const char* tokenString = token.c_str();
    
    unsigned int vertIndexStart = 0;
    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
    
    CGCore::OBJIndex result;
    result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    result.uvIndex = 0;
    result.normalIndex = 0;
    
    if(vertIndexEnd >= tokenLength)
        return result;
    
    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
    
    result.uvIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasUVs = true;
    
    if(vertIndexEnd >= tokenLength)
        return result;
    
    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
    
    result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasNormals = true;
    
    return result;
}

glm::vec3 CGCore::OBJModel::ParseOBJVec3(const std::string& line)
{
    unsigned int tokenLength = (unsigned int)line.length();
    const char* tokenString = line.c_str();
    
    unsigned int vertIndexStart = 2;
    
    while(vertIndexStart < tokenLength)
    {
        if(tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }
    
    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
    
    float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
    
    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
    
    float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
    
    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
    
    float z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
    
    return glm::vec3(x,y,z);
    
    //glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()))
}

glm::vec2 CGCore::OBJModel::ParseOBJVec2(const std::string& line)
{
    unsigned int tokenLength = (unsigned int)line.length();
    const char* tokenString = line.c_str();
    
    unsigned int vertIndexStart = 3;
    
    while(vertIndexStart < tokenLength)
    {
        if(tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }
    
    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
    
    float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
    
    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
    
    float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
    
    return glm::vec2(x,y);
}

static bool CompareOBJIndexPtr(const CGCore::OBJIndex* a, const CGCore::OBJIndex* b)
{
    return a->vertexIndex < b->vertexIndex;
}

static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
{
    unsigned int result = start;
    while(result < length)
    {
        result++;
        if(str[result] == token)
            break;
    }
    
    return result;
}

static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end)
{
    return atoi(token.substr(start, end - start).c_str()) - 1;
}

static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end)
{
    return atof(token.substr(start, end - start).c_str());
}

static inline std::vector<std::string> SplitString(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    
    const char* cstr = s.c_str();
    unsigned int strLength = (unsigned int)s.length();
    unsigned int start = 0;
    unsigned int end = 0;
    
    while(end <= strLength)
    {
        while(end <= strLength)
        {
            if(cstr[end] == delim)
                break;
            end++;
        }
        
        elems.push_back(s.substr(start, end - start));
        start = end + 1;
        end = start;
    }
    
    return elems;
}

std::string CGCore::OBJModel::ToString() const
{
    std::string x = "OBJ File";
    
    return x;
}

