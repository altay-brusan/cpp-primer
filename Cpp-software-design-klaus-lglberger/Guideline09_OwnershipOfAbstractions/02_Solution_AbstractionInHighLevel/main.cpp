/*
 * Guideline 9 - Pay Attention to the Ownership of Abstractions (SOLUTION)
 *
 * Runnable wiring for the correct plug-in architecture. The behavior is the same
 * as in the problem, but the dependency structure is now sound. The Plugin
 * abstraction is owned by the high-level Editor package; the low-level
 * VimModePlugin depends on it. Follow the includes and you see every arrow now
 * points UP toward the high level. That is the Dependency Inversion Principle:
 * high-level modules do not depend on low-level modules, and the abstraction is
 * owned by the high level.
 *
 * Key notes:
 *   - Include direction: main.cpp -> vim_plugin.h -> editor.h. The low level
 *     depends on the high level. The Editor owns the requirements; plug-ins
 *     conform to them.
 *   - Adding a brand-new plug-in (a SpeedTransfer-style addition) cannot force a
 *     change on the Editor, because no plug-in owns the abstraction.
 *   - This satisfies both the DIP (dependencies inverted) and the SRP (the
 *     Editor and its plug-in requirements are grouped together where they
 *     belong).
 */
#include <iostream>

#include "vim_plugin.h" // pulls in the high-level editor.h, the correct way

int main()
{
    app::Editor editor;
    editor.addPlugin(std::make_unique<plugins::VimModePlugin>());

    std::cout << "Correct plug-in architecture (abstraction owned by high level):\n";
    editor.listPlugins();
    std::cout << "  output: " << editor.process("hello world") << '\n';

    std::cout << "\nSame behavior, sound dependencies:\n"
                 "main -> vim_plugin.h -> editor.h. The low level depends on the\n"
                 "high level because the high level OWNS the Plugin abstraction.\n"
                 "That is true dependency inversion, the DIP fully applied.\n";
    return 0;
}
