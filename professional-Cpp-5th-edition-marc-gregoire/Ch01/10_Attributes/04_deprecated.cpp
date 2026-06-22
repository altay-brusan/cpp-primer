/*
 * Chapter 1 - [[deprecated]]
 *
 * [[deprecated]] marks an entity as discouraged. Callers still compile but receive a
 * compiler diagnostic, which is the gentle way to retire an API without breaking builds.
 *
 * Key notes:
 *   - Optional argument is a message string: [[deprecated("Use newApi() instead")]].
 *   - Applies to functions, classes/structs, type aliases, variables, non-static data
 *     members, enumerators, and namespaces.
 *   - Build systems can promote warnings to errors (-Werror, /WX) which turns this into a
 *     hard cutoff.
 *   - Standardized in C++14.
 */

[[deprecated("Unsafe function, please use xyz")]] void func() {}

int main()
{
	func();
}