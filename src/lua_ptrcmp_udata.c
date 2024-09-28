#include "lua_ptrcmp_udata.h"
#include <lauxlib.h>
#include <string.h>

static const char* LUA_KEY_AAAAAA = NULL;
static const char* LUA_KEY_AAAAAB = NULL;
static const char* LUA_KEY_AAAAAC = NULL;

static int
test_lua_ptrcmp_udata__index(lua_State* L)
{
  const char* string = lua_tostring(L, 2);

  if (LUA_KEY_AAAAAA == string) {
    lua_pushnumber(L, 1);
  } else if (LUA_KEY_AAAAAB == string) {
    lua_pushnumber(L, 2);
  } else if (LUA_KEY_AAAAAC == string) {
    lua_pushnumber(L, 3);
  } else {
    lua_pushnumber(L, 0);
  }

  return 1;
}

static const struct luaL_Reg test_lua_ptrcmp_udata_mt[] = {
  {"__index", test_lua_ptrcmp_udata__index},
  {NULL, NULL}
};

void
test_lua_ptrcmp_udata_init(lua_State* L)
{
  lua_pushstring(L, "aaaaaa");
  LUA_KEY_AAAAAA = lua_tostring(L, -1);
  luaL_ref(L, LUA_REGISTRYINDEX); // freeze
                                  //
  lua_pushstring(L, "aaaaab");
  LUA_KEY_AAAAAB = lua_tostring(L, -1);
  luaL_ref(L, LUA_REGISTRYINDEX); // freeze
                                  //
  lua_pushstring(L, "aaaaac");
  LUA_KEY_AAAAAC = lua_tostring(L, -1);
  luaL_ref(L, LUA_REGISTRYINDEX); // freeze

  lua_getglobal(L, "package");
  lua_getfield(L, -1, "loaded");

  lua_newuserdata(L, 0);
  lua_newtable(L);
  luaL_setfuncs(L, test_lua_ptrcmp_udata_mt, 0);
  lua_setmetatable(L, -2);

  lua_setfield(L, -2, "ptrcmp");
  lua_pop(L, 2);
}
