/*
 * Guideline 9 - Pay Attention to the Ownership of Abstractions (PROBLEM)
 *
 * Runnable wiring for the broken plug-in architecture. The program works and
 * prints sensible output, which is exactly why the design flaw is dangerous: the
 * code compiles and runs even though the dependencies point the wrong way. The
 * high-level Editor depends, through its editor.h header, on the low-level
 * thirdparty_plugins.h, because the Plugin abstraction is owned by the low
 * level. Introducing the Plugin base class achieved only a LOCAL inversion; the
 * global architecture is still upside down.
 *
 * Key notes:
 *   - Follow the includes: main.cpp -> editor.h -> thirdparty_plugins.h. The
 *     arrow of dependency runs from the high level down to the low level.
 *     Whoever owns the abstraction controls the requirements.
 *   - Because the community owns Plugin, the Editor must change whenever the
 *     community changes the abstraction. That is not the stable core you want.
 *   - The fix is not more abstractions; it is moving the abstraction's OWNERSHIP
 *     to the high level. See 02_Solution_AbstractionInHighLevel.
 */
#include <iostream>

#include "editor.h" // transitively pulls in the low-level thirdparty header

int main()
{
    app::Editor editor;
    editor.addPlugin(std::make_unique<thirdparty::VimModePlugin>());

    std::cout << "Broken plug-in architecture (abstraction owned by low level):\n";
    editor.listPlugins();
    std::cout << "  output: " << editor.process("hello world") << '\n';

    std::cout << "\nIt compiles and runs, yet the dependency is misdirected:\n"
                 "main -> editor.h -> thirdparty_plugins.h. The high level\n"
                 "depends on the low level because the low level OWNS the Plugin\n"
                 "abstraction. That is only a local inversion, not the DIP.\n";
    return 0;
}
