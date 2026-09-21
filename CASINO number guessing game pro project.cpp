
// =================================================================
    // PROJECT TITLE: CASINO NUMBER GUESSING GAME
// =================================================================

#include <iostream>
#include <string>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time() to seed random numbers
#include <iomanip> // Needed for formatting currency output

using namespace std;

int main() {
    // Seed the random number generator using the current system time
    srand(time(0));

    // =================================================================
    // LOCAL CONFIGURATION VARIABLES
    // =================================================================
    int numPlayers = 0;
    int roundNumber = 1;
    bool anyPlayerLeft = true;

    // Standard Player Data Arrays (Max 10 players)
    string playerNames[10];
    double balances[10];
    double betAmounts[10];
    int playerGuesses[10];
    bool isPlaying[10];

    // Casino Performance Metrics
    double casinoTotalWonFromLossers = 0;
    double casinoTotalLostToWinners = 0;

    // =================================================================
    // GLOBAL HISTORIC LEDGER BOOKS (Declaring them safely up here)
    // =================================================================
    double historyInitialDeposits[10] = {0};
    int historyRoundNumbers[10][50] = {0};
    double historyBetAmounts[10][50] = {0};
    string historyOutcomeStr[10][50];
    int historyWinningNumbers[10][50] = {0};
    int historyGuesses[10][50] = {0};
    double historyBalances[10][50] = {0};

    // =================================================================
    // GAME INTRODUCTORY INTERFACE & RULES
    // =================================================================
    cout << "\n\n";
    cout << "\t========================================================\n";
    cout << "\t🎰✨🔥✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨🔥\n";
    cout << "\t🎰✨🔥✨✨ WELCOME TO THE C++ CASINO WORLD✨✨✨✨✨✨🔥\n";
    cout << "\t🎰✨🔥✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨🔥\n";
    cout << "\t========================================================\n";

    cout << "\n\t====== CASINO NUMBER GUESSING RULES! ======\n";
    cout << "\t1. Choose a number between 1 to 10\n";
    cout << "\t2. This casino only accommodates MAXIMUM 10 players\n";
    cout << "\t3. Winner gets 10 times of the money bet\n";
    cout << "\t4. Wrong bet, and you lose the amount you bet\n";
    cout << "\t=========================================\n\n";

    // =================================================================
    // MULTIPLAYER STEP 1: Registration (Player Slots Count)
    // =================================================================
    while (true) {
        cout << "\tEnter the number of players that are playing against casino(1 to 10)= ";
        cin >> numPlayers;
        cout << "\n";

        if (cin.fail() || cin.peek() != '\n') {
            cout << "\t>>invalid input!!!\n\tInput must be a natual number!(letters,spaces,or symbols aren't allowed)\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (numPlayers < 1 || numPlayers > 10) {
            cout << "\t>> Error!!!\n\tThe casino only has slots for 1 to 10 players. Please try again.\n\n";
        }
        else {
            break;
        }
    }
    cin.ignore(10000, '\n'); // Strip residual newlines

    // =================================================================
    // MULTIPLAYER STEP 2: Profile Setup (Names Collection)
    // =================================================================
for (int i = 0; i < numPlayers; i++) {
        while (true) {
            cout << "\tEnter player " << (i + 1) << " name / username = ";
            getline(cin, playerNames[i]);

            // Step 1: Check if the name is completely blank
            if (playerNames[i] == "") {
                cout << "\n\t  >> Error!!!\n\t\tName cannot be blank! Please type your name / username.\n\n";
            }
            else {
                // Step 2: Check if there is at least one visible character
                bool hasVisibleChar = false;
                for (size_t j = 0; j < playerNames[i].length(); j++) {
                    if (playerNames[i][j] != ' ') {
                        hasVisibleChar = true; // Found a letter or number!
                    }
                }
                // If no visible characters were found, it means the user typed only spaces
                if (hasVisibleChar == false) {
                    cout << "\n\t  >> Error!!!\n\t\tName cannot be only spaces! Please type your name / username.\n\n";
                }
                else {
                    break; // Acceptable! Contains visible letters/words (like Abenet Degefa)
                }
            }
        }
        isPlaying[i] = true;
    }
    // =================================================================
    // MULTIPLAYER STEP 3: Financial Capital Configuration (Deposits)
    // =================================================================
    cout << "\n\t---------------------------------------------------------\n";
    for (int i = 0; i < numPlayers; i++) {
        cout << "\tPlayer " << (i + 1) << " is " << playerNames[i] << " ,\n";

        while (true) {
            cout << "\t\tEnter your deposit = ";
            cin >> balances[i];

            if (!cin.fail() && balances[i] > 0 && cin.peek() == '\n') {
                historyInitialDeposits[i] = balances[i]; // Store original baseline balance safely
                cout << "\n";
                break;
            }
            else {
                cout << "\n\t\t>> Invalid input!\n\t\t\tEnter a valid positive real number.\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
    // =================================================================
    // MASTER CORE GAME ROUND RUNTIME LOOP
    // =================================================================
    while (anyPlayerLeft) {

        cout << "\n\t=========================================================\n";
        cout << "\t                      ROUND " << roundNumber << " \n";
        cout << "\t=========================================================\n";

        // Collect Bet Stakes
        for (int i = 0; i < numPlayers; i++) {
            if (isPlaying[i] == false) {
                continue;
            }
            cout << "\tPlayer " << (i + 1) << " is " << playerNames[i] << ",\n";
            cout << "\t  👤 " << playerNames[i] << "'s Current Balance: $" << fixed << setprecision(2) << balances[i] << "\n";

            while (true) {
                cout << "\t\tEnter your betting amount = ";
                cin >> betAmounts[i];

                if (!cin.fail() && cin.peek() == '\n') {
                    if (betAmounts[i] <= 0) {
                        cout << "\n\t\t>> Bet must be greater than 0.\n\n";
                    }
                    else if (betAmounts[i] > balances[i]) {
                        cout << "\n\t\t>> Error!!!\n\t\t\tYou cannot bet more than your balance!\n\n";
                    }
                    else {
                        cout << "\n";
                        break;
                    }
                }
                else {
                    cout << "\n\t\t>> Invalid entry.\n\t\t\tPlease enter positive real number.\n\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
        }

        // Collect Numeric Predictions
        cout << "\t---------------------------------------------------------\n";
        for (int i = 0; i < numPlayers; i++) {
            if (isPlaying[i] == false) {
                continue;
            }

            cout << "\tPlayer " << (i + 1) << " is " << playerNames[i] << " ,\n";
            while (true) {
                cout << "\t\t🎲 " << playerNames[i] << " , Guess the winning number from (1 to 10) = ";
                cin >> playerGuesses[i];

                if (!cin.fail() && cin.peek() == '\n' && playerGuesses[i] >= 1 && playerGuesses[i] <= 10) {
                    cout << "\n";
                    break;
                }
                else {
                    cout << "\n\t\t  >> Invalid input\n\t\t\tChoice must be a natural number between 1 and 10.\n\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
        }

        // Random Execution Engine
        int winningNumber = rand() % 10 + 1;
        cout << "\n\tRolling number the number is ..............\n";
        cout << "\tThe winning number is = " << winningNumber << "\n\n";

        cout << "\t========================================================\n";
        cout << "\t🎰✨🔥          ROUND CONGRATULATIONS            🔥✨🎰\n";
        cout << "\t========================================================\n";

        bool roundHasWinner = false;
        for (int i = 0; i < numPlayers; i++) {
            if (isPlaying[i] == true && playerGuesses[i] == winningNumber) {
                cout << "\t🎉 The winner is player " << (i + 1) << " , " << playerNames[i] << "!\n";
                roundHasWinner = true;
            }
        }
        if (roundHasWinner == false) {
            cout << "\tNo players guessed correctly this round. The house wins!\n";
        }
        cout << "\t========================================================\n\n";

        // =================================================================
        // ROUND EVALUATION & COLLECTIVE BOARD METRICS DISPLAY
        // =================================================================
        cout << "\t" << setfill('-') << setw(92) << "" << setfill(' ') << "\n";
        cout << "\t| " << setw(10) << left << "Player No"
             << "| " << setw(12) << left << "Player Name"
             << "| " << setw(16) << left << "Initial Deposit"
             << "| " << setw(10) << left << "Win/Loss"
             << "| " << setw(17) << left << "Guess This Round"
             << "| " << setw(13) << left << "Final Amount" << " |\n";
        cout << "\t" << setfill('-') << setw(92) << "" << setfill(' ') << "\n";

        for (int i = 0; i < numPlayers; i++) {
            if (isPlaying[i] == false) {
                continue;
            }

            string outcomeStr = "";
            if (playerGuesses[i] == winningNumber) {
                double winnings = betAmounts[i] * 10;
                balances[i] = balances[i] + winnings;
                outcomeStr = "WIN";
                casinoTotalLostToWinners = casinoTotalLostToWinners + winnings;
            }
            else {
                balances[i] = balances[i] - betAmounts[i];
                outcomeStr = "LOSS";
                casinoTotalWonFromLossers = casinoTotalWonFromLossers + betAmounts[i];
            }

            // Record chronological history step
            historyRoundNumbers[i][roundNumber] = roundNumber;
            historyBetAmounts[i][roundNumber] = betAmounts[i];
            historyOutcomeStr[i][roundNumber] = outcomeStr;
            historyWinningNumbers[i][roundNumber] = winningNumber;
            historyGuesses[i][roundNumber] = playerGuesses[i];
            historyBalances[i][roundNumber] = balances[i];

            // Print Master Round Row Entry
            cout << "\t|  " << setw(10) << left << (i + 1)
                 << "|  " << setw(10) << left << playerNames[i]
                 << "| $ " << setw(14) << left << fixed << setprecision(2) << historyInitialDeposits[i]
                 << "|   " << setw(8) << left << outcomeStr
                 << "|   " << setw(15) << left << playerGuesses[i]
                 << "| $ " << setw(12) << left << fixed << setprecision(2) << balances[i] << "|\n";

            // Bankruptcy Handler: If a player goes completely broke
            if (balances[i] <= 0) {
                cout << "\n\t| >> " << playerNames[i] << " has run out of funds and is eliminated!\n";

                cout << "\t" << setfill('=') << setw(112) << "" << setfill(' ') << "\n";
                cout << "\t| " << setw(48) << right << playerNames[i] << " - ACCUMULATED GAME STATEMENT" << setw(34) << "|\n";
                cout << "\t" << setfill('=') << setw(112) << "" << setfill(' ') << "\n";
                cout << "\t| " << setw(8) << left << "Round"
                     << "| " << setw(18) << left << "Initial Deposit"
                     << "| " << setw(14) << left << "Bet Amount"
                     << "| " << setw(12) << left << "Win/Loss"
                     << "| " << setw(16) << left << "Winning Number"
                     << "| " << setw(15) << left << "Your Guess"
                     << "| " << setw(13) << left << "Final Balance" << " |\n";
                cout << "\t" << setfill('-') << setw(112) << "" << setfill(' ') << "\n";

                for (int r = 1; r <= roundNumber; r++) {
                    cout << "\t| " << setw(8) << left << historyRoundNumbers[i][r]
                         << "| $ " << setw(16) << left << fixed << setprecision(2) << historyInitialDeposits[i]
                         << "| $ " << setw(12) << left << fixed << setprecision(2) << historyBetAmounts[i][r]
                         << "|   " << setw(10) << left << historyOutcomeStr[i][r]
                         << "|   " << setw(14) << left << historyWinningNumbers[i][r]
                         << "|   " << setw(13) << left << historyGuesses[i][r]
                         << "| $ " << setw(12) << left << fixed << setprecision(2) << historyBalances[i][r] << "|\n";
                }
                cout << "\t" << setfill('=') << setw(112) << "" << setfill(' ') << "\n\n";

                isPlaying[i] = false;
            }
        }
        cout << "\t" << setfill('-') << setw(92) << "" << setfill(' ') << "\n\n";

        // =================================================================
        // RETENTION & LEAVE PROCESSING INTERFACE
        // =================================================================
        for (int i = 0; i < numPlayers; i++) {
            if (isPlaying[i] == false) {
                continue;
            }

            char playAgainChoice;
            while (true) {
                cout << "\tPlayer " << (i + 1) << " , " << playerNames[i] << ", do you want to play again (y/n)? ";
                cin >> playAgainChoice;

                if ((playAgainChoice == 'y' || playAgainChoice == 'Y' || playAgainChoice == 'n' || playAgainChoice == 'N') && cin.peek() == '\n') {
                    break;
                }
                else {
                    cout << "\n\t  >> Invalid choice!\n\t\tPlease type exactly 'y' or 'n'.\n\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }

            // Voluntary Walkaway Handler
            if (playAgainChoice == 'n' || playAgainChoice == 'N') {
                cout << "\n\t" << setfill('=') << setw(112) << "" << setfill(' ') << "\n";
                cout << "\t| " << setw(48) << right << playerNames[i] << " - ACCUMULATED GAME STATEMENT" << setw(34) << "|\n";
                cout << "\t" << setfill('=') << setw(112) << "" << setfill(' ') << "\n";
                cout << "\t| " << setw(8) << left << "Round"
                     << "| " << setw(18) << left << "Initial Deposit"
                     << "| " << setw(14) << left << "Bet Amount"
                     << "| " << setw(12) << left << "Win/Loss"
                     << "| " << setw(16) << left << "Winning Number"
                     << "| " << setw(15) << left << "Your Guess"
                     << "| " << setw(14) << left << "Final Balance" << "|\n";
                cout << "\t" << setfill('-') << setw(112) << "" << setfill(' ') << "\n";

                for (int r = 1; r <= roundNumber; r++) {
                    cout << "\t| " << setw(8) << left << historyRoundNumbers[i][r]
                         << "| $ " << setw(16) << left << fixed << setprecision(2) << historyInitialDeposits[i]
                         << "| $ " << setw(12) << left << fixed << setprecision(2) << historyBetAmounts[i][r]
                         << "|   " << setw(10) << left << historyOutcomeStr[i][r]
                         << "|   " << setw(14) << left << historyWinningNumbers[i][r]
                         << "|   " << setw(13) << left << historyGuesses[i][r]
                         << "| $ " << setw(12) << left << fixed << setprecision(2) << historyBalances[i][r] << "|\n";
                }
                cout << "\t" << setfill('=') << setw(112) << "" << setfill(' ') << "\n\n";

                isPlaying[i] = false;
            }
        }

        // Check if a following round can execute
        anyPlayerLeft = false;
        for (int i = 0; i < numPlayers; i++) {
            if (isPlaying[i] == true) {
                anyPlayerLeft = true;
            }
        }

        if (anyPlayerLeft == true) {
            roundNumber = roundNumber + 1;
        }
    }

    // =================================================================
    // HOUSE BOARD TERMINATION SUMMARY
    // =================================================================
    cout << "\n\t====================================================\n";
    cout << "\t                FINAL GAME OVER SUMMARY            \n";
    cout << "\t====================================================\n";

    cout << "\t" << setfill('-') << setw(51) << "" << setfill(' ') << "\n";
    cout << "\t| " << setw(20) << left << "Player Name"
         << "| " << setw(25) << left << "Final Accumulated Balance" << " |\n";
    cout << "\t" << setfill('-') << setw(51) << "" << setfill(' ') << "\n";

    for (int i = 0; i < numPlayers; i++) {
        cout << "\t| " << setw(20) << left << playerNames[i]
             << "| $ " << setw(24) << left << fixed << setprecision(2) << balances[i] << "|\n";
    }
    cout << "\t" << setfill('-') << setw(51) << "" << setfill(' ') << "\n\n";

    cout << "\t=============================================================================\n";
    cout << "\t      💰 CASINO HOUSE BALANCE METRICS\n";
    cout << "\t=============================================================================\n";
    cout << "\t Total amount gained from losing bets:  $ " << casinoTotalWonFromLossers << "\n";
    cout << "\t Total amount paid out to winning bets: $ " << casinoTotalLostToWinners << "\n";

    double netHouseProfit = casinoTotalWonFromLossers - casinoTotalLostToWinners;
    cout << "\t Net Casino Performance:                ";
    if (netHouseProfit >= 0) {
        cout << "+$ " << netHouseProfit << " (House Profit)\n";
    } else {
        cout << "-$ " << (-netHouseProfit) << " (House Net Loss)\n";
    }
    cout << "\t=============================================================================\n\n";

    return 0;
}
