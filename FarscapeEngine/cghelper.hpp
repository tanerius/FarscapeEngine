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
    private:
        const int VEC_LEN = 4;
    protected:
        double* Data = nullptr; // x,y,z,alpha
        double Clipping; // a clipping value
        void CheckZeros();
    public:
        // ctors
        Vec3();
        Vec3(const double x, const double y);
        Vec3(const double x, const double y, const double z);
        Vec3(const Vec3& V);
        ~Vec3();
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
        inline double XYZA(int x) { return Data[x]; }
        
        operator Vec2() const;
        double& operator[] (int x) {
            return Data[x];
        }
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
    
    
    
    class Vec4 : public Vec3
    {
    public:
        // ctors
        Vec4() : Vec3() {}
        Vec4(const double x, const double y) : Vec3(x, y) { Data[2] = 0.0f; Data[3] = 1.0f; Clipping = 0.0000001f; }
        Vec4(const double x, const double y, const double z, const double a) : Vec3(x, y, z) { Data[3] = a; Clipping = 0.0000001f; }
        Vec4(const Vec3& V) : Vec3(V) { }
        Vec4(const Vec4& V) : Vec3(V) { Data[3] = V.Data[3]; Clipping = 0.0000001f; }
        void Set(const double X, const double Y, const double Z, const double A);
        void SetA(const double A);
        double A() const { return Data[3]; }
    };
    
    
    
    // Implementation of a 4x4 Vec4 (stored in Row-major order) matrix
    class Mat4f
    {
    private:
        Vec4** Data;
        const int DATA_SIZE = 4;
        float* DumpLinearArray(int& Size, bool IsColumnMajorOrder=true) const;
    public:
        Mat4f();
        ~Mat4f();
        float* GetColumnMajorOrderLinear(int& Size) const;
        float* GetRowMajorOrderLinear(int& Size) const;
    };
}

#endif /* cghelper_hpp */
