#include "Filter.h"

// Definiera konstanta gränsvärden för int16_t för att undvika användning av makron.
constexpr int16_t INT16_MAX_VAL = 32767;
constexpr int16_t INT16_MIN_VAL = -32768;

// Standardkonstruktor för Filter-klassen.
Filter::Filter()
: minValue(INT16_MAX_VAL), // Sätt igång med det största möjliga negativa värdet för int16_t.
  maxValue(INT16_MIN_VAL){ // Sätt igång med det största möjliga positiva värdet för int16_t.
            // Initialisera nästa index för insättning till 0.
    // Initialisera värdena i 'values'-arrayen med 0.
    for (int i = 0; i < 5; i++) {
        values[i] = 0;
    }
    nextIndex = 0;
}

// Metod för att lägga till ett nytt värde i filterlistan.
void Filter::addValue(int16_t value) {
    // Om det nya värdet ersätter minValue eller maxValue,
    // kan vi behöva uppdatera dessa värden.
    if (values[nextIndex] == minValue || values[nextIndex] == maxValue) {
        // Återställ min och max.
        minValue = INT16_MAX_VAL;
        maxValue = INT16_MIN_VAL;
        
        // Beräkna det nya min- och max-värdet, hoppa över det aktuella nextIndex-värdet.
        for (int i = 0; i < 5; i++) {
            if (i == nextIndex) continue; // Hoppa över det värde som ska ersättas.
            if (values[i] < minValue) minValue = values[i];
            if (values[i] > maxValue) maxValue = values[i];
        }
    }

    // Uppdatera med det nya värdet.
    if (value < minValue) minValue = value;
    if (value > maxValue) maxValue = value;

    // Spara det nya värdet och uppdatera nextIndex.
    values[nextIndex] = value;
    nextIndex = (nextIndex + 1) % 5; // Använd modulo för att loopa tillbaka till början av arrayen om det behövs.
}

// Metod för att hämta medelvärdet av de lagrade värdena, exkluderar minsta och största värdet.
int16_t Filter::getAverage() {
    int32_t sum = 0; // Använd ett 32-bitars heltal för att undvika överflöde när man summerar.

    // Beräkna summan av alla värden.
    for (int i = 0; i < 5; i++) {
        sum += values[i];
    }

    // Dra bort minsta och största värdet från summan.
    sum -= (minValue + maxValue);

    // Returnera medelvärdet, och omvandla tillbaka till 16-bit efter division.
    return static_cast<int16_t>(sum / 3);
}
