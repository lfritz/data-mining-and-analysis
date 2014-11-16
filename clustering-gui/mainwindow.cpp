#include "mainwindow.h"

#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>

#include <kernelfunction.h>
#include <kernelkmeans.h>
#include <kmeans.h>

#include "kernelkmeansdialog.h"
#include "kmeansdialog.h"
#include "pointsarea.h"

using std::vector;

MainWindow::MainWindow() {
    // central widget
    QWidget * widget;
    setCentralWidget(widget = new QWidget);
    QVBoxLayout * layout;
    widget->setLayout(layout = new QVBoxLayout);

    // PointsArea
    layout->addWidget(pointsArea = new PointsArea);

    // buttons
    QHBoxLayout * buttonsLayout;
    layout->addLayout(buttonsLayout = new QHBoxLayout);
    QPushButton * quitButton;
    buttonsLayout->addWidget(quitButton = new QPushButton("Quit"));
    connect(quitButton, SIGNAL(pressed()), this, SLOT(close()));
    buttonsLayout->addStretch();
    QPushButton * clearPointsButton;
    buttonsLayout->addWidget(clearPointsButton = new QPushButton("Clear"));
    connect(clearPointsButton, SIGNAL(pressed()),
            pointsArea, SLOT(clearPoints()));
    QPushButton * multiButton;
    buttonsLayout->addWidget(multiButton = new QPushButton("Multi"));
    multiButton->setCheckable(true);
    connect(multiButton, SIGNAL(toggled(bool)),
            pointsArea, SLOT(toggleMulti(bool)));
    buttonsLayout->addStretch();
    QPushButton * clearClusteringButton;
    buttonsLayout->addWidget(clearClusteringButton =
                             new QPushButton("No Clustering"));
    connect(clearClusteringButton, SIGNAL(pressed()),
            pointsArea, SLOT(clearClustering()));
    QPushButton * kmeansButton;
    buttonsLayout->addWidget(kmeansButton = new QPushButton("K-means"));
    connect(kmeansButton, SIGNAL(pressed()), this, SLOT(kmeans()));
    QPushButton * kernelKmeansButton;
    buttonsLayout->addWidget(kernelKmeansButton =
                             new QPushButton("Kernel K-means"));
    connect(kernelKmeansButton, SIGNAL(pressed()), this, SLOT(kernelKmeans()));

    // window title and size
    setWindowTitle("Points");
    resize(640,640);
}

void MainWindow::kmeans() {
    KmeansDialog dialog(this);
    if ( ! dialog.exec())
        return;
    auto points = pointsArea->points();
    auto clustering = kmeans_repeat(dialog.repetitions(),
                                    points,
                                    dialog.clusters(),
                                    0.001);
    pointsArea->setClustering(clustering, points.size());
}

void MainWindow::kernelKmeans() {
    KernelKmeansDialog dialog(this);
    if ( ! dialog.exec())
        return;
    auto points = pointsArea->points();
    Eigen::MatrixXd kernel;
    switch (dialog.kernel()) {
        case 0:
        kernel = homogeneous_polynomial_kernel(points, dialog.q());
        break;
        case 1:
        kernel = inhomogeneous_polynomial_kernel(points,
                                                 dialog.q(),
                                                 dialog.c());
        break;
        default:
        double s = dialog.sigma();
        kernel = gaussian_kernel(points, s*s);
    }
    auto clustering = kernel_kmeans_repeat(dialog.repetitions(),
                                           kernel,
                                           dialog.clusters(),
                                           0.001);
    pointsArea->setClustering(clustering, points.size());
}
