#include <iostream>

#include <CarParkSimLib/Car.h>
#include <CarParkSimLib/CarPark.h>
#include <CarParkSimLib/UKRegistrationMarkGenerator.h>

int main() {
  CarPark cp(25);

  UKRegistrationMarkGenerator reggen;

  for (int i = 0; i < 10; i++) {
    Car c(reggen.generate());
    if (cp.enter(c)) {
      cp.pay(c);
      cp.exit(c);
    }
  }
  return 0;
}