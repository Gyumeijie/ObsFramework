//
//
// TestCasePUSMemoryLoadOffset_2.h
//


#ifndef TESTCASEPUSMEMORYLOADOFFSET_2_H
#define TESTCASEPUSMEMORYLOADOFFSET_2_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the checksum-related functionalities of the <code>DC_PUSMemoryLoadOffset</code>
 * class. 
 * One telecommand instance of type <code>DC_PUSMemoryLoadOffset</code> is 
 * created. The image of a telecommand packet consisting of one block with four data 
 * is set up. The following specific tests are then performed:<ol>
 * <li>The telecommand is loaded with a valid checksum and it is then executed. It is 
 * checked that the outcome code of 
 * the telecommand is ACTION_SUCCESS and that the memory load is correctly executed.</li>
 * <li>The telecommand is loaded with a invalid checksum and it is then executed. It is 
 * checked that the correctness of the outcome code and that the memory load is 
 * not performed.</li>
 * </ol>
 * This test case assumes the type <code>TD_PUSMemData</code> to be defined as
 * <code>unsigned char</code>.
 * @see DC_PUSMemoryLoadOffset
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEPUSMEMORYLOADOFFSET_2 "testcasepusmemoryloadoffset_2"

void TestCasePUSMemoryLoadOffset_2_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSMemoryLoadOffset_2 {
    TestCaseWithEvtCheck parent;
} TestCasePUSMemoryLoadOffset_2;


typedef struct TestCasePUSMemoryLoadOffset_2Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCasePUSMemoryLoadOffset_2Class;


#define TESTCASEPUSMEMORYLOADOFFSET_2_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSMemoryLoadOffset_2Class, \
                                       obj, TYPE_TESTCASEPUSMEMORYLOADOFFSET_2)

#define TESTCASEPUSMEMORYLOADOFFSET_2_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSMemoryLoadOffset_2Class, \
                                     klass, TYPE_TESTCASEPUSMEMORYLOADOFFSET_2)

#define TESTCASEPUSMEMORYLOADOFFSET_2(obj) \
        OBJECT_CHECK(TestCasePUSMemoryLoadOffset_2, \
                                       obj, TYPE_TESTCASEPUSMEMORYLOADOFFSET_2)


TestCasePUSMemoryLoadOffset_2* TestCasePUSMemoryLoadOffset_2_new(void);

#endif
