#ifndef LUA_SANDBOX_HPP
#define LUA_SANDBOX_HPP

#include <sol/sol.hpp>
#include "Config.hpp"

// TODO: add bindings for logger, widgets, Expected<T> etc.
namespace tnt
{
class [[deprecated("LuaSandbox is not recommended (as it is part of the engine, NOT the SDK). Use LuaManager instead.")]] LuaSandbox
{
public:
    static LuaSandbox &This();

    sol::state *operator->()
    {
        return &lua;
    }

private:
    LuaSandbox();

    void loadVector();
    void loadMatrix();
    // void loadVFS();
    void loadCamera();
    void loadTimer();
    void loadObject();
    void loadEasings();

    static sol::state lua;
};

class /*TNT_API*/ LuaManager
{
public:
    static LuaManager &This();

private:
    LuaManager();
};
} // namespace tnt

#endif //!LUA_SANDBOX_HPP