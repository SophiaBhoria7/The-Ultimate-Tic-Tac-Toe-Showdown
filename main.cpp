//Programmer: Sophia Bhoria 
//Date: 09/27/2024
//Purpose: The purpose of this code is to simulate a customizable Tic-Tac-Toe game with different board sizes, where two players alternate turns until one wins or the game ends in a tie.

#include <iostream>
#include <string>

using namespace std; 

// Function prototypes
void printWelcomeMessage();
void displayMenu();
string initializeBoard(const int size);
void printBoard(const string &board, const int size);
void updateBoard(string &board, const int size, const int chosenCell, const string &playerSymbol);
bool checkWin(const string &board, const int size);
bool checkTie(const string &board, const int size);
void printGoodbyeMessage();

int main() {
  // Print the initial welcome message
  printWelcomeMessage();

  // Variables to store player names
  string player1, player2;
  cout << "Please enter the first name of Player 1: ";
  cin >> player1; // Get Player 1's name
  cout << "Please enter the first name of Player 2: ";
  cin >> player2; // Get Player 2's name

  int choice;
  do {
    // Display the menu options for the board size
    displayMenu();
    cout << "Enter your choice: ";
    cin >> choice;

    // Check if the choice is out of the acceptable range
    if (choice < 1 || choice > 8) {
      cout << "Invalid choice! Exiting the program." << endl;
      break;
    }

    // If user chooses to quit
    if (choice == 8) {
      printGoodbyeMessage();
      break;
    }

    // Determine the board size based on the menu choice
    int boardSize = choice + 2; // 3x3 starts at option 1 (1 + 2 = 3), 4x4 starts at option 2 (2 + 2 = 4), etc.
    string board = initializeBoard(boardSize); // Initialize the board with cell numbers

    // Variables to keep track of current player and their symbol
    string currentPlayer = player1;
    string currentSymbol = "SS"; // 'SS' symbol for Player 1

    while (true) {
      // Print the current board state
      printBoard(board, boardSize);
      int cell;
      cout << currentPlayer << " (" << currentSymbol << "), choose a cell: ";
      cin >> cell;


      // Update the board with the player's move
      updateBoard(board, boardSize, cell, currentSymbol);

      // Check if the current player has won
      if (checkWin(board, boardSize)) {
        printBoard(board, boardSize);
        cout << "Congratulations " << currentPlayer << ", you won!" << endl;
        break;
      }

      // Check if the game is a tie
      if (checkTie(board, boardSize)) {
        printBoard(board, boardSize);
        cout << "It's a draw!" << endl;
        break;
      }

      // Swap to the next player and their symbol
      if (currentPlayer == player1) {
        currentPlayer = player2;
        currentSymbol = "TT"; // 'TT' symbol for Player 2
      } else {
        currentPlayer = player1;
        currentSymbol = "SS"; // 'SS' symbol for Player 1
      }
    }
  } while (choice != 8); // Loop until user chooses to quit

  return 0; // Exit the program
}

// Function to print a welcome message at the start of the game
void printWelcomeMessage() {
  cout << "Welcome to Dynamic Tic-Tac-Toe Missouri S&T Edition!" << endl;
}

// Function to display the main menu with options for board sizes or quitting the game
void displayMenu() {
  cout << "Choose the size of the Tic-Tac-Toe board or Quit:" << endl;
  cout << "1. 3x3 Board" << endl;
  cout << "2. 4x4 Board" << endl;
  cout << "3. 5x5 Board" << endl;
  cout << "4. 6x6 Board" << endl;
  cout << "5. 7x7 Board" << endl;
  cout << "6. 8x8 Board" << endl;
  cout << "7. 9x9 Board" << endl;
  cout << "8. Quit the Program" << endl;
}

// Function to initialize the game board with cell numbers based on the selected size
string initializeBoard(const int size) {
  string board = ""; // Initialize an empty string to hold the board
  for (int i = 1; i <= size * size; i++) {
    if (i < 10)
      board += "0" + to_string(i); // Add leading zero for single-digit numbers
    else
      board += to_string(i); // Directly add the number for two-digit cells
  }

  return board; // Return the initialized board string
}

// Function to print the current state of the board in a formatted way
void printBoard(const string &board, const int size) {
  for (int i = 0; i < size * size; i += size) {
    for (int j = 0; j < size; ++j) {
      cout << board.substr((i + j) * 2, 2) << " "; // Print each cell
    }
    cout << endl; // New line after each row
  }
}

// Function to update the board based on the player's move
void updateBoard(string &board, const int size, const int chosenCell, const string &playerSymbol) {
  int pos = (chosenCell - 1) * 2; // Calculate the position in the string for the chosen cell
  // Check if the cell is already occupied
  if (board.substr(pos, 2) == playerSymbol || board.substr(pos, 2) == "SS" || board.substr(pos, 2) == "TT") {
    cout << "Cell is already occupied. Choose another cell." << endl;
  } else {
    board.replace(pos, 2, playerSymbol); // Update the cell with the player's symbol
  }
}

// Function to check if there is a winning condition on the board
bool checkWin(const string &board, const int size) {
  // Check rows
  for (int i = 0; i < size * size; i += size) {
    if (board.substr(i * 2, 2) == board.substr((i + 1) * 2, 2) && board.substr(i * 2, 2) == board.substr((i + 2) * 2, 2) && board.substr(i * 2, 2) != "00") {
      return true;
    }
  }

  // Check columns
  for (int j = 0; j < size; ++j) {
    if (board.substr(j * 2, 2) == board.substr((j + size) * 2, 2) && board.substr(j * 2, 2) == board.substr((j + size * 2) * 2, 2) && board.substr(j * 2, 2) != "00") {
      return true;
    }
  }

  // Check diagonals
  if (board.substr(0, 2) == board.substr(size * 2 + 2, 2) && board.substr(0, 2) == board.substr(size * 2 * 2 + 4, 2) && board.substr(0, 2) != "00") {
    return true;
  }
  if (board.substr(size - 2, 2) == board.substr(size * 2 - 2, 2) && board.substr(size - 2, 2) == board.substr(size * 2 * 2 - 4, 2) && board.substr(size - 2, 2) != "00") {
    return true;
  }

  return false; // No winning condition found
}

// Function to check if the game has ended in a tie (no more moves left)
bool checkTie(const string &board, const int size) {
  // Implement the logic to check for a tie condition
  return false; // Placeholder
}

// Function to print a goodbye message when the user exits the program
void printGoodbyeMessage() {
  cout << "Thank you for playing Dynamic Tic-Tac-Toe Missouri S&T Edition!" << endl;
}
