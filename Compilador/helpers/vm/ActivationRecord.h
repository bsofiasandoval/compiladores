#pragma once

struct ActivationRecord {
    int    returnHere;
    int    localIntStart;
    int    localFloatStart;
    int*   ints;
    float* floats;


    ActivationRecord(int returnHere, int localIntCount, int tempIntCount, int localFloatCount, int tempFloatCount){
        this->returnHere = returnHere;
        this->localIntStart = localIntCount;
        this->localFloatStart = localFloatCount;
        int intsSize = localIntCount + tempIntCount;
        int floatsSize = localFloatCount + tempFloatCount;
        ints   = intsSize > 0 ? new int  [intsSize]() : nullptr;
        floats = floatsSize > 0 ? new float[floatsSize]() : nullptr;
    }
  

    ~ActivationRecord() {
        delete[] ints;
        delete[] floats;
    }
};
