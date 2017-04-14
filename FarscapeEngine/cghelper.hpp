//
//  cghelper.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/14/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cghelper_hpp
#define cghelper_hpp

#define PI 3.14159265

namespace CGCore
{

    // Defining high precision data types
    class Vec2;
    
    // 3d Vector
    class Vec3
    {
    protected:
        double Data[3];
        double Clipping; // a clipping value
        void CheckZeros();
    public:
        // ctors
        Vec3() { Data[0] = 0.0f; Data[1] =0.0f; Data[2] =0.0f; }
        Vec3(const double x, const double y) { Data[0] = x; Data[1] = y; Data[2] = 0.0f; Clipping = 0.0000001f; }
        Vec3(const double x, const double y, const double z) { Data[0] = x; Data[1] = y; Data[2] = z; Clipping = 0.0000001f; }
        Vec3(const Vec3& V) { Data[0] = V.Data[0]; Data[1] = V.Data[1]; Clipping = 0.0000001f; }
        // Get angle between this and V
        double AngleBetween(const Vec3& V) const;
        Vec3 CrossProduct(const Vec3& V) const;
        // dot product (scalar product) of this and V vectors (this is commutative)
        double DotProduct(const Vec3& V) const;
        Vec3 GetNormalized() const; // get a normalized version of this
        virtual double Magnitude() const;
        virtual void Normalize(); // normalize this
        virtual void SetClipping(double C);
        void Set(const double X, const double Y, const double Z);
        virtual void SetX(const double X);
        virtual void SetY(const double Y);
        void SetZ(const double Z);
        // Square of components
        virtual double Sqrmag() const;
        
        inline double GetClipping() const { return Clipping; }
        inline virtual double X() const { return Data[0]; }
        inline virtual double Y() const { return Data[1]; }
        inline double Z() const { return Data[2]; }
        
        operator Vec2() const;
    };
    
    
    
    class Vec2 : protected Vec3
    {
    public:
        Vec2() : Vec3(0.0f,0.0f) {}
        Vec2(const double x, const double y) : Vec3(x,y) {}
        Vec2(const Vec2& V) : Vec3(V.Data[0], V.Data[1]) {}
        
        double AngleBetween(const Vec2& V) const;
        double DotProduct(const Vec2& V) const;
        Vec2 GetNormalized() const;
        virtual double Magnitude() const override;
        virtual void Normalize() override;
        virtual void SetClipping(double C) override;
        void Set(const double X, const double Y);
        virtual void SetX(const double X) override;
        virtual void SetY(const double Y) override;
        virtual double X() const override;
        virtual double Y() const override;
    };
}

#endif /* cghelper_hpp */
