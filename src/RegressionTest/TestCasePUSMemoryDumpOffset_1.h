//
//
// TestCasePUSMemoryDumpOffset_1.h
//


#ifndef TESTCASEPUSMEMORYDUMPOFFSET_1_H
#define TESTCASEPUSMEMORYDUMPOFFSET_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_PUSMemoryDumpOffset</code>
 * class. 
 * One telecommand instance of type <code>DC_PUSMemoryDumpOffset</code> is 
 * created and the following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>The correctness of the type and subtype is checked.</li>
 * <li>It is checked that the telemetry packet component is initially not configured.</li>
 * <li>The maximum number of blocks in the telemetry packet component is set and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>The size of the dump buffer is set and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the component is now configured.</li>
 * <li>The base address is set and the correctness of the
 * set operation is checked.</li>
 * <li>The memory block identifier is set and the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the checksum flag is initially set to "false".</li>
 * <li>The memory dump blocks are defined and the correctness of the configuration operation
 * is checked.</li>
 * <li>It is checked that the fast acquisition service is available.</li>
 * <li>A data update operation is performed and is followed by a data acquisition operation.
 * The correctness of the acquired data is checked.</li>
 * <li>The number of bytes in the telemetry packet is read out and the correctness of the
 * read-out value is checked.</li>
 * <li>The checksum flag is changed to "true" (checksum field required) and the correctness of the
 * operation is checked.</li>
 * <li>One memory dump block is defined, a data update and a data acquisition are performed, 
 * and the correctness of the memory dump data(including the checksum filed) is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to load too many memory blocks and
 * it is checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an attempt is made to configure a non-existent block
 * and it is checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an attempt is made to dump a set of blocks that overflow
 * the <i>dump buffer</i>
 * and it is checked that the correct event is generated.</li>
 * </ol>
 * @see DC_PUSMemoryLoadOffset
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEPUSMEMORYDUMPOFFSET_1 "testcasepusmemorydumpoffset_1"

void TestCasePUSMemoryDumpOffset_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSMemoryDumpOffset_1 {
    TestCaseWithEvtCheck parent;
} TestCasePUSMemoryDumpOffset_1;


typedef struct TestCasePUSMemoryDumpOffset_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCasePUSMemoryDumpOffset_1Class;


#define TESTCASEPUSMEMORYDUMPOFFSET_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSMemoryDumpOffset_1Class,\
                                       obj, TYPE_TESTCASEPUSMEMORYDUMPOFFSET_1)

#define TESTCASEPUSMEMORYDUMPOFFSET_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSMemoryDumpOffset_1Class,\
                                     klass, TYPE_TESTCASEPUSMEMORYDUMPOFFSET_1)

#define TESTCASEPUSMEMORYDUMPOFFSET_1(obj) \
        OBJECT_CHECK(TestCasePUSMemoryDumpOffset_1,\
                                       obj, TYPE_TESTCASEPUSMEMORYDUMPOFFSET_1)


TestCasePUSMemoryDumpOffset_1* TestCasePUSMemoryDumpOffset_1_new(void);

#endif
