#include "Filter.h"

Filter::Filter()
: minValue(INT16_MAX), 
  maxValue(INT16_MIN) {}

void Filter::addValue(int16_t value) {
    // If the new value replaces minValue or maxValue,
    // we need to update these values.
    if (values[nextIndex] == minValue || values[nextIndex] == maxValue) {
        minValue = value;
        maxValue = value;
        for (int i = 0; i < 5; i++) {
            if (values[i] < minValue) minValue = values[i];
            if (values[i] > maxValue) maxValue = values[i];
        }
    } else {
        if (value < minValue) minValue = value;
        if (value > maxValue) maxValue = value;
    }

    values[nextIndex] = value;
    nextIndex = (nextIndex + 1) % 5;
}

int16_t Filter::getAverage()  {
    int32_t sum = 0; // Use a 32-bit int to avoid overflow when summing
    for (int i = 0; i < 5; i++) {
        sum += values[i];
    }
    sum -= (minValue + maxValue);
    return static_cast<int16_t>(sum / 3); // Cast back to 16-bit after division
}
