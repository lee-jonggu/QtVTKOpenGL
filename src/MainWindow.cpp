#include <MainWindow.h>
#include "ui_MainWindow.h"

#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
    mRenderer(vtkSmartPointer<vtkRenderer>::New()),
    mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
    mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New())
{
    ui->setupUi(this);

    // Set Rendering
    mRenderWindow->AddRenderer(mRenderer);
    mRenderWindow->SetInteractor(mInteractor);
    ui->openGLWidget->SetRenderWindow(mRenderWindow);
    mInteractor->SetInteractorStyle(mInteractorStyle);
    mInteractor->Initialize();

    // Widget Background
    mRenderer->SetBackground(1, 0, 0);

    // Set Connect
    QObject::connect(ui->drawSphere_button, &QPushButton::clicked, this, &MainWindow::onDrawSphereClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDrawSphereClick()
{
    // Make Sphere
    vtkSmartPointer<vtkSphereSource> sphereSource =
        vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(5);
    sphereSource->Update();

    // Sphere Rendering Actor
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    sphereMapper->SetInputData(sphereSource->GetOutput());
    
    vtkSmartPointer<vtkActor> sphere = vtkSmartPointer<vtkActor>::New();
    sphere->SetMapper(sphereMapper);
    
    // OpenGL added Sphere
    mRenderer->AddViewProp(sphere);
    mRenderer->ResetCamera();
    mRenderWindow->Render();
    
}
