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

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include <stddef.h>

#include "LIST.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

LIST_Status_t LIST_Initialize( LIST_t * LISTx )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        LISTx->Head = NULL;
        LISTx->Tail = NULL;
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_IsEmpty( LIST_t * LISTx )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( ( LISTx->Head != NULL ) || ( LISTx->Tail != NULL ) )
        {
            Status = LIST_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PushBack( LIST_t * LISTx, LIST_Node_t * Node )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( ( LISTx == NULL ) || ( Node == NULL ) )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( LIST_Remove( LISTx, Node ) == LIST_Status_Success )
        {
            // @note Node was already in the list and has been removed to be pushed into the right place
        }

        LIST_Node_t * Tail = LISTx->Tail;
        LIST_Node_t * Next = Tail ? Tail->Next : NULL;

        if ( Next != NULL )
        {
            Next->Previous = Node;
        }

        if ( Tail != NULL )
        {
            Tail->Next = Node;
        }

        Node->Next = Next;
        Node->Previous = Tail;
        LISTx->Tail = Node;

        if ( LISTx->Head == NULL )
        {
            LISTx->Head = Node;
        }
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PullBack( LIST_t * LISTx, LIST_Node_t ** Node )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( ( LISTx == NULL ) || ( Node == NULL ) )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( LISTx->Tail == NULL )
        {
            Status = LIST_Status_Empty;
            break;
        }

        LIST_Node_t * Tail = LISTx->Tail;
        LIST_Node_t * Next = Tail ? Tail->Next : NULL;
        LIST_Node_t * Previous = Tail ? Tail->Previous : NULL;

        if ( Next != NULL )
        {
            Next->Previous = Previous;
        }

        if ( Previous != NULL )
        {
            Previous->Next = Next;
        }

        LISTx->Tail = Previous;

        if ( LISTx->Head == Tail )
        {
            LISTx->Head = Previous;
        }

        Tail->Next = NULL;
        Tail->Previous = NULL;

        *Node = Tail;
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PushFront( LIST_t * LISTx, LIST_Node_t * Node )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Node == NULL )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( LIST_Remove( LISTx, Node ) == LIST_Status_Success )
        {
            // @note Node was already in the list and has been removed to be pushed into the right place
        }

        LIST_Node_t * Head = LISTx->Head;
        LIST_Node_t * Previous = Head ? Head->Previous : NULL;

        if ( Head != NULL )
        {
            Head->Previous = Node;
        }

        if ( Previous != NULL )
        {
            Previous->Next = Node;
        }

        Node->Next = Head;
        Node->Previous = Previous;
        LISTx->Head = Node;

        if ( LISTx->Tail == NULL )
        {
            LISTx->Tail = Node;
        }
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PullFront( LIST_t * LISTx, LIST_Node_t ** Node )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Node == NULL )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( LISTx->Head == NULL )
        {
            Status = LIST_Status_Empty;
            break;
        }

        LIST_Node_t * Head = LISTx->Head;
        LIST_Node_t * Next = Head ? Head->Next : NULL;
        LIST_Node_t * Previous = Head ? Head->Previous : NULL;

        if ( Next != NULL )
        {
            Next->Previous = Previous;
        }

        if ( Previous != NULL )
        {
            Previous->Next = Next;
        }

        LISTx->Head = Next;

        if ( LISTx->Tail == Head )
        {
            LISTx->Tail = Next;
        }

        Head->Next = NULL;
        Head->Previous = NULL;

        *Node = Head;
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PushAfter( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t * New )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Node == NULL || New == NULL || Node == New )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( LIST_Remove( LISTx, New ) == LIST_Status_Success )
        {
            // @note New was already in the list and has been removed to be pushed into the right place
        }

        LIST_Node_t * Target = LISTx->Head;
        while ( ( Target != NULL ) && ( Target != Node ) )
        {
            Target = Target->Next;
        }

        if ( Target == NULL )
        {
            Status = LIST_Status_Error;
            break;
        }

        New->Previous = Target;
        New->Next = Target->Next;

        Target->Next = New;

        if ( Target == LISTx->Tail )
        {
            LISTx->Tail = New;
        }
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PushBefore( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t * New )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Node == NULL || New == NULL || Node == New )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( LIST_Remove( LISTx, New ) == LIST_Status_Success )
        {
            // @note New was already in the list and has been removed to be pushed into the right place
        }

        LIST_Node_t * Target = LISTx->Head;
        while ( ( Target != NULL ) && ( Target != Node ) )
        {
            Target = Target->Next;
        }

        if ( Target == NULL )
        {
            Status = LIST_Status_Error;
            break;
        }

        New->Next = Target;
        New->Previous = Target->Previous;

        Target->Previous = New;

        if ( Target == LISTx->Head )
        {
            LISTx->Head = New;
        }
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_Remove( LIST_t * LISTx, LIST_Node_t * Node )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Node == NULL )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( LIST_IsEmpty( LISTx ) == LIST_Status_Success )
        {
            Status = LIST_Status_Empty;
            break;
        }

        LIST_Node_t * Target = LISTx->Head;
        while ( ( Target != NULL ) && ( Target != Node ) )
        {
            Target = Target->Next;
        }

        if ( Target == NULL )
        {
            Status = LIST_Status_Error;
            break;
        }

        LIST_Node_t * Previous = Target->Previous;
        LIST_Node_t * Next = Target->Next;

        if ( Previous )
        {
            Previous->Next = Next;
        }

        if ( Next )
        {
            Next->Previous = Previous;
        }

        Target->Next = NULL;
        Target->Previous = NULL;

        if ( Target == LISTx->Head )
        {
            LISTx->Head = Next;
        }

        if ( Target == LISTx->Tail )
        {
            LISTx->Tail = Previous;
        }
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PeekNext( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t ** Next )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Next == NULL )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( ( LISTx->Head != LISTx->Tail ) && ( ( LISTx->Head == NULL ) || ( LISTx->Tail == NULL ) ) )
        {
            Status = LIST_Status_Error;
            break;
        }

        if ( ( LISTx->Head == LISTx->Tail ) && ( LISTx->Head == NULL ) )
        {
            Status = LIST_Status_Empty;
            break;
        }

        LIST_Node_t * Target = LISTx->Head;
        if ( Node != NULL )
        {
            while ( ( Target != NULL ) && ( Target != Node ) )
            {
                Target = Target->Next;
            }

            if ( Target == NULL )
            {
                Status = LIST_Status_Error;
                break;
            }

            Target = Target->Next;
        }

        *Next = Target;
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PeekPrevious( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t ** Previous )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Previous == NULL )
        {
            Status = LIST_Status_ArgumentInvalid;
            break;
        }

        if ( ( LISTx->Head != LISTx->Tail ) && ( ( LISTx->Head == NULL ) || ( LISTx->Tail == NULL ) ) )
        {
            Status = LIST_Status_Error;
            break;
        }

        if ( ( LISTx->Head == LISTx->Tail ) && ( LISTx->Head == NULL ) )
        {
            Status = LIST_Status_Empty;
            break;
        }

        LIST_Node_t * Target = LISTx->Tail;
        if ( Node != NULL )
        {
            while ( ( Target != NULL ) && ( Target != Node ) )
            {
                Target = Target->Previous;
            }

            if ( Target == NULL )
            {
                Status = LIST_Status_Error;
                break;
            }

            Target = Target->Previous;
        }

        *Previous = Target;
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char LIST_VERSION[] = "0.0.0.v20261026-0152";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
