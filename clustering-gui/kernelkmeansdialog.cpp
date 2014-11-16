#include "kernelkmeansdialog.h"

#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QSpinBox>
#include <QVBoxLayout>

KernelKmeansDialog::KernelKmeansDialog(QWidget * parent) : QDialog(parent) {
    QVBoxLayout * layout;
    setLayout(layout = new QVBoxLayout);

    layout->addWidget(new QLabel("Kernel K-means clustering"));

    QHBoxLayout * clustersLayout;
    layout->addLayout(clustersLayout = new QHBoxLayout);
    clustersLayout->addWidget(new QLabel("Number of clusters:"));
    clustersLayout->addWidget(clustersSpinBox = new QSpinBox);
    clustersSpinBox->setRange(1, 1000);
    clustersSpinBox->setValue(3);

    QHBoxLayout * repetitionsLayout;
    layout->addLayout(repetitionsLayout = new QHBoxLayout);
    repetitionsLayout->addWidget(new QLabel("Repetitions:"));
    repetitionsLayout->addWidget(repetitionsSpinBox = new QSpinBox);
    repetitionsSpinBox->setRange(1, 1000);
    repetitionsSpinBox->setValue(10);

    kernelGroup = new QButtonGroup(this);

    QRadioButton * r0;
    layout->addWidget(r0 =
                      new QRadioButton("Homogeneous polynomial kernel"));
    kernelGroup->addButton(r0, 0);
    QHBoxLayout * l0;
    layout->addLayout(l0 = new QHBoxLayout);
    l0->addWidget(q0Label = new QLabel("q ="));
    l0->addWidget(q0 = new QDoubleSpinBox);
    q0->setRange(0.0, 100.0);
    q0->setValue(2.0);

    QRadioButton * r1;
    layout->addWidget(r1 =
                      new QRadioButton("Inhomogeneous polynomial kernel"));
    kernelGroup->addButton(r1, 1);
    QHBoxLayout * l1;
    layout->addLayout(l1 = new QHBoxLayout);
    l1->addWidget(q1Label = new QLabel("q ="));
    l1->addWidget(q1 = new QDoubleSpinBox);
    q1->setRange(0.0, 100.0);
    q1->setValue(2.0);
    l1->addWidget(cLabel = new QLabel("c ="));
    l1->addWidget(cSpinBox = new QDoubleSpinBox);
    cSpinBox->setRange(0.0, 1000.0);
    cSpinBox->setValue(1.0);

    QRadioButton * r2;
    layout->addWidget(r2 =
                      new QRadioButton("Gaussian kernel"));
    kernelGroup->addButton(r2, 2);
    QHBoxLayout * l2;
    layout->addLayout(l2 = new QHBoxLayout);
    l2->addWidget(varLabel = new QLabel("sigma ="));
    l2->addWidget(sigmaSpinBox = new QDoubleSpinBox);
    sigmaSpinBox->setRange(0.0, 1000.0);
    sigmaSpinBox->setValue(20);

    r0->setChecked(true);
    updateKernel();
    connect(kernelGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(updateKernel()));

    QDialogButtonBox * buttonBox;
    layout->addWidget(buttonBox =
                      new QDialogButtonBox(QDialogButtonBox::Ok |
                                           QDialogButtonBox::Cancel));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

int KernelKmeansDialog::clusters() const {
    return clustersSpinBox->value();
}
int KernelKmeansDialog::repetitions() const {
    return repetitionsSpinBox->value();
}

int KernelKmeansDialog::kernel() const {
    return kernelGroup->checkedId();
}
double KernelKmeansDialog::q() const {
    return (kernel() == 0) ? q0->value() : q1->value();
}
double KernelKmeansDialog::c() const {
    return cSpinBox->value();
}
double KernelKmeansDialog::sigma() const {
    return sigmaSpinBox->value();
}

void KernelKmeansDialog::updateKernel() {
    int checked = kernel();
    q0Label->setEnabled(checked == 0);
    q0->setEnabled(checked == 0);
    q1Label->setEnabled(checked == 1);
    q1->setEnabled(checked == 1);
    cLabel->setEnabled(checked == 1);
    cSpinBox->setEnabled(checked == 1);
    varLabel->setEnabled(checked == 2);
    sigmaSpinBox->setEnabled(checked == 2);
}
