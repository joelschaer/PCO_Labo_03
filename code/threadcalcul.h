#ifndef THREADCALCUL_H
#define THREADCALCUL_H
#include <QThread>
#include<QImage>
#include <iostream>
class ThreadCalcul : public QThread
{
private:
    int yStart;
    int yFinal;
    int halfWidth;
    int halfHeight;
    QSize resultSize;       // pas utilisée
    double scaleFactor;
    double centerX;
    double centerY;
    QImage* image;
    bool* restart;
    bool* abort;
    int Limit;
    int MaxIterations;

    uint* colormap;
    int ColormapSize;

public:
    ThreadCalcul(int yStart, int yFinal, int halfWidth, int halfHeight, QSize resultSize, double scaleFactor, double centerX, double centerY, QImage* image, bool* restart, bool* abort, int Limit, int MaxIterations, uint colormap[], int ColormapSize):
        yStart(yStart), yFinal(yFinal), halfWidth(halfWidth),halfHeight(halfHeight), resultSize(resultSize), scaleFactor(scaleFactor), centerX(centerX), centerY(centerY), image(image), restart(restart), abort(abort), Limit(Limit), MaxIterations(MaxIterations), colormap(colormap), ColormapSize(ColormapSize){}

    void run();
};

#endif // THREADCALCUL_H
