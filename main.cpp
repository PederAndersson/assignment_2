
#include "src/measurement.h"
#include "src/SystemController.h"
int main() {
    ThresholdObserver obs;
    MeasurementStorage storage;
    SystemController controller(storage);
    controller.run();
    return 0;
}