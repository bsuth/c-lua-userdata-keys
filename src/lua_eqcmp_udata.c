#include "lua_eqcmp_udata.h"
#include <lauxlib.h>
#include <stdbool.h>
#include <string.h>

static int LUA_KEY_AAAAAA = LUA_NOREF;
static int LUA_KEY_AAAAAB = LUA_NOREF;
static int LUA_KEY_AAAAAC = LUA_NOREF;

static bool
lua_key_cmp(lua_State* L, int key_ref, int idx)
{
  lua_rawgeti(L, LUA_REGISTRYINDEX, key_ref);
  int result = lua_equal(L, -1, idx);
  lua_pop(L, 1);
  return result == 1;
}

static int
test_lua_eqcmp_udata__index(lua_State* L)
{
  const char* string = lua_tostring(L, 2);

  if (lua_key_cmp(L, LUA_KEY_AAAAAA, 2)) {
    lua_pushnumber(L, 1);
  } else if (lua_key_cmp(L, LUA_KEY_AAAAAB, 2)) {
    lua_pushnumber(L, 2);
  } else if (lua_key_cmp(L, LUA_KEY_AAAAAC, 2)) {
    lua_pushnumber(L, 3);
  } else {
    lua_pushnumber(L, 0);
  }

  return 1;
}

static const struct luaL_Reg test_lua_eqcmp_udata_mt[] = {
  {"__index", test_lua_eqcmp_udata__index},
  {NULL, NULL}
};

void
test_lua_eqcmp_udata_init(lua_State* L)
{
  lua_pushstring(L, "aaaaaa");
  LUA_KEY_AAAAAA = luaL_ref(L, LUA_REGISTRYINDEX); // freeze
  lua_pushstring(L, "aaaaab");
  LUA_KEY_AAAAAB = luaL_ref(L, LUA_REGISTRYINDEX); // freeze
  lua_pushstring(L, "aaaaac");
  LUA_KEY_AAAAAC = luaL_ref(L, LUA_REGISTRYINDEX); // freeze

  lua_getglobal(L, "package");
  lua_getfield(L, -1, "loaded");

  lua_newuserdata(L, 0);
  lua_newtable(L);
  luaL_setfuncs(L, test_lua_eqcmp_udata_mt, 0);
  lua_setmetatable(L, -2);

  lua_setfield(L, -2, "eqcmp");
  lua_pop(L, 2);
}
