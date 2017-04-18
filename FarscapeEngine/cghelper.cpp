//
//  cghelper.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/14/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cghelper.hpp"
#include <cmath>
#include <cstdio>
#include <assert.h>
#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef USE_GLM

// Use C++11 standard
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>



glm::mat4 CGCore::CreateTransformationMatrix(
     const glm::vec3& Translation,
     const glm::vec3& RotAxis,
     const float RotAngle,
     const glm::vec3& Scale
     )
{
    glm::mat4 TranslationMat = glm::translate(glm::mat4(1.0f), Translation);
    //TestPrintMatrix4(TranslationMat, "TRANSLATION");

    glm::mat4 RotMat = glm::rotate(TranslationMat, RotAngle, RotAxis);
    //TestPrintMatrix4(RotMat, "ROTATION");

    glm::mat4 ScaleMat = glm::scale(RotMat, Scale);

    glm::mat4 TransformationMat =
    TranslationMat * RotMat * ScaleMat;
    return TransformationMat;
}


void CGCore::TestPrintMatrix4(glm::mat4& M, const char* msg ){
    if(msg !=nullptr)
    {
        printf("************************* mat4 %s \n",msg);
    }

    for(int Col = 0; Col < 4; Col++)
    {
        printf("|\t");
        for(int Row = 0; Row < 4; Row++)
        {
            printf("%f\t",M[Row][Col]);
        }
        printf("\n");
    }
    printf("************************* END");
}
#endif


// Vec3 Implementation
CGCore::Vec3::Vec3()
{
    Data = new double[VEC_LEN];
    Data[0] = 0.0f;
    Data[1] =0.0f;
    Data[2] =0.0f;
    Data[3] = 1.0f;
}


CGCore::Vec3::Vec3(const double x, const double y)
{
    Data = new double[VEC_LEN];
    Data[0] = x;
    Data[1] = y;
    Data[2] = 0.0f;
    Data[3] = 1.0f;
    Clipping = 0.0000001f;
}


CGCore::Vec3::Vec3(const double x, const double y, const double z)
{
    Data = new double[VEC_LEN];
    Data[0] = x;
    Data[1] = y;
    Data[2] = z;
    Data[3] = 1.0f;
    Clipping = 0.0000001f;
}


CGCore::Vec3::Vec3(const Vec3& V)
{
    Data = new double[VEC_LEN];
    Data[0] = V.Data[0];
    Data[1] = V.Data[1];
    Data[2] = V.Data[2];
    Data[3] = 1.0f;
    Clipping = 0.0000001f;
}


CGCore::Vec3::~Vec3()
{
    delete [] Data;
    Data = nullptr;
}



double CGCore::Vec3::AngleBetween(const CGCore::Vec3& V) const
{
    double CosTheta = DotProduct(V) / (Magnitude() * V.Magnitude());
    return std::acos(CosTheta);
}


void CGCore::Vec3::CheckZeros()
{
    if (Data[0] < Clipping) Data[0] = 0.0f;
    if (Data[1] < Clipping) Data[1] = 0.0f;
    if (Data[2] < Clipping) Data[2] = 0.0f;
}


CGCore::Vec3 CGCore::Vec3::CrossProduct(const Vec3& V) const
{
    CGCore::Vec3 NewV3;

    NewV3.Data[0] = Data[1] * V.Data[2] - Data[2] * V.Data[1];
    NewV3.Data[1] = Data[2] * V.Data[0] - Data[0] * V.Data[2];
    NewV3.Data[2] = Data[0] * V.Data[1] - Data[1] * V.Data[0];

    return NewV3;
}


double CGCore::Vec3::DotProduct(const CGCore::Vec3& V) const
{
    return Data[0]*V.Data[0] + Data[1]*V.Data[1] + Data[2]*V.Data[2];
}


CGCore::Vec3 CGCore::Vec3::GetNormalized() const
{
    double MagV = Magnitude();
    CGCore::Vec3 Vn(Data[0] / MagV, Data[1] / MagV, Data[2] / MagV);

    return Vn;
}


double CGCore::Vec3::Magnitude() const
{
    return std::sqrt(Sqrmag());
}


void CGCore::Vec3::Normalize()
{
    double MagV = Magnitude();

    Data[0] = Data[0] / MagV;
    Data[1] = Data[1] / MagV;
    Data[2] = Data[2] / MagV;

}


void CGCore::Vec3::Set(const double X, const double Y, const double Z)
{
    SetX(X);
    SetY(Y);
    SetZ(Z);
}


void CGCore::Vec3::SetClipping(double C)
{
    Clipping = C;
}


void CGCore::Vec3::SetX(const double X)
{
    Data[0] = X;
}


void CGCore::Vec3::SetY(const double Y)
{
    Data[1] = Y;
}


void CGCore::Vec3::SetZ(const double Z)
{
    Data[2] = Z;
}


double CGCore::Vec3::Sqrmag() const
{
    return (Data[0] * Data[0] + Data[1] * Data[1] + Data[2] * Data[2]);
}


CGCore::Vec3::operator Vec2() const
{
    return Vec2(Data[0], Data[1]);
}


// Vec2

double CGCore::Vec2::AngleBetween(const Vec2& V) const
{
    return CGCore::Vec3::AngleBetween((Vec3)V);
}


double CGCore::Vec2::DotProduct(const Vec2& V) const
{
    return CGCore::Vec3::DotProduct(V);
}


CGCore::Vec2 CGCore::Vec2::GetNormalized() const
{
    CGCore::Vec3 V3d = CGCore::Vec3::GetNormalized();
    CGCore::Vec2 V2d(V3d.X(),V3d.Y());
    return V2d;
}


double CGCore::Vec2::Magnitude() const
{
    return CGCore::Vec3::Magnitude();
}


void CGCore::Vec2::Normalize()
{
    CGCore::Vec3::Normalize();
}


void CGCore::Vec2::SetClipping(double C)
{
    CGCore::Vec3::SetClipping(C);
}


void CGCore::Vec2::Set(const double X, const double Y)
{
    CGCore::Vec3::Set(X, Y, 0.0f);
}


void CGCore::Vec2::SetX(const double X)
{
    CGCore::Vec3::SetX(X);
}


void CGCore::Vec2::SetY(const double Y)
{
    CGCore::Vec3::SetY(Y);
}


double CGCore::Vec2::X() const
{
    return Data[0];
}


double CGCore::Vec2::Y() const
{
    return Data[1];
}


// Vec4
void CGCore::Vec4::Set(const double X, const double Y, const double Z, const double A)
{
    CGCore::Vec3::Set(X, Y, Z);
    Data[3] = A;
}


void CGCore::Vec4::SetA(const double A)
{
    Data[3] = A;
}


CGCore::Vec4& CGCore::Vec4::operator=(const CGCore::Vec4& Other)
{
    if (this != &Other) { // self-assignment check expected
        Other.Data[0] = Data[0];
        Other.Data[1] = Data[1];
        Other.Data[2] = Data[2];
        Other.Data[3] = Data[3];
    }
    return *this;
}


// MAt4f

CGCore::Mat4f::Mat4f()
{
    Data = new Vec4* [DATA_SIZE];
    for(int i = 0; i < DATA_SIZE; i++)
    {
        // Define a column (Column-major order)
        Data[i] = new Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
}


CGCore::Mat4f::Mat4f(const Vec3& Translation, const Vec3& Rotation, const float Scale)
{
    Data = new Vec4* [DATA_SIZE];
    for(int i = 0; i < DATA_SIZE; i++)
    {
        Data[i] = new Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    SetIdentity();



}


CGCore::Mat4f::~Mat4f()
{

    for(int i = 0; i < DATA_SIZE; i++)
    {
        // Delete each col
        delete Data[i];
    }
    delete[] Data;
}



float* CGCore::Mat4f::DumpLinearArray(int& Size, bool IsColumnMajorOrder) const
{
    // USER RESPONSIBLE FOR DESTROYING THIS ARRAY
    float* Array = new float[16];
    Size = 16;
    int CurPosition = 0;
    for(int Col = 0; Col < DATA_SIZE; Col++)
    {
        for(int Row = 0; Row < DATA_SIZE; Row++)
        {
            if(IsColumnMajorOrder)
            {
                Array[CurPosition] = (float)(*(Data[Col]))[Row];
            }
            else
            {
                Array[CurPosition] = (float)(*(Data[Row]))[Col];
            }
            CurPosition++;
        }
    }
    return Array;
}


float* CGCore::Mat4f::GetColumnMajorOrderLinear(int& Size) const
{
    return DumpLinearArray(Size, true);
}


float* CGCore::Mat4f::GetRowMajorOrderLinear(int& Size) const
{
    return DumpLinearArray(Size, false);
}


CGCore::Vec4* CGCore::Mat4f::GetVector(int VectorIndex) const
{
    assert(VectorIndex < DATA_SIZE);
    return Data[VectorIndex];
}


void CGCore::Mat4f::PrintMatrix() const
{
    printf("|\tV0\tV1\tV2\tV3\n");
    for(int Col = 0; Col < DATA_SIZE; Col++)
    {
        printf("|\t");
        for(int Row = 0; Row < DATA_SIZE; Row++)
        {
            printf("%f\t", (float)(*(Data[Row]))[Col]);
        }
        printf("\n");
    }
}


void CGCore::Mat4f::SetIdentity()
{
    for(int Col = 0; Col < DATA_SIZE; Col++)
    {
        for(int Row = 0; Row < DATA_SIZE; Row++)
        {
            if(Col == Row)
            {
                (*(Data[Col]))[Row] = 1.0f;
            }
            else
            {
                (*(Data[Col]))[Row] = 0.0f;
            }
        }
    }
}


void CGCore::Mat4f::SetVector(int Index, const Vec4& V)
{
    assert(Index < DATA_SIZE);
    (*(Data[Index])).Set(V.X(), V.Y(), V.Z(), V.A());
}


// Overloading Mat4f operators
CGCore::Mat4f& CGCore::Mat4f::operator=(const CGCore::Mat4f& Other)
{
    if (this != &Other) { // self-assignment check expected
        for(int i=0; i < DATA_SIZE; i++)
        {
            *(Other.Data[i]) = *(Data[i]);
        }
    }
    return *this;
}

