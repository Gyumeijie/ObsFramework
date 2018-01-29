//
//
// TestCaseBasicPUSTmStream_1.h
//


#ifndef TESTCASEBASICPUSTMSTREAM_1_H
#define TESTCASEBASICPUSTMSTREAM_1_H


#include "../Utilities/TestCaseWithFactories.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_BasicPUSTmStream</code>
 * class. An instance of this class is created and a sample telemetry packet(instance
 * of class <code>DC_DummyPUSTelemetryPacket</code>) is
 * retrieved from the telemetry packet factory. The following
 * specific checks are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the TM stream is initially not configured.</li>
 * <li>The value of the stream capacity is set and read back. The correctness
 * of the read-back value is checked.</li>
 * <li>The value of the start address of the telemetry write area is set and read back.
 * The correctness of the read-back value is checked. </li>
 * <li>It is checked that the TM stream is now configured.</li>
 * <li>The value of the packet counter is retrieved and it is checked that is equal to
 * zero. </li>
 * <li>A telemetry packet is written to the stream and the correctness of the write
 * operation is checked.</li>
 * <li>It is checked that the packet counter and the sequence counter are 
 * incremented by one after the write
 * operation.</li>
 * <li>The packet is repeatedly written until the telemetry write area is filled.
 * It is checked that a write operation results
 * in the generation of the correct event report.</li>
 * <li>The telemetry area is reset and it is checked that the next
 * write request executes successfully.</li>
 * <li>It is checked that the packet counter and the write counters are reset to 0 and 1,
 * respectively.</li>
 * <li>The last two checks are repeated using a flush operation instead of a reset
 * operation and it is checked that the outcome is the same.</li>
 * </ol>
 * @see DC_BasicPUSTmStream
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEBASICPUSTMSTREAM_1 "testcasebasicpustmstream_1"

void TestCaseBasicPUSTmStream_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseBasicPUSTmStream_1 {
    TestCaseWithFactories parent;

    unsigned char *tmArea;
    DC_DummyPUSTelemetryPacket *pTM;
    DC_BasicPUSTmStream *pTMS;
} TestCaseBasicPUSTmStream_1;


typedef struct TestCaseBasicPUSTmStream_1Class {
    TestCaseWithFactoriesClass parent_class;
} TestCaseBasicPUSTmStream_1Class;


#define TESTCASEBASICPUSTMSTREAM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseBasicPUSTmStream_1Class, \
                                          obj, TYPE_TESTCASEBASICPUSTMSTREAM_1)

#define TESTCASEBASICPUSTMSTREAM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseBasicPUSTmStream_1Class, \
                                        klass, TYPE_TESTCASEBASICPUSTMSTREAM_1)

#define TESTCASEBASICPUSTMSTREAM_1(obj) \
        OBJECT_CHECK(TestCaseBasicPUSTmStream_1, \
                                          obj, TYPE_TESTCASEBASICPUSTMSTREAM_1)


TestCaseBasicPUSTmStream_1* TestCaseBasicPUSTmStream_1_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check the correctness of the telemetry image written by the telemetry stream under test.
 * The telemetry image is assumed to start at location <code>start</code> in the
 * telemetry write area and the value of the application data generated by the
 * telemetry packet is assumed to be <code>value</code>.
 * @param start the start location of the telemetry image
 * @param value the value of the application data
 * @return true if the telemetry image is correct, false otherwise
 */
bool TestCaseBasicPUSTmStream_1_checkTmImage
(
    TestCaseBasicPUSTmStream_1 *This, 
    unsigned int start, 
    unsigned char value
);


#endif
