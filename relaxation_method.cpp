#include <bits/stdc++.h>
using namespace std;

const int N = 100;
int n;
vector< vector<double> > matrix;
vector<double> currentSolution;
double w;
int cnt = 0;


void init() {
	for (int i = 0; i < n; i++) {
		double dd = matrix[i][i];
    	for (int j = 0; j < n + 1; j++) {
        	matrix[i][j] = -matrix[i][j] / dd;
        }
    }
    for (int i = 0; i < n; i++) {
    	currentSolution.push_back(0.0);
    }
}


double getError(const vector<double>& solution) {
	double error = 0.0;
	for (int i = 0; i < n; i++) {
		double curError = matrix[i][n];
		for (int j = 0; j < n; j++) {
			curError += solution[j] * matrix[i][j];
		}
		error = max(error, abs(curError));
	}
	return abs(error);
}


vector<double> nextSolve() {
	cnt++;
	vector<double> tmpSolution;
	vector<double> nextSolution;
	for (int i = 0; i < n; i++) {
		tmpSolution.push_back(currentSolution[i]);
	}
    for (int i = 0; i < n; i++) {
        tmpSolution[i] = matrix[i][n];
        //????
        for (int j = 0; j < n; j++) {
            if (i != j) tmpSolution[i] += tmpSolution[j] * matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        nextSolution.push_back(w * tmpSolution[i] + (1 - w) * currentSolution[i]);
    }
	cout.precision(6);
	cout << "��� " << cnt << ". ������� �������: (";
	for (int i = 0; i < n; i++) {
		cout << nextSolution[i];
		if (i < n - 1) cout << ", ";
		else cout << ") ";
	}
	cout << "������ = " << getError(nextSolution) << endl;
	return nextSolution;
}

vector<double> getSolution(double eps) {
	double error = getError(currentSolution);
	while (error > eps) {
		currentSolution = nextSolve();
		error = getError(currentSolution);
	}
	return currentSolution;
}

int main() {
	cin >> n;
    for (int i = 0; i < n; i++) {
    	vector<double> tmp;
    	for (int j = 0; j <= n; j++) {
    		double a;
    		cin >> a;
	        tmp.push_back(a);
        }                    
        matrix.push_back(tmp);
    }
    init();
    cout.precision(6);

    cout << "������� ���������:" << endl;
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		cout << matrix[i][j] << "*x_" << j + 1 << " + ";
    	}
    	cout << matrix[i][n]  << " = 0" << endl;
    }

	cin >> w;
	double eps;
	cin >> eps;
	cout << "w = " << w << "; epsilon = " << eps << endl;
	cout << "===================" << endl;
    vector<double> solution = getSolution(eps);
    cout << "��������� �������: (";
	for (int i = 0; i < n; i++) {
		cout << solution[i];
		if (i < n - 1) cout << ", ";
		else cout << ")";
	}	
	cout << endl;
	return 0;
}