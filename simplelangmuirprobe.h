#ifndef SIMPLELANGMUIRPROBE_H
#define SIMPLELANGMUIRPROBE_H

#include <QMainWindow>

#include <iostream>
#include <string>
#include <sstream>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SimpleLangmuirProbe; }
QT_END_NAMESPACE

class SimpleLangmuirProbe : public QMainWindow
{
    Q_OBJECT

public slots:
    void updateTeSliderPos(int newTeSliderPos)     { this->teSliderPos   = newTeSliderPos;   updateTe(); }
    void updateTiSliderPos(int newTiSliderPos)     { this->tiSliderPos   = newTiSliderPos;   updateTi(); }
    void updateNSliderPos(int newNSliderPos)       { this->nSliderPos    = newNSliderPos;    updateN(); }
    void updatePhiPSliderPos(int newPhipSliderPos) { this->phipSliderPos = newPhipSliderPos; updatePhiP(); }

    void updateMinTe(double newMinTe) { this->minTe = newMinTe; updateTe(); }
    void updateMaxTe(double newMaxTe) { this->maxTe = newMaxTe; updateTe(); }

    void updateMinTi(double newMinTi) { this->minTi = newMinTi; updateTi(); }
    void updateMaxTi(double newMaxTi) { this->maxTi = newMaxTi; updateTi(); }

    void updateMinN(double newMinN) { this->minN = newMinN; updateN(); }
    void updateMaxN(double newMaxN) { this->maxN = newMaxN; updateN(); }

    void updateMinPhiP(double newMinPhiP) { this->minPhiP = newMinPhiP; updatePhiP(); }
    void updateMaxPhiP(double newMaxPhiP) { this->maxPhiP = newMaxPhiP; updatePhiP(); }

    void updateNumPoints(int newNumPoints) { this->numPoints = newNumPoints; updateEvalRange(); }
    void updateMinU(double newMinU)        { this->minU = newMinU; updateEvalRange(); }
    void updateMaxU(double newMaxU)        { this->maxU = newMaxU; updateEvalRange(); }

    void updateAutoscale(int newState) {
        this->autoscale = (newState != 0);

        if(initialized) {
            updatePlot();
        }
    }

public:
    SimpleLangmuirProbe(QWidget *parent = nullptr);
    ~SimpleLangmuirProbe();

private:
    Ui::SimpleLangmuirProbe *ui;

    void setupConnections();
    void updatePlot();
    void setInitialValues();

    void updateTe();
    void updateTi();
    void updateN();
    void updatePhiP();

    void updateEvalRange();

    double eval(double biasVoltage);

    bool initialized;
    bool autoscale;

    int teSliderPos, tiSliderPos, nSliderPos, phipSliderPos;
    double minTe, maxTe;
    double minTi, maxTi;
    double minN, maxN;
    double minPhiP, maxPhiP;

    double te, ti, n, phiP;

    int numPoints;
    double minU, maxU;

    QVector<double> U;
    QVector<double> I;

};
#endif // SIMPLELANGMUIRPROBE_H

