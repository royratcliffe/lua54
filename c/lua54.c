#include "lua_State.h"

foreign_t
lua_newstate_1(term_t l)
{ return unify_lua_State(l);
}

install_t
install_lua54()
{ PL_register_foreign("lua_newstate", 1, lua_newstate_1, 0);
}

install_t
uninstall_lua54()
{ ;
}
