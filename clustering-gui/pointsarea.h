#pragma once

#include <Eigen/Core>
#include <QWidget>
#include <vector>

#include <clustering.h>

// Widget that shows the input and output of clustering a set of points in 2D.
// The user can add points by clicking anywhere in the widget. Points are
// initially shown as little black circles; after a clustering is set, points
// in different clusters are shown in different colors.
class PointsArea : public QWidget {
    Q_OBJECT

    std::vector<QColor> colors;
    std::vector<QPoint> ps;
    unsigned points_in_clustering;
    Clustering clustering;
    bool multi;

public:
    // Create a PointsArea, initially with no points.
    PointsArea(QWidget * parent = nullptr);

    // Get the current set of points.
    std::vector<Eigen::VectorXd> points() const;

public slots:
    // Set a clustering for the points. The clustering must be a valid
    // clustering of the points 0 through size-1 and size must not be more than
    // the number of points (although it may be less).
    void setClustering(Clustering c, unsigned size);

    // Remove all points.
    void clearPoints();

    // Reset the clustering.
    void clearClustering();

    // Should we add multiple points every time the user clicks in the area?
    // Off initially.
    void toggleMulti(bool on);

protected:
    void mousePressEvent(QMouseEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
};
