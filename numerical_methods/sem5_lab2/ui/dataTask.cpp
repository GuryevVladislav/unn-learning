#include "dataTask.h"

void TaskData::push(DataType type, double val) {
    switch (type) {
        case DataType::I:
            i.push_back(val);
        break;
        case DataType::X:
            x.push_back(val);
        break;
        case DataType::V:
            v.push_back(val);
        break;
        case DataType::U:
            u.push_back(val);
        break;
        case DataType::X2:
            x2.push_back(val);
        break;
        case DataType::V2:
            v2.push_back(val);
        break;
        case DataType::DIFF:
            diff.push_back(val);
        break;
    }
}
