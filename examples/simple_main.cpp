
#include "toylab/log.hpp"

int main() {
    LOG(DEBUG) << "A DEBUG message test";
    LOG(INFO) << "An INFO message test";
    LOG(WARNING) << "A WARNING message test";
    LOG(ERROR) << "A ERROR message test";
    LOG(APPFATAL) << "An APPFATAL message test";
    LOG(FATAL) << "fatal level log - this LOG call will kill the process";
    return 0;
}
