/* Generating Values by Specific Probabilities */

#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>
#include <unordered_map>
using namespace std;


int random(vector<int> const &input, vector<int> const &prob){

	size_t n = input.size();                // Getting the Size of Input Vector
	// The Size of Input Vector must Be Equal to the Size of Probability Vector
	if (n != prob.size())
		return -1;  // Error!


	vector<int> prob_sum(n, 0);     // Creating a New Vector with the Size of Input and 0 Elements

    // Assigning Incremental Summation of Probability Vector Elements to the prob_sum() Vector
	prob_sum.at(0) = prob.at(0);                            // prob_sum[0] = prob[0]
	for (size_t i = 1; i < n; i++)                          // prob_sum[1] = prob[1] + prob_sum[0];
		prob_sum.at(i) = prob_sum.at(i-1) + prob.at(i);     // prob_sum[2] = prob[2] + prob_sum[1];
                                                            // prob_sum[3] = prob[3] + prob_sum[2];
                                                            // ...

	int prand = (rand() % 100) + 1;         // Assigning A Random Integer (Probability Value) to prand: [1, 100]

	if (prand <= prob_sum.at(0))                                    // If: 0 < r <= prob_sum[0]
		return input.at(0);                                         // return input[0]

	for (size_t i = 1; i < n; i++){                                 // For Each Element Except 1st One in the Input
		if (prand > prob_sum.at(i-1) && prand <= prob_sum.at(i))    // If i Provides: prob_sum[i-1] < r <= prob_sum[i]
			return input.at(i);                                     // return input[i]
	}

return 0;
}


int main(){

	vector<int> inputnumber = {1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> probability = {20, 15, 5, 10, 20, 15, 5, 10};

	cout << "\ninputnumber = {" << inputnumber.at(0);
    for(size_t i=1; i<inputnumber.size(); i++)
        cout << ", " << inputnumber.at(i);
    cout << "}" << endl;

    cout << "probability = {" << probability.at(0);
    for(size_t i=1; i<probability.size(); i++)
        cout << ", " << probability.at(i);
    cout << "}" << endl;


	srand(time(NULL));

	unordered_map<int, int> freq;   // To Store the Generated Values with Their Frequences

    float run = 1000;
    cout << endl << "random(inputnumber, probability){100x" << run << "}:" << endl << endl;

	for (int i = 0; i < 100 * run; i++) {
		int val = random(inputnumber, probability);
		freq[val]++;   // Filling the Unordered Map with Frequencies of the Returned Values
	}


    int prec = log10(run);
    cout << setprecision(prec) << fixed;

	for (size_t i = 0; i < inputnumber.size(); i++)
		cout << "Returned inputnumber[" << i << "]=" << inputnumber.at(i) << " w/ " << setfill('0') << setw(3 + prec)
             << freq[inputnumber.at(i)] / run << "% ~ " << setfill('0') << setw(2) << probability.at(i) << "%" << endl;


cout << endl << endl << "-------------" << endl;
system("pause");
return 0;
}
