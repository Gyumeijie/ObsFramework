//
//
// PUSMemoryLoad.h
//


#ifndef PUSMEMORYLOAD_H
#define PUSMEMORYLOAD_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * Base class for telecommands implementing the PUS memory load service requests
 * (PUS service type 6).
 * This class is intended as a base for telecommand classes implementing 
 * the following subtypes of PUS service number 6:<ul>
 * <li>Subtype 1: load memory using base plus offsets</li>
 * <li>Subtype 2: load memory using absolute addresses</li>
 * </ul>
 * This class defines internal data structures where the data to be
 * loaded in memory can be stored and provides implementations for the operations 
 * to load the data in memory. 
 * The maximum size of the internal data structures is defined during the
 * application initialization phase. The following operations must be performed:<ul>
 * <li>Method <code>setMaxNumberOfBlocks</code> must be called to set the maximum
 * number of memory blocks that can be managed by this telecommand</li>
 * <li>Method <code>setMaxNumberData</code> must be called to set the maximum size of
 * the internal buffer where the memory data are stored.</li>
 * </ul>
 * The data to be loaded in memory are defined dynamically(normally by the 
 * <i>telecommand loader</i> component). The operations to define them are however left
 * undefined by this class as they differ for the case of a memory load that uses the base plus 
 * offset mechanism(service subtype 1) and for the case of a memory load that uses
 * absolute addresses(service subtype 2). In general, the definition of the memory
 * load data can be done using the <i>raw data load mechanism</i>. 
 * <p>
 * Execution of this telecommand can have two outcomes. The telecommand
 * can either have a successful outcome(the return value of <code>doAction</code>
 * is ACTION_SUCCESS) or it can fail(the return value of <code>doAction</code>
 * is MEM_LOAD_PRE_CHECKSUM_FAILED or MEM_LOAD_POST_CHECKSUM_FAILED). A failure 
 * is declared if a checksum check has failed.
 * <p>
 * The PUS leaves some leeway in the definition of the structure of the application
 * data for memory load telecommands. This implementation makes the following 
 * assumptions: <ul>
 * <li>The number of blocks is always present.</li>
 * <li>The checksum field is always present. If no checksum is required, the checksum
 * field should be set to zero.</li>
 * <li>The memory data are treated as integers of syntactical type 
 * <code>TD_PUSMemData</code>.</li>
 * </ul>
 * The implementation of this class assumes type <code>TD_PUSMemData</code> to have
 * size 1 (i.e. to be a <code>char</code> or an <code>unsigned char</code>). If this
 * were not the case, then run time exceptions will arise on some processors(notably
 * on the ERC32) due to alignment problems.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_PUSMEMORYLOAD "pusmemoryload"

void PUSMemoryLoad_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////


struct PUSMemoryLoad {
    PUSTelecommand parent;

    /**
     * The i-th item of this array holds the descriptor for the i-th memory block
     * to be loaded
     */
    MemBlockType *block;
    /**
     * The maximum number of memory load blocks
     */
    TD_PUSNumberMemBlocks maxNumberBlocks;
    /**
     * The number of memory load blocks that have actually been loaded into the telecommand.
     */
    TD_PUSNumberMemBlocks numberBlocks;
    /**
     * This array holds all the memory load data for the currently defined blocks.
     * If the length of the first block is N, then the first N locations of this array
     * hold the memory load data for the first block. If the length of the second block is M,
     * then the locations between N and N+M-1, hold the data memory load data for the second
     * block. And so forth for the other blocks.
     */
    TD_PUSMemData *data;
    /**
     * The maximum number of memory load data(this is the size of the array <code>data</code>.
     */
    unsigned int maxNumberData;
};


struct PUSMemoryLoadClass {
    PUSTelecommandClass parent_class;
};


#define PUSMEMORYLOAD_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PUSMemoryLoadClass, obj, TYPE_PUSMEMORYLOAD)

#define PUSMEMORYLOAD_CLASS(klass) \
        OBJECT_CLASS_CHECK(PUSMemoryLoadClass, klass, TYPE_PUSMEMORYLOAD)

#define PUSMEMORYLOAD(obj) \
        OBJECT_CHECK(PUSMemoryLoad, obj, TYPE_PUSMEMORYLOAD)


PUSMemoryLoad* PUSMemoryLoad_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the maximum number of memory blocks that can be managed by this telecommand.
 * This is an initialization method that should only be called once.
 * A call to this method causes the internal data structures where the blocks are
 * held to be allocated and initialized. Only positive values of the method argument
 * are legal.
 * @param max the maximum number of blocks
 */
void PUSMemoryLoad_setMaxNumberBlocks(PUSMemoryLoad *This, unsigned int max);

/**
 * Get the maximum number of memory blocks that can be managed by this telecommand.
 * @see #setMaxNumberBlocks
 * @return the maximum number of blocks
 */
unsigned int PUSMemoryLoad_getMaxNumberBlocks(const PUSMemoryLoad *This);

/**
 * Get the number of memory blocks that are managed by this telecommand.
 * This number is read from the application data loaded into the telecommand.
 * @return the number of blocks
 */
unsigned int PUSMemoryLoad_getNumberBlocks(const PUSMemoryLoad *This);

/**
 * Set the maximum number of memory load data that can be managed by this telecommand.
 * This is an initialization method that should only be called once.
 * A call to this method causes the internal data structures where the blocks are
 * held to be allocated and initialized. Only positive values of the method argument
 * are legal.
 * @param max the maximum number of memory data
 */
void PUSMemoryLoad_setMaxNumberData(PUSMemoryLoad *This, unsigned int max);

/**
 * Get the maximum number of memory data that can be managed by this telecommand.
 * @see #setMaxNumberData
 * @return the maximum number of memory data
 */
unsigned int PUSMemoryLoad_getMaxNumberData(const PUSMemoryLoad *This);

/**
 * Get the start address of the i-th currently loaded block.
 * The block index i must lie in the interval [0, N-1] where N is the number
 * of currently loaded PUSMemoryLoad_blocks(the value returned by method 
 * <code>getNumberBlocks</code>). If this condition is not satisfied, 
 * the return value is unpredictable.
 * This is an unsafe method because it returns a pointer. It should only
 * be used during testing. It should never be called by an application.
 * @param i the block index
 * @return the start address of the i-th currently loaded block
 */
TD_PUSMemData* PUSMemoryLoad_getStartAddress
(
    const PUSMemoryLoad *This, 
    unsigned int i
);

/**
 * Get the length of the i-th currently loaded block.
 * The block index i must lie in the interval [0, N-1] where N is the number
 * of currently loaded PUSMemoryLoad_blocks(the value returned by method 
 * <code>getNumberBlocks</code>). If this condition is not satisfied, 
 * the return value is unpredictable.
 * @param i the block index
 * @return the length of the i-th currently loaded block
 */
TD_PUSMemLength PUSMemoryLoad_getLength
(
    const PUSMemoryLoad *This,
    unsigned int i
);

/**
 * Get the checksum of the i-th currently loaded block.
 * The block index i must lie in the interval [0, N-1] where N is the number
 * of currently loaded PUSMemoryLoad_blocks(the value returned by method 
 * <code>getNumberBlocks</code>). If this condition is not satisfied, 
 * the return value is unpredictable.
 * @param i the block index
 * @return the length of the i-th currently loaded block
 */
unsigned short PUSMemoryLoad_getChecksum
(
    const PUSMemoryLoad *This, 
    unsigned int i
);


#endif
