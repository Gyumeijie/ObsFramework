//
//
// TelecommandLoader.h
//


#ifndef TELECOMMANDLOADER_H
#define TELECOMMANDLOADER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all telecommand loaders are derived.
 * A telecommand loader is an object that is responsible for receiving
 * telecommands, decoding them and for
 * constructing the objects of type <CODE>Telecommand</CODE> that represent
 * the telecommand inside the application software.
 * <p>
 * Telecommand loaders must load a telecommand object in the telecommand
 * manager after having constructed it.
 * For this reason, they have the telecommand manager as a plug-in component
 * and this class declares the corresponding method to load the telecommand
 * manager.
 * <p>
 * During the process of constructing a telecommand object, the telecommand
 * loader may need to allocate
 * resources(typically memory to hold the telecommand object).
 * These resources must be released after the telecommand has been executed.
 * For this reason, this class declares a <CODE>release</CODE> method
 * that must be called by the
 * telecommand manager after it has executed a telecommand and that triggers
 * the release of the resources associated to the telecommand object.
 * <p>
 * Telecommand loaders are <i>activated</i> when a new telecommand has
 * (potentially) been received.
 * Depending on the implementation, this activation could be in response to
 * the arrival of an interrupt
 * signaling the actual reception of a new telecommand or it could be done
 * periodically to direct the
 * telecommand loader to check whether a new telecommand has arrived.
 * <p>
 * This is an abstract class. Concrete telecommand loaders are obtained by
 * deriving this class.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Telecommand
 */
#define TYPE_TELECOMMANDLOADER "telecommandloader"

void TelecommandLoader_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TelecommandLoader {
    CC_RootObject parent;

    CC_TelecommandManager *pTelecommandManager;
};


struct TelecommandLoaderClass {
    CC_RootObjectClass parent_class;
 
    void (*activate)(void *obj);
    void (*release)(void *obj, Telecommand *pTelecommand);
};


#define TELECOMMANDLOADER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TelecommandLoaderClass, obj, TYPE_TELECOMMANDLOADER)

#define TELECOMMANDLOADER_CLASS(klass) \
        OBJECT_CLASS_CHECK(TelecommandLoaderClass, klass, TYPE_TELECOMMANDLOADER)

#define TELECOMMANDLOADER(obj) \
        OBJECT_CHECK(TelecommandLoader, obj, TYPE_TELECOMMANDLOADER)


TelecommandLoader* TelecommandLoader_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the telecommand manager as a plug-in component.
 * A telecommand loader needs access to the telecommand manager because
 * it must load newly created
 * telecommand objects in the telecommand manager.
 * @param pTcManager the telecommand manager
 */
void TelecommandLoader_setTelecommandManager
(
    TelecommandLoader *This, 
    CC_TelecommandManager *pTcManager
);

/**
 * Getter method for the telecommand manager plug-in component.
 * @see #setTelecommandManager
 * @return the telecommand manager
 */
CC_TelecommandManager* TelecommandLoader_getTelecommandManager
(
    TelecommandLoader *This
);


#endif
