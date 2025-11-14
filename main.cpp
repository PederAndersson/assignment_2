
#include <filesystem>
#include "src/measurement.h"
#include "src/SystemController.h"
namespace fs = std::filesystem;
int main() {
    MeasurementStorage storage;
    SystemController controller(storage);
    controller.run();
    return 0;
}