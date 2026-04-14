#pragma once

class Barrier {

public:
  Barrier();
  void open();
  void close();
  bool is_open() const;

private:

  enum class BarrierState { Open, Closed };
  BarrierState state_;
};
