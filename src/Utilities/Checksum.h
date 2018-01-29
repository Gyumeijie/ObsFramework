//
//
// Checksum.h 
//
//
// Change Record:

/**
 * @file Checksum.h
 * Utility functions to compute and verify a 16-bits ISO checksum. The checksum algorithms are
 * as specified in appendix A.2 of the Packet Utilization Standard (issue of Jan.
 * 30-th 2003). A checksum is computed by calling function <code>doChecksum</code>.
 * It is verified by calling function <code>verifyChecksum</code>.
 * The checksum is computed or verified over items that
 * are treated as of type <code>unsigned char</code>. A checksum result is expressed as an
 * <code>unsigned short</code> where the leftmost byte of the result (CK1) is the least significant
 * byte of the return value of <code>doChecksum</code> and the rightmost byte (CK2) is the
 * most significant byte.
 * <p>
 * The variable where the inermediate quantities C0 and C1 are accumulated is defined
 * to be of type <code>int</code>. There is no check against an overflow in this
 * variable. This essentially puts a limit on the maximum length of the data stream
 * over which the checksum is computed.
 * <p>
 * The functions defined in this module do not conform to project-specific coding rule
 * PR3.3. They take as argument an array holding the items over which the checksum is to be
 * computer/verified. The alternative design is where the items are passed one by one and
 * intermediate results are stored internally to the module. This alternative would have
 * complied with PR3.3 but would also have been significantly slower for large chunks of data.
 */

static int C0;
static int C1;
static unsigned char CK1;
static unsigned char CK2;

/**
 * Compute the checksum.
 * The first argument is treated as an array of size n that holds the items over which
 * the checksum is to be computed. The return value of the function is the checksum value.
 * @param item the array holding the items that must be checksummed
 * @param n the number of items in the array 
 * @return the value of the checksum
 * @version 1.0
 * @author A. Pasetti
 */
unsigned short doChecksum(unsigned char *item, unsigned int n);

/**
 * Verify the checksum.
 * The first argument is treated as an array of size n that holds the items over which
 * the checksum is to be verified. Argument <code>checksum</code> holds the expected
 * checksum value. The return value of the function indicates whether the checksum
 * is verified (return value of true) or not (return value of false).
 * @param item the array holding the items that must be checksum verified
 * @param n the number of items in the array 
 * @param checksum the value of the checksum
 * @return the flag indicating whether the check sum is verified
 * @version 1.0
 * @author A. Pasetti
 */
bool verifyChecksum(unsigned char *item, unsigned int n, unsigned short checksum);
