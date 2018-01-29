//
//
// ClassId.h
//

/**
 * @file ClassId.h 
 * This file defines the class identifiers for all the classes defined by the OBS
 * Framework. Class identifiers are associated to all the classes that are
 * derived from class <code>CC_RootObject</code>. The name of the identifier is 
 * formed by the prefix "ID_" followed by the name of the class.
 * <p>
 * One "fictitious" class identifier is added for module <code>Checksum</code>. 
 * Although this module is not implemented as a class, a class identifier is still
 * required because a test case is devoted to this class (class <code>TestcaseChecksum_1</code>)
 * and a class identifier is required to construct the test case identifier.
 * @see CC_RootObject
 */

#ifndef CLASSID_H
#define CLASSID_H

#include "BasicTypes.h"

#define ID_ROOTOBJECT                       (TD_ClassId)1   //@- Class Identifier
#define ID_EVENT                            (TD_ClassId)2   //@- Class Identifier
#define ID_EVENTREPOSITORY                  (TD_ClassId)3   //@- Class Identifier
#define ID_PUSEVENTREPOSITORY               (TD_ClassId)4   //@- Class Identifier

#define ID_DUMMYOBSCLOCK                    (TD_ClassId)10  //@- Class Identifier

#define ID_DATAITEM                         (TD_ClassId)20  //@- Class Identifier
#define ID_RAWDATAITEM                      (TD_ClassId)21  //@- Class Identifier

#define ID_DUMMYTRACER                      (TD_ClassId)30  //@- Class Identifier
#define ID_TESTTRACER                       (TD_ClassId)31  //@- Class Identifier

#define ID_DUMMYPUNCTUALACTION              (TD_ClassId)40  //@- Class Identifier
#define ID_DUMMYCONDITIONALPUNCTUALACTION   (TD_ClassId)41  //@- Class Identifier
#define ID_SIMPLEPUNCTUALACTIONMODEMANAGER  (TD_ClassId)42  //@- Class Identifier
#define ID_PUNCTUALACTIONMANAGER            (TD_ClassId)43  //@- Class Identifier
#define ID_CYCLINGPUNCTUALACTIONMODEMANAGER (TD_ClassId)44  //@- Class Identifier

#define ID_FSMEVENT                         (TD_ClassId)50  //@- Class Identifier
#define ID_FROMFSMEVENT                     (TD_ClassId)51  //@- Class Identifier
#define ID_DUMMYFSMSTATE                    (TD_ClassId)52  //@- Class Identifier
#define ID_FSM                              (TD_ClassId)53  //@- Class Identifier
#define ID_DUMMYCONFIGURABLEFSMSTATE        (TD_ClassId)54  //@- Class Identifier
#define ID_NESTEDFSMACTIVATOR               (TD_ClassId)55  //@- Class Identifier
#define ID_NESTEDFSMACTIVATORWITHENDSTATE   (TD_ClassId)56  //@- Class Identifier
#define ID_NESTEDFSMACTIVATORWITHEXITCHECK  (TD_ClassId)57  //@- Class Identifier
#define ID_UNSTABLEFSMSTATE                 (TD_ClassId)58  //@- Class Identifier

#define ID_BASICDATABASE                    (TD_ClassId)60  //@- Class Identifier
#define ID_SAMPLER1DATABASE                 (TD_ClassId)61  //@- Class Identifier
#define ID_SAMPLER2DATABASE                 (TD_ClassId)62  //@- Class Identifier
#define ID_SAMPLER3DATABASE                 (TD_ClassId)63  //@- Class Identifier
#define ID_DUMMYDATABASE                    (TD_ClassId)64  //@- Class Identifier

#define ID_DUMMYTELECOMMAND                 (TD_ClassId)80  //@- Class Identifier
#define ID_DUMMYTELECOMMANDLOADER           (TD_ClassId)81  //@- Class Identifier
#define ID_TELECOMMANDMANAGER               (TD_ClassId)82  //@- Class Identifier
#define ID_DUMMYCRITICALTELECOMMAND         (TD_ClassId)83  //@- Class Identifier
#define ID_DUMMYPUSTELECOMMAND              (TD_ClassId)84  //@- Class Identifier
#define ID_BASICPUSTCLOADER                 (TD_ClassId)85  //@- Class Identifier

#define ID_SIMPLECHANGEPROFILE              (TD_ClassId)90  //@- Class Identifier
#define ID_STUCKDATAPROFILE                 (TD_ClassId)91  //@- Class Identifier
#define ID_DELTAPROFILE                     (TD_ClassId)92  //@- Class Identifier
#define ID_FORBIDDENVALUEPROFILE            (TD_ClassId)93  //@- Class Identifier
#define ID_INRANGEPROFILE                   (TD_ClassId)94  //@- Class Identifier
#define ID_OUTOFRANGEPROFILE                (TD_ClassId)95  //@- Class Identifier
#define ID_NULLPROFILE                      (TD_ClassId)96  //@- Class Identifier
#define ID_PROFILELIST                      (TD_ClassId)97  //@- Class Identifier

#define ID_DUMMYMODEMANAGER                 (TD_ClassId)100 //@- Class Identifier

#define ID_DUMMYMANOEUVRE                   (TD_ClassId)110 //@- Class Identifier
#define ID_DUMMYCONFIGURABLEMANOEUVRE       (TD_ClassId)111 //@- Class Identifier
#define ID_TESTPUSCONFIGURABLEMANOEUVRE     (TD_ClassId)112 //@- Class Identifier
#define ID_MANOEUVREMANAGER                 (TD_ClassId)113 //@- Class Identifier
#define ID_MANOEUVREPUNCTUALACTION          (TD_ClassId)114 //@- Class Identifier

#define ID_DUMMYCOPYCONTROLBLOCK            (TD_ClassId)120 //@- Class Identifier
#define ID_DUMMYPOINTERCONTROLBLOCK         (TD_ClassId)121 //@- Class Identifier
#define ID_DUMMYDATAITEMCONTROLBLOCK        (TD_ClassId)122 //@- Class Identifier
#define ID_DUMMYDATAPOOLCONTROLBLOCK        (TD_ClassId)123 //@- Class Identifier
#define ID_CONTROLACTION                    (TD_ClassId)124 //@- Class Identifier
#define ID_CONTROLLIST                      (TD_ClassId)125 //@- Class Identifier

#define ID_BASICRECONFIGURER                (TD_ClassId)130 //@- Class Identifier

#define ID_MATLABCOPYPID                    (TD_ClassId)140 //@- Class Identifier
#define ID_MATLABPOINTERPID                 (TD_ClassId)141 //@- Class Identifier
#define ID_MATLABDATAITEMPID                (TD_ClassId)142 //@- Class Identifier
#define ID_MATLABDATAPOOLPID                (TD_ClassId)143 //@- Class Identifier

#define ID_NULLRECOVERYACTION               (TD_ClassId)150 //@- Class Identifier
#define ID_DUMMYRECOVERYACTION              (TD_ClassId)151 //@- Class Identifier

#define ID_FDIRCHECK                        (TD_ClassId)160 //@- Class Identifier

#define ID_ROOTOBJECTSTACK                  (TD_ClassId)170 //@- Class Identifier
#define ID_INTSTACK                         (TD_ClassId)171 //@- Class Identifier

#define ID_BASICDATAPOOL                    (TD_ClassId)180 //@- Class Identifier
#define ID_SAMPLEFULLDATAPOOL               (TD_ClassId)181 //@- Class Identifier
#define ID_SAMPLEMONITOREDDATAPOOL          (TD_ClassId)182 //@- Class Identifier
#define ID_DATAPOOLMONITOR                  (TD_ClassId)183 //@- Class Identifier
#define ID_DUMMYDATAPOOL                    (TD_ClassId)184 //@- Class Identifier

#define ID_DUMMYTELEMETRYSTREAM             (TD_ClassId)190 //@- Class Identifier
#define ID_PUSTMLOGGER                      (TD_ClassId)191 //@- Class Identifier

#define ID_DUMMYPUSTCVERIFICATIONPACKET     (TD_ClassId)200 //@- Class Identifier
#define ID_PUSDATAREPORTINGPACKET           (TD_ClassId)201 //@- Class Identifier
#define ID_PUSDATAREPORTINGPACKETFACTORY    (TD_ClassId)202 //@- Class Identifier
#define ID_PUSTCVERIFICATIONPACKET          (TD_ClassId)203 //@- Class Identifier
#define ID_PUSMEMORYDUMPOFFSET              (TD_ClassId)204 //@- Class Identifier
#define ID_PUSMEMORYDUMPABSOLUTE            (TD_ClassId)205 //@- Class Identifier

#define ID_PUSCONTROLDATAREPORTING          (TD_ClassId)220 //@- Class Identifier
#define ID_PUSCLEARDATAREPORTING            (TD_ClassId)221 //@- Class Identifier
#define ID_PUSREQUESTDATAREPORTING          (TD_ClassId)222 //@- Class Identifier
#define ID_PUSDEFINEDATAREPORTING           (TD_ClassId)223 //@- Class Identifier
#define ID_PUSMEMORYLOADOFFSET              (TD_ClassId)224 //@- Class Identifier
#define ID_PUSMEMORYLOADABSOLUTE            (TD_ClassId)225 //@- Class Identifier
#define ID_PUSDUMPMEMORYOFFSET              (TD_ClassId)226 //@- Class Identifier
#define ID_PUSDUMPMEMORYABSOLUTE            (TD_ClassId)227 //@- Class Identifier
#define ID_TESTPUSTELECOMMAND               (TD_ClassId)228 //@- Class Identifier

#define ID_TELEMETRYPACKETFACTORY           (TD_ClassId)250 //@- Class Identifier
#define ID_TELECOMMANDFACTORY               (TD_ClassId)251 //@- Class Identifier
#define ID_MANOEUVREFACTORY                 (TD_ClassId)252 //@- Class Identifier

#define ID_DATAITEM16TMWORD                 (TD_ClassId)260  //@- Class Identifier
#define ID_CYCLEDATAITEM16TMSTREAM          (TD_ClassId)261  //@- Class Identifier
#define ID_SIMPLETELEMETRYMODEMANAGER       (TD_ClassId)262  //@- Class Identifier
#define ID_TELEMETRYMANAGER                 (TD_ClassId)263  //@- Class Identifier
#define ID_FILETELEMETRYSTREAM              (TD_ClassId)264  //@- Class Identifier
#define ID_DUMMYTELEMETRYITEM               (TD_ClassId)265  //@- Class Identifier
#define ID_DUMMYPUSTELEMETRYPACKET          (TD_ClassId)266  //@- Class Identifier
#define ID_BYTEARRAYTELEMETRYSTREAM         (TD_ClassId)267  //@- Class Identifier
#define ID_CYCLINGTELEMETRYMODEMANAGER      (TD_ClassId)268  //@- Class Identifier
#define ID_PUSTELEMETRYMODEMANAGER          (TD_ClassId)269  //@- Class Identifier
#define ID_BASICPUSTMSTREAM                 (TD_ClassId)270  //@- Class Identifier


#define ID_CHECKSUM                         (TD_ClassId)400 //@- Class Identifier

#endif
