#ifndef SRC_SCENE_H
#define SRC_SCENE_H

#include <QWidget>
#include <QPointer>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>

class Scene final
{
    QPointer<Qt3DExtras::Qt3DWindow> view; ///< окно просмотра
    Qt3DCore::QEntity * scene; ///< корневой объект окна просмотра. выступает в роли сцены
    Qt3DRender::QCamera * camera; ///< камера
    Qt3DExtras::QOrbitCameraController * cameraController; ///< контроллер камеры

public:
    Scene(const Scene &) = delete;
    Scene(Scene &&) = delete;
    Scene() = delete;
    Scene & operator=(const Scene &) = delete;
    Scene & operator=(Scene &&) = delete;

    explicit Scene(Qt3DExtras::Qt3DWindow * view);
    ~Scene();

    /**
     * @brief установка перспективной проекции
     * @param fieldOfView угол обзора в градусах
     * @param aspect соотношение сторон
     * @param nearPlane ближняя плоскость обзора
     * @param farPlane дальняя плоскость обзора
     */
    void SetCameraPerspectiveProjection(float fieldOfView, float aspect, float nearPlane, float farPlane);

    /// установка позиции камеры
    void SetCameraPosition(const QVector3D & position);

    /// установка центра обзора камеры
    void SetCameraViewCenter(const QVector3D & viewCenter);

    /// установка скорости вращения камеры
    void SetCameraLookSpeed(float cameraLookSpeed);

    /// установка скорости движения камеры
    void SetCameraLinearSpeed(float cameraLinearSpeed);

    Qt3DCore::QEntity * GetScene() { return scene; }
    QPointer<Qt3DExtras::Qt3DWindow> GetView() { return view; }
    float Width() { return view->width(); }
    float Height() { return view->height(); }
};

#endif //SRC_SCENE_H
