#include "Barrier.h"
#include "log.h"

Barrier::Barrier() : state_(BarrierState::Closed) {}

void Barrier::open() {
  log2("BARRIER", "Barrier open.");
  state_ = BarrierState::Open;
}

void Barrier::close() {
  log2("BARRIER", "Barrier closed.");
  state_ = BarrierState::Closed;
}

bool Barrier::is_open() const { return state_ == BarrierState::Open; }
