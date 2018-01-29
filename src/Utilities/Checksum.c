//
//
// Checksum.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Utilities/Checksum.h"

unsigned short doChecksum(unsigned char *item, unsigned int n) {
    assert(item != pNULL);
    assert(n > 0);

    C0 = 0;
    C1 = 0;

    for (unsigned int i=0; i<n; i++) {
        C0 = C0 + (int)item[i];
        C1 = C1 + C0;
    }

    CK1 = (unsigned char)(255-((C0+C1)%255));
    CK2 = (unsigned char)(C1%255);

    if (CK1 == 0) CK1 = 255;

    if (CK2 == 0) CK2 = 255;

    return (CK1*256 + CK2);
}

bool verifyChecksum(unsigned char *item, unsigned int n, unsigned short checksum) {
    assert(item != pNULL);
    assert(n > 0);

    CK1 = (unsigned char)(checksum/256);
    CK2 = (unsigned char)(checksum%256);

    if (((CK1 == 0)&&(CK2 != 0)) || ((CK1 != 0)&&(CK2 == 0))) return false;

    C0 = 0;
    C1 = 0;

    for (unsigned int i=0; i<n; i++) {
        C0 = C0 + (unsigned short)item[i];
        C1 = C1 + C0;
    }

    C0 = C0 + CK1;
    C1 = C1 + C0;

    C0 = C0 + CK2;
    C1 = C1 + C0;

    if (((C0%255) == 0) && ((C1%255) == 0)) {
        return true;
    } else {
        return false;
    }
}
