#include "SysInfo.h"

#include <QtGlobal>

#if defined(Q_OS_WIN)
#include "SysInfoWindowImpl.h"
#elif defined(Q_OS_LINUX)
#include "SysInfoLinuxImpl.h"
#else
#error "Unknown OS"
#endif

SysInfo::SysInfo()
{

}

SysInfo::~SysInfo()
{

}


SysInfo& SysInfo::instance()
{
#if defined(Q_OS_WIN)
    static SysInfoWindowImpl singleton;
#elif defined(Q_OS_LINUX)
    static SysInfoLinuxImpl singleton;
#endif
    return singleton;
}
