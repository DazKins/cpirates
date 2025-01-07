#include "num.h"

float clamp(float value, float min, float max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

float wrap(float value, float min, float max) {
  if (value < min) {
    return max - (min - value);
  } else if (value > max) {
    return min + (value - max);
  } else {
    return value;
  }
}