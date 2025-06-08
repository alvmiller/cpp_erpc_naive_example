#ifndef _ERPC_CONFIG_H_
#define _ERPC_CONFIG_H_

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

#define ERPC_ALLOCATION_POLICY_DYNAMIC (0U)
#define ERPC_ALLOCATION_POLICY_STATIC (1U)
#define ERPC_THREADS_NONE (0U)
#define ERPC_THREADS_PTHREADS (1U)
#define ERPC_THREADS_FREERTOS (2U)
#define ERPC_THREADS_ZEPHYR (3U)
#define ERPC_THREADS_MBED (4U)
#define ERPC_THREADS_WIN32 (5U)
#define ERPC_THREADS_THREADX (6U)
#define ERPC_NOEXCEPT_DISABLED (0U)
#define ERPC_NOEXCEPT_ENABLED (1U)
#define ERPC_NESTED_CALLS_DISABLED (0U)
#define ERPC_NESTED_CALLS_ENABLED (1U)
#define ERPC_NESTED_CALLS_DETECTION_DISABLED (0U)
#define ERPC_NESTED_CALLS_DETECTION_ENABLED (1U)
#define ERPC_MESSAGE_LOGGING_DISABLED (0U)
#define ERPC_MESSAGE_LOGGING_ENABLED (1U)
#define ERPC_TRANSPORT_MU_USE_MCMGR_DISABLED (0U)
#define ERPC_TRANSPORT_MU_USE_MCMGR_ENABLED (1U)
#define ERPC_PRE_POST_ACTION_DISABLED (0U)
#define ERPC_PRE_POST_ACTION_ENABLED (1U)
#define ERPC_PRE_POST_ACTION_DEFAULT_DISABLED (0U)
#define ERPC_PRE_POST_ACTION_DEFAULT_ENABLED (1U)
#define ERPC_THREADS (ERPC_THREADS_PTHREADS)
#define ERPC_DEFAULT_BUFFER_SIZE (4096U)

#endif // _ERPC_CONFIG_H_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
