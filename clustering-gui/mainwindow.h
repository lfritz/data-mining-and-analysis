#pragma once

#include <QMainWindow>

class PointsArea;

// The application's main window. Contains a PointsArea widget, where the
// current set of points is shown, and a number of buttons.
class MainWindow : public QMainWindow {
    Q_OBJECT

    PointsArea * pointsArea;

public:
    MainWindow();

private slots:
    void kmeans();
    void kernelKmeans();
};
