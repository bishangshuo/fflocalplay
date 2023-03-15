#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QCloseEvent>

class QLabel;
class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();
protected:
    void closeEvent(QCloseEvent *event);
public slots:
    void startPlay();
    void stopPlay();
    void onFFLPCreated(void *fflp);
signals:
    void sigFFLPCreated(void *fflp);
private:
    static void FFLPCallbackFunc(int res, void *fflp, void *receiver);
    void ProcCallback(int res, void *fflp);
    void doStart();
    void doStop();
private:
    QLabel *m_pLabel;

    void *m_pPlayerHandle{NULL};
};

#endif // PLAYERWIDGET_H
