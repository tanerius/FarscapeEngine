//
//  cghelper.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/14/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cghelper.hpp"
#include <cmath>

// Vec2 Implementation

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
    SetX(Y);
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
    CGCore::Vec2::Vec3 V3d = CGCore::Vec3::GetNormalized();
    CGCore::Vec2::Vec2 V2d(V3d.X(),V3d.Y());
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
