#include <MainWindow.h>
#include "ui_MainWindow.h"
#include "ta7a.h"
#include <QFileDialog>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->open, &QPushButton::clicked, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile() {
     QString Filepath = QFileDialog::getOpenFileName(this, tr("Open File"),"D://", "All files (*.*);;Dicom (*.dcm);;");
     std::string inputFilename = Filepath.toStdString();
     render(inputFilename);
}

void MainWindow::render(std::string filepath) {
    vtkSmartPointer<vtkDICOMImageReader> reader =
        vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetFileName(filepath.c_str());
    reader->Update();

    vtkSmartPointer<vtkImageViewer2> imageViewer =
        vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());
    imageViewer->SetRenderWindow(ui->openGLWidget->GetRenderWindow());
    imageViewer->Render();
}

