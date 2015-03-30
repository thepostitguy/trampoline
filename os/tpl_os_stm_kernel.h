/*
 * @file tpl_os_stm.h
 *
 * @section desc File description
 *
 * Trampoline STM header file
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Copyright ESEO for function and data structures documentation
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date: 2015-03-02 16:00:39 +0100 (lun., 02 mars 2015) $
 * $Rev: 0 $
 * $Author: audrey $
 * $URL: http://trampoline.rts-software.org/svn/trunk/os/tpl_os_stm.h $
 */
//#include "tpl_compiler.h"
#include "tpl_os_error.h" // pour core_id

//#include "tpl_os_stm.h"
#include "tpl_os_stm_internal_types.h"

/**
 * Array of all transaction descriptors (one per core)
 *
  */
extern VAR(tpl_stm_tx_descriptor, OS_APPL_DATA) trans_table[NUMBER_OF_CORES];

/**
 * Array of all STM-HRT objects
 *
  */
extern VAR(tpl_stm_object, OS_APPL_DATA) object_table[NUMBER_OF_OBJECTS];

/**
 * Array of all transaction descriptors of writers
 *
  */
extern P2VAR(tpl_stm_tx_descriptor, AUTOMATIC, OS_APPL_DATA) writer_table[NUMBER_OF_OBJECTS];


/********************************************************************************
*				Macros						*
*										*
********************************************************************************/						
#define INSTANCE(status)			(status >> 2) & 0xFFFFFFFF
#define STATUS(status)				(status & 3)

#define CURRENT_OBJECT_POS(concurrency_vector)	((concurrency_vector >> 30) & 1)
#define READ_VECTOR(concurrency_vector)		((concurrency_vector & NUMBER_OF_CORES))

#define POW2_NUMBER_OF_CORES (1 << 8)
#define FAIL_VECTOR(concurrency_vector)		((concurrency_vector >> 8) & (POW2_NUMBER_OF_CORES-1))

#define SET_UPDATE_FLAG(concurrency_vector)	(concurrency_vector |  (1 << 31)) 
#define UPDATE_FLAG(concurrency_vector)	((concurrency_vector >> 31) & 1)

#define SET_ACCESS_VECTOR(access_vector, object_id) 	(access_vector | (1 << object_id))




/********************************************************************************
*				Functions					*
*										*
********************************************************************************/
/**
 * @internal
 *
 * Displays on screen the message given as an argument
 *
 * @param   msg     message to display
 *
 * @retval  E_OK        no error
 *
 */
FUNC(StatusType, OS_CODE) tpl_screen_display_service(
  P2CONST(char, AUTOMATIC, OS_APPL_DATA) msg);

/*
 * tpl_stm_begin_read_tx_service
 *
 * Initializes a read-set transaction
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_begin_read_tx_service();

/*
 * tpl_stm_begin_write_tx_service
 *
 * Initializes a write-set transaction on the core given as an argument
 *
 * tx:  Transaction descriptor
 *
 * coreId:  Core on which the write-set transaction begins
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_begin_write_tx_service();

/*
 * tpl_stm_end_read_tx_service
 *
 * Ends a read-set transaction 
 *
 * tx:  Transaction descriptor
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_end_read_tx_service();

/*
 * tpl_stm_end_write_tx_service
 *
 * Ends a write-set transaction
 *
 * tx:  Transaction descriptor
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_end_write_tx_service();

/*
 * tpl_stm_open_read_object_service
 *
 * A read-set transaction opens for reading a given object
 *
 * object_id:  Object identifier
 *
 * data_type:  Data type
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_open_read_object_service(CONST(ObjectType, AUTOMATIC) object_id, P2VAR(void, AUTOMATIC, OS_APPL_DATA) data_type);

/*
 * tpl_stm_open_write_object_service
 *
 * A write-set transaction opens for writing a given object on a given
 * core
 *
 * tx:  Transaction descriptor
 *
 * coreId:  Core on which the write-set transaction opens the object
 *
 * dataId:  Data identifier
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_open_write_object_service(P2VAR(void, AUTOMATIC, OS_APPL_DATA) data);

/*
 * tpl_stm_commit_read_tx_service
 *
 * A read-set transaction tries to commit on a given core
 *
 * tx:  Transaction descriptor
 *
 * instance:  Transaction instance number
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_commit_read_tx_service();

/*
 * tpl_stm_commit_write_tx_service
 *
 * A write-set transaction tries to commit on a given core
 *
 * tx:  Transaction descriptor
 *
 * Return value:
 * E_OK:    No error (Standard & Extended)
 * 
 */
FUNC(StatusType, OS_CODE) tpl_stm_commit_write_tx_service();

