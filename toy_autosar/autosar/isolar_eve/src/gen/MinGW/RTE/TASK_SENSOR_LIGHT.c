/** @file     TASK_SENSOR_LIGHT.c
  * 
  * @brief    Task TASK_SENSOR_LIGHT body
  * 
  * @note     AUTOMATICALLY GENERATED FILE! DO NOT EDIT!
  * 
  * @note     Generated by ETAS GmbH  RTA-RTE v5.8.4  (R4.0 backend version: v7.8.7 (Build 46772))
  */

#define RTE_CORE

#include "Rte_Const.h"
#if !defined(RTE_VENDOR_MODE)
#pragma message "Compiling an individual task file but RTE_VENDOR_MODE not defined. Compiling a stale file?"
#endif /* !defined(RTE_VENDOR_MODE) */
#if defined(RTE_USE_TASK_HEADER)
#include "TASK_SENSOR_LIGHT.h"
#else /* defined(RTE_USE_TASK_HEADER) */
#include "Os.h"
#endif /* defined(RTE_USE_TASK_HEADER) */
#if defined(RTE_REQUIRES_IOC)
#include "Ioc.h"
#endif /* defined(RTE_REQUIRES_IOC) */
#include "Rte.h"
#include "Rte_Intl.h"
#include "Rte_Type.h"
#include "Rte_DataHandleType.h"

/* Runnable entity prototypes */
#define SENSOR_LIGHT_START_SEC_CODE
#include "SENSOR_LIGHT_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(void, SENSOR_LIGHT_CODE) RE_LIGHT(void);
#define SENSOR_LIGHT_STOP_SEC_CODE
#include "SENSOR_LIGHT_MemMap.h" /*lint !e537 permit multiple inclusion */

#define RTE_START_SEC_TASKBODY
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
TASK(TASK_SENSOR_LIGHT)
{
   /* Box: Implicit Buffer Initialization begin */
   /* Box: Implicit Buffer Initialization end */
   /* Box: Implicit Buffer Fill begin */
   /* Box: Implicit Buffer Fill end */
   {
      /* Box: CPT_SENSOR_LIGHT begin */
      RE_LIGHT();
      /* Box: CPT_SENSOR_LIGHT end */
   }
   /* Box: Implicit Buffer Flush begin */
   /* Box: Implicit Buffer Flush end */
   TerminateTask();
} /* TASK_SENSOR_LIGHT */
#define RTE_STOP_SEC_TASKBODY
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

