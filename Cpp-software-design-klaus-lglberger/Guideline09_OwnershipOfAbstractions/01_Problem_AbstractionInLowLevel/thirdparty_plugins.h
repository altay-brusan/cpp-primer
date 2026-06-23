/*
 * Guideline 9 - Pay Attention to the Ownership of Abstractions (the broken
 * plug-in architecture: the abstraction is owned by the LOW level)
 *
 * This header models the THIRD-PARTY / LOW-LEVEL package, the realm of your fan
 * community. It defines BOTH the Plugin abstraction and a concrete VimModePlugin
 * that implements it. Introducing an abstraction (Plugin) is necessary, but it
 * is not sufficient. The Dependency Inversion Principle (DIP) is about more than
 * adding a base class: it is also about WHO OWNS that base class. Here the high
 * level (the Editor) will have to include this low-level header to see Plugin,
 * so the dependency still runs the wrong way: high level toward low level.
 *
 * Key notes:
 *   - The abstraction lives next to the concrete plug-ins, in the low level.
 *     Whoever owns the abstraction defines the requirements; here the fan
 *     community does, so the community can change Plugin at will and force the
 *     Editor to change with it.
 *   - This is the situation the book draws as <thirdparty/Plugin.h> included by
 *     <yourcode/Editor.h>: a misdirected dependency.
 *   - Having an abstraction is only a LOCAL inversion. Globally, the high level
 *     still depends on the low level, so the DIP is not yet satisfied.
 */
#pragma once

#include <string>

namespace thirdparty
{
    // The abstraction, but OWNED BY THE LOW LEVEL. This is the design flaw the
    // guideline warns about: the requirements on plug-ins belong here, in the
    // community's package, not in the Editor's package.
    class Plugin
    {
    public:
        virtual ~Plugin() = default;
        virtual std::string name() const = 0;
        virtual std::string apply(std::string text) const = 0;
    };

    // A concrete plug-in supplied by the fan community.
    class VimModePlugin : public Plugin
    {
    public:
        std::string name() const override { return "VimMode"; }
        std::string apply(std::string text) const override
        {
            return "[vim] " + text;
        }
    };
}
