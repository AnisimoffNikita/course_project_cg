#ifndef LIGHT_H
#define LIGHT_H

#include "sceneobject.h"
#include "src/image/color.h"

class Light : public SceneObject
{
public:
    Light() = default;
    Light(const Vec3 &position, float intensity);
    virtual ~Light() = default;

    virtual void draw(std::unique_ptr<Renderer> &) override;
    virtual void transform(Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;

    virtual Color getIntensity(const Vec3 &normal, const Vec3 &position,
                               const Vec3 &camera,
                               const Color &ka, const Color &kd, const Color &ks,
                               float ns) const = 0;

    virtual bool isPoint() const = 0;
protected:
    float intensity;
};

using SharedLight = std::shared_ptr<Light>;
using WeakLight = std::weak_ptr<Light>;


#endif // LIGHT_H
