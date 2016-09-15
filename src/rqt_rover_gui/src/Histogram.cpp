#include "Histogram.h"

#include <string>
#include <QPainter>
#include <cmath>
#include <iostream>

using namespace std;

Histogram::Histogram(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f),
_bins(0),
_heightMax(1)
{
    x_max = 0.0f;
};

void Histogram::setBins(QVector<int>& bins)
{
    _bins = bins;
    update();
}

void Histogram::setBins(int* bins, int nbBins)
{
    _bins.resize(nbBins);
    memcpy(_bins.data(), bins, nbBins*sizeof(int));
    update();
}


void Histogram::clear()
{
    _bins.clear();
    update();
}

void Histogram::mousePressEvent(QMouseEvent*)
{
    //_toggled = ! _toggled;
    //if( !_toggled ) clear();
}

void Histogram::paintEvent(QPaintEvent*)
{
    //cout << "Histogram updated" << endl;

    QRect viewPort = rect();
    int xLeft = viewPort.left();
    int xRight = viewPort.right();
    int yTop = viewPort.top();
    int yBottom = viewPort.bottom();
    int width = viewPort.width();
    int height = viewPort.height();
     
    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);

    QBrush brush(Qt::SolidPattern);
    brush.setColor("#DDDDDD");
    painter.setBrush(brush);

    // ---- Draw gray background ------------------------------------------------
    painter.drawRect(xLeft, yTop, xRight, yBottom);

    // ---- Draw vertical lines -------------------------------------------------
    pen.setColor("#AAAAAA");
    pen.setStyle(Qt::DashDotLine);
    painter.setPen(pen);

    int stepsV = 1<< int(log(width/40.0f)/log(2.0f));
    for(int i=1; i<stepsV; ++i)
    {
        painter.drawLine(width*float(i)/stepsV, yTop+1,
                         width*float(i)/stepsV, yBottom-1);
    }

    // ---- Draw horizontal lines -----------------------------------------------
    int stepsH = 1<< int(log(height/40.0f)/log(2.0f));
    for(int i=1; i<stepsH; ++i)
    {
        painter.drawLine(xLeft+1, height*float(i)/stepsH,
                         xRight-1,height*float(i)/stepsH);
    }

    QString x_max_str = QString::number(x_max, 'g', 5);

    QString x_max_label = x_max_str + x_units;//\u00b5m/s";

    QByteArray ba = x_max_label.toLocal8Bit();
    const char* x_max_label_char_array = ba.data();

    QFontMetrics fm = painter.fontMetrics();

    // Calculate text center position into the screen using QFontMetrics class
    int x_max_label_width = fm.width(x_max_label);




    // ---- Histogram itself ----------------------------------------------------
    int nbBins = _bins.size();

    if( !nbBins )
    {
        pen.setColor("#016790");
        painter.setPen(pen);
        //painter.drawText(xLeft+2, yBottom-2, tr("Histogram off"));
        return;
    }

    // Find maximum height in bins unit
    int heightMax=1;
    for( int i=0; i<nbBins; ++i )
        if( _bins[i]>heightMax ) heightMax = _bins[i];

    // Avoid giggling graph: do not update heightmax if variation <5%
    if( abs(_heightMax-heightMax)/float(_heightMax) > 0.05f )
        _heightMax = heightMax;
    
    // Scale histogram from bins unit to pixels unit
    // handle upscaling and downscaling in a different way
    QPolygon myPolygon;
    QLinearGradient linearGradient(0, 0, 0, height);
    pen.setStyle(Qt::SolidLine);

    if( nbBins < width )
    {

        float wScale = width/float(nbBins);
        float hScale = height/float(_heightMax);
        float hScaleLog = height/log(float(_heightMax));

        // log(bins)

        pen.setColor("#00aaee");   painter.setPen(pen);
        linearGradient.setColorAt(0.2, Qt::white);
        linearGradient.setColorAt(1.0, "#00aaee");
        painter.setBrush(linearGradient);

        //brush.setColor("#00aaee"); painter.setBrush(brush);

        myPolygon.clear();
        myPolygon << QPoint(xRight, yBottom) << QPoint(xLeft, yBottom);
        for( int i=0; i<nbBins; ++i )
            myPolygon << QPoint(xLeft+wScale*i, yTop+hScaleLog*( _bins[i] ? log(_heightMax/float(_bins[i])) : _heightMax));
        painter.drawPolygon(myPolygon);


        // bins
        pen.setColor("#016790");
        painter.setPen(pen);
        linearGradient.setColorAt(0.2, Qt::white);
        linearGradient.setColorAt(1.0, "#016790");
        painter.setBrush(linearGradient);

        myPolygon.clear();
        myPolygon << QPoint(xRight, yBottom) << QPoint(xLeft, yBottom);
        for( int i=0; i<nbBins; ++i )
            myPolygon << QPoint(xLeft+wScale*i, yTop+hScale*(_heightMax-_bins[i]));
        painter.drawPolygon(myPolygon);

    }
    else
    {
        float wScale = float(nbBins-1)/(width-1);
        float hScale = height/float(_heightMax);
        float hScaleLog = height/log(float(_heightMax));

        // log(bins)
        pen.setColor("#00aaee");   painter.setPen(pen);
        linearGradient.setColorAt(0.2, Qt::white);
        linearGradient.setColorAt(1.0, "#00aaee");
        painter.setBrush(linearGradient);

        myPolygon.clear();
        myPolygon << QPoint(xRight, yBottom) << QPoint(xLeft, yBottom);
        for( int i=0; i<width; ++i )
            myPolygon << QPoint(xLeft+i, yTop+hScaleLog*( _bins[wScale*i] ? log(_heightMax/float(_bins[wScale*i])) : _heightMax));
        painter.drawPolygon(myPolygon);

        // bins
        pen.setColor("#016790");
        painter.setPen(pen);
        linearGradient.setColorAt(0.2, Qt::white);
        linearGradient.setColorAt(1.0, "#016790");
        painter.setBrush(linearGradient);

        myPolygon.clear();
        myPolygon << QPoint(xRight, yBottom) << QPoint(xLeft, yBottom);
        for( int i=0; i<width; ++i )
            myPolygon << QPoint(xLeft+i, yTop+hScale*(_heightMax-_bins[wScale*i]));
        painter.drawPolygon(myPolygon);
    }

    // Label the x and y axis
    QPen penHText(QColor("#000000"));
    painter.setPen(penHText);
    painter.drawText(xLeft+2, yBottom-2, tr("0"));
    painter.drawText(xRight-x_max_label_width, yBottom-2, tr(x_max_label_char_array));
}

void Histogram::setMaxValue( float v )
{
    x_max = v;
    update();
}

void Histogram::setXUnits(QString v)
{
    x_units = v;
}
