# Caesar's Cipher Solver

This project includes functions and a user-friendly menu-based application for various tasks related to Caesar's cipher.

## Functions:

### 1. Read Distribution from File
- **Description:** Reads the distribution of letters from a file named `distribution.txt` and stores it into an array. Each line in the file represents the frequency of a specific letter.
- **Function Name:** `read_letter_distribution(filename)`

### 2. Compute Normalized Frequency of Characters (Histogram)
- **Description:** Computes the normalized frequency of each character (a histogram) in a given text.
- **Function Name:** `calculate_letter_frequency_of_a_string(text)`

### 3. Compute Chi-square Distance between Two Histograms
- **Description:** Computes the Chi-square distance between two histograms representing the distribution of characters.
- **Function Name:** `chi_square_distance(frequency1, frequency2)`

### 4. Break Caesar’s Cipher using Frequency Analysis
- **Description:** Iteratively shifts the encrypted code through all possible permutations, computes the Chi-square distance between each permutation and the approximate distribution of letters in English, and returns the permutation with the least Chi-squared distance as the solution.
- **Function Name:** `break_caesar(language_frequency, encoded_message)`

## User-Friendly Menu Application:

The user-friendly menu application provides an interface for performing various tasks related to Caesar's cipher. It includes options such as:

1. Encrypt a text using Caesar's cipher
2. Decrypt a Caesar's cipher text
3. Break Caesar's cipher using frequency analysis
4. Exit

## How to Use:

1. Clone the repository to your local machine.
2. Ensure you have C++ installed.
3. Run the main script.
4. Follow the on-screen instructions to perform your desired task.

## Contributors:

- Brad Beniamin

