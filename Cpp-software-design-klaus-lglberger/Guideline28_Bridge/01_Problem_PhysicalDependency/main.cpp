/*
 * Guideline 28 - The physical dependency problem (a class that exposes its
 *                implementation in its own header)
 *
 * The book opens with an ElectricCar that stores an ElectricEngine BY VALUE.
 * To know the size of an ElectricCar the compiler must see the full definition
 * of ElectricEngine, so in a real project ElectricCar.h is forced to include
 * ElectricEngine.h. That single include creates a transitive, physical
 * (compile-time) dependency: every translation unit that touches ElectricCar.h
 * now also depends on ElectricEngine.h. Change anything in the engine header
 * and ElectricCar, plus potentially many unrelated clients, must be recompiled,
 * retested, and in the worst case redeployed.
 *
 * There is a second, subtler problem. The private label is an ACCESS label, not
 * a VISIBILITY label: everything in the class definition is visible to everyone
 * who sees it. So the engine_ member reveals the implementation, the in-memory
 * layout is public knowledge, and the class cannot change without clients
 * noticing - which also means no ABI stability.
 *
 * This file compiles and runs; it is the starting point the later samples fix.
 *
 * Key notes:
 *   - A by-value member needs the member type's full definition, which drags
 *     its header into the class header: a physical, compile-time dependency.
 *   - private hides access, not visibility; layout and member types leak.
 *   - Changing the engine here changes ElectricCar's size, so its ABI breaks.
 */
#include <iostream>

// ---- <ElectricEngine.h> ------------------------------------------------
// In a real build this lives in its own header. ElectricCar.h would have to
// include it because ElectricCar stores an ElectricEngine by value.
class ElectricEngine
{
public:
    void start() { std::cout << "ElectricEngine: start\n"; }
    void stop() { std::cout << "ElectricEngine: stop\n"; }

private:
    // Implementation details. Edit any of these and EVERY client that includes
    // ElectricCar.h must recompile, and ElectricCar's size (its ABI) changes.
    int power_ = 100;
    double charge_ = 1.0;
};

// ---- <ElectricCar.h> ---------------------------------------------------
// This header is physically coupled to <ElectricEngine.h>: it cannot even be
// parsed without the full ElectricEngine definition above.
class ElectricCar
{
public:
    ElectricCar() = default;

    void drive()
    {
        engine_.start();
        std::cout << "ElectricCar: driving\n";
        engine_.stop();
    }

private:
    ElectricEngine engine_; // by-value member -> physical dependency leaks out
    // ... more car-specific data members (wheels, drivetrain, ...)
};

int main()
{
    ElectricCar car;
    car.drive();

    std::cout << "\nProblem: ElectricCar.h must include ElectricEngine.h, so the\n"
                 "engine layout leaks to every client and any engine change forces\n"
                 "recompilation and breaks ABI. See 02_Solution_Pimpl.\n";
    return 0;
}
