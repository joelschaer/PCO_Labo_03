/***************************************************
 *
 * threadcalcul.h
 *
 * autheurs: Yann Lederrey, Joel Schär
 *
 * Classe threadée avec pour but de diviser la charge
 * de travail du calcul de la courbe de mandelbrot en
 * plusieurs thread séparés.
 * Celle-ci reprend tous les paramètres nécessaires
 * pour faire ces calculs pour la partie de l'image
 * qui lui est attrbuée.
 *
 * Le code pour faire ces calculs est tiré de la
 * version de démonstration de QT et à ensuite été
 * adaptée avec pour but d'optmiser les calculs en
 * faisant une séparation de l'image en plusieurs
 * parties qui sont calculées par plusieurs threads
 * différents.
 *
 ***************************************************/

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
    ThreadCalcul(int yStart, int yFinal, int halfWidth, int halfHeight, double scaleFactor, double centerX, double centerY,
                 QImage* image, bool* restart, bool* abort, int Limit, int MaxIterations, uint colormap[], int ColormapSize):
        yStart(yStart), yFinal(yFinal), halfWidth(halfWidth),halfHeight(halfHeight), scaleFactor(scaleFactor), centerX(centerX), centerY(centerY),
        image(image), restart(restart), abort(abort), Limit(Limit), MaxIterations(MaxIterations), colormap(colormap), ColormapSize(ColormapSize){}

    void run();
};

#endif // THREADCALCUL_H
