#include "playerwidget.h"
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

extern "C"
{
#include "fflocalplayersdk.h"
}

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    QPushButton *btnPlay = new QPushButton(this);
    btnPlay->setText("Play");
    btnPlay->setGeometry(30, 30, 100, 40);
    connect(btnPlay, &QPushButton::clicked, this, &PlayerWidget::startPlay);

    QPushButton *btnStop = new QPushButton(this);
    btnStop->setText("Stop");
    btnStop->setGeometry(150, 30, 100, 40);
    connect(btnStop, &QPushButton::clicked, this, &PlayerWidget::stopPlay);

    int vWidth = 640;
    int vHeight = 640;
    m_pLabel = new QLabel(this);
    int hei = this->size().height()-90;
    int wid = vWidth*hei/vHeight;
    int left = (this->size().width() - wid )/2;
    m_pLabel->setGeometry(30, 80, wid, hei);
    m_pLabel->setStyleSheet("QLabel{background-color:rgb(0, 0, 0);}");

    connect(this, SIGNAL(sigFFLPCreated(void*)), this, SLOT(onFFLPCreated(void*)));
}

PlayerWidget::~PlayerWidget()
{

}

void PlayerWidget::closeEvent(QCloseEvent *event)
{
    stopPlay();
}

void PlayerWidget::startPlay()
{
    doStart();
}

void PlayerWidget::stopPlay()
{
    doStop();
}

void PlayerWidget::FFLPCallbackFunc(int res, void *fflp, void *receiver)
{
    qDebug() << "FFLPCallbackFunc called" << res;
    PlayerWidget *pThis = reinterpret_cast<PlayerWidget *>(receiver);
    pThis->ProcCallback(res, fflp);
}

void PlayerWidget::ProcCallback(int res, void *fflp)
{
    if(res == 1) {
        emit sigFFLPCreated(fflp);
    } else {
        qDebug() << "FFLPCallbackFunc result error ";;
    }
}

void PlayerWidget::onFFLPCreated(void *fflp)
{
    m_pPlayerHandle = fflp;
    int vWidth = 0;
    int vHeight = 0;
    fflp_resolution(m_pPlayerHandle, &vWidth, &vHeight);
    int hei = this->size().height()-90;
    int wid = vWidth*hei/vHeight;
    int left = (this->size().width() - wid )/2;
    m_pLabel->setGeometry(30, 80, wid, hei);

    fflp_start(m_pPlayerHandle);
}


void PlayerWidget::doStart()
{
    m_pPlayerHandle = fflp_create((char *)"rtmp://192.168.0.104:1935/live/100210", (HWND)m_pLabel->winId(), PlayerWidget::FFLPCallbackFunc, (void *)this);
    qDebug() << "create fflp, handle=" << (int) m_pPlayerHandle;
}

void PlayerWidget::doStop()
{
    if(m_pPlayerHandle != NULL) {
        fflp_stop(m_pPlayerHandle);
        m_pPlayerHandle = NULL;
    }
}


