#include "ProcessResult.h"
int main() {
    struct ProcessResult* processResult = createProcessResult(1,1,1);
    printResultHeader();
    printProcessResult(processResult);
    incrementContextSwitchCount(processResult);
    printProcessResult(processResult);
    setFinish(processResult, 100);
    printProcessResult(processResult);
    return 0;
}
