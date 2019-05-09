#include <stdio.h>
#include "ProcessResultsDynamicArray.h"
#include "ProcessResult.h"

int main() {
    struct ProcessResultsDynamicArray* resultsArray = createProcessResultsDynamicArray(2);
    printf("ProcessResultsDynamicArray: { size: %d, capacity: %d }\n", resultsArray->size, resultsArray->capacity);
    struct ProcessResult* result1 = createProcessResult(1, 0, 10);
    setFinish(result1, 10);
    addResultToDynamicArray(resultsArray, result1);
    printf("ProcessResultsDynamicArray: { size: %d, capacity: %d }\n", resultsArray->size, resultsArray->capacity);
    struct ProcessResult* result2 = createProcessResult(2, 1, 2);
    setFinish(result2, 12);
    addResultToDynamicArray(resultsArray, result2);
    printf("ProcessResultsDynamicArray: { size: %d, capacity: %d }\n", resultsArray->size, resultsArray->capacity);
    struct ProcessResult* result3 = createProcessResult(3, 2, 9);
    setFinish(result3, 21);
    addResultToDynamicArray(resultsArray, result3);
    struct ProcessResult* result4 = createProcessResult(4, 3, 5);
    setFinish(result4, 26);
    addResultToDynamicArray(resultsArray, result4);
    printf("ProcessResultsDynamicArray: { size: %d, capacity: %d }\n", resultsArray->size, resultsArray->capacity);

    struct ProcessResult* retrieve = getProcessResultFromDynamicArray(resultsArray, 1);
    printProcessResult(retrieve);
    printf("\n\n");
    
    printResults(resultsArray);
    return 0;
}
