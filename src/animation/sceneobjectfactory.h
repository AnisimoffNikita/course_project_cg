#ifndef SCENEOBJECTFACTORY_H
#define SCENEOBJECTFACTORY_H

#include "sceneobject.h"
#include "camera.h"
#include "model.h"
#include "ambientlight.h"
#include "pointlight.h"

class SceneObjectFactory
{
public:
    SceneObjectFactory() = default;

    virtual ~SceneObjectFactory() = default;

    virtual SharedSceneObject create() = 0;
};

//TODO: move to own header
class CameraFactory : public SceneObjectFactory
{
public:
    struct PerspectiveData
    {
        float fovX;
        float fovY;
        float near;
        float far;
    };

public:
    CameraFactory(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up,
                  const PerspectiveData &data);
    //TODO: CameraFactory(const Vertex &position, const Vertex &target, const OrthographicData &data);
    virtual ~CameraFactory() = default;

    virtual SharedSceneObject create() override;

private:
    std::unique_ptr<Camera> camera;
};

class ModelFactory : public SceneObjectFactory
{
public:
    ModelFactory(const Vec3 &position, const Mesh &mesh);
    virtual ~ModelFactory() = default;

    virtual SharedSceneObject create() override;
private:
    std::unique_ptr<Model> model;
};

class AmbientLightFactory : public SceneObjectFactory
{
public:
    AmbientLightFactory(float intensity);
    virtual ~AmbientLightFactory() = default;

    virtual SharedSceneObject create() override;
private:
    std::unique_ptr<AmbientLight> light;
};

class PointLightFactory : public SceneObjectFactory
{
public:
    PointLightFactory(const Vec3 &position, float intensity);
    virtual ~PointLightFactory() = default;

    virtual SharedSceneObject create() override;
private:
    std::unique_ptr<PointLight> light;
};
#endif // SCENEOBJECTFACTORY_H
