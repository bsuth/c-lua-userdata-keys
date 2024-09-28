#include "lua_strcmp_udata.h"
#include <lauxlib.h>
#include <string.h>

static int
test_lua_strcmp_udata__index(lua_State* L)
{
  const char* string = lua_tostring(L, 2);

  if (strcmp(string, "aaaaaa") == 0) {
    lua_pushnumber(L, 1);
  } else if (strcmp(string, "aaaaab") == 0) {
    lua_pushnumber(L, 2);
  } else if (strcmp(string, "aaaaac") == 0) {
    lua_pushnumber(L, 3);
  } else {
    lua_pushnumber(L, 0);
  }

  return 1;
}

static const struct luaL_Reg test_lua_strcmp_udata_mt[] = {
  {"__index", test_lua_strcmp_udata__index},
  {NULL, NULL}
};

void
test_lua_strcmp_udata_init(lua_State* L)
{
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "loaded");

  lua_newuserdata(L, 0);
  lua_newtable(L);
  luaL_setfuncs(L, test_lua_strcmp_udata_mt, 0);
  lua_setmetatable(L, -2);

  lua_setfield(L, -2, "strcmp");
  lua_pop(L, 2);
}
