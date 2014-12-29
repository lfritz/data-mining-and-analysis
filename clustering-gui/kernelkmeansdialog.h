#pragma once

#include <QDialog>

class QButtonGroup;
class QDoubleSpinBox;
class QLabel;
class QSpinBox;

// Dialog where the user can specify parameters for the Kernel K-means
// algorithm. The user can choose between three kernel functions: homogeneous
// polynomial kernel, inhomogeneous polynomial kernel and Gaussian kernel.
class KernelKmeansDialog : public QDialog {
    Q_OBJECT

    QSpinBox * clustersSpinBox;
    QSpinBox * repetitionsSpinBox;
    QButtonGroup * kernelGroup;
    QLabel * q0Label;
    QDoubleSpinBox * q0;
    QLabel * q1Label;
    QDoubleSpinBox * q1;
    QLabel * cLabel;
    QDoubleSpinBox * cSpinBox;
    QLabel * varLabel;
    QDoubleSpinBox * sigmaSpinBox;

public:
    KernelKmeansDialog(QWidget * parent = nullptr);

    int clusters() const;
    int repetitions() const;

    int kernel() const;
    double q() const;
    double c() const;
    double sigma() const;

private slots:
    void updateKernel();
};