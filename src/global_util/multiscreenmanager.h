#ifndef MULTISCREENMANAGER_H
#define MULTISCREENMANAGER_H

#include <QObject>
#include <QWidget>
#include <QScreen>
#include <QMap>
#include <functional>
#include <QTimer>
#include <com_deepin_system_systemdisplay.h>

using SystemDisplayInter = com::deepin::system::Display;

const static int COPY_MODE = 1;
const static int EXTENDED_MODE = 2;

class MultiScreenManager : public QObject
{
    Q_OBJECT
public:
    explicit MultiScreenManager(QObject *parent = nullptr);

    void register_for_mutil_screen(std::function<QWidget* (QScreen *, int)> function);
    void startRaiseContentFrame();

private:
    void onScreenAdded(QScreen *screen);
    void onScreenRemoved(QScreen *screen);
    void raiseContentFrame();
    int getDisplayModeByConfig(const QString &config) const;

private slots:
    void onDisplayModeChanged(const QString &);

private:
    std::function<QWidget* (QScreen *, int)> m_registerFunction;
    QMap<QScreen*, QWidget*> m_frames;
    QTimer *m_raiseContentFrameTimer;
    SystemDisplayInter *m_systemDisplay;
    bool m_isCopyMode;
};

#endif // MULTISCREENMANAGER_H
