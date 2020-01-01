#ifndef SYSINFOWINDOWIMPL_H
#define SYSINFOWINDOWIMPL_H

#include <QtGlobal>
#include <QVector>

#include "SysInfo.h"

typedef struct _FILETIME FILETIME;

class SysInfoWindowImpl : public SysInfo
{
public:
    SysInfoWindowImpl();


    // SysInfo interface
public:
    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<quint64> cpuRawData();
    quint64 convertFileTime(const FILETIME& filetime) const;

private:
    QVector<quint64> mCpuLoadLastValues;


};

#endif // SYSINFOWINDOWIMPL_H
