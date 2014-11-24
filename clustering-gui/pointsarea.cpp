#include "pointsarea.h"

#include <QMouseEvent>
#include <QPainter>
#include <random>

using Eigen::VectorXd;
using std::vector;

PointsArea::PointsArea(QWidget * parent) :
QWidget(parent),
colors {
    Qt::red, Qt::green, Qt::blue,
    Qt::cyan, Qt::magenta, Qt::yellow,
    Qt::darkRed, Qt::darkGreen, Qt::darkBlue,
    Qt::darkCyan, Qt::darkMagenta, Qt::darkYellow
},
ps(),
points_in_clustering(0),
clustering(),
multi(false) {
    setAttribute(Qt::WA_StaticContents);
}

vector<VectorXd> PointsArea::points() const {
    unsigned n = ps.size();
    vector<VectorXd> vs(n, VectorXd(2));
    for (unsigned i = 0; i < n; ++i) {
        vs[i][0] = ps[i].x();
        vs[i][1] = ps[i].y();
    }
    return vs;
}

void PointsArea::setClustering(Clustering c, unsigned size) {
    points_in_clustering = size;
    clustering = c;
    update();
}

void PointsArea::clearPoints() {
    points_in_clustering = 0;
    clustering.clear();
    ps.clear();
    update();
}

void PointsArea::clearClustering() {
    points_in_clustering = 0;
    clustering.clear();
    update();
}

void PointsArea::toggleMulti(bool on) {
    multi = on;
}

void PointsArea::mousePressEvent(QMouseEvent * event) {
    QPoint p = event->pos();
    if (multi) {
        static const double stddev = 10.0;
        static std::random_device random_device;
        static std::default_random_engine random_engine(random_device());
        static std::normal_distribution<double> normal_dist(0.0, stddev);
        for (unsigned i = 0; i < 5; ++i)
            ps.push_back(QPoint(p.rx() + normal_dist(random_engine),
                                p.ry() + normal_dist(random_engine)));
    } else {
        ps.push_back(p);
    }
    update();
}

void PointsArea::paintEvent(QPaintEvent * event) {
    QPainter painter(this);
    unsigned n = ps.size();
    unsigned k = clustering.size();

    // draw points assigned to a cluster
    for (unsigned j = 0; j < k; ++j) {
        const vector<unsigned>& cluster = clustering[j];
        QColor color = colors[j % colors.size()];
        painter.setPen(color);
        painter.setBrush(color);
        for (unsigned i : cluster)
            painter.drawEllipse(ps[i], 2,2);
    }

    // draw new points
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    for (unsigned i = points_in_clustering; i < n; ++i)
        painter.drawEllipse(ps[i], 2,2);
}
