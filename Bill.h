#pragma once
#include <string>
struct Bill {
  int money;
  int64_t unique_id;
  int limit_confirmed;
  int limit_uncomfired;
  int lowest_border;
  Bill() = default;
};