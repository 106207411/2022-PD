#include <iostream>
#include <cstring>
using namespace std;

// find the city to build hospital
void findHospital(int** cityDist, int*& hospitalArr, int nCity, int nHospital, int maxDist, int mode);

// find the smallest sum distance from each city to the hospital
// find the number of happy city
void findSmallestDistAndHappyCity(int** cityDist, int* hospitalArr, int nCity, int nHospital, int maxDist, int& sumDistToHospital, int& nHappyCity);

// return true if the city is already a hospital
bool isHospital(int* hospitalArr, int nHospital, int city);

// compute the distance from the city to the hospital built
int localMinDist(int** cityDist, int* hospitalArr, int hosp, int city);

// print out the cities with hospital in lowercase
void printCityWithHospital(char** cityName, int* hospitalArr, int nHospital);

int main() {
    int n = 0, k = 0, l = 0, t = 0;
    cin >> n >> k >> l >> t;

    // read the distance between each city
    int** cityDist = new int*[n];
    for (int i = 0; i < n; i++) {
        cityDist[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> cityDist[i][j];
        }
    }

    // read the name of each city
    char** cityName = new char*[n];
    // ignore the newline character \n
    cin.ignore();
    for (int i = 0; i < n; i++) {
        cityName[i] = new char[50];
        cin.getline(cityName[i], 50);
    }
    
    // find the city to build hospital
    int* cityWithHospital = new int[k];
    findHospital(cityDist, cityWithHospital, n, k, l, t);

    // find the smallest sum distance from each city to the hospital
    // find the number of happy city
    int sumDistToHospital = 0;
    int nHappyCity = 0;
    findSmallestDistAndHappyCity(cityDist, cityWithHospital, n, k, l, sumDistToHospital, nHappyCity);

    // print out the cities with hospital in lowercase
    printCityWithHospital(cityName, cityWithHospital, k);

    cout << sumDistToHospital << ";" << nHappyCity;
    return 0;
}

void findHospital(int** cityDist, int*& hospitalArr, int nCity, int nHospital, int maxDist, int mode){

    // mode = 0: find nHospital cities with the smallest sum of distances to other cities
    // mode = 1: find nHospital cities with the largest happy cities
    for (int hosp = 0; hosp < nHospital; hosp++) {
        int minDist = 1000000;
        int maxHappyCity = 0;
        for (int i = 0; i < nCity; i++) {

            // if the city is already a hospital, skip the iteration
            if (isHospital(hospitalArr, hosp, i)) {
                continue;
            }

            int sumDistToHospital = 0;
            int nHappyCity = 0;
            for (int j = 0; j < nCity; j++) {
                if (mode == 0) {
                    // compute the distance from the city to the hospital built
                    sumDistToHospital += min(cityDist[i][j], localMinDist(cityDist, hospitalArr, hosp, j));
                }
                else if (mode == 1) {
                    // compute the distance from the city to the hospital built
                    if (min(cityDist[i][j], localMinDist(cityDist, hospitalArr, hosp, j)) <= maxDist) {
                        nHappyCity++;
                    }
                }
            }
            if (mode == 0) {
                if (sumDistToHospital < minDist) {
                    minDist = sumDistToHospital;
                    hospitalArr[hosp] = i;
                }
            }
            else if (mode == 1) {
                if (nHappyCity > maxHappyCity) {
                    maxHappyCity = nHappyCity;
                    hospitalArr[hosp] = i;
                }
            }
        }
    }
}


bool isHospital(int* hospitalArr, int hosp, int city) {
    for (int i = 0; i < hosp; i++) {
        if (hospitalArr[i] == city) {
            return true;
        }
    }
    return false;
}


int localMinDist(int** cityDist, int* hospitalArr, int hosp, int city) {
    int localMinDist = 1000000;
    for (int k = 0; k < hosp; k++) {
        localMinDist = min(cityDist[hospitalArr[k]][city], localMinDist);
    }
    return localMinDist;
}



void findSmallestDistAndHappyCity(int** cityDist, int* hospitalArr, int nCity, int nHospital, int maxDist, int& sumDistToHospital, int& nHappyCity) {
    for (int i = 0; i < nCity; i++) {
        int minDist = 1000000; 
        for (int j = 0; j < nHospital; j++) {
            if (cityDist[i][hospitalArr[j]] < minDist) {
                minDist = cityDist[i][hospitalArr[j]];
            }
        }
        sumDistToHospital += minDist;
        if (minDist <= maxDist) {
            nHappyCity++;
        }
    }
}

void printCityWithHospital(char** cityName, int* hospitalArr, int nHospital) {
    for (int i = 0; i < nHospital; i++) {

        // remove multiple spaces in the city name
        int j = 0;
        while (cityName[hospitalArr[i]][j] != '\0') {
            if (cityName[hospitalArr[i]][j] == ' ' && cityName[hospitalArr[i]][j + 1] == ' ') {
                for (unsigned int k = j; k < strlen(cityName[hospitalArr[i]]); k++) {
                    cityName[hospitalArr[i]][k] = cityName[hospitalArr[i]][k + 1];
                }
            }
            else {
                j++;
            }
        }

        // replace the space in the city name with -
        for (unsigned int j = 0; j < strlen(cityName[hospitalArr[i]]); j++) {
            if (cityName[hospitalArr[i]][j] == ' ') {
                cityName[hospitalArr[i]][j] = '-';
            }
            cout << static_cast<char>(tolower(cityName[hospitalArr[i]][j]));
        }
        cout << endl;
    }
}