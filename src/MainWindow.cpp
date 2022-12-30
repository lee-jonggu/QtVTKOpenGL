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

    // ������ ����
    mRenderWindow->AddRenderer(mRenderer);
    mRenderWindow->SetInteractor(mInteractor);
    ui->openGLWidget->SetRenderWindow(mRenderWindow);
    mInteractor->SetInteractorStyle(mInteractorStyle);
    mInteractor->Initialize();

    // ���� ���� ����
    mRenderer->SetBackground(1, 0, 0);

    // Ŀ��Ʈ ����
    QObject::connect(ui->drawSphere_button, &QPushButton::clicked, this, &MainWindow::onDrawSphereClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDrawSphereClick()
{
    // �� �����
    vtkSmartPointer<vtkSphereSource> sphereSource =
        vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(5);
    sphereSource->Update();

    // ���� ������ �Ǵ� ���� �����
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    sphereMapper->SetInputData(sphereSource->GetOutput());
    
    vtkSmartPointer<vtkActor> sphere = vtkSmartPointer<vtkActor>::New();
    sphere->SetMapper(sphereMapper);
    
    // OpenGL�� �� �߰�
    mRenderer->AddViewProp(sphere);
    mRenderer->ResetCamera();
    mRenderWindow->Render();
    
}