#pragma once

#include <limits>
#include <random>
#include <string>

#include "SortCreator.h"
#include "FileHandler.h"
#include "GetRandom.h"
#include "Timer/Timer.h"

class Manager {
public:
    //file mode
    Manager(int p, int a, const std::string& iF, const std::string& oF) {
        problem = p;
        algorithm = a;
        inputFile = iF;
        outputFile = oF;

        loadFromFile();
    }

    Manager(int p, int a, const std::string& iF) {
        problem = p;
        algorithm = a;
        inputFile = iF;

        loadFromFile();
    }

    //test mode
    Manager(int p, int a, int s, int d, int c, const std::string& oF) {
        problem = p;
        algorithm = a;
        size = s;
        density = d;
        count = c;
        outputFile = oF;

        fillArrayRandom();
    }

    void sortArray() {
        auto sorter = creator.createSorter(algorithm);
        if (!sorter) {
            throw std::invalid_argument("Invalid algorithm type. ");
        }

        Timer zegareczek;
        sorter->sort(initialData, size);
        zegareczek.stop();

        fileHandler.writeFileResults(algorithm, dataType, size, outputFile, zegareczek.result());
        delete sorter;
    }

    private:
    void loadFromFile() {
        fileHandler.readFile(inputFile);
        initialData = fileHandler.getData();
        size = fileHandler.getSize();
    }

    void printArray(const T* arr, int size) {
        if (arr == nullptr || size <= 0) {
            std::cout << "Invalid array or size." << std::endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void fillArrayRandom() {
        initialData = new T[size];

        if constexpr (std::is_integral_v<T>) {
            for (int i = 0; i < size; i++) {
                initialData[i] = GetRandom::getInt(
                    std::numeric_limits<T>::lowest(),
                    std::numeric_limits<T>::max()
                );
            }
        } else {
            constexpr T limit = static_cast<T>(1e6);
            for (int i = 0; i < size; i++) {
                initialData[i] = GetRandom::getReal(-limit, limit);
            }
        }
    }

    [[nodiscard]] int getAlgorithm() const {
        return algorithm;
    }

    [[nodiscard]] int getSize() const {
        return size;
    }

    [[nodiscard]] std::string getInputFile() const {
        return inputFile;
    }

    [[nodiscard]] std::string getOutputFile() const {
        return outputFile;
    }

    int problem;
    int algorithm;
    int density;
    int count;
    int size = 0;

    std::string inputFile;
    std::string outputFile;

    T* initialData = nullptr;
    SortCreator<T> creator;
    FileHandler<T> fileHandler;
};