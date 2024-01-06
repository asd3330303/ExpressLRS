#include "targets.h"
#include "devCRSF.h"

#ifdef CRSF_TX_MODULE

#include "../POWERMGNT/POWERMGNT.h"

static int start()
{
    CRSF::Begin();
#if defined(DEBUG_TX_FREERUN)
    CRSF::CRSFstate = true;
    if (CRSF::connected)
    {
        CRSF::connected();
    }
    else
    {
        ERRLN("CRSF::connected has not been initialised");
    }
#endif
    return DURATION_IMMEDIATELY;
}

static int timeout()
{
    CRSF::handleUARTin();
    return DURATION_IMMEDIATELY;
}

static int event()
{
    // An event should be generated every time the TX power changes
    //每次TX功率变化时都应该生成一个事件
    CRSF::LinkStatistics.uplink_TX_Power = powerToCrsfPower(PowerLevelContainer::currPower());
    return DURATION_IGNORE;
}

device_t CRSF_device = {
    .initialize = nullptr,
    .start = start,
    .event = event,
    .timeout = timeout
};
#endif
