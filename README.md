# CarParkSim

A modern C++20 car park management system with ANPR (Automatic Number Plate Recognition) integration, automated payment processing, and intelligent barrier control.

## Features

- **ANPR Integration**: Automatic vehicle registration plate reading at entry and exit
- **Dual Authentication**: Registration mark lookup or physical ticket-based sessions
- **Automated Payments**: Autopay service with account-based payment processing
- **Session Management**: Comprehensive parking session tracking from entry to exit
- **Barrier Control**: Automated barrier operation based on payment and policy verification
- **Grace Period Enforcement**: Configurable grace period for exit after payment
- **Payment Fallback**: Ticket machines for manual payment at designated payment machines
- **User Feedback**: Real-time display messages guiding customers through the parking process

## Architecture

### Core Components

```
┌─────────────────────────────────────────────────────────────┐
│                      CarPark Manager                         │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│  ┌─────────────────┐                ┌─────────────────┐    │
│  │  Entry Point    │                │  Exit Point     │    │
│  ├─────────────────┤                ├─────────────────┤    │
│  │ • ANPR Camera   │                │ • ANPR Camera   │    │
│  │ • Ticket Machine│                │ • Barrier       │    │
│  │ • Barrier       │                │ • Exit Policy   │    │
│  └─────────────────┘                │ • AutoPay       │    │
│                                      └─────────────────┘    │
│                                                               │
│  ┌──────────────────────────────────────────────────────┐  │
│  │         Core Services & Managers                      │  │
│  ├──────────────────────────────────────────────────────┤  │
│  │ • ParkingSessionManager     • AutoPayService         │  │
│  │ • TicketManager             • PaymentService         │  │
│  │ • AutoSessionService (ANPR) • CustomerAccountManager │  │
│  │ • ExitPolicy                • RegistrationIndex      │  │
│  └──────────────────────────────────────────────────────┘  │
│                                                               │
└─────────────────────────────────────────────────────────────┘
```

### Key Classes

- **CarPark**: Main orchestrator managing entry, exit, and payment flows
- **EntryPoint**: Handles vehicle entry with ANPR and ticket issuance
- **ExitPoint**: Manages exit verification, autopay, and barrier operation
- **ParkingSession**: Represents a parking session with entry/exit timestamps and payment status
- **AutoPayService**: Processes automatic payments using registered vehicle accounts
- **ExitPolicy**: Enforces exit rules based on payment status and grace period
- **TicketManager**: Manages physical ticket-based sessions

## System Requirements

- **CMake**: Version 3.10 or higher (4.2.3+ tested)
- **C++ Standard**: C++20
- **Generator**: Ninja (primary), MSVC compatible
- **Compiler**: MSVC (Visual Studio 2019+) or compatible C++20 compiler

## Building

### Prerequisites

Install CMake 3.10 or higher and Ninja build system.

### Build Steps

```powershell
# Clone the repository
git clone https://github.com/dhbellringer/CarParkSim.git
cd CarParkSim

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake -G Ninja ..

# Build the project
cmake --build .

# Build with tests
cmake --build . --target all
```

### Visual Studio

The project can be opened directly in Visual Studio Community 2026+:

```powershell
# Open in Visual Studio
start CarParkSim.sln
```

## Running Tests

```powershell
# Run all tests
ctest

# Run specific test
ctest -R "Car_test"

# Run with verbose output
ctest --verbose
```

## Project Structure

```
CarParkSim/
├── src/
│   ├── CarParkSimLib/           # Main library
│   │   ├── CarPark.cpp/h        # Main orchestrator
│   │   ├── EntryPoint.cpp/h     # Entry flow logic
│   │   ├── ExitPoint.cpp/h      # Exit flow logic
│   │   ├── ParkingSession.h     # Session data model
│   │   ├── AutoPayService.cpp/h # Autopay logic
│   │   ├── ExitPolicy.cpp/h     # Exit validation rules
│   │   ├── TicketManager.cpp/h  # Ticket operations
│   │   ├── PaymentService.cpp/h # Payment processor
│   │   ├── ANPRCamera.cpp/h     # ANPR simulation
│   │   ├── Barrier.cpp/h        # Barrier control
│   │   ├── Display.cpp/h        # User messaging
│   │   └── ... (additional services)
│   └── CMakeLists.txt
├── app/
│   ├── Demo/                    # Demo application
│   └── CMakeLists.txt
├── tests/
│   ├── Car_test.cpp
│   ├── StrongID_test.cpp
│   ├── Display_test.cpp
│   ├── TicketManager_test.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt               # Root CMake configuration
└── README.md
```

## Payment Flow

### Automatic Payment (ANPR-Based)

```
Vehicle arrives at exit
  ↓
ANPR reads registration mark
  ↓
System looks up parking session
  ↓
If session active (unpaid):
  - Retrieve customer account
  - Calculate parking fee
  - Attempt automatic payment
  - Mark session as paid
  ↓
Evaluate exit policy
  - Check payment status ✓
  - Check grace period
  ↓
Open barrier → Allow exit → Close barrier
```

### Ticket-Based Payment

```
Vehicle arrives at exit
  ↓
ANPR fails or registration not found
  ↓
Driver prompted to insert ticket
  ↓
Ticket looked up in system
  ↓
If session unpaid:
  - Driver must pay at payment machine
  ↓
After payment:
  - Session marked as paid
  ↓
Evaluate exit policy & open barrier
```

## Configuration

### Exit Policy

Set grace period (configurable in `CarPark` constructor):

```cpp
ExitPolicy exitPolicy(std::chrono::seconds(60));  // 60-second grace period
```

Grace period determines how long after payment a vehicle can exit without additional payment.

### Payment Calculations

Payment is calculated based on:
- Parking duration (entry to exit time)
- Payment rates (configurable via `BasicPaymentCalculator`)

## API Examples

### Basic Usage

```cpp
#include "CarPark.h"
#include "Car.h"

// Create car park (max 100 sessions, 60-second grace period)
RegistrationIndex regIndex;
CustomerAccountManager accountMgr;
CarPark carPark(100, regIndex, accountMgr);

// Vehicle entry
Car car1(RegistrationMark("ABC123"), true);
bool entrySuccess = carPark.enter(car1);

// ... time passes ...

// Vehicle exit
bool exitSuccess = carPark.exit(car1);

// Payment at machine
bool paymentSuccess = carPark.pay(car1);
```

## Testing

The project uses Catch2 for unit testing. Current test coverage includes:

- ✅ Car operations (ticket management)
- ✅ StrongID type safety
- ✅ Display messaging
- ✅ Ticket manager operations
- ✅ AutoSession service integration

## Production Status

The system is **production-ready** with the following notes:

- ✅ Autopay logic properly handles all payment outcomes
- ✅ Revenue protection through multi-factor session verification
- ✅ Comprehensive error handling and user feedback
- ✅ Configurable grace periods and payment rules
- ⚠️ Consider adding structured logging for audit trails
- ⚠️ Implement payment service resilience/retry logic

## Future Enhancements

- [ ] Structured logging system for audit trails
- [ ] Payment service retry logic with exponential backoff
- [ ] SMS/email notifications for payment failures
- [ ] Admin dashboard for real-time monitoring
- [ ] Revenue reporting and reconciliation
- [ ] Dynamic pricing based on occupancy
- [ ] Reservation system integration
- [ ] License plate history and banned vehicle tracking

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Code Standards

- Follow C++20 standards
- Use `std::optional` for optional values
- Prefer const-correctness
- Add tests for new functionality
- Ensure all tests pass before submitting PR

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

**David Bellringer** - [GitHub](https://github.com/dhbellringer)

## Acknowledgments

- Catch2 testing framework
- CMake build system
- C++20 standard library

---

## Quick Start

```powershell
# Clone and build
git clone https://github.com/dhbellringer/CarParkSim.git
cd CarParkSim
mkdir build && cd build
cmake -G Ninja ..
cmake --build .

# Run tests
ctest --verbose
```

For more detailed information, see the source code documentation and inline comments.
