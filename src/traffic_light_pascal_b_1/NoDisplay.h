#pragma once
#include "IDisplay.h"

class NoDisplay : public IDisplay {
  public:
    void begin() override {}
    void show(int) override {}
};
