
#include "src/measurement.h"
#include "src/SystemController.h"
int main() {
    MeasurementStorage storage;
    SystemController controller(storage);
    controller.run();
    return 0;
}