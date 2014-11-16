#pragma once

#include <QDialog>

class QSpinBox;

// Dialog where the user can specify parameters for the K-means algorithm.
class KmeansDialog : public QDialog {
    Q_OBJECT

    QSpinBox * clustersSpinBox;
    QSpinBox * repetitionsSpinBox;

public:
    KmeansDialog(QWidget * parent = 0);
    int clusters() const;
    int repetitions() const;
};