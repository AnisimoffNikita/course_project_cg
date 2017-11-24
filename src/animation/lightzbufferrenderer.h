#ifndef LIGHTZBUFFERRENDERER_H
#define LIGHTZBUFFERRENDERER_H

#include "renderer.h"

#include "zbuffer.h"
#include <QPixmap>

class LightZBufferRenderer : public Renderer
{
public:
    LightZBufferRenderer() = default;
    LightZBufferRenderer(float scale, int width, int height);
    virtual ~LightZBufferRenderer();

    virtual void setCamera(SharedCamera value) override;
    virtual void addLight(SharedLight) override;

    virtual void start(float scale, int width, int height) override;
    virtual void renderMesh(shared_ptr<Mesh> mesh) override;

    virtual uchar *getRendered() override;
    virtual void finish() override;

protected:
    void fillTriangle(Triangle &triangle);
    void getLeftRightBounds(std::vector<int> &lleft, std::vector<int> &lright,
                            std::vector<Vec3> &nleft, std::vector<Vec3> &nright, Triangle &triangle,
                            bool &swapped);
    void triangleSort(const std::vector<Vertex> &vertices, Triangle &triangle);
    float calculateIntensity(const Vec3 &n, const Vec3 &orig);

    void putPixel(int x, int y, const Color &color);
    std::vector<int> getBrezenhemY(const Vec3 &p1, const Vec3 &p2);
    std::vector<Vec3> getNormals(const std::vector<int> &l, const Vec3 &n1,
                                 const Vec3 &n2);

    ZBuffer zbuffer;
    uchar *buffer;
    SharedCamera camera;

    vector<SharedLight> lights;

    vector<shared_ptr<Mesh>> meshes;
    shared_ptr<Mesh> currentMesh;
    vector<Vertex> projected;
};


#endif // LIGHTZBUFFERRENDERER_H