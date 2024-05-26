#include <iostream> 
using namespace std; 
int partition(string first_name[], string last_name[], 
			int height[], int low, int high) 
{ 
	int pivot = height[high];
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++) {  
		if (height[j] <= pivot) {  
			i++;  
			string temp = first_name[i]; 
			first_name[i] = first_name[j]; 
			first_name[j] = temp; 
			temp = last_name[i]; 
			last_name[i] = last_name[j]; 
			last_name[j] = temp; 
			int temp1 = height[i]; 
			height[i] = height[j]; 
			height[j] = temp1; 
		} 
	} 
	string temp = first_name[i + 1]; 
	first_name[i + 1] = first_name[high]; 
	first_name[high] = temp; 
	temp = last_name[i + 1]; 
	last_name[i + 1] = last_name[high]; 
	last_name[high] = temp; 
	int temp1 = height[i + 1]; 
	height[i + 1] = height[high]; 
	height[high] = temp1; 
	return (i + 1); 
} 
void quickSort(string first_name[], string last_name[], 
			int height[], int low, int high) 
{ 
	if (low < high) { 
		int pi = partition(first_name, last_name, 
						height, low, high);  
		quickSort(first_name, last_name, height, 
				low, pi - 1); 
		quickSort(first_name, last_name, height, 
				pi + 1, high); 
	} 
} 
void binarySearch(string first_name[], string 
										last_name[], 
				int height[], int value, int n) 
{ 

	int low = 0, high = n - 1; 
	int index; 
	while (low <= high) { 

		index = (high + low) / 2; 
		if (height[index] == 158) {  
			cout << "Person having height 158"
					" cms is "
				<< first_name[index] 
				<< " " << last_name[index] << endl; 
			return; 
		} 
		else if (height[index] > 158) 
			high = index - 1; 
		else
			low = index + 1; 
	} 
	cout << "Sorry, no such person with"
			" height 158 cms"; 
	cout << "is found in the record"; 
}  
void printParallelArray(string first_name[], 
						string last_name[], int height[], int n) 
{ 

	cout << "Name of people in increasing"; 
	cout << "order of their height: " << endl; 
	for (int i = 0; i < n; i++) { 

		cout << first_name[i] << " "
			<< last_name[i] << " has height "
			<< height[i] << " cms\n"; 
	} 
	cout << endl; 
} 
int main() 
{  
	int n = 10; 
	string first_name[] = { "Bones", "Welma", 
							"Frank", "Han", "Jack", "Jinny", "Harry", 
							"Emma", "Tony", "Sherlock" }; 
	string last_name[] = { "Smith", "Seger", 
						"Mathers", "Solo", "Jackles", "Weasly", 
						"Potter", "Watson", "Stark", "Holmes" }; 
	int height[] = { 169, 158, 201, 183, 172, 
					152, 160, 163, 173, 185 }; 
	quickSort(first_name, last_name, height, 
			0, n - 1); 
	printParallelArray(first_name, last_name, 
					height, n);  
	cout << "Name of the second tallest person"
			" is "
		<< first_name[n - 2] << " "
		<< last_name[n - 2] << endl; 
	cout << "Name of the third shortest person is "
		<< first_name[2] << " " << last_name[2] 
		<< endl;  
	binarySearch(first_name, last_name, height, 
				158, n); 
	return 0; 
}

