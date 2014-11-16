#include "kmeansdialog.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

KmeansDialog::KmeansDialog(QWidget * parent) : QDialog(parent) {
    QVBoxLayout * layout;
    setLayout(layout = new QVBoxLayout);

    layout->addWidget(new QLabel("K-means clustering"));

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

    QDialogButtonBox * buttonBox;
    layout->addWidget(buttonBox =
                      new QDialogButtonBox(QDialogButtonBox::Ok |
                                           QDialogButtonBox::Cancel));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

int KmeansDialog::clusters() const {
    return clustersSpinBox->value();
}
int KmeansDialog::repetitions() const {
    return repetitionsSpinBox->value();
}
