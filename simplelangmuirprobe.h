#ifndef SIMPLELANGMUIRPROBE_H
#define SIMPLELANGMUIRPROBE_H

#include <QMainWindow>

#include <iostream>
#include <string>
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui { class SimpleLangmuirProbe; }
QT_END_NAMESPACE

class SimpleLangmuirProbe : public QMainWindow
{
    Q_OBJECT

public slots:
    void updateTe(int newTeSliderPos)     { this->teSliderPos   = newTeSliderPos;   updateTe(); }
    void updateN(int newNSliderPos)       { this->nSliderPos    = newNSliderPos;    updateN(); }
    void updatePhiP(int newPhipSliderPos) { this->phipSliderPos = newPhipSliderPos; updatePhiP(); }

    void updateMinTe(double newMinTe) { this->minTe = newMinTe; updateTe(); }
    void updateMaxTe(double newMaxTe) { this->maxTe = newMaxTe; updateTe(); }

    void updateMinN(double newMinN) { this->minN = newMinN; updateN(); }
    void updateMaxN(double newMaxN) { this->maxN = newMaxN; updateN(); }

    void updateMinPhiP(double newMinPhiP) { this->minPhiP = newMinPhiP; updatePhiP(); }
    void updateMaxPhiP(double newMaxPhiP) { this->maxPhiP = newMaxPhiP; updatePhiP(); }

public:
    SimpleLangmuirProbe(QWidget *parent = nullptr);
    ~SimpleLangmuirProbe();

private:
    Ui::SimpleLangmuirProbe *ui;

    void setupConnections();
    void updatePlot();

    void updateTe();
    void updateN();
    void updatePhiP();

    int teSliderPos, nSliderPos, phipSliderPos;
    double minTe, maxTe;
    double minN, maxN;
    double minPhiP, maxPhiP;

    double te, n, phiP;

};
#endif // SIMPLELANGMUIRPROBE_H
