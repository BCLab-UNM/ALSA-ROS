#pragma once

#include <QObject>
#include <QWidget>

class Histogram : public QWidget
{
    Q_OBJECT

public:
    Histogram(QWidget* parent = 0, Qt::WindowFlags f = 0);
    void setBins(QVector<int>& bins);
    void setBins(int* bins, int nbBins);
    void clear();
    bool toggled() {return _toggled;}
    void setMaxValue(float v);
    void setXUnits(QString v);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    QVector<int> _bins;
    bool _toggled;
    int _heightMax;
    float x_max;
    QString x_units;

};
