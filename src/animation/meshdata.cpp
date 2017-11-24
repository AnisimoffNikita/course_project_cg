#include "meshdata.h"

Vertex::Vertex(const Vec3 v, const Vec3 n)
    : v(v)
    , n(n)
{
}

const Vec3 &Vertex::getV() const
{
    return v;
}

void Vertex::setV(const Vec3 &value)
{
    v = value;
}

const Vec3 &Vertex::getN()
{
    return n;
}

void Vertex::setN(const Vec3 &value)
{
    n = value;
}

void Vertex::transform(const Transformation &transformation)
{
    n += v;
    transformation.transform(v);
    transformation.transform(n);
    n -= v;
}

bool Vertex::operator ==(const Vertex &other)
{
    return n == other.n && v == other.v;
}


Triangle::Triangle(const int &v1, const int &v2, const int &v3)
    : v{v1, v2, v3}
{
}

int Triangle::getV1() const
{
    return v[0];
}

void Triangle::setV1(const int &value)
{
    v[0] = value;
}

int Triangle::getV2() const
{
    return v[1];
}

void Triangle::setV2(const int &value)
{
    v[1] = value;
}

int Triangle::getV3() const
{
    return v[2];
}

void Triangle::setV3(const int &value)
{
    v[2] = value;
}

Material::Material(const Color &ka, const Color &kd, const Color &ks, float ns,
                   float ni, float d)
    : ka(ka)
    , kd(kd)
    , ks(ks)
    , ns(ns)
    , ni(ni)
    , d(d)
{
}

Color Material::getKa() const
{
    return ka;
}

void Material::setKa(const Color &value)
{
    ka = value;
}

Color Material::getKd() const
{
    return kd;
}

void Material::setKd(const Color &value)
{
    kd = value;
}

Color Material::getKs() const
{
    return ks;
}

void Material::setKs(const Color &value)
{
    ks = value;
}

float Material::getD() const
{
    return d;
}

void Material::setD(float value)
{
    d = value;
}

float Material::getNi() const
{
    return ni;
}

void Material::setNi(float value)
{
    ni = value;
}

float Material::getNs() const
{
    return ns;
}

void Material::setNs(float value)
{
    ns = value;
}
