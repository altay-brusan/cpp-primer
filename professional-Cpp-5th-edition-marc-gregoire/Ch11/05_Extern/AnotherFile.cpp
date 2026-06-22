/*
 * Chapter 11 - extern Variables (definition side)
 *
 * `extern int x;` declares (no storage). `int x{3};` defines (storage +
 * initial value). One translation unit must contain the definition; any
 * number can contain declarations.
 *
 * `extern int x{3};` is sometimes seen - the `extern` is redundant when
 * there is an initializer (the initializer alone is enough to make it a
 * definition). Modern style is to drop the `extern` on the definition line
 * for clarity.
 */
extern int x;
int x{ 3 };

//extern int x{ 3 };   // redundant `extern`: the initializer already makes it a definition
