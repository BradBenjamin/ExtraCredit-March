#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

string read_file(const string& filename) {
    string content; // Initialize an empty string to store the file content

    // Open the file for reading
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file " << filename << endl;
        return ""; // Return an empty string if file cannot be opened
    }

    // Read the content of the file into the string
    char ch;
    while (file.get(ch)) {
        content += ch; // Append each character to the string
    }

    file.close(); // Close the file

    return content;
}
vector<float> read_letter_distribution(const string& filename) {
    vector<float> letter_distribution;

    // Open the file for reading
    ifstream file(filename);
    if (!file.is_open()) {
        // Print error message if unable to open the file
        cerr << "Error: Unable to open the file " << filename << endl;
        return letter_distribution; // Return empty vector if file cannot be opened
    }

    // Read each line in the file
    string line;
    while (getline(file, line)) {
        // Convert the frequency from string to float and append to the vector
        letter_distribution.push_back(stof(line));
    }

    file.close(); // Close the file
    return letter_distribution;
}
vector<float> calculate_letter_frequency_of_a_string(const string& text) {
    vector<int> letter_count(26, 0); // Initialize a vector to store the count of each letter
    vector<float> letter_frequency(26, 0.0); // Initialize a vector to store the frequency of each letter
    int total_letters = 0; // Initialize a variable to count the total number of letters in the text

    // Read each character in the file
    for(char ch : text) {
        if (isalpha(ch)) { // Check if the character is a letter
            ch = tolower(ch); // Convert the character to lowercase
            letter_count[ch - 'a']++; // Increment the count for the corresponding letter
            total_letters++; // Increment the total number of letters
        }
    }

    // Calculate the frequency of each letter
    for (int i = 0; i < 26; ++i) {
        letter_frequency[i] = static_cast<float>(letter_count[i]) / total_letters * 100; // Convert count to frequency (percentage)
    }

    return letter_frequency;
}
float chi_square_distance(const vector<float>& frequency1, const vector<float>& frequency2) {
    if (frequency1.size() != frequency2.size()) {
        cerr << "Error: Histogram sizes do not match." << endl;
        return -1.0; // Return -1.0 to indicate an error
    }

    float distance = 0.0;
    for (size_t i = 0; i < frequency1.size(); ++i) {
        if (frequency1[i] + frequency2[i] != 0) { // Avoid division by zero
            float term = pow(frequency1[i] - frequency2[i], 2) / (frequency1[i] + frequency2[i]);
            distance += term;
        }
    }

    return distance;
}
void left_rotate_alphabet(string& input) {
    for (char& ch : input) {
        if (isalpha(ch)) { // Check if the character is a letter
            if (ch == 'a') { // Wrap around to 'z' if character is 'a'
                ch = 'z';
            } else if (ch == 'A') { // Wrap around to 'Z' if character is 'A'
                ch = 'Z';
            } else { // Otherwise, shift the character one position to the left in the alphabet
                ch--;
            }
        }
    }
}
string break_caesar(const vector<float>& language_frequency, string &encoded_message){
    string solution;
    string copy;
    float min_distance= chi_square_distance(calculate_letter_frequency_of_a_string(encoded_message), language_frequency);
    copy=encoded_message;
    for(int i=1;i<=26;i++)
    {
        left_rotate_alphabet(copy);
        vector<float> distribution_of_current= calculate_letter_frequency_of_a_string(copy);
        float new_distance= chi_square_distance(distribution_of_current, language_frequency);
        if(new_distance<min_distance)
        {
            solution=copy;
            min_distance=new_distance;
        }
    }
    return solution;
}
void display_menu(){
    cout<<"Choose one of the following options:"<<endl;
    cout<<"0.Exit"<<endl;
    cout<<"1.Decode the message in coded_prop.txt"<<endl;
    cout<<"2.Display the frequency of each letter in coded_prop.txt"<<endl;
    cout<<"3.Display the frequency of each letter in English"<<endl;
}
int main() {
    const string distribution_file = "distribution.txt";
    vector<float> distribution_array = read_letter_distribution(distribution_file);
    // Check if the vector is empty (indicating failure to open the file)
    if (distribution_array.empty()) {
        // Print error message if file cannot be opened
        cerr << "Error: Unable to read data from file." << endl;
        return 1; // Return non-zero exit code to indicate failure
    }
    cout<<endl;
    display_menu();
    cout<<"Option: ";
    int x;
    cin>>x;
    while (x!=0){
        if (x==1){
            string coded_message= read_file("coded_prop.txt");
            cout<<break_caesar(distribution_array, coded_message);
        }
        if(x==2){
            string coded_message= read_file("coded_prop.txt");
            vector<float> coded_array= calculate_letter_frequency_of_a_string(coded_message);
            cout << "Letter Distribution in the coded message:" << endl;
            for (size_t i = 0; i < coded_array.size(); ++i) {
                cout << "Letter " << (char)('a' + i) << ": " << coded_array[i] << endl;
            }
        }
        if (x==3){
            cout << "Letter Distribution in the English alphabet:" << endl;
            for (size_t i = 0; i < distribution_array.size(); ++i) {
                cout << "Letter " << (char)('a' + i) << ": " << distribution_array[i] << endl;
            }
        }
        cout<<endl<<"Option: ";
        cin>>x;
    }
    return 0;
}