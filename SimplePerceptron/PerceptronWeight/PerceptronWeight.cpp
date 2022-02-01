#include <iostream>
#include <math.h>
using namespace std;

//Classes (linked list)
class dataPoint {
    public:
        dataPoint() {
            value[0] = 0;
            value[1] = 0;
            yValue = 0;
            nextDataPoint = nullptr;
        };
        dataPoint(float start[], int startYValue) {
            value[0] = start[0];
            value[1] = start[1];
            yValue = startYValue;
            nextDataPoint = nullptr;
        };
        float value [2];
        int yValue;
        dataPoint *nextDataPoint;
        friend ostream& operator<<(ostream& os, dataPoint outputDataPoint) {
            os << "[" << outputDataPoint.value[0] << "  " << outputDataPoint.value[1] << "]" << endl << "Y = " << outputDataPoint.yValue << endl;
            return os;
        }
};
class dataPointLinkedList {
    private:
        dataPoint *head;
        dataPoint *tail;
        int length;
    public:
        dataPointLinkedList(){
            length = 0;
            head = nullptr;
            tail = nullptr;
        }
        dataPoint* getHead() {
            return head;
        }
        dataPoint* getTail() {
            return tail;
        }
        dataPoint* getIndex(int index) {
            dataPoint* searching = head;
            for (int k = 0; k < index; k++) {
                searching = searching->nextDataPoint;
            }
            return searching;
        }
        void addDataPoint(dataPoint* addData) {
            dataPoint* creation = new dataPoint;
            *creation = *addData;
            if (length == 0) {
                head = creation;
            }
            else {
                dataPoint* previous = head;
                for (int k = 0; k < length - 1; k++) {
                    previous = previous->nextDataPoint;
                }
                previous->nextDataPoint = creation;
            }
            tail = creation;
            length++;
        }

        //Simplified linked list. Remove function and others have not been coded for simplicity
};

//functions
bool verifyWeights(dataPoint* checking, float testWeights[2], float testBias) {
    float result = (checking->value[0] * testWeights[0]) + (checking->value[1] * testWeights[1]) + testBias;
    if (result * checking->yValue > 0) {
        return true;
    }
    else {
        return false;
    }
};
int verifyShow(dataPoint* checking, float testWeights[2], float testBias) {
    float result = (checking->value[0] * testWeights[0]) + (checking->value[1] * testWeights[1]) + testBias;
    cout << "Y value = value[0]*weight[0] + value[1]*weight[1] + bias = " << checking->value[0] << "*" << testWeights[0] << " + " << checking->value[1] << "*" << testWeights[1] << " + " << testBias << " = " << result << endl;
    cout << "Expected Y value: " << checking->yValue << endl;
    if (result * checking->yValue > 0) {
        cout << "dataPoints Y value has the same sign as Y value calculated with current weight and bias" << endl;
        return true;
    }
    else {
        cout << "dataPoints Y value does not have the same sign as Y value calculated with current weight and bias" << endl;
        return false;
    }
};
void updateWeight(float currentWeight[], dataPoint* checking) {
    currentWeight[0] += (checking->yValue * checking->value[0]);
    currentWeight[1] += (checking->yValue * checking->value[1]);
};
float updateBias(float currentBias, dataPoint* checking) {
    return(currentBias + checking->yValue);
};
float dataLength(float value1, float value2) {
    float result;
    result = sqrt((value1*value1) + (value2 * value2));
    return result;
};

int main() {
    dataPointLinkedList dataSet;
    float* weight = new float[2];
    float initialWeight[2];
    float bias;
    float initialBias;
    int dataPointCount = 0;
    int misclassificationCount;
    int correctClassifications;
    int index;
    cout << "Enter initial weight vector values separated by spaces:" << endl;
    cin >> initialWeight[0];
    cin >> initialWeight[1];
    weight[0] = initialWeight[0];
    weight[1] = initialWeight[1];
    cout << weight[0] << " " << weight[1] << endl;
    cout << "Enter initial bias value:" << endl;
    cin >> initialBias;
    bias = initialBias;
    cout << "How many data points are being used?" << endl;
    while(dataPointCount < 2) {
        cin >> dataPointCount;
        if (dataPointCount < 2) {
            cout << "Please use more than 1 data point" << endl;
        }
    }
    for (int k = 0; k < dataPointCount; k++) {
        float inputs[2];
        int tempYValue;
        cout << "Enter the data for dataPoint " << k + 1 << " separated by spaces:" << endl;
        cin >> inputs[0];
        cin >> inputs[1];
        cout << "Enter the y value for dataPoint " << k + 1 << ":" << endl;
        cin >> tempYValue;
        dataPoint tempDataPoint(inputs, tempYValue);
        dataSet.addDataPoint(&tempDataPoint);
        cout << "Added dataPoint" << endl;
    }
    cout << "Data collected" << endl;
    //menu
    while (true) {
        string request;
        cout << endl << "Menu:" << endl << "-ViewInputs" << endl << "-Results" << endl << "-ShowWork" << endl << "-End" << endl;
        cin >> request;
        if (request == "Results") {
            weight[0] = initialWeight[0];
            weight[1] = initialWeight[1];
            bias = initialBias;
            misclassificationCount = 0;
            correctClassifications = 0;
            index = 0;
            while (correctClassifications < dataPointCount) {
                if (verifyWeights(dataSet.getIndex(index), weight, bias) == false) {
                    updateWeight(weight, dataSet.getIndex(index));
                    bias = updateBias(bias, dataSet.getIndex(index));
                    misclassificationCount++;
                    correctClassifications = 0;
                }
                else {
                    correctClassifications++;
                }
                index++;
                if (index >= dataPointCount) {
                    index = 0;
                }
            }
            cout << endl << "Resulting weight vector:" << endl;
            cout << "[" << weight[0] << "  " << weight[1] << "]" << endl;
            cout << "Length of resulting weight vector: " << dataLength(weight[0], weight[1]) << endl;
            cout << "Resulting bias: " << bias << endl;
            cout << "Number of misclassifications: " << misclassificationCount << endl;
        }
        if (request == "ViewInputs") {
            cout << endl << "Inputs:" << endl;
            for (int k = 0; k < dataPointCount; k++) {
                cout << "DataPoint " << (k + 1) << ":" << endl << *dataSet.getIndex(k) << endl;
            }
            cout << "Starting weight:" << endl << "[" << initialWeight[0] << "  " << initialWeight[1] << "]" << endl;
            cout << "Starting bias: " << initialBias << endl;
        }
        if (request == "ShowWork") {
            weight[0] = initialWeight[0];
            weight[1] = initialWeight[1];
            bias = initialBias;
            misclassificationCount = 0;
            correctClassifications = 0;
            index = 0;
            while (correctClassifications < dataPointCount) {
                cout << "Checking dataPoint " << index + 1 << " with weight [" << weight[0] << "  " << weight[1] << "], and bias " << bias << endl;
                if (verifyShow(dataSet.getIndex(index), weight, bias) == false) {
                    cout << "Encountered misclassification" << endl;
                    cout << "Updating weight" << endl;
                    updateWeight(weight, dataSet.getIndex(index));
                    cout << "Updating bias" << endl;
                    bias = updateBias(bias, dataSet.getIndex(index));
                    misclassificationCount++;
                    correctClassifications = 0;
                    cout << "Consecutive correct classifications reset" << endl << endl;
                }
                else {
                    correctClassifications++;
                    cout << correctClassifications << " consecutive correct classifications" << endl << endl;
                }
                index++;
                if (index >= dataPointCount) {
                    index = 0;
                }
            }
            cout << endl << "Resulting weight vector:" << endl;
            cout << "[" << weight[0] << "  " << weight[1] << "]" << endl;
            cout << "Length of resulting weight vector: " << dataLength(weight[0], weight[1]) << endl;
            cout << "Resulting bias: " << bias << endl;
            cout << "Number of misclassifications: " << misclassificationCount << endl;
        }
        if (request == "End") {
            delete[] weight;
	        return 1;
        }
    }
}
