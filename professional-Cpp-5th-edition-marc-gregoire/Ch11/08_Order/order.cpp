/*
 * Chapter 11 - Initialization Order
 *
 * Within a single translation unit, non-local variables are initialized in
 * the order they appear at file scope. Here `Demo::x` is initialized
 * before `y`, because `int Demo::x{3};` is on line 14 and `int y{4};` is on
 * the next line.
 *
 * What this sample does NOT show but the book emphasizes:
 *   - ACROSS translation units, the order is *unspecified*. If `Demo::x`
 *     and `y` were in different .cpps, you could not assume one was ready
 *     when the other's constructor ran. This is the famous "static
 *     initialization order fiasco".
 *   - Workarounds: use function-local statics (sample 07), or convert
 *     bare globals into accessor functions that return a reference to a
 *     local static.
 *
 * The empty main() is intentional - the entire point is what happens
 * before main() starts.
 */
class Demo
{
public:
	static int x;
};

int Demo::x{ 3 };    // initialized first within this TU
int y{ 4 };          // initialized after Demo::x


int main()
{
}
