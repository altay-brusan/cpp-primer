/*
 * Guideline 28 - The full Bridge (an abstract implementation behind a pimpl)
 *
 * When the implementation has more than one form, Pimpl grows into the classic
 * Bridge: introduce an Engine ABSTRACTION (a pure virtual base) and let the
 * "abstraction" side hold a std::unique_ptr<Engine> as its pimpl. Now the
 * concrete engine type is a private, secret detail. Clients of ElectricCar see
 * only the Engine interface, so the actual engine can be tuned, swapped, or
 * upgraded with no client noticing and no client recompiling. The book factors
 * the pimpl into a Car base class so every car kind reuses the same Bridge.
 *
 * This is a Bridge, not a Strategy, because of HOW the pointer is set: the car
 * KNOWS its implementation and chooses it INTERNALLY (here in the ElectricCar
 * constructor and in upgrade()). It is never injected from outside. Bridge
 * reduces PHYSICAL dependencies (a structural pattern); Strategy would accept
 * the engine from a caller to reduce LOGICAL dependencies (a behavioral one).
 *
 * The pimpl_ lives in Car's private section (Core Guideline C.133: avoid
 * protected data); derived classes reach it through protected getEngine().
 *
 * Key notes:
 *   - The Engine abstraction is the compilation firewall: concrete engine
 *     headers stay out of the car header, so engine changes do not recompile
 *     clients and the layout (one pointer) stays ABI-stable.
 *   - Telltale of Bridge vs Strategy: the engine is set internally with
 *     make_unique, not passed in from outside.
 *   - upgrade() swaps the concrete engine at runtime; the abstraction and its
 *     clients never notice, satisfying the Open-Closed Principle.
 */
#include <iostream>
#include <memory>
#include <utility>

// ---- <Engine.h> --------------------------------------------------------
// The implementation abstraction. This is the only engine header a car needs.
class Engine
{
public:
    virtual ~Engine() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};

// ---- <Car.h> -----------------------------------------------------------
// Holds the one pimpl for every kind of car and exposes it only to derived
// classes via getEngine(). pimpl_ is private, never protected data.
class Car
{
protected:
    explicit Car(std::unique_ptr<Engine> engine) : pimpl_{std::move(engine)} {}

    Engine* getEngine() { return pimpl_.get(); }
    const Engine* getEngine() const { return pimpl_.get(); }

    // Lets a derived car replace its implementation internally (Bridge, not
    // Strategy: the change is the car's own secret, chosen from within).
    void resetEngine(std::unique_ptr<Engine> engine) { pimpl_ = std::move(engine); }

public:
    virtual ~Car() = default;
    virtual void drive() = 0;

private:
    std::unique_ptr<Engine> pimpl_; // pointer-to-implementation (the Bridge)
    // ... more car-specific data members (wheels, drivetrain, ...)
};

// ---- <ElectricEngine.h> + <PowerEngine.h> ------------------------------
// Concrete engines: in a real build these headers are included ONLY by the
// ElectricCar source file, never by clients of ElectricCar.
class ElectricEngine : public Engine
{
public:
    void start() override { std::cout << "ElectricEngine: start\n"; }
    void stop() override { std::cout << "ElectricEngine: stop\n"; }
};

class PowerEngine : public Engine
{
public:
    void start() override { std::cout << "PowerEngine: start (more torque)\n"; }
    void stop() override { std::cout << "PowerEngine: stop\n"; }
};

// ---- <ElectricCar.h> + <ElectricCar.cpp> -------------------------------
class ElectricCar : public Car
{
public:
    // Bridge telltale: the engine is chosen internally, not passed in.
    ElectricCar() : Car{std::make_unique<ElectricEngine>()} {}

    void drive() override
    {
        getEngine()->start();
        std::cout << "ElectricCar: driving\n";
        getEngine()->stop();
    }

    // Upgrade the hidden implementation; clients see no change in the interface.
    void upgrade() { resetEngine(std::make_unique<PowerEngine>()); }
};

int main()
{
    ElectricCar car;
    std::cout << "Driving with the original engine:\n";
    car.drive();

    car.upgrade();
    std::cout << "\nAfter an internal upgrade (impl swapped, interface unchanged):\n";
    car.drive();

    std::cout << "\nClients of ElectricCar depend only on the Engine abstraction,\n"
                 "never on the concrete engine headers, so swapping or upgrading the\n"
                 "engine costs no client recompilation and breaks no ABI.\n";
    return 0;
}
