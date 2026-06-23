/*
 * Guideline 9 - Pay Attention to the Ownership of Abstractions (a low-level
 * plug-in that DEPENDS ON the high-level abstraction)
 *
 * This header models the THIRD-PARTY / LOW-LEVEL package, the realm of your fan
 * community. The concrete VimModePlugin implements the Plugin abstraction, but
 * notice the include below: the low-level package now includes the HIGH-LEVEL
 * editor.h to see Plugin. This is the correct direction of dependencies, exactly
 * the book's <thirdparty/VimModePlugin.h> including <yourcode/Plugin.h>. The low
 * level depends on the high level, never the other way around.
 *
 * Key notes:
 *   - The include direction is now reversed compared to the problem: low level
 *     includes high level. That single change of ownership is what truly
 *     inverts the dependency.
 *   - The community can write as many plug-ins as they like; none of them can
 *     force a change on the Editor, because they all conform to requirements the
 *     Editor owns.
 *   - app::Plugin is the set of requirements; VimModePlugin merely fulfills
 *     them, the way a derived class fulfills the contract of its base.
 */
#pragma once

#include <string>

// CORRECT DIRECTION: the low-level plug-in package includes the high-level
// header to obtain the abstraction it must conform to.
#include "editor.h"

namespace plugins
{
    class VimModePlugin : public app::Plugin
    {
    public:
        std::string name() const override { return "VimMode"; }
        std::string apply(std::string text) const override
        {
            return "[vim] " + text;
        }
    };
}
