# src/CarParkSimLib/CMakeLists.txt

# Create static library from the collected source files (CPP files will be listed in generated project)
add_library(libcarparksim STATIC
  "CarParkSimLib/ANPRCamera.cpp"
  "CarParkSimLib/AutoSessionService.cpp"
  "CarParkSimLib/Barrier.cpp"
  "CarParkSimLib/BasicPaymentCalculator.cpp"
  "CarParkSimLib/Car.cpp"
  "CarParkSimLib/CarPark.cpp"
  "CarParkSimLib/CustomerAccountManager.cpp"
  "CarParkSimLib/Display.cpp"
  "CarParkSimLib/EntryPoint.cpp"
  "CarParkSimLib/ExitPoint.cpp"
  "CarParkSimLib/ExitPolicy.cpp"
  "CarParkSimLib/ParkingSessionManager.cpp"
  "CarParkSimLib/PaymentCalculatorFactory.cpp"
  "CarParkSimLib/PaymentMachine.cpp"
  "CarParkSimLib/PaymentService.cpp"
  "CarParkSimLib/RegistrationIndex.cpp"
  "CarParkSimLib/TicketMachine.cpp"
  "CarParkSimLib/TicketManager.cpp"
  "CarParkSimLib/AutoPayService.cpp"
)

#target_sources(libcarparksim PUBLIC
#  "CarParkSimLib/AccountManager.h"
#  "CarParkSimLib/ANPRCamera.h"
#  "CarParkSimLib/ANPRReading.h"
#  "CarParkSimLib/AutoSessionService.h"
#  "CarParkSimLib/Barrier.h"
#  "CarParkSimLib/BasicPaymentCalculator.h"
#  "CarParkSimLib/Car.h"
#  "CarParkSimLib/CarPark.h"
#  "CarParkSimLib/CustomerAccount.h"
#  "CarParkSimLib/CustomerAccountManager.h"
#  "CarParkSimLib/Display.h"
#  "CarParkSimLib/EntryPoint.h"
#  "CarParkSimLib/ExitPoint.h"
#  "CarParkSimLib/ExitPolicy.h"
#  "CarParkSimLib/IPaymentCalculator.h"
#  "CarParkSimLib/Log.h"
#  "CarParkSimLib/ParkingSession.h"
#  "CarParkSimLib/ParkingSessionManager.h"
#  "CarParkSimLib/PaymentCalculatorFactory.h"
#  "CarParkSimLib/PaymentDetails.h"
#  "CarParkSimLib/PaymentMachine.h"
#  "CarParkSimLib/PaymentService.h"
#  "CarParkSimLib/RegistrationIndex.h"
#  "CarParkSimLib/SessionDataSource.h"
#  "CarParkSimLib/StrongID.h"
#  "CarParkSimLib/TicketMachine.h"
#  "CarParkSimLib/TicketManager.h"
#  "CarParkSimLib/UKRegistrationMarkGenerator.h"
#  "CarParkSimLib/UUIDv4.h"
#)

target_include_directories(libcarparksim
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(libcarparksim PUBLIC cxx_std_20)
