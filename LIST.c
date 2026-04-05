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

        if ( ( LISTx->Head != LISTx->Tail ) && ( ( LISTx->Head == NULL ) || ( LISTx->Tail == NULL ) ) )
        {
            Status = LIST_Status_Error;
            break;
        }

        if ( ( LISTx->Head == LISTx->Tail ) && ( LISTx->Tail == NULL ) )
        {
            LISTx->Head = Node;
            LISTx->Tail = Node;

            Node->Next = NULL;
            Node->Previous = NULL;
        }
        else
        {
            Node->Previous = LISTx->Tail;

            Node->Next = LISTx->Tail->Next;
            LISTx->Tail->Next = Node;

            LISTx->Tail = Node;
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

        if ( ( LISTx->Head != LISTx->Tail ) && ( ( LISTx->Head == NULL ) || ( LISTx->Tail == NULL ) ) )
        {
            Status = LIST_Status_Error;
            break;
        }

        if ( ( LISTx->Head == LISTx->Tail ) && ( LISTx->Tail == NULL ) )
        {
            Status = LIST_Status_Empty;
            break;
        }

        LIST_Node_t * Target = LISTx->Tail;

        if ( LISTx->Head == LISTx->Tail )
        {
            LISTx->Head = NULL;
            LISTx->Tail = NULL;
        }
        else
        {
            LISTx->Tail = Target->Previous;
            LISTx->Tail->Next = Target->Next;

            Target->Previous = NULL;
            Target->Next = NULL;
        }

        *Node = Target;
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

        if ( ( LISTx->Head != LISTx->Tail ) && ( ( LISTx->Head == NULL ) || ( LISTx->Tail == NULL ) ) )
        {
            Status = LIST_Status_Error;
            break;
        }

        if ( ( LISTx->Head == LISTx->Tail ) && ( LISTx->Head == NULL ) )
        {
            LISTx->Head = Node;
            LISTx->Tail = Node;

            Node->Next = NULL;
            Node->Previous = NULL;
        }
        else
        {
            Node->Next = LISTx->Head;

            Node->Previous = LISTx->Head->Previous;
            LISTx->Head->Previous = Node;

            LISTx->Head = Node;
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

        if ( LISTx->Head == LISTx->Tail )
        {
            LISTx->Head = NULL;
            LISTx->Tail = NULL;
        }
        else
        {
            LISTx->Head = Target->Next;
            LISTx->Head->Previous = Target->Previous;

            Target->Previous = NULL;
            Target->Next = NULL;
        }

        *Node = Target;
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PushAfter( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t * New )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Node == NULL || New == NULL )
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
        while ( Target != Node )
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
    }
    while ( 0 );

    return Status;
}

LIST_Status_t LIST_PushBefore( LIST_t * LISTx, LIST_Node_t * Node, LIST_Node_t * New )
{
    LIST_Status_t Status = LIST_Status_Success;

    do
    {
        if ( LISTx == NULL || Node == NULL || New == NULL )
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
        while ( Target != Node )
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
        while ( Target != Node )
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

const char LIST_VERSION[] = "0.0.0.v20260405-1156";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
