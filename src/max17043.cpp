#include "max17043.h"

#include "MAX1704X.h"

static MAX1704X max1704x = MAX1704X(5);

void max17043_begin() {
  max1704x.begin();
}

void max17043_handle() {
  max1704x.voltage();
  max1704x.percent();
}
