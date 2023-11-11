//#Manuscript Title: Identifying genes related to Retinitis Pigmentosa in Drosophila Melanogaster using gene expression data
//#Supplementary Material
//C++ code for the implemented algorithm
//code built using CLion 2021.3.3

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>


using namespace std;

int main() {

    // defining all variables and parameters as needed

    ifstream inputFileGeneExpression;
    ifstream inputFileEyeSizes;
    ifstream outputFileGenes;
    string Strain;
    string MeanEyeSize;
    vector<string> expressionFieldLines;
    vector<string> Strain_;
    vector<float> MeanEyeSize_;
    float maxEyeSizes;
    float minEyeSizes;
    int countEyeSizeData = 0;



    // reading first input file dgrp_expression_Female.txt

    inputFileGeneExpression.open(
            "C:/Users/sahit/OneDrive/Desktop/CS_grad/hpc/Project/dgrp_expression_Female_test.txt");


    // access each word from the txt file and store them into a string vector so it can be manipulated later as required
    // remember there are 369 values in each line these values can be stores in a 2D array after finalizing no of rows
    // use the following code to populate 2D array
    //    string newarray[3][369];
    //    int a;
    //    for (int i=0; i < 3; i++){
    //        for (int j = 0; j< 369; j ++,a++){
    //            newarray[i][j]= expressionFieldLines[i];
    //        }
    //    }
    // currently separating each word and send to vector as a member

    if (inputFileGeneExpression.is_open()) {
        string line;
        while (!inputFileGeneExpression.eof()) {
            while (getline(inputFileGeneExpression, line, '\t')) {
                stringstream ss(line);
                string temp;
                while (getline(ss, temp, '\t'))
                    expressionFieldLines.push_back(temp);

            }

        }
    }
// checking to see if data are received and stored correctly

    int rows = expressionFieldLines.size();
    cout << "no of rows = " << rows << endl;
    cout << "first element = " << expressionFieldLines[0] << endl;
    cout << "second element = " << expressionFieldLines[1] << endl;
}
/*
    // read second input file Rh1G69D.txt and store each column on separate vector

    inputFileEyeSizes.open("C:/Users/suman/OneDrive/Documents/College/Semester 1/HPC/DataInC/Rh1G69D.txt");

    if (inputFileEyeSizes.is_open()) {
        //ignore first line
        string header;
        getline(inputFileEyeSizes, header, '\n');

        while (!inputFileEyeSizes.eof()) {   // while not at the end of the file perform the operation inside the loop
            getline(inputFileEyeSizes, Strain,
                    '\t'); // read data separated by tab // it is the first element of the row i.e Strain
            stringstream ss(
                    Strain); // creating stringstream object ss as passing Stain directly did not load the vector correctly
            string temp;                 // creating new variable to pass the value obtained in ss
            while (getline(ss, temp, '\t'))
                Strain_.push_back(temp); // push value in the Strain_ vector
            getline(inputFileEyeSizes, MeanEyeSize, '\n'); // jump to new line
            MeanEyeSize_.push_back(stof(MeanEyeSize));   //Push value in the MeanEyeSize_ vector
            countEyeSizeData = countEyeSizeData + 1;

        }
        cout << "Number of entries in = " << countEyeSizeData - 1 << endl;
        //Printing First and Last values for confirmation
        cout << "Check First Strain = " << Strain_[0] << " and First Mean Eye Size = " << MeanEyeSize_[0] << endl;
        cout << "Check Last Strain = " << Strain_[countEyeSizeData - 2] << " and Last Mean Eye Size = "
             << MeanEyeSize_[countEyeSizeData - 2] << endl;

    } else {
        cout << "unable to open file" << endl;
    }
    minEyeSizes = *min_element(MeanEyeSize_.begin(), MeanEyeSize_.end());
    maxEyeSizes = *max_element(MeanEyeSize_.begin(), MeanEyeSize_.end());
    cout << "The min element is " << minEyeSizes << endl;
    cout << "The max element is " << maxEyeSizes << endl;

    // calculate 20.9 and 87.2 percentile value from the minimum and maximum value
    // they are used as the threshold for the extreme phenotype in the reference R program

    double extremeTopThreshold, extremeBotttomThreshold;
    extremeBotttomThreshold = minEyeSizes + ((maxEyeSizes - minEyeSizes) * 0.209);
    extremeTopThreshold = minEyeSizes + ((maxEyeSizes - minEyeSizes) * 0.872);

    cout << "The upperthreshhold_value is " << extremeTopThreshold << endl;
    cout << "lowerthreshhold_value is " << extremeBotttomThreshold << endl;

    // create smallEyeSizesIndexVector by comparing each element of eyeSizes vector with extremeBottomThreshold
    // and returning 1 if eye size is less than extremeBottomThreshold
    // use vector definition code  below if needed. Currently, using array instead of vector so array are index
    // based and easy to write values
    // ********************************************************************
    // vector <int> smallEyeSizesIndexVector;
    //    for (int i = 0; i < MeanEyeSize_.size(); i++) {
    //        if (MeanEyeSize_[i] < extremeBotttomThreshold)
    //        eyeSizesIndex.push_back(1)
    //        else eyeSizesIndex.push_back(0)
    //    }

    int smallEyeSizesIndexVector[countEyeSizeData];

    for (int i = 0; i < MeanEyeSize_.size(); i++) {
        if (MeanEyeSize_[i] < extremeBotttomThreshold)
            smallEyeSizesIndexVector[i] = 1;
        else smallEyeSizesIndexVector[i] = 0;
    }

//    cout << "MeanEyeSize_[0] = " << MeanEyeSize_[0] << endl;
//    cout << "extremeBottomThreshold = " << extremeBotttomThreshold << endl;
//    cout << "smallEyeSizesIndexVector[0] = " << smallEyeSizesIndexVector[0] << endl;


    // create largeEyeSizesIndexVector by comparing each element of eyeSizes vector with extremeTopThreshold
    // and returning 1 if eyesize is greater than extremeTopThreshold

    int largeEyeSizesIndexVector[countEyeSizeData];

    for (int i = 0; i < MeanEyeSize_.size(); i++) {
        if (MeanEyeSize_[i] > extremeTopThreshold)
            largeEyeSizesIndexVector[i] = 1;
        else largeEyeSizesIndexVector[i] = 0;
    }

    // combining smallEyeSizesIndexVector and largeEyeSizesIndexVector
    // and putting them into a single eyeSizesBooleanIndexVector

    int eyeSizesBooleanIndexVector[countEyeSizeData];

    for (int i = 0; i < MeanEyeSize_.size(); i++) {
        if (smallEyeSizesIndexVector[i] || largeEyeSizesIndexVector[i])
            eyeSizesBooleanIndexVector[i] = 1;
        else eyeSizesBooleanIndexVector[i] = 0;
    }

    // create eyeSize index vector that contains the value of position of extreme phenotypes in the MeanEyeSize vector

    vector<int> eyeSizesIndex;
    for (int i = 0; i < MeanEyeSize_.size(); i++) {
        if (eyeSizesBooleanIndexVector[i] == 1) {
            eyeSizesIndex.push_back(i);
        }

    }
    int numberOfSelectedLines = eyeSizesIndex.size();
    cout << "size of eyeSizeIndex vector = " << numberOfSelectedLines << endl;
    cout << "eyeSizesIndex[0] = " << eyeSizesIndex[0] << endl;
    // the value we get here is 6 but remember this is 7th element on the table as it is 0 based indexing

    int smallEyeSizes =
}
*/