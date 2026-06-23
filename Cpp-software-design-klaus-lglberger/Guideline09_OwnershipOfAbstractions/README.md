# Guideline 9 — Pay Attention to the Ownership of Abstractions

> **Concern:** The **Dependency Inversion Principle (DIP)** says the most flexible
> systems are those whose source-code dependencies refer only to *abstractions*,
> not *concretions* — high-level modules must not depend on low-level modules;
> both depend on abstractions. But introducing an abstraction is not enough. What
> truly inverts the dependency is **who owns the abstraction**: the abstraction
> must be owned by the **high level**, not the low level.

## The idea

The book uses a next-generation text editor with a plug-in architecture. The
high-level `Editor` is your stable core; concrete plug-ins (e.g.
`VimModePlugin`) are the volatile low level, written by your fan community.

- **Naive design.** The `Editor` depends directly on the concrete
  `VimModePlugin`. Every new plug-in forces a change to the editor. Broken.
- **Abstraction alone is not the fix.** You introduce a `Plugin` base class so
  the `Editor` talks only to the abstraction. This *looks* inverted, but if the
  `Plugin` header lives in the **low-level / third-party** package, the editor's
  header must `#include` it. The high level still transitively depends on the low
  level. The book calls this a **local inversion only** — not the DIP.

  ```text
  // PROBLEM: wrong direction
  thirdparty/Plugin.h          // abstraction owned by the low level
  thirdparty/VimModePlugin.h   -> #include thirdparty/Plugin.h
  yourcode/Editor.h            -> #include thirdparty/Plugin.h   // high includes low
  ```

- **The real fix: move ownership.** Assign the abstraction to the **high level**.
  Group `Plugin` *with* the `Editor`. Now the low-level plug-in includes the
  high-level header, and every dependency arrow points **up** toward the high
  level.

  ```text
  // SOLUTION: correct direction
  yourcode/Plugin.h            // abstraction owned by the high level
  yourcode/Editor.h            -> #include yourcode/Plugin.h
  thirdparty/VimModePlugin.h   -> #include yourcode/Plugin.h     // low includes high
  ```

This is more than a mental shift: it is a **reassignment of ownership** — moving
the header from one package to another and rearranging the include statements.
The abstraction expresses the *requirements*; the `Editor` **defines and owns**
them, the plug-ins **depend on** them. That is dependency inversion. It also
honors the **SRP**: the things that belong together are the editor and its
plug-in requirements, not the concrete plug-ins.

The DIP is not limited to inheritance. It is also achieved with **templates and
concepts** (and with **overload sets**). There, ownership is *automatic*: a
high-level algorithm states its requirements as a concept defined alongside it,
exactly as `std::copy_if` owns `InputIt`, `OutputIt`, and `UnaryPredicate`.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_AbstractionInLowLevel` | A `Plugin` abstraction exists, but it is owned by the low-level `thirdparty_plugins.h`. The high-level `editor.h` must include that low-level header, so the dependency runs `main -> editor.h -> thirdparty_plugins.h`: high level toward low level. Compiles and runs — the flaw is silent. |
| 02 | `02_Solution_AbstractionInHighLevel` | The `Plugin` abstraction is grouped with the `Editor` in the high-level `editor.h`. The low-level `vim_plugin.h` includes it, so the dependency runs `main -> vim_plugin.h -> editor.h`: low level toward high level. True DIP. |
| 03 | `03_Solution_Templates` | The same inversion via a `PluginLike` **concept** owned by a high-level algorithm. Low-level value types satisfy it with no base class. Ownership is automatic, like the STL algorithms. |

Each sample uses local headers only; no cross-folder includes. Follow the
`#include` arrows to see the direction of dependencies change between 01 and 02.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 9

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 9
```

Standard library only. The "third-party" plug-in library is a tiny local stub.

## Notes

- An abstraction gives a **local** inversion; only correct **ownership** gives a
  **global** inversion. Both points of Martin's DIP must hold: (1) high-level
  modules should not depend on low-level modules — both depend on abstractions;
  (2) abstractions should not depend on details — details depend on abstractions.
- "Where to put the interface" is an architectural decision, not a cosmetic one.
  The abstraction belongs in the **package of the code that defines the
  requirements** (the high level), not the package that implements them.
- The abstraction represents the *set of requirements* the implementations must
  fulfill (see Guideline 6). The owner defines the requirements and does not
  depend on the implementers; the implementers depend on the requirements.
- The DIP is closely related to the SRP and ISP but is distinct: it is about the
  **global** dependency structure of the architecture, not just local grouping.

## Related

→ Guideline 2 (Design for Change) and Guideline 6 (Expected Behavior of
Abstractions) set up *why* abstractions exist. → Guideline 3 (Separate
Interfaces) is the ISP step that segregates client-specific interfaces. →
Guideline 7 (Base Classes and Concepts) underlies the template-based inversion in
sample 03.
