#include "lua_eqcmp_udata.h"
#include "lua_ptrcmp_udata.h"
#include "lua_script.h"
#include "lua_strcmp_udata.h"
#include <lauxlib.h>
#include <lualib.h>

int
main(int argc, char* argv[])
{
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  test_lua_eqcmp_udata_init(L);
  test_lua_ptrcmp_udata_init(L);
  test_lua_strcmp_udata_init(L);

  if (luaL_loadstring(L, test_lua_script) || lua_pcall(L, 0, 0, 0)) {
    printf("%s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }

  lua_close(L);
  return 0;
}
