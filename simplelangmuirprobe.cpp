#include "simplelangmuirprobe.h"
#include "ui_simplelangmuirprobe.h"

SimpleLangmuirProbe::SimpleLangmuirProbe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimpleLangmuirProbe)
{
    ui->setupUi(this);
    setupConnections();
}

SimpleLangmuirProbe::~SimpleLangmuirProbe()
{
    delete ui;
}


void SimpleLangmuirProbe::setupConnections() {
    connect(ui->teSlider,   SIGNAL(valueChanged(int)), this, SLOT(updateTe(int)));
    connect(ui->nSlider,    SIGNAL(valueChanged(int)), this, SLOT(updateN(int)));
    connect(ui->phipSlider, SIGNAL(valueChanged(int)), this, SLOT(updatePhiP(int)));

    connect(ui->minTeBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinTe(double)));
    connect(ui->maxTeBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxTe(double)));

    connect(ui->minNBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinN(double)));
    connect(ui->maxNBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxN(double)));

    connect(ui->minPhiPBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinPhiP(double)));
    connect(ui->maxPhiPBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxPhiP(double)));
}

void SimpleLangmuirProbe::updateTe() {
    int sliderMin = this->ui->teSlider->minimum();
    int sliderMax = this->ui->teSlider->maximum();
    int sliderSpan = sliderMax - sliderMin;

    double relSliderPos = (this->teSliderPos - sliderMin) / ((double)sliderSpan);
    std::cout << "rel. slider pos of Te: " << relSliderPos << std::endl;

    double teSpan = this->maxTe - this->minTe;
    this->te = this->minTe + relSliderPos*teSpan;

    std::stringstream strstr;
    strstr << "Te = ";
    strstr << this->te;
    strstr << " eV";
    QString teLabelStr = QString(strstr.str().c_str());

    this->ui->teLabel->setText(teLabelStr);
}

void SimpleLangmuirProbe::updateN() {
    int sliderMin = this->ui->nSlider->minimum();
    int sliderMax = this->ui->nSlider->maximum();
    int sliderSpan = sliderMax - sliderMin;

    double relSliderPos = (this->nSliderPos - sliderMin) / ((double)sliderSpan);
    std::cout << "rel. slider pos of n: " << relSliderPos << std::endl;

    double nSpan = this->maxN - this->minN;
    this->n = this->minN + relSliderPos*nSpan;

    std::stringstream strstr;
    strstr << "n = ";
    strstr << this->n;
    strstr << " * 1e19 m^-3";
    QString nLabelStr = QString(strstr.str().c_str());

    this->ui->nLabel->setText(nLabelStr);
}

void SimpleLangmuirProbe::updatePhiP() {
    int sliderMin = this->ui->phipSlider->minimum();
    int sliderMax = this->ui->phipSlider->maximum();
    int sliderSpan = sliderMax - sliderMin;

    double relSliderPos = (this->phipSliderPos - sliderMin) / ((double)sliderSpan);
    std::cout << "rel. slider pos of phip: " << relSliderPos << std::endl;

    double phipSpan = this->maxPhiP - this->minPhiP;
    this->phiP = this->minPhiP + relSliderPos*phipSpan;

    std::stringstream strstr;
    strstr << "PhiP = ";
    strstr << this->phiP;
    strstr << " V";
    QString phipLabelStr = QString(strstr.str().c_str());

    this->ui->phipLabel->setText(phipLabelStr);
}

void SimpleLangmuirProbe::updatePlot() {

    std::cout << "Te="<< this->te << " n=" << this->n << " phiP=" << this->phiP << std::endl;


}
