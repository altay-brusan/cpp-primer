/*
 * Guideline 9 - Pay Attention to the Ownership of Abstractions (high-level
 * Editor forced to depend on a low-level-owned abstraction)
 *
 * This header models the HIGH-LEVEL package: your own realm, the stable core of
 * the text editor. The Editor only ever talks to the Plugin abstraction, never
 * to a concrete plug-in, so at first glance the dependencies look inverted. But
 * look at the include below: to even name Plugin, this high-level header must
 * include the THIRD-PARTY low-level header. That is the wrong direction of
 * dependencies. The Editor still transitively depends on the low level, because
 * the abstraction is owned there, not here.
 *
 * Key notes:
 *   - The include of thirdparty_plugins.h is the smoking gun: high level
 *     including low level. Moving the include statements is exactly what the
 *     book says a real fix requires; an abstraction alone does not move it.
 *   - Because the community owns Plugin, any change they make to the abstraction
 *     ripples into the Editor: recompilation in the best case, redeployment in
 *     the worst.
 *   - This is a LOCAL inversion only. The global architecture is still upside
 *     down: the stable high level depends on the volatile low level.
 */
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// WRONG DIRECTION: the high-level Editor package includes the low-level
// third-party package just to see the Plugin abstraction.
#include "thirdparty_plugins.h"

namespace app
{
    // The high-level core. Note it must spell out thirdparty::Plugin, a type it
    // does not own, in its own interface.
    class Editor
    {
    public:
        void addPlugin(std::unique_ptr<thirdparty::Plugin> plugin)
        {
            m_plugins.push_back(std::move(plugin));
        }

        std::string process(std::string text) const
        {
            for (const auto& plugin : m_plugins)
            {
                text = plugin->apply(std::move(text));
            }
            return text;
        }

        void listPlugins() const
        {
            std::cout << "  loaded plug-ins:";
            for (const auto& plugin : m_plugins)
            {
                std::cout << ' ' << plugin->name();
            }
            std::cout << '\n';
        }

    private:
        std::vector<std::unique_ptr<thirdparty::Plugin>> m_plugins;
    };
}
