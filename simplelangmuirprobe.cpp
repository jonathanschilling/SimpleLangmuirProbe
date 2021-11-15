#include "simplelangmuirprobe.h"
#include "ui_simplelangmuirprobe.h"

SimpleLangmuirProbe::SimpleLangmuirProbe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimpleLangmuirProbe)
{
    ui->setupUi(this);
    setupConnections();

    initialized = false;
    setInitialValues();
}

SimpleLangmuirProbe::~SimpleLangmuirProbe()
{
    delete ui;
}


void SimpleLangmuirProbe::setupConnections() {
    connect(ui->teSlider,   SIGNAL(valueChanged(int)), this, SLOT(updateTeSliderPos(int)));
    connect(ui->tiSlider,   SIGNAL(valueChanged(int)), this, SLOT(updateTiSliderPos(int)));
    connect(ui->nSlider,    SIGNAL(valueChanged(int)), this, SLOT(updateNSliderPos(int)));
    connect(ui->phipSlider, SIGNAL(valueChanged(int)), this, SLOT(updatePhiPSliderPos(int)));

    connect(ui->minTeBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinTe(double)));
    connect(ui->maxTeBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxTe(double)));

    connect(ui->minTiBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinTi(double)));
    connect(ui->maxTiBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxTi(double)));

    connect(ui->minNBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinN(double)));
    connect(ui->maxNBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxN(double)));

    connect(ui->minPhiPBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinPhiP(double)));
    connect(ui->maxPhiPBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxPhiP(double)));

    connect(ui->numPointsBox, SIGNAL(valueChanged(int)), this, SLOT(updateNumPoints(int)));
    connect(ui->minUBox, SIGNAL(valueChanged(double)), this, SLOT(updateMinU(double)));
    connect(ui->maxUBox, SIGNAL(valueChanged(double)), this, SLOT(updateMaxU(double)));

    connect(ui->autoscaleBox, SIGNAL(stateChanged(int)), this, SLOT(updateAutoscale(int)));
}

void SimpleLangmuirProbe::setInitialValues() {
    updateNumPoints(ui->numPointsBox->value());
    updateMinU(ui->minUBox->value());
    updateMaxU(ui->maxUBox->value());

    updateMinTe(ui->minTeBox->value());
    updateMaxTe(ui->maxTeBox->value());

    updateMinTi(ui->minTiBox->value());
    updateMaxTi(ui->maxTiBox->value());

    updateMinN(ui->minNBox->value());
    updateMaxN(ui->maxNBox->value());

    updateMinPhiP(ui->minPhiPBox->value());
    updateMaxPhiP(ui->maxPhiPBox->value());

    updateTeSliderPos(ui->teSlider->value());
    updateTiSliderPos(ui->tiSlider->value());
    updateNSliderPos(ui->nSlider->value());
    updatePhiPSliderPos(ui->phipSlider->value());

    updateAutoscale(ui->autoscaleBox->isChecked() ? 1 : 0);

    initialized = true;
    updatePlot();
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

    if (initialized) {
        updatePlot();
    }
}

void SimpleLangmuirProbe::updateTi() {
    int sliderMin = this->ui->tiSlider->minimum();
    int sliderMax = this->ui->tiSlider->maximum();
    int sliderSpan = sliderMax - sliderMin;

    double relSliderPos = (this->tiSliderPos - sliderMin) / ((double)sliderSpan);
    std::cout << "rel. slider pos of Ti: " << relSliderPos << std::endl;

    double tiSpan = this->maxTi - this->minTi;
    this->ti = this->minTi + relSliderPos*tiSpan;

    std::stringstream strstr;
    strstr << "Ti = ";
    strstr << this->ti;
    strstr << " eV";
    QString tiLabelStr = QString(strstr.str().c_str());

    this->ui->tiLabel->setText(tiLabelStr);

    if (initialized) {
        updatePlot();
    }
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

    if (initialized) {
        updatePlot();
    }
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

    if (initialized) {
        updatePlot();
    }
}

void SimpleLangmuirProbe::updateEvalRange() {

    if (U.size() != numPoints) {
        U.resize(numPoints);
        I.resize(numPoints);
    }

    double uSpan = maxU - minU;
    for (int i=0; i<numPoints; ++i) {
        U[i] = minU + i*uSpan/((double)numPoints);
    }

    if (initialized) {
        updatePlot();
    }
}

void SimpleLangmuirProbe::updatePlot() {

    std::cout << "Te="<< this->te << "Ti=" << this->ti << " n=" << this->n << " phiP=" << this->phiP << std::endl;
    std::cout << "   from " << this->minU << " to " << this->maxU << " at " << this->numPoints << " points" << std::endl;

    for (int i=0; i<numPoints; ++i) {
        I[i] = eval(U[i]);
    }

    bool newGraph = false;
    if (ui->qcp->graphCount() == 0) {
        // create graph
        ui->qcp->addGraph();

        newGraph = true;
    }

    // assign data to graph
    ui->qcp->graph(0)->setData(U, I);

    if (newGraph) {
        // give the axes some labels:
        ui->qcp->xAxis->setLabel("U / V");
        ui->qcp->yAxis->setLabel("I / A");

        // enable zooming
        ui->qcp->setInteractions(QCP::iRangeZoom);
        ui->qcp->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
    }

    if (autoscale) {

        // 5% overrange on each side of the grid
        double uSpan = U.last() - U.first();
        double iSpan = I.last() - I.first();

        double minU = U.first() - 0.05*uSpan;
        double maxU = U.last()  + 0.05*uSpan;

        double minI = I.first() - 0.05*iSpan;
        double maxI = I.last()  + 0.05*iSpan;

        // set axes ranges, so we see all data:
        ui->qcp->xAxis->setRange(minU, maxU);
        ui->qcp->yAxis->setRange(minI, maxI);
    }

    ui->qcp->replot();
}

double SimpleLangmuirProbe::eval(double biasVoltage) {

    double e = 1.602e-19;
    double m_e = 9.109e-31;

    double probeSurfaceArea = 7.4e-6; // m^2
    double zEff = 2.0;

    double ionMass = 3.344e-27; // D2

    double nUnit = 1.0e19;

    double teToUse = te;
    double tiToUse = ti;
    double nToUse = n * nUnit;

    /**
     * adiabatic coefficient of the ions and electrons
     * 1   == isothermal
     * 5/3 == adiabatic (?)
     */
    double gammaI = 1.0; // for now ...
    double gammaE = 1.0; // for now ...

    /** ion sound speed in m/s */
    double c_s_i = sqrt(e*(zEff*teToUse + gammaI*tiToUse)/ionMass);

    /** ion saturation current density in A/m^2  */
    double j_i_0 = -0.61 * e * nToUse * c_s_i;

    /** electron sound speed in m/s */
    double c_s_e = sqrt(e*(gammaE*teToUse + tiToUse)/(2.0*M_PI*m_e));

    /** electron saturation current density in A/m^2 */
    double j_e_0 = e * nToUse * c_s_e;

    /** electron retardation current density in A/m^2  */
    double j_e = j_e_0 * exp((biasVoltage-phiP)/teToUse);

    /** probe current */
    double I = (j_i_0 + j_e)*probeSurfaceArea;

    return I;
}
