#include <iostream>

#include <CarParkSimLib/Car.h>
#include <CarParkSimLib/CarPark.h>
#include <CarParkSimLib/UKRegistrationMarkGenerator.h>
#include <CarParkSimLib/RegistrationIndex.h>
#include <CarParkSimLib/CustomerAccountManager.h>


int main() {

  CustomerAccountManager accountManager;
  RegistrationIndex registrationIndex;
  UKRegistrationMarkGenerator reggen;

  auto c1 = accountManager.createCustomerAccount({ "Customer 1 Payment details" });
  auto c2 = accountManager.createCustomerAccount({ "Customer 2 Payment details" });
  auto c3 = accountManager.createCustomerAccount({ "Customer 3 Payment details" });
  auto c4 = accountManager.createCustomerAccount({ "Customer 4 Payment details" });

  RegistrationMark regs[10] = {
    RegistrationMark(reggen.generate())
    , RegistrationMark(reggen.generate())
    , RegistrationMark(reggen.generate())

    , RegistrationMark(reggen.generate())
    , RegistrationMark(reggen.generate())
    , RegistrationMark(reggen.generate())

    , RegistrationMark(reggen.generate())
    , RegistrationMark(reggen.generate())
    , RegistrationMark(reggen.generate())

    , RegistrationMark(reggen.generate())
  };

  registrationIndex.addAssociation(regs[0], c1.getAccountID());
  registrationIndex.addAssociation(regs[1], c1.getAccountID());
  registrationIndex.addAssociation(regs[2], c2.getAccountID());
  registrationIndex.addAssociation(regs[3], c2.getAccountID());
  registrationIndex.addAssociation(regs[4], c3.getAccountID());
  registrationIndex.addAssociation(regs[5], c3.getAccountID());
  registrationIndex.addAssociation(regs[6], c3.getAccountID());
  registrationIndex.addAssociation(regs[7], c4.getAccountID());
  registrationIndex.addAssociation(regs[8], c4.getAccountID());
  //registrationIndex.addAssociation(regs[9], c4.getAccountID());

  Car cars[10] = {
    Car(regs[0], true)
    , Car(regs[1], true)
    , Car(regs[2], true)
    , Car(regs[3], true)
    , Car(regs[4], true)
    , Car(regs[5], true)
    , Car(regs[6], true)
    , Car(regs[7], true)
    , Car(regs[8], false)
    , Car(regs[9], false)
  };

  CarPark cp(25, registrationIndex, accountManager);


  for (int i = 0; i < 10; i++) {
    if (cp.enter(cars[i])) {
      std::cout << "\n";
      if (!cars[i].is_auto_payer()) {
        cp.pay(cars[i]);
        std::cout << "\n";
      }
      cp.exit(cars[i]);
      std::cout << "############################################\n\n";
    }
  }
  return 0;
}