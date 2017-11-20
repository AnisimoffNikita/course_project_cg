#include "modelview.h"

#include <QStyle>

#include "src/animation/rotatetransform.h"

#include "src/animation/scene.h"
#include "src/animation/renderer.h"
#include "src/animation/meshgenerator.h"
#include "src/animation/sceneobjectfactory.h"
#include "src/animation/carcassrenderer.h"
#include "src/animation/trianglerenderer.h"

ModelView::ModelView(QWidget *parent) :
    QGraphicsView(parent),
    graphicsScene(new QGraphicsScene()),
    canvas(640,480),
    scene(std::make_unique<Scene>())
{
    this->setStyleSheet("border: none;outline: none;");
    this->setBackgroundBrush(QBrush(QColor(236,232,228)));
    this->setScene(graphicsScene);
    this->setSizeAdjustPolicy(AdjustIgnored);
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    CameraFactory::PerspectiveData data;
    data.fovX = Math::ToRadians(80);
    data.fovY = Math::ToRadians(80);
    data.near = 0.1;
    data.far = 100;
    CameraFactory cameraFactory(Vertex(3,3,3), Vertex(0,0,0), Vertex(0,0,1), data);
    auto camera = cameraFactory.create();

    ModelFactory modelFactory(Vertex(0,0,0), MeshGenerator::CylinderTriangles(1,5,10));
    auto model = modelFactory.create();

    scene->add(camera);
    scene->add(model);
    scene->setActiveCamera(camera);

    renderer = std::make_unique<TriangleRenderer>(100,1024,768);

    scene->render(renderer);

    canvas = renderer->getRendered();

    updateCanvas();

}

void ModelView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    this->fitInView(graphicsScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void ModelView::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ModelView::mouseMoveEvent(QMouseEvent *event)
{
    auto dx = event->pos().x() - lastPos.x();
    auto dy = event->pos().y() - lastPos.y();

    auto camera = scene->getActiveCamera();
    if (camera.expired())
        return;

    auto workCamera = camera.lock();

    Vertex cameraPos = workCamera->getPosition();

    RotateZTransformation z(Math::ToRadians(-dx)/2, Vertex(0,0,cameraPos.getZ()));
    workCamera->transform(z);


    if (Math::Abs(cameraPos.getX()) > Math::Abs(cameraPos.getY()))
    {
        RotateYTransformation y(Math::ToRadians(-dy)/2, Vertex(0,0,0));
        workCamera->transform(y);
    }
    else
    {
        RotateXTransformation x(Math::ToRadians(-dy)/2, Vertex(0,0,0));
        workCamera->transform(x);
    }


    scene->render(renderer);
    canvas = renderer->getRendered();

    updateCanvas();

    lastPos = event->pos();
}

void ModelView::updateCanvas()
{
    graphicsScene->clear();
    graphicsScene->addPixmap(canvas);
    this->fitInView(graphicsScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void ModelView::setModelScene(std::unique_ptr<Scene> &&value)
{
    scene = std::move(value);
}
