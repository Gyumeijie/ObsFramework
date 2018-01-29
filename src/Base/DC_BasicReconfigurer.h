//
//
// DC_BasicReconfigurer.h
//


#ifndef DC_BASICRECONFIGURER_H
#define DC_BASICRECONFIGURER_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * <i>Reconfiguration manager</i> that implements a basic reconfiguration
 * policy independent of any <i>reconfiguration functionality</i>.
 * This component is useful under the following conditions<ul>
 * <li>There are N independent
 * implementations of the reconfigurable functionality to which there
 * correspond N <i>configurations</i> of the configuration manager.</li>
 * <li>At any given time, one configuration is designated by the
 * reconfiguration manager to be the <i>active configuration</i></li>.
 * <li>Each configuration is either <i>healthy</i> or
 * <i>unhealthy</i></li>
 * <li>When the reconfiguration manager receives a <i>reconfigure</i>
 * request, it checks whether any of the non-active configurations are
 * healthy and, if so, it selects one of these configurations as the
 * new active configuration. The previously active configuration is
 * marked as "unhealthy"</li>
 * </ul>
 * This component implements the management of the configurations but
 * it does not make any assumptions about what the configurations
 * represent. A configuration is simply represented by an integer
 * that can take a value in the interval [0, N-1]. The health status
 * is represented by a boolean with the value true representing
 * "healthy".
 * <p>
 * Reconfigurations(i.e. changes in the active configuration) are
 * recorded through an event report.
 * <p>
 * It is possible to force the healthy/unhealthy state of a
 * configuration and it is possible to enable/disable reconfigurations.
 * <p>
 * This class can be used as the base class for reconfiguration
 * managers that are responsible for managing reconfigurations across
 * concrete implementations of a specific functionality. Or it can be
 * used as a "helper class" for such a concrete reconfiguration manager.
 * <p>
 * Method <code>reconfigure</code> is implemented as a virtual method
 * to allow easy implementations of alternative reconfiguration policies.
 * <p>
 * Some of the methods defined by the class take as a parameter
 * an integer index i that designates a configuration. Run-time
 * checks on the legality of the index
 * are only performed where errors might corrupt internal data
 * structures(typically, during write accesses). In other cases,
 * responsibility for ensuring the legality of the index is left
 * to the caller.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 */
#define TYPE_DC_BASICRECONFIGURER "dc_basicreconfigurer"

void DC_BasicReconfigurer_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_BasicReconfigurer {
    CC_RootObject parent;

    TD_Config numberOfConfig;         // number of configurations
    TD_Config active;    // currently active configuration
    bool enableStatus;   // reconfiguration enable status
    bool *isHealthy;     // isHealthy[i] is the health status of the i-th configuration
};


struct DC_BasicReconfigurerClass {
    CC_RootObjectClass parent_class;
 
    void (*reconfigure)(void *obj);
};


#define DC_BASICRECONFIGURER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_BasicReconfigurerClass, obj, TYPE_DC_BASICRECONFIGURER)

#define DC_BASICRECONFIGURER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_BasicReconfigurerClass, klass, TYPE_DC_BASICRECONFIGURER)

#define DC_BASICRECONFIGURER(obj) \
        OBJECT_CHECK(DC_BasicReconfigurer, obj, TYPE_DC_BASICRECONFIGURER)


DC_BasicReconfigurer* DC_BasicReconfigurer_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the number of configurations controlled by this reconfiguration
 * manager.
 * This is an initialization method. It should only be called once.
 * The number of configurations must be
 * greater than zero.
 * A call to this method causes the component to allocate the memory it
 * needs for its internal data structures. All configurations are
 * initialized to "healthy" and the configuration with index zero is
 * designated as the active configuration.
 * @param nOfConfig the number of configurations
 */
void DC_BasicReconfigurer_setNumberOfConfigurations
(
    DC_BasicReconfigurer *This,
    TD_Config nOfConfig
);

/**
 * Set the health status of the i-th configuration.
 * The parameter i must be in the range [0, N-1] where N is the total
 * number of configurations.
 * A check is performed to verify that the value of i is legal. If it is
 * not, event EVT_ILLEGAL_CONFIG is generated.
 * @see TD_EventType
 * @param i the configuration index
 * @param healthStatus the health status of the i-th configuration
 */
void DC_BasicReconfigurer_setHealthStatus
(
    DC_BasicReconfigurer *This, 
    TD_Config i, 
    bool healthStatus
);

/**
 * Return the health status of the i-th configuration.
 * The parameter i must be in the range [0, N-1] where N is the total
 * number of configurations but no check is performed on the legality
 * of i.
 * @param i the configuration index
 * @return true if the i-th configuration is healthy, false otherwise
 */
bool DC_BasicReconfigurer_isConfigurationHealthy
(
    const DC_BasicReconfigurer *This,
    TD_Config i
);

/**
 * Set the active configuration.
 * After calling this method, the active configuration is guaranteed
 * to be equal to the value of the parameter <code>active</code>. This
 * is the case independently of whether or not reconfiguration are
 * enabled or disabled and irrespective of the health status of the
 * target configuration.
 * <p>
 * Note that forcing the active configuration will often be equivalent to
 * performing a DC_BasicReconfigurer_reconfiguration(if the original active configuration
 * is different from the target configuration specified by this method).
 * If this is the case, then an event report of type EVT_RECONFIG
 * is generated.
 * <p>
 * Note also that no check is performed upon the health status of the
 * target configuration specified by this method. Execution of this method
 * may thus result in an unhealthy configuration being the active
 * configuration.
 * <p>
 * The parameter i must be in the range [0, N-1] where N is the total
 * number of configurations.
 * A check is performed to verify that the value of i is legal. If it is
 * not, event EVT_ILLEGAL_CONFIG is generated.
 * @see TD_EventType
 * @param activeConfig the new active configuration
 */
void DC_BasicReconfigurer_setActive
(
    DC_BasicReconfigurer *This,
    TD_Config activeConfig
);

/**
 * Enable/disable all reconfigurations.
 * @see #reconfigure
 * @param enabled the transition are disabled if false, enabled if true
 */
void DC_BasicReconfigurer_setEnabled
(
    DC_BasicReconfigurer *This, 
    bool enabled
);

/**
 * Check whether reconfigurations are enabled.
 * @see #setEnabled
 * @return true if reconfigurations are enabled, false otherwise
 */
bool DC_BasicReconfigurer_isEnabled(const DC_BasicReconfigurer *This);

/**
 * Return the currently active configuration.
 * @return the currently active configuration
 */
TD_Config DC_BasicReconfigurer_getActive(const DC_BasicReconfigurer *This);

/**
 * Return the number of configurations.
 * @return the number of configurations
 */
TD_Config DC_BasicReconfigurer_getNumberOfConfigurations
(
    const DC_BasicReconfigurer *This
);

/**
 * Enable all reconfigurations, set all configuration status to "healthy", 
 * set the active configuration equal to configuration 0.
 */
void DC_BasicReconfigurer_reset(DC_BasicReconfigurer *This);


#endif
