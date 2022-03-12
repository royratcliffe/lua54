/*  File:    lua54.pl
    Author:  Roy Ratcliffe
    Created: Mar 10 2022
    Purpose: Lua 5.4.x embedded interpreter

Copyright (c) 2022, Roy Ratcliffe, Northumberland, United Kingdom

Permission is hereby granted, free of charge,  to any person obtaining a
copy  of  this  software  and    associated   documentation  files  (the
"Software"), to deal in  the   Software  without  restriction, including
without limitation the rights to  use,   copy,  modify,  merge, publish,
distribute, sublicense, and/or sell  copies  of   the  Software,  and to
permit persons to whom the Software is   furnished  to do so, subject to
the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY OF ANY KIND, EXPRESS
OR  IMPLIED,  INCLUDING  BUT  NOT   LIMITED    TO   THE   WARRANTIES  OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR   PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS  OR   COPYRIGHT  HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY,  WHETHER   IN  AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM,  OUT  OF   OR  IN  CONNECTION  WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

:- module(lua54,
    [ lua_open/1,                               % +L
      lua_newstate/1,                           % -L
      lua_close/1,                              % +L

      % stack manipulation
      lua_absindex/3,
      lua_gettop/2,
      lua_settop/2
    ]).
:- use_foreign_library(foreign(lua54)).

%!  lua_open(+L) is det.
%!  lua_newstate(-L) is det.
%!  lua_close(+L) is det.
%
%   Opening a Lua state means creating and binding a `lua_State`
%   instance. Close and re-open a Lua state in order to start again from
%   a fresh state while retaining the same standard streams.
%
%   New states also open a new Lua state at L. Implicitly
%   opens the new state L; see lua_open/1 for details.
%
%   Asking for a new state means allocating a new Lua blob then opening
%   a new underlying Lua state; either step can fail. The first fails by
%   raising a memory resource exception as does the second.
%
%   Closing Lua releases the bound Lua state on success; fails if
%   already closed. You can only successfully close an open Lua state,
%   speaking from logic.

%!  lua_absindex(+L, +Index, ?Abs) is semidet.
%!  lua_gettop(+L, ?Top) is semidet.
%!  lua_settop(+L, +Top) is det.
%
%   Basic stack manipulation.
