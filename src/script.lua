local eqcmp = require('eqcmp')
local ptrcmp = require('ptrcmp')
local strcmp = require('strcmp')

local function test(name, udata, dry)
  local start = os.clock()

  for _ = 1, 1000000 do
    assert(udata.aaaaaa == 1)
    assert(udata.aaaaab == 2)
    assert(udata.aaaaac == 3)
  end

  if not dry then
    print(string.format("%s: %0.6f", name, os.clock() - start))
  end
end

test("eqcmp", eqcmp, true)
test("ptrcmp", ptrcmp, true)
test("strcmp", strcmp, true)

test("eqcmp", eqcmp)
test("ptrcmp", ptrcmp)
test("strcmp", strcmp)
