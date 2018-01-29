//
//
// CC_TelecommandFactory.c
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_DummyPUSTelecommand.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "../Telecommand/DC_PUSControlDataReporting.h"
#include "../Telecommand/DC_PUSDefineDataReporting.h"
#include "../Telecommand/DC_PUSDumpMemoryAbsolute.h"
#include "../Telecommand/DC_PUSDumpMemoryOffset.h"
#include "../Telecommand/DC_PUSMemoryLoadAbsolute.h"
#include "../Telecommand/DC_PUSMemoryLoadOffset.h"
#include "../Telecommand/DC_TestPUSTelecommand.h"
#include "../Base/CC_RootObject.h"
#include "CC_TelecommandFactory.h"
#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static CC_TelecommandFactory *pInstance;     



///////////////////////////////////////////////////////////////////////////////
//
//                            class  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

CC_TelecommandFactory* CC_TelecommandFactory_getInstance(void)
{
    if (pInstance == pNULL) {
        pInstance = CC_TelecommandFactory_new();
    }

    return pInstance;
}



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_TelecommandFactory_setTelecommand(CC_TelecommandFactory *This, 
                                          unsigned int i,
                                          Telecommand *pItem)
{
    assert(pItem != pNULL); 

    const char *typeName = object_get_typename((Object*)pItem);

    if (strcmp(typeName, TYPE_DC_DUMMYPUSTELECOMMAND) == 0) {

        setDummyPUSTelecommand(This, i, (DC_DummyPUSTelecommand*)pItem);
    } else if (strcmp(typeName, TYPE_DC_DUMMYTELECOMMAND) == 0) {

        setDummyTelecommand(This, i, (DC_DummyTelecommand*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSDUMPMEMORYABSOLUTE) == 0) {

        setPUSDumpMemoryAbsolute(This, i, (DC_PUSDumpMemoryAbsolute*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSDUMPMEMORYOFFSET) == 0) {

        setPUSDumpMemoryOffset(This, i, (DC_PUSDumpMemoryOffset*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSMEMORYLOADABSOLUTE) == 0) {

        setPUSMemoryLoadAbsolute(This, i, (DC_PUSMemoryLoadAbsolute*)pItem); 
    } else if (strcmp(typeName, TYPE_DC_PUSMEMORYLOADOFFSET) == 0) {

        setPUSMemoryLoadOffset(This, i, (DC_PUSMemoryLoadOffset*)pItem);
    } else if (strcmp(typeName, TYPE_DC_TESTPUSTELECOMMAND) == 0) {

        setTestPUSTelecommand(This, i, (DC_TestPUSTelecommand*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSCONTROLDATAREPORTING) == 0) {

        setPUSControlDataReporting(This, i, (DC_PUSControlDataReporting*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSDEFINEDATAREPORTING) == 0) {

        setPUSDefineDataReporting(This, i, (DC_PUSDefineDataReporting*)pItem);
    } else {
        // Unknown Telecommand type
        assert(false); 
    }
}


static void setDummyPUSTelecommand(CC_TelecommandFactory *This, 
                                   unsigned int i,
                                   DC_DummyPUSTelecommand *pItem)
{
    assert(i < This->sizeDummyPUSTelecommand);
    assert(pItem != pNULL);
    This->poolDummyPUSTelecommand[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolDummyPUSTelecommand[i], false);
}

unsigned int CC_TelecommandFactory_getNumberDummyPUSTelecommand
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_DummyPUSTelecommand** const pool = This->poolDummyPUSTelecommand;
    for (unsigned int i=0; i<This->sizeDummyPUSTelecommand; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityDummyPUSTelecommand
(
    CC_TelecommandFactory *This
)
{
    return This->sizeDummyPUSTelecommand;
}

DC_DummyPUSTelecommand* CC_TelecommandFactory_allocateDummyPUSTelecommand
(
    CC_TelecommandFactory *This
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_DummyPUSTelecommand** const pool = This->poolDummyPUSTelecommand;
    for (unsigned int i=0; i<This->sizeDummyPUSTelecommand; i++) {
        if (!Telecommand_isInUse((Telecommand*)pool[i])) {
           Telecommand_setInUse((Telecommand*)pool[i], true);
           return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelecommandFactory_isFreeDummyPUSTelecommand(CC_TelecommandFactory *This)
{
    DC_DummyPUSTelecommand ** const pool = This->poolDummyPUSTelecommand;
    for (unsigned int i=0; i<This->sizeDummyPUSTelecommand; i++) {
        if (!Telecommand_isInUse((Telecommand*)pool[i])) {
           return true;
        }
    }

    return false;
}

static void setDummyTelecommand(CC_TelecommandFactory *This, 
                                unsigned int i,
                                DC_DummyTelecommand *pItem)
{
    assert(i < This->sizeDummyTelecommand);
    assert(pItem != pNULL);
    This->poolDummyTelecommand[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolDummyTelecommand[i], false);
}

unsigned int CC_TelecommandFactory_getNumberDummyTelecommand
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_DummyTelecommand** const pool = This->poolDummyTelecommand;
    for (unsigned int i=0; i<This->sizeDummyTelecommand; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityDummyTelecommand
(
    CC_TelecommandFactory *This
)
{
    return This->sizeDummyTelecommand;
}

DC_DummyTelecommand* CC_TelecommandFactory_allocateDummyTelecommand
(
    CC_TelecommandFactory *This
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_DummyTelecommand** const pool = This->poolDummyTelecommand;
    for (unsigned int i=0; i<This->sizeDummyTelecommand; i++) {
        if (!Telecommand_isInUse((Telecommand*)pool[i])) {
           Telecommand_setInUse((Telecommand*)pool[i], true);
           return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelecommandFactory_isFreeDummyTelecommand(CC_TelecommandFactory *This)
{
    DC_DummyTelecommand** const pool = This->poolDummyTelecommand;
    for (unsigned int i=0; i<This->sizeDummyTelecommand; i++) {
        if (!Telecommand_isInUse((Telecommand*)pool[i])) {
           return true;
        }
    }

    return false;
}

static void setPUSControlDataReporting(CC_TelecommandFactory *This, 
                                       unsigned int i,
                                       DC_PUSControlDataReporting *pItem)
{
    assert(i < This->sizePUSControlDataReporting);
    assert(pItem != pNULL);
    This->poolPUSControlDataReporting[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolPUSControlDataReporting[i], false);
}

unsigned int CC_TelecommandFactory_getNumberPUSControlDataReporting
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSControlDataReporting** const pool = This->poolPUSControlDataReporting;
    for (unsigned int i=0; i<This->sizePUSControlDataReporting; i++) {
       if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
       }
    }

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityPUSControlDataReporting
(
    CC_TelecommandFactory *This
)
{
    return This->sizePUSControlDataReporting;
}

DC_PUSControlDataReporting* CC_TelecommandFactory_allocatePUSControlDataReporting
(
    CC_TelecommandFactory *This, 
    unsigned int MaxNumberSID
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_PUSControlDataReporting** const pool = This->poolPUSControlDataReporting;
    for (unsigned int i=0; i<This->sizePUSControlDataReporting; i++) {
        unsigned int maxNumSid; 
        
        maxNumSid = DC_PUSControlDataReporting_getMaxNumberSID(pool[i]);
        if ((maxNumSid >= MaxNumberSID) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
            Telecommand_setInUse((Telecommand*)pool[i], true);
            return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelecommandFactory_isFreePUSControlDataReporting
(
    CC_TelecommandFactory *This, 
    unsigned int MaxNumberSID
)
{
    DC_PUSControlDataReporting** const pool = This->poolPUSControlDataReporting;
    for (unsigned int i=0; i<This->sizePUSControlDataReporting; i++) {
        unsigned int maxNumSid; 
        
        maxNumSid = DC_PUSControlDataReporting_getMaxNumberSID(pool[i]);
        if ((maxNumSid >= MaxNumberSID) &&
            (!Telecommand_isInUse((Telecommand*)pool[i])))
        {
           return true;
        }
    }

    return false;
}

static void setPUSDefineDataReporting(CC_TelecommandFactory *This, 
                                      unsigned int i,
                                      DC_PUSDefineDataReporting *pItem)
{
    assert(i < This->sizePUSDefineDataReporting);
    assert(pItem != pNULL);
    This->poolPUSDefineDataReporting[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolPUSDefineDataReporting[i], false);
}

unsigned int CC_TelecommandFactory_getNumberPUSDefineDataReporting
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSDefineDataReporting** const pool = This->poolPUSDefineDataReporting;
    for (unsigned int i=0; i<This->sizePUSDefineDataReporting; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityPUSDefineDataReporting
(
    CC_TelecommandFactory *This
)
{
    return This->sizePUSDefineDataReporting;
}

DC_PUSDefineDataReporting* CC_TelecommandFactory_allocatePUSDefineDataReporting
(
    CC_TelecommandFactory *This, 
    unsigned int NumberOfRawData
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_PUSDefineDataReporting** const pool = This->poolPUSDefineDataReporting;
    for (unsigned int i=0; i<This->sizePUSDefineDataReporting; i++) {
        TelecommandClass *tc;
        unsigned int nRawData;

        tc = TELECOMMAND_CLASS(pool[i]);
        nRawData = tc->getNumberOfRawData(pool[i]);
        if ((nRawData >= NumberOfRawData) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
           Telecommand_setInUse((Telecommand*)pool[i], true);
           return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelecommandFactory_isFreePUSDefineDataReporting
(
   CC_TelecommandFactory *This, 
   unsigned int NumberOfRawData
)
{
    DC_PUSDefineDataReporting** const pool = This->poolPUSDefineDataReporting;
    for (unsigned int i=0; i<This->sizePUSDefineDataReporting; i++) {
        TelecommandClass *tc;
        unsigned int nRawData;

        tc = TELECOMMAND_CLASS(pool[i]);
        nRawData = tc->getNumberOfRawData(pool[i]);
        if ((nRawData >= NumberOfRawData) &&
            (!Telecommand_isInUse((Telecommand*)pool[i])))
        {
           return true;
        }
    }

    return false;
}

static void setPUSDumpMemoryAbsolute(CC_TelecommandFactory *This, 
                                     unsigned int i, 
                                     DC_PUSDumpMemoryAbsolute *pItem)
{
    assert(i < This->sizePUSDumpMemoryAbsolute);
    assert(pItem != pNULL);
    This->poolPUSDumpMemoryAbsolute[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolPUSDumpMemoryAbsolute[i], false);
}

unsigned int CC_TelecommandFactory_getNumberPUSDumpMemoryAbsolute
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSDumpMemoryAbsolute** const pool = This->poolPUSDumpMemoryAbsolute;
    for (unsigned int i=0; i<This->sizePUSDumpMemoryAbsolute; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) { 
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityPUSDumpMemoryAbsolute
(
    CC_TelecommandFactory *This
)
{
    return This->sizePUSDumpMemoryAbsolute;
}

DC_PUSDumpMemoryAbsolute* CC_TelecommandFactory_allocatePUSDumpMemoryAbsolute
(
    CC_TelecommandFactory *This, 
    unsigned int NumberOfRawData
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_PUSDumpMemoryAbsolute** const pool = This->poolPUSDumpMemoryAbsolute;
    for (unsigned int i=0; i<This->sizePUSDumpMemoryAbsolute; i++) {
        TelecommandClass *tc;
        unsigned int nRawData;

        tc = TELECOMMAND_CLASS(pool[i]);
        nRawData = tc->getNumberOfRawData(pool[i]);

        if ((nRawData >= NumberOfRawData) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
            Telecommand_setInUse((Telecommand*)pool[i], true);
            return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelecommandFactory_isFreePUSDumpMemoryAbsolute
(
    CC_TelecommandFactory *This, 
    unsigned int NumberOfRawData
)
{
    DC_PUSDumpMemoryAbsolute** const pool = This->poolPUSDumpMemoryAbsolute;
    for (unsigned int i=0; i<This->sizePUSDumpMemoryAbsolute; i++) {
        TelecommandClass *tc;
        unsigned int nRawData;

        tc = TELECOMMAND_CLASS(pool[i]);
        nRawData = tc->getNumberOfRawData(pool[i]);
        if ((nRawData >= NumberOfRawData) &&
             !Telecommand_isInUse((Telecommand*)pool[i])) 
        {
           return true;
        }
    }

    return false;
}

static void setPUSDumpMemoryOffset(CC_TelecommandFactory *This, 
                                   unsigned int i, 
                                   DC_PUSDumpMemoryOffset *pItem)
{
    assert(i < This->sizePUSDumpMemoryOffset);
    assert(pItem != pNULL);
    This->poolPUSDumpMemoryOffset[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolPUSDumpMemoryOffset[i], false);
}

unsigned int CC_TelecommandFactory_getNumberPUSDumpMemoryOffset
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSDumpMemoryOffset** const pool = This->poolPUSDumpMemoryOffset;
    for (unsigned int i=0; i<This->sizePUSDumpMemoryOffset; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityPUSDumpMemoryOffset
(
    CC_TelecommandFactory *This
)
{
    return This->sizePUSDumpMemoryOffset;
}

DC_PUSDumpMemoryOffset* CC_TelecommandFactory_allocatePUSDumpMemoryOffset
(
    CC_TelecommandFactory *This, 
    unsigned int NumberOfRawData
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_PUSDumpMemoryOffset** const pool = This->poolPUSDumpMemoryOffset;
    for (unsigned int i=0; i<This->sizePUSDumpMemoryOffset; i++) {
        TelecommandClass *tc;
        unsigned int nRawData;

        tc = TELECOMMAND_CLASS(pool[i]);
        nRawData = tc->getNumberOfRawData(pool[i]);
        if ((nRawData >= NumberOfRawData) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
           Telecommand_setInUse((Telecommand*)pool[i], true);
           return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelecommandFactory_isFreePUSDumpMemoryOffset(CC_TelecommandFactory *This, 
                                                     unsigned int NumberOfRawData)
{
    DC_PUSDumpMemoryOffset** const pool = This->poolPUSDumpMemoryOffset;
    for (unsigned int i=0; i<This->sizePUSDumpMemoryOffset; i++) {
        TelecommandClass *tc;
        unsigned int nRawData;

        tc = TELECOMMAND_CLASS(pool[i]);
        nRawData = tc->getNumberOfRawData(pool[i]);
        if ((nRawData >= NumberOfRawData) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
           return true;
        }
    }

    return false;
}

static void setPUSMemoryLoadAbsolute(CC_TelecommandFactory *This, 
                                     unsigned int i, 
                                     DC_PUSMemoryLoadAbsolute *pItem)
{
    assert(i < This->sizePUSMemoryLoadAbsolute);
    assert(pItem != pNULL);
    This->poolPUSMemoryLoadAbsolute[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolPUSMemoryLoadAbsolute[i], false);
}

unsigned int CC_TelecommandFactory_getNumberPUSMemoryLoadAbsolute
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSMemoryLoadAbsolute** const pool = This->poolPUSMemoryLoadAbsolute;
    for (unsigned int i=0; i<This->sizePUSMemoryLoadAbsolute; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityPUSMemoryLoadAbsolute
(
    CC_TelecommandFactory *This
)
{
    return This->sizePUSMemoryLoadAbsolute;
}

DC_PUSMemoryLoadAbsolute* CC_TelecommandFactory_allocatePUSMemoryLoadAbsolute
(
    CC_TelecommandFactory *This, 
    unsigned int MaxNumberData, 
    unsigned int MaxNumberBlocks
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_PUSMemoryLoadAbsolute** const pool = This->poolPUSMemoryLoadAbsolute;
    for (unsigned int i=0; i<This->sizePUSMemoryLoadAbsolute; i++) {
        unsigned int maxNumData;
        unsigned int maxNumBlk;

        maxNumData = PUSMemoryLoad_getMaxNumberData((PUSMemoryLoad*)pool[i]);
        maxNumBlk = PUSMemoryLoad_getMaxNumberBlocks((PUSMemoryLoad*)pool[i]);
        if ((maxNumData >= MaxNumberData) &&
            (maxNumBlk >= MaxNumberBlocks) &&
            (!Telecommand_isInUse((Telecommand*)pool[i])))
        {
           Telecommand_setInUse((Telecommand*)pool[i], true);
           return pool[i];
        }
    }
    return pNULL;
}

bool CC_TelecommandFactory_isFreePUSMemoryLoadAbsolute(CC_TelecommandFactory *This, 
                                                       unsigned int MaxNumberData, 
                                                       unsigned int MaxNumberBlocks)
{
    DC_PUSMemoryLoadAbsolute** const pool = This->poolPUSMemoryLoadAbsolute;
    for (unsigned int i=0; i<This->sizePUSMemoryLoadAbsolute; i++) {
        unsigned int maxNumData;
        unsigned int maxNumBlk;

        maxNumData = PUSMemoryLoad_getMaxNumberData((PUSMemoryLoad*)pool[i]);
        maxNumBlk = PUSMemoryLoad_getMaxNumberBlocks((PUSMemoryLoad*)pool[i]);
        if ((maxNumData >= MaxNumberData) &&
            (maxNumBlk >=MaxNumberBlocks) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
           return true;
        }

    }

    return false;
}

static void setPUSMemoryLoadOffset(CC_TelecommandFactory *This,
                                   unsigned int i,
                                   DC_PUSMemoryLoadOffset *pItem)
{
    assert(i<This->sizePUSMemoryLoadOffset);
    assert(pItem!=pNULL);
    This->poolPUSMemoryLoadOffset[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolPUSMemoryLoadOffset[i], false);
}

unsigned int CC_TelecommandFactory_getNumberPUSMemoryLoadOffset
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSMemoryLoadOffset** const pool = This->poolPUSMemoryLoadOffset;
    for (unsigned int i=0; i<This->sizePUSMemoryLoadOffset; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
        }
    }        

    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityPUSMemoryLoadOffset
(
    CC_TelecommandFactory *This
)
{
    return This->sizePUSMemoryLoadOffset;
}

DC_PUSMemoryLoadOffset* CC_TelecommandFactory_allocatePUSMemoryLoadOffset
(
    CC_TelecommandFactory *This, 
    unsigned int MaxNumberData, 
    unsigned int MaxNumberBlocks
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_PUSMemoryLoadOffset** const pool = This->poolPUSMemoryLoadOffset;
    for (unsigned int i=0; i<This->sizePUSMemoryLoadOffset; i++) {
        unsigned int maxNumData;
        unsigned int maxNumBlk;

        maxNumData = PUSMemoryLoad_getMaxNumberData((PUSMemoryLoad*)pool[i]);
        maxNumBlk = PUSMemoryLoad_getMaxNumberBlocks((PUSMemoryLoad*)pool[i]);
        if ((maxNumData >= MaxNumberData) &&
            (maxNumBlk >= MaxNumberBlocks) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
           Telecommand_setInUse((Telecommand*)pool[i], true);
           return pool[i];
        
        }
    }
    return pNULL;
}

bool CC_TelecommandFactory_isFreePUSMemoryLoadOffset(CC_TelecommandFactory *This, 
                                                     unsigned int MaxNumberData, 
                                                     unsigned int MaxNumberBlocks)
{
    DC_PUSMemoryLoadOffset** const pool = This->poolPUSMemoryLoadOffset;
    for (unsigned int i=0; i<This->sizePUSMemoryLoadOffset; i++) {
        unsigned int maxNumData;
        unsigned int maxNumBlk;

        maxNumData = PUSMemoryLoad_getMaxNumberData((PUSMemoryLoad*)pool[i]);
        maxNumBlk = PUSMemoryLoad_getMaxNumberBlocks((PUSMemoryLoad*)pool[i]);
        if ((maxNumData >= MaxNumberData) &&
            (maxNumBlk >= MaxNumberBlocks) &&
            (!Telecommand_isInUse((Telecommand*)pool[i]))) 
        {
           return true;
        }
    }

    return false;
}

static void setTestPUSTelecommand(CC_TelecommandFactory *This, 
                                  unsigned int i,
                                  DC_TestPUSTelecommand *pItem)
{
    assert(i < This->sizeTestPUSTelecommand);
    assert(pItem != pNULL);
    This->poolTestPUSTelecommand[i] = pItem;
    Telecommand_setInUse((Telecommand*)This->poolTestPUSTelecommand[i], false);
}

unsigned int CC_TelecommandFactory_getNumberTestPUSTelecommand
(
    CC_TelecommandFactory *This
)
{
    unsigned int counter = 0;
    DC_TestPUSTelecommand** const pool  = This->poolTestPUSTelecommand;
    for (unsigned int i=0; i<This->sizeTestPUSTelecommand; i++) {
        if (Telecommand_isInUse((Telecommand*)pool[i])) {
            counter++;
        }
    }
    return counter;
}

unsigned int CC_TelecommandFactory_getCapacityTestPUSTelecommand
(
    CC_TelecommandFactory *This
)
{
    return This->sizeTestPUSTelecommand;
}

DC_TestPUSTelecommand* CC_TelecommandFactory_allocateTestPUSTelecommand
(
    CC_TelecommandFactory *This
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_TestPUSTelecommand** const pool  = This->poolTestPUSTelecommand;
    for (unsigned int i=0; i<This->sizeTestPUSTelecommand; i++) {
        if (!Telecommand_isInUse((Telecommand*)pool[i])) {
            Telecommand_setInUse((Telecommand*)pool[i], true);
            return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelecommandFactory_isFreeTestPUSTelecommand(CC_TelecommandFactory *This)
{
    DC_TestPUSTelecommand** const pool  = This->poolTestPUSTelecommand;
    for (unsigned int i=0; i<This->sizeTestPUSTelecommand; i++) {
        if (!Telecommand_isInUse((Telecommand*)pool[i])) {
           return true;
        }
    }

    return false;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check that all component instances required by the factory have been loaded.
 * @return true if the component is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    CC_TelecommandFactory *This = CC_TELECOMMANDFACTORY(obj);

    if (!cc_roc->isObjectConfigured(obj)) {
        return false;
    }
  
    if (This->poolDummyPUSTelecommand == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizeDummyPUSTelecommand; i++) {
        if (This->poolDummyPUSTelecommand[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolDummyTelecommand == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizeDummyTelecommand; i++) {
        if (This->poolDummyTelecommand[i] == pNULL) {
            return false;
        }
    }

    if (This->poolPUSControlDataReporting==pNULL) { 
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSControlDataReporting; i++) {
        if (This->poolPUSControlDataReporting[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSDefineDataReporting == pNULL)
        return false;

    for (unsigned int i=0; i<This->sizePUSDefineDataReporting; i++) { 
        if (This->poolPUSDefineDataReporting[i] == pNULL) {
            return false;
        }
    }

    if (This->poolPUSDumpMemoryAbsolute == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSDumpMemoryAbsolute; i++) {
        if (This->poolPUSDumpMemoryAbsolute[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSDumpMemoryOffset == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSDumpMemoryOffset; i++) {
        if (This->poolPUSDumpMemoryOffset[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSMemoryLoadAbsolute == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSMemoryLoadAbsolute; i++) {
        if (This->poolPUSMemoryLoadAbsolute[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSMemoryLoadOffset == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSMemoryLoadOffset; i++) {
        if (This->poolPUSMemoryLoadOffset[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolTestPUSTelecommand == pNULL) {
        return false;
    }


    for (unsigned int i=0; i<This->sizeTestPUSTelecommand; i++) {
        if (This->poolTestPUSTelecommand[i] == pNULL) {
            return false;
        }
    }
     
   return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{

    CC_TelecommandFactory *This = CC_TELECOMMANDFACTORY(obj);
    unsigned int size;
  
    // DC_DummyPUSTelecommand*
    size = 1;
    This->poolDummyPUSTelecommand = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolDummyPUSTelecommand[i] = pNULL;
    }
    This->sizeDummyPUSTelecommand = size;

    // DC_DummyTelecommand*
    size = 2;
    This->poolDummyTelecommand = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolDummyTelecommand[i] = pNULL;
    }
    This->sizeDummyTelecommand = 2;
      
    // DC_PUSControlDataReporting*
    size = 1;
    This->poolPUSControlDataReporting = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSControlDataReporting[i] = pNULL;
    }
    This->sizePUSControlDataReporting = size;

    // DC_PUSDefineDataReporting*
    size = 1;
    This->poolPUSDefineDataReporting = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSDefineDataReporting[i] = pNULL;
    }
    This->sizePUSDefineDataReporting = size;
      
    // DC_PUSDumpMemoryAbsolute*
    size = 1;
    This->poolPUSDumpMemoryAbsolute = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++)
       This->poolPUSDumpMemoryAbsolute[i] = pNULL;
    This->sizePUSDumpMemoryAbsolute = size;
      
    // DC_PUSDumpMemoryOffset*
    size = 1;
    This->poolPUSDumpMemoryOffset = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSDumpMemoryOffset[i] = pNULL;
    }
    This->sizePUSDumpMemoryOffset = size;

    // DC_PUSMemoryLoadAbsolute*
    size = 2;
    This->poolPUSMemoryLoadAbsolute = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSMemoryLoadAbsolute[i] = pNULL;
    }
    This->sizePUSMemoryLoadAbsolute = size;
      
    // DC_PUSMemoryLoadOffset*
    size = 1;
    This->poolPUSMemoryLoadOffset = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSMemoryLoadOffset[i] = pNULL;
    }
    This->sizePUSMemoryLoadOffset = size;
      
    // DC_TestPUSTelecommand*
    size = 3;
    This->poolTestPUSTelecommand = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolTestPUSTelecommand[i] = pNULL;
    }
    This->sizeTestPUSTelecommand = size;


    CC_RootObject_setClassId((CC_RootObject*)obj, ID_TELECOMMANDFACTORY);
}

CC_TelecommandFactory* CC_TelecommandFactory_new(void)
{
    Object *obj = object_new(TYPE_CC_TELECOMMANDFACTORY);
    return (CC_TelecommandFactory*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_TELECOMMANDFACTORY,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_TelecommandFactory),
    .abstract = false,
    .class_size = sizeof(CC_TelecommandFactoryClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_TelecommandFactory_register(void)
{
    type_register_static(&type_info);
}
