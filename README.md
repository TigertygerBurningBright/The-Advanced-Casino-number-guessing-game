# Casino Number Guessing Game Pro

Welcome to the C++ Casino World! This is a feature-rich, terminal-based multiplayer betting game where players test their luck against the house by guessing a randomly generated number. 

## 🎲 Features

*   **Multiplayer Support:** The casino accommodates a maximum of 10 players simultaneously.[cite: 1]
*   **High Stakes:** Players choose a number between 1 and 10; winners receive 10 times their bet amount, while incorrect guesses result in a loss of the wager.[cite: 1]
*   **Comprehensive Financial Tracking:** The game maintains detailed historic ledger books for each player, tracking initial deposits, round-by-round bets, win/loss outcomes, and final balances.[cite: 1]
*   **Dynamic Player Management:** Players are eliminated if their balance drops to zero, and they are provided with a complete "Accumulated Game Statement" upon bankruptcy or voluntary exit.[cite: 1]
*   **House Metrics:** At the end of the session, the game generates a Final Game Over Summary, detailing the total amount the casino gained from losers, the amount paid to winners, and the net house profit or loss.[cite: 1]
*   **Robust Input Validation:** The system prevents blank usernames, blank spaces for names, betting more than the current balance, and invalid numeric entries.[cite: 1]

## 📜 Game Rules

1.  Choose a number between 1 to 10.[cite: 1]
2.  This casino only accommodates MAXIMUM 10 players.[cite: 1]
3.  Winner gets 10 times of the money bet.[cite: 1]
4.  Wrong bet, and you lose the amount you bet.[cite: 1]

## 🚀 Getting Started

### Prerequisites
You will need a standard C++ compiler (like `g++` or `clang++`) installed on your system.

### Compilation & Execution
The entire game is contained within a single source file. You can compile and run it using your terminal:

1. Clone the repository or download the source code.
2. Navigate to the directory containing the file.
3. Compile the game using the following command:
   ```bash
   g++ -o casino_game "CASINO number guessing game pro project.cpp"
   
