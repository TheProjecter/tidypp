/*
    tidypp - a c++ wrapper around HTML Tidy Lib
    Copyright (C) 2012  Francesco "Franc[e]sco" Noferi (francesco1149@gmail.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the
    Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
    Boston, MA  02110-1301, USA.
*/

#pragma once

#include <tidy/tidy.h>

namespace tidypp
{
    /**
     * Tidy uses a user provided allocator for all memory allocations. If this allocator is not provided, then a
     * default allocator is used which simply wraps standard C malloc/free calls. These wrappers call the panic
     * function upon any failure. The default panic function prints an out of memory message to stderr, and calls
     * exit(2).<br />
     * For applications in which it is unacceptable to abort in the case of memory allocation, then the panic
     * function can be replaced with one which longjmps() out of the tidy code. For this to clean up completely,
     * you should be careful not to use any tidy methods that open files as these will not be closed before
     * panic() is called.<br />
     * <br />
     * Calling the constructors/methods that accept an mem::allocator as a parameter allow settings custom allocators.<br />
     * All parts of the document use the same allocator. Calls that require a user provided buffer can optionally
     * use a different allocator.<br />
     * For reference in designing a plug-in allocator, most allocations made by tidy are less than 100 bytes,
     * corresponding to attribute names/values, etc.<br />
     * There is also an additional class of much larger allocations which are where most of the data from the
     * lexer is stored. (It is not currently possible to use a separate allocator for the lexer, this would be a
     * useful extension).<br />
     * In general, approximately 1/3rd of the memory used by tidy is freed during the parse, so if memory usage
     * is an issue then an allocator that can reuse this memory is a good idea.
     * @see buffer::buffer(mem::allocator &allocator)
     * @see buffer::alloc(mem::allocator &allocator, uint size)
     */
    namespace mem
    {
        typedef TidyMalloc malloc; /**< Callback for "malloc" replacement.
                                        Called to allocate a block of nBytes of memory. */

        typedef TidyRealloc realloc; /**< Callback for "realloc" replacement.
                                          Called to resize (grow, in general) a block of memory.
                                          Must support being called with NULL. */

        typedef TidyFree free; /**< Callback for "free" replacement. Called to free a previously
                                    allocated block of memory */

        typedef TidyPanic panic; /**< Callback for "out of memory" panic state. Called when a panic condition is
                                      detected. Must support block == NULL. This function is not called if either
                                      alloc or realloc fails; it is up to the allocator to do this.<br />
                                      Currently this function can only be called if an error is detected in the
                                      tree integrity via the internal function node::checkintegrity. This is a
                                      situation that can only arise in the case of a programming error in tidylib.
                                      You can turn off node integrity checking by defining the constant
                                      NO_NODE_INTEGRITY_CHECK during the build. */

        typedef TidyAllocatorVtbl allocatorvtbl; /**< An allocator's function table. All functions
                                                      here must be provided. */

        typedef TidyAllocator allocator; /**< An allocator. To create your own allocator, do something
                                              like the following:<br />
                                              @verbatim
                                              struct my_allocator : tidypp::mem::allocator // could also use a class
                                              {
                                                  // other custom allocator members
                                              };

                                              void *my_allocator_alloc(tidypp::mem::allocator base, void *block, size_t nbytes)
                                              {
                                                  my_allocator *self = reinterpret_cast<my_allocator>(base);

                                                  // do custom allocator stuff
                                              }

                                              // insert other allocator callbacks here (realloc, free, panic)

                                              static const tidypp::mem::allocatorvtbl my_allocator_vtbl =
                                              {
                                                  my_allocator_alloc,
                                                  my_allocator_realloc,
                                                  my_allocator_free,
                                                  my_allocator_panic
                                              };

                                              // [...]

                                              my_allocator alloc;
                                              alloc.vtbl = &my_allocator_vtbl;
                                              // initialize your custom allocator here
                                              tidypp::document doc(alloc);
                                              // do stuff with the document
                                              @endverbatim

                                              Although this looks slightly long winded, the advantage is that to create a custom
                                              allocator you simply need to set the vtbl pointer correctly. The vtbl itself can
                                              reside in static/global data, and hence does not need to be initialised each
                                              time an allocator is created, and furthermore the memory is shared amongst all
                                              created allocators. */

        /**
         * Give Tidy a free() replacement.
         * @param ffree the replacement for free().
         */
        bool setfree(free ffree);

        /**
         * Give Tidy a malloc() replacement.
         * @param fmalloc the replacement for malloc().
         */
        bool setmalloc(malloc fmalloc);

        /**
         * Give Tidy an "out of memory" handler.
         * @param fpanic the out of memory handler.
         */
        bool setpanic(panic fpanic);

        /**
         * Give Tidy a realloc() replacement.
         * @param frealloc the replacement for realloc().
         */
        bool setrealloc(realloc frealloc);
    }
}
