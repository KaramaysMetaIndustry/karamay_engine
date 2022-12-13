#include "widget_lib.h"
#include "embedded/lua/lvm_helper.h"

LUA_LIB_EXPORTER(kanas)

LUA_LIB_FUNCTION(kanas, log, &kanas::log)
LUA_LIB_FUNCTION(kanas, logf, &kanas::logf)
