#ifndef MESHDATA_H
#define MESHDATA_H

#include "src/image/color.h"
#include "src/math/vec3.h"
#include <array>
#include "transformation.h"

using namespace std;

class Vertex
{
public:
    Vertex() = default;
    Vertex(const Vec3 v, const Vec3 n);

    const Vec3 &getV() const;
    void setV(const Vec3 &value);

    const Vec3 &getN();
    void setN(const Vec3 &value);

    void transform(const Transformation &transformation);

    bool operator ==(const Vertex &other);

private:
    Vec3 v;
    Vec3 n;
};


class Triangle
{
public:
    Triangle() = default;
    Triangle(const int &v1, const int &v2, const int &v3);

    int getV1() const;
    void setV1(const int &value);

    int getV2() const;
    void setV2(const int &value);

    int getV3() const;
    void setV3(const int &value);
private:
    array<int, 3> v;
};

class Material
{
public:
    Material() = default;
    Material(const Color &ka, const Color &kd, const Color &ks, float ns,
             float ni, float d);

    Color getKa() const;
    void setKa(const Color &value);

    Color getKd() const;
    void setKd(const Color &value);

    Color getKs() const;
    void setKs(const Color &value);

    float getNs() const;
    void setNs(float value);

    float getNi() const;
    void setNi(float value);

    float getD() const;
    void setD(float value);

private:
    Color ka;
    Color kd;
    Color ks;
    float ns;
    float ni;
    float d;
};


#endif // MESHDATA_H