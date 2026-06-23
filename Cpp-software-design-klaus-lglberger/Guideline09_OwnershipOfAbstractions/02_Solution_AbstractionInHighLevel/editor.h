/*
 * Guideline 9 - Pay Attention to the Ownership of Abstractions (the abstraction
 * is OWNED by the high level)
 *
 * This header models the HIGH-LEVEL package: your own realm. Crucially, it now
 * defines BOTH the Editor AND the Plugin abstraction, and it includes nothing
 * from the low level. The Plugin base class expresses the set of requirements
 * that every plug-in must fulfill, and those requirements belong to you, the
 * owner of the Editor. The Editor does not depend on plug-ins; instead, plug-ins
 * depend on the requirements the Editor defines. That is true dependency
 * inversion.
 *
 * Key notes:
 *   - The Plugin abstraction is grouped WITH the Editor, in the high level. This
 *     is the reassignment of ownership the book calls for, not just a mental
 *     shift but a real move of the header into the high-level package.
 *   - There is no include of any low-level header here. The high level depends
 *     on nothing below it; all arrows now point up toward this package.
 *   - This also honors the SRP: the things that truly belong together are the
 *     Editor and the plug-in requirements it defines, not the concrete plug-ins.
 */
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace app
{
    // The abstraction, OWNED BY THE HIGH LEVEL. These are the Editor's own
    // requirements on every plug-in. The Editor defines them; it does not
    // depend on anyone else to define them.
    class Plugin
    {
    public:
        virtual ~Plugin() = default;
        virtual std::string name() const = 0;
        virtual std::string apply(std::string text) const = 0;
    };

    // The high-level core, depending only on its own Plugin abstraction.
    class Editor
    {
    public:
        void addPlugin(std::unique_ptr<Plugin> plugin)
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
        std::vector<std::unique_ptr<Plugin>> m_plugins;
    };
}
