//
//
// PUSMemoryDump.h
//


#ifndef PUSMEMORYDUMP_H
#define PUSMEMORYDUMP_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelemetryPacket.h"
#include "../Qom/object.h"


/*
 * Base class from which the classes implementing the memory dump telemetry packets 
 * (PUS service type 6, subtypes 4 and 6) can be derived.
 * This class defines an internal memory structure where the characteristics of the
 * memory blocks to be dumped(start address, length, and checksum) are stored.
 * Additionally, it defines <i>dump buffer</i> to be used to store the telemetry packet
 * image. The <i>data acqusition service</i>
 * (defined by the super class <code>TelemetryPacket</code>) is implemented to flush
 * this buffer. Since the amount of data in a memory packet may be large, this class
 * implements both the safe and fast versions of the data acquisition service.
 * Finally, this class defines a <i>checksum flag</i>) that can be set
 * to indicate whether checksum should be computed and included in the telemetry packet 
 * data. the checksum flag is defined as a static variable and is initialized to false.
 * The <i>data update service</i> depends on the data subtype and must therefore
 * be defined by the subclasses. All the internal data structures defined by this class
 * are declared <code>protected</code> to allow easy access to them by the subclasses
 * that implement the two forms of the memory dump service.
 * <p>
 * The initial configuration of this class is performed as follows:<ul>
 * <li>Method <code>setMaxNumberOfBlocks</code> must be called to set the maximum
 * number of memory blocks that can be managed by this telemetry packet</li>
 * <li>Method <code>setDumpBufferSize</code> must be called to set the maximum size of
 * the dump buffer.</li>
 * <li>The checksum flag is set with method <code>setChecksumFlag</code>. Note that 
 * this is a static method and that the checksum flag applies globally to all
 * memory dump telemetry blocks.</li>
 * </ul>
 * The dynamic configuration of the telemetry packet is performed as follows:<ul>
 * <li>The number of blocks to be dumped is set with method <code>setNumberOfBlocks</code>  </li>
 * <li>The blocks are defined with a sequence of calls to method <code>defineBlock</code>  </li>
 * </ul>
 * The PUS leaves some leeway in the definition of the structure of the application
 * data for memory load telecommands. This implementation makes the following 
 * assumptions: <ul>
 * <li>The memory ID is always present and is an integer of syntactical type <code>TD_PUSMemId</code>.</li>
 * <li>The number of memory blocks field is always present. The number of memory blocks is treated
 * as an integer of syntatical type <code>TD_PUSNumberMemBlocks</code>.</li>
 * <li>The memory data are treated as integers of syntactical type 
 * <code>TD_PUSMemData</code>. This type defines the single addressable unit(or SAU).</li>
 * <li>The offset of a memory block with respect to a base address is treated as an integer
 * of syntactic type <code>TD_PUSMemOffset</code>.</li>
 * <li>The length of a memory block is treated as an integer
 * of syntactic type <code>TD_PUSMemLength</code>.</li>
 * <li>The checksum field is always included(it is set to zero when no checksum is required).</li>
 * </ul>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_PUSMEMORYDUMP "pusmemorydump"

void PUSMemoryDump_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////


struct PUSMemoryDump {
    PUSTelemetryPacket parent;

     /**
     * The i-th item of this array holds the descriptor for the i-th memory block
     * to be dumped
     */
    MemBlockType *block;
    /**
     * The maximum number of memory dump blocks
     */
    TD_PUSNumberMemBlocks maxNumberBlocks;
    /**
     * The number of memory dump blocks that must be dumped by this telemetry packet.
     */
    TD_PUSNumberMemBlocks numberBlocks;
    /**
     * Dump buffer. 
     */
    unsigned char *data;
    /**
     * The size of the telemetry packet in number of bytes. 
     */
    unsigned int tmPacketSize;
    /**
     * The size of the dump buffer.
     */
    unsigned int maxNumberData;
    /**
     * Identifier of the memory block.
     */
    TD_PUSMemId memId;
};


struct PUSMemoryDumpClass {
    PUSTelemetryPacketClass parent_class;
};


#define PUSMEMORYDUMP_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PUSMemoryDumpClass, obj, TYPE_PUSMEMORYDUMP)

#define PUSMEMORYDUMP_CLASS(klass) \
        OBJECT_CLASS_CHECK(PUSMemoryDumpClass, klass, TYPE_PUSMEMORYDUMP)

#define PUSMEMORYDUMP(obj) \
        OBJECT_CHECK(PUSMemoryDump, obj, TYPE_PUSMEMORYDUMP)


PUSMemoryDump* PUSMemoryDump_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the checksum flag. If this flag is set to true, then the checksum is computed
 * for each memory block to be dumped. Otherwise, the checksum field is set to zero.
 * Note that the checksum field is always included in the telemetry packet.
 * @param checksumFlag the value of the checksum flag
 */
void PUSMemoryDump_setChecksumFlag(bool checksumFlag);

/**
 * Return the value of the checksum flag. 
 * @return the value of the checksum flag
 */
bool PUSMemoryDump_isChecksumFlagSet(void);



///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the maximum number of memory blocks that can be managed by this telemetry packet.
 * This is an initialization method that should only be called once.
 * A call to this method causes the internal data structures where the blocks are
 * held to be allocated and initialized. Only positive values of the method argument
 * are legal.
 * @param max the maximum number of blocks
 */
void PUSMemoryDump_setMaxNumberBlocks(PUSMemoryDump *This, TD_PUSNumberMemBlocks max);

/**
 * Get the maximum number of memory blocks that can be managed by this telemetry packet.
 * @see #setMaxNumberBlocks
 * @return the maximum number of blocks
 */
TD_PUSNumberMemBlocks PUSMemoryDump_getMaxNumberBlocks(const PUSMemoryDump *This);

/**
 * Set the number of memory blocks that must be managed by this telemetry packet.
 * This method is normally called when the telemetry packet is dynamically configured.
 * The value of the argument N must lie in the range [1, N] where N is the maximum number of
 * blocks set with method <code>setmaxNumberBlocks</code>. If this is not the case, the number
 * of blocks is set to N and event report EVT_PUS_TOO_MANY_DUMP_BLOCKS. Only positive values are legal for the number
 * of blocks.
 * @param max the maximum number of blocks
 */
void PUSMemoryDump_setNumberBlocks(PUSMemoryDump *This, TD_PUSNumberMemBlocks max);

/**
 * Get the number of memory blocks that are managed by this telemetry packet.
 * @see #setNumberBlocks
 * @return the number of blocks
 */
TD_PUSNumberMemBlocks PUSMemoryDump_getNumberBlocks(const PUSMemoryDump *This);

/**
 * Set the PUSMemoryDump_size(in number of bytes) of the dump buffer. 
 * This is an initialization method that should only be called once.
 * A call to this method causes the memory for the dump buffer to be 
 * allocated and initialized. Only positive values of the method argument
 * are legal.
 * @param max the size of the dump buffer
 */
void PUSMemoryDump_setDumpBufferSize(PUSMemoryDump *This, unsigned int max);

/**
 * Get the PUSMemoryDump_size(in number of bytes) of the dump buffer.
 * @see #setDumpBufferSize
 * @return the PUSMemoryDump_size(in number of bytes) of the dump buffer.
 */
unsigned int PUSMemoryDump_getDumpBufferSize(const PUSMemoryDump *This);

/**
 * Define the characteristics of the i-th memory block to be dumped. This method
 * would normally be called as part of the dynamic telemetry packet configuration.
 * The index i must lie in the range [0, N-1] where N is the number of blocks
 * set with method <code>setNumberBlocks</code>). If this is not the case, 
 * the method generates event report EVT_PUS_ILLEGAL_BLOCK_INDEX and returns immediately.
 * The checksum value of the i-th block is initialized to zero.
 * @param i the memory dump index
 * @param start the start address of the i-th memory dump block
 * @param length the length of the i-th memory dump block
 */
void PUSMemoryDump_defineBlock
(
    PUSMemoryDump *This, 
    TD_PUSNumberMemBlocks i, 
    TD_PUSMemData *start, 
    TD_PUSMemLength length
);

/**
 * Get the start address of the i-th currently loaded block.
 * The block index i must lie in the interval [0, N-1] where N is the number
 * of currently loaded PUSMemoryDump_blocks(the value returned by method 
 * <code>getNumberBlocks</code>). If this condition is not satisfied, 
 * the return value is unpredictable. This method is unsafe because it
 * returns a pointer. It is intended to be used only for testing purposes.
 * @param i the block index
 * @return the start address of the i-th currently loaded block
 */
TD_PUSMemData* PUSMemoryDump_getStartAddressOfMemBlock
(
    const PUSMemoryDump *This, 
    TD_PUSNumberMemBlocks i
);

/**
 * Get the length of the i-th currently loaded block.
 * The block index i must lie in the interval [0, N-1] where N is the number
 * of currently loaded PUSMemoryDump_blocks(the value returned by method 
 * <code>getNumberBlocks</code>). If this condition is not satisfied, 
 * the return value is unpredictable. 
 * @param i the block index
 * @return the length of the i-th currently loaded block
 */
TD_PUSMemLength PUSMemoryDump_getLength
(
    const PUSMemoryDump *This,
    TD_PUSNumberMemBlocks i
);

/**
 * Get the value of the checksum field for the i-th currently loaded block.
 * The block index i must lie in the interval [0, N-1] where N is the number
 * of currently loaded PUSMemoryDump_blocks(the value returned by method 
 * <code>getNumberBlocks</code>). If this condition is not satisfied, 
 * the return value is unpredictable.
 * @param i the block index
 * @return the length of the i-th currently loaded block
 */
unsigned short PUSMemoryDump_getChecksum
(
    const PUSMemoryDump *This,
    TD_PUSNumberMemBlocks i
);

/**
 * Set the memory block identifier for the dump packet.
 * Only values greater than zero are legal.
 * @see #update
 * @param memId the memory block identifier
 */
void PUSMemoryDump_setMemoryId(PUSMemoryDump *This, TD_PUSMemId memId);

/**
 * Get the memory block identifier for the dump packet.
 * @see #setMemId
 * @return the memory block identifier
 */
TD_PUSMemId PUSMemoryDump_getMemoryId(PUSMemoryDump *This);


#endif
