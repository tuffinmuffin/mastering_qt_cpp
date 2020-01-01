#include "SysInfoWindowImpl.h"

#include <Windows.h>
#include <QDebug>

SysInfoWindowImpl::SysInfoWindowImpl():
    SysInfo(),
    mCpuLoadLastValues()
{

}

void SysInfoWindowImpl::init()
{
    mCpuLoadLastValues = cpuRawData();
}

double SysInfoWindowImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);
    quint64 memoryPhysicalUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
    return static_cast<double>(memoryPhysicalUsed) / static_cast<double>(memoryStatus.ullTotalPhys) * 100.0;
}

QVector<quint64> SysInfoWindowImpl::cpuRawData()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    QVector<quint64> rawData;
    rawData.append(convertFileTime(idleTime));
    rawData.append(convertFileTime(kernelTime));
    rawData.append(convertFileTime(userTime));
    return rawData;
}

quint64 SysInfoWindowImpl::convertFileTime(const FILETIME &filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;
    return largeInteger.QuadPart;
}

double SysInfoWindowImpl::cpuLoadAverage()
{
    auto firstSample = mCpuLoadLastValues;
    auto secondSample = cpuRawData();
    mCpuLoadLastValues = secondSample;

    auto currentIdle   = secondSample[0] - firstSample[0];
    auto currentKernel = secondSample[1] - firstSample[1];
    auto currentUser   = secondSample[2] - firstSample[2];
    auto currentSystem = currentKernel + currentUser;

    double percent = (currentSystem - currentIdle) * 100.0 / currentSystem;
    return qBound(0.0, percent, 100.0);
}
