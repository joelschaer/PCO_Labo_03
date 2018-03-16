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
    QSize resultSize;
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
        yStart(yStart), yFinal(yFinal), halfWidth(halfWidth),halfHeight(halfHeight), resultSize(resultSize), scaleFactor(scaleFactor), centerX(centerX), centerY(centerY), image(image), restart(restart), abort(abort), Limit(Limit), MaxIterations(MaxIterations), colormap(colormap), ColormapSize(ColormapSize){

      // colormap = (uint*) malloc(ColormapSize);

    }

    void run() {
        //-HALFHEIGHT => HALFhEIG/NBTHREAD
        for (int y = yStart; y < yFinal; ++y) {
            if (*restart)
                break;
            if (*abort)
                return;

            QRgb *scanLine = reinterpret_cast<QRgb *>(image->scanLine(y + halfHeight));
            double ay = centerY + (y * scaleFactor);

            for (int x = -halfWidth; x < halfWidth; ++x) {
                double ax = centerX + (x * scaleFactor);
                double a1 = ax;
                double b1 = ay;
                int numIterations = 0;

                do {
                    ++numIterations;
                    double a2 = (a1 * a1) - (b1 * b1) + ax;
                    double b2 = (2 * a1 * b1) + ay;
                    if ((a2 * a2) + (b2 * b2) > Limit)
                        break;

                    ++numIterations;
                    a1 = (a2 * a2) - (b2 * b2) + ax;
                    b1 = (2 * a2 * b2) + ay;
                    if ((a1 * a1) + (b1 * b1) > Limit)
                        break;
                } while (numIterations < MaxIterations);

                if (numIterations < MaxIterations) {
                    *scanLine++ = colormap[numIterations % ColormapSize];
                } else {
                    *scanLine++ = qRgb(0, 0, 0);
                }
            }
        }
    }
};

#endif // THREADCALCUL_H
