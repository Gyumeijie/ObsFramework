//
//
// TestCasePUSMemoryLoadOffset_1.h
//


#ifndef TESTCASEPUSMEMORYLOADOFFSET_1_H
#define TESTCASEPUSMEMORYLOADOFFSET_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_PUSMemoryLoadOffset</code>
 * class for the case where no checksum checks are performed. 
 * One telecommand instance of type <code>DC_PUSMemoryLoadOffset</code> is 
 * created and the following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the telecommand component is initially not configured.</li>
 * <li>The maximum number of blocks in the telecommand component is set to 3 and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>The maximum number of data in the telecommand component is set to 10 and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the component is now configured.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for one block
 * with two data. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that the outcome code of 
 * the telecommand is ACTION_SUCCESS and that the memory load is correctly executed.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for three blocks
 * with three data each. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that the outcome code of 
 * the telecommand is ACTION_SUCCESS and that the memory load is correctly executed.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for four blocks.
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for two blocks
 * with two data(first block) and nine data(second block).
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * <li>The telecommand raw data service is called with an invalid number of bytes to 
 * be transfered.
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * <li>The telecommand raw data service is called with an inconsistent number of bytes to 
 * be transfered.
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * </ol>
 * @see DC_PUSMemoryLoadOffset
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEPUSMEMORYLOADOFFSET_1 "testcasepusmemoryloadoffset_1"

void TestCasePUSMemoryLoadOffset_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSMemoryLoadOffset_1 {
    TestCaseWithEvtCheck parent;
} TestCasePUSMemoryLoadOffset_1;


typedef struct TestCasePUSMemoryLoadOffset_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCasePUSMemoryLoadOffset_1Class;


#define TESTCASEPUSMEMORYLOADOFFSET_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSMemoryLoadOffset_1Class, \
                                       obj, TYPE_TESTCASEPUSMEMORYLOADOFFSET_1)

#define TESTCASEPUSMEMORYLOADOFFSET_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSMemoryLoadOffset_1Class, \
                                     klass, TYPE_TESTCASEPUSMEMORYLOADOFFSET_1)

#define TESTCASEPUSMEMORYLOADOFFSET_1(obj) \
        OBJECT_CHECK(TestCasePUSMemoryLoadOffset_1, \
                                       obj, TYPE_TESTCASEPUSMEMORYLOADOFFSET_1)


TestCasePUSMemoryLoadOffset_1* TestCasePUSMemoryLoadOffset_1_new(void);

#endif
