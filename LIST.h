// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

/**
 *  @file
 *
 *  @brief Platform LIST Library
 */

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

/**
 *  @addtogroup Platform_Library
 *
 *  @{
 */

/**
 *  @defgroup Platform_LIST LIST
 *
 *  @{
 */

#ifndef LIST_H_
    #define LIST_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

#include <stdint.h>

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

/**
 *  @brief LIST Operation Status
 *
 *  @enum LIST_Status_t
 */
typedef enum LIST_Status
{
    LIST_Status_Success = 0,     ///< Success
    LIST_Status_ArgumentInvalid, ///< Argument Invalid
    LIST_Status_NotSupported,    ///< Not Supported
    LIST_Status_Error,           ///< General Error
    LIST_Status_Empty,           ///< Empty
} LIST_Status_t;

/**
 * @brief List Node (Forward declaration)
 *
 * @struct LIST_Node_t
 */
typedef struct LIST_Node LIST_Node_t;

/**
 * @brief List Node
 *
 * @struct LIST_Node_t
 */
typedef struct LIST_Node
{
  /**
   *  @brief Next Node
   */
  LIST_Node_t * Next;

  /**
   *  @brief Previous Node
   */
  LIST_Node_t * Previous;
} LIST_Node_t;

/**
 * @brief List
 *
 * @struct LIST_t
 */
typedef struct LISTx
{
  /**
   *  @brief Head/start
   */
  LIST_Node_t * Head;

  /**
   *  @brief Tail/end
   */
  LIST_Node_t * Tail;
} LIST_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

/**
 * @brief Initialize list instance
 *
 * @note MUST BE called before using any LIST API
 *
 * @param[out] LISTx Instance
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_Initialize( LIST_t * LISTx );

/**
 * @brief Push a node into back of the list
 *
 * @param[in,out] LISTx Instance
 * @param[in]     Node  Node
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_PushBack( LIST_t * LISTx, LIST_Node_t * Node );

/**
 * @brief Pull a node from back of the list
 *
 * @param[in,out] LISTx Instance
 * @param[out]    Node  Node
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_PullBack( LIST_t * LISTx, LIST_Node_t ** Node );

/**
 * @brief Push a node into front of the list
 *
 * @param[in,out] LISTx Instance
 * @param[in]     Node  Node
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_PushFront( LIST_t * LISTx, LIST_Node_t * Node );

/**
 * @brief Pull a node from front of the list
 *
 * @param[in,out] LISTx Instance
 * @param[out]    Node  Node
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_PullFront( LIST_t * LISTx, LIST_Node_t ** Node );

/**
 * @brief Push a new node after a node of the list
 *
 * @param[in,out] LISTx Instance
 * @param[in]     Node  Node
 * @param[in]     New   New Node
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_PushAfter( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t * New );

/**
 * @brief Push a new node before a node of the list
 *
 * @param[in,out] LISTx Instance
 * @param[in]     Node  Node
 * @param[in]     New   New Node
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_PushBefore( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t * New );

/**
 * @brief Remove a node from the list
 *
 * @param[in,out] LISTx Instance
 * @param[in]     Node  Node
 *
 * @return LIST_Status_t
 */
LIST_Status_t LIST_Remove( LIST_t * LISTx, LIST_Node_t * Node );

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    /**
     *  @brief Version
     */
    extern const char LIST_VERSION[];

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* LIST_H_ */

/**
 *  @}
 *
 *  @}
 */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
