#include "dispatcher.h"
#include "embedded/lua/lvm_helper.h"



DEFINE_LUA_FUNCTION(__add, &kanas::dispatcher::pak)
DEFINE_LUA_MEMBER_FUNCTION(tick, &kanas::dispatcher::tick)