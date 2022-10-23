#include <iostream>
#include <bits/stdc++.h> 
#include <string>

#define ROW_SIZE        15
#define COLUMN_SIZE     15
#define WORDS_SIZE      16

char puzzle[ROW_SIZE][COLUMN_SIZE] = {
    {'a', 'x', 'd', 'u', 'r', 'y', 'h', 'p', 's', 'p', 't', 't', 'i', 'd', 't'},
    {'v', 'n', 'x', 's', 'e', 'c', 'a', 'q', 'c', 'u', 'i', 'u', 'o', 'z', 'p'},
    {'m', 'e', 'r', 'g', 'f', 'w', 'o', 'z', 'i', 's', 'n', 'l', 'k', 'a', 'c'},
    {'v', 's', 'c', 'x', 's', 'e', 's', 'x', 'o', 'f', 'l', 'w', 'z', 'j', 'z'},
    {'v', 't', 'r', 'p', 'n', 'd', 'l', 'p', 'b', 'a', 'c', 'h', 'e', 'b', 'y'},
    {'p', 'r', 'e', 'k', 'a', 'w', 'e', 'c', 'r', 'c', 't', 'x', 'n', 's', 'b'},
    {'f', 'p', 'd', 'm', 'r', 'd', 'l', 'o', 's', 'p', 'e', 'j', 'a', 'q', 't'},
    {'w', 'h', 'i', 'n', 't', 'l', 'y', 'i', 'b', 't', 'c', 'a', 's', 'h', 'n'},
    {'l', 'a', 't', 'c', 'i', 'q', 'n', 'n', 'r', 'i', 'l', 'h', 't', 'y', 'j'},
    {'k', 'r', 'r', 'x', 'o', 'i', 'f', 'k', 'y', 'b', 'w', 'o', 'e', 'w', 'a'},
    {'v', 'c', 'p', 'd', 'u', 'y', 'z', 'k', 'l', 'e', 't', 'n', 'a', 'k', 'w'},
    {'i', 'u', 'e', 'o', 'h', 'k', 'n', 'a', 'b', 'd', 'o', 't', 'a', 'n', 'a'},
    {'f', 'a', 'q', 'h', 'y', 't', 'j', 'b', 'i', 'm', 'y', 'm', 'u', 'd', 's'},
    {'v', 'q', 'z', 'f', 'c', 'j', 'i', 'e', 'e', 'm', 'n', 'k', 'u', 'x', 'l'},
    {'b', 'a', 'l', 'a', 'n', 'c', 'e', 'w', 'e', 'c', 'n', 'u', 'o', 'p', 'b'}
};

const char *words[WORDS_SIZE] = {
    "balance",
    "bank",
    "cash",
    "check",
    "coin",
    "credit",
    "debit",
    "deposit",
    "dollar",
    "loan",
    "money",
    "paws",
    "pounce",
    "sunwest",
    "qqo",
    "uqf"
};

void print_puzzle_matrix()
{
    for (auto i=0; i<COLUMN_SIZE; ++i)
    {
        for (auto j=0; j<ROW_SIZE; ++j)
        {
            std::cout << puzzle[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void update_horizontal_patterns()
{
    // Find patterns horizontally [Left to Right, Right to Left]
    std::string cmp_row (ROW_SIZE, 0);
    for (auto i=0; i<ROW_SIZE; i++)
    {
        // Left to Right
        for (auto j=0; j<COLUMN_SIZE; j++)
        {
            cmp_row[j] = puzzle[i][j];
        }

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_row.find(words[k]);
            if (found != std::string::npos)
            {
                for (auto l = found; l < found + strlen(words[k]); l++)
                {
                    puzzle[i][l] = std::toupper(puzzle[i][l]);
                }
            }
        }

        // Right to Left
        auto cmp_row_reverse = cmp_row;
        std::reverse(cmp_row_reverse.begin(), cmp_row_reverse.end());    

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_row_reverse.find(words[k]);
            if (found != std::string::npos)
            {
                for (auto l = COLUMN_SIZE -1 - found; l > COLUMN_SIZE -1 - found - strlen(words[k]); l--)
                {
                    puzzle[i][l] = std::toupper(puzzle[i][l]);
                }
            }
        }
    }
}

void update_vertical_patterns()
{
    // Find patterns vertically [Up to Down, Down to Up]
    std::string cmp_col (COLUMN_SIZE, 0);
    for (auto i=0; i<COLUMN_SIZE; i++)
    {
        // Up to Down
        for (auto j=0; j<ROW_SIZE; j++)
        {
            cmp_col[j] = puzzle[j][i];
        }

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_col.find(words[k]);
            if (found != std::string::npos)
            {
                for (auto l = found; l < found + strlen(words[k]); l++)
                {
                    puzzle[l][i] = std::toupper(puzzle[l][i]);
                }
            }
        }

        // Down to Up
        auto cmp_col_reverse = cmp_col;
        std::reverse(cmp_col_reverse.begin(), cmp_col_reverse.end());

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_col_reverse.find(words[k]);
            if (found != std::string::npos)
            {
                for (auto l = ROW_SIZE -1 - found; l > ROW_SIZE -1 - found - strlen(words[k]); l--)
                {
                    puzzle[l][i] = std::toupper(puzzle[l][i]);
                }
            }
        }
    }
}

void update_right_to_left_diagonal()
{
    std::string cmp_diagonal_right_to_left_down;

    // Upper half of matrix
    for(auto column_counter = 0; column_counter < COLUMN_SIZE; column_counter++)
    {
        auto current_column = column_counter;
        auto current_row = 0;
        for(;current_column >= 0 && current_row < ROW_SIZE; current_column--, current_row++)
        {
            cmp_diagonal_right_to_left_down += puzzle[current_row][current_column];
        }

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_diagonal_right_to_left_down.find(words[k]);
            if (found != std::string::npos)
            {
                auto current_column = column_counter-found;
                auto current_row = found;
                for(auto l = 0; l < strlen(words[k]); current_column--, current_row++, l++)
                {
                    puzzle[current_row][current_column] = std::toupper(puzzle[current_row][current_column]);
                }
            }
        }

        auto cmp_diagonal_right_to_left_down_reverse = cmp_diagonal_right_to_left_down;
        std::reverse(cmp_diagonal_right_to_left_down_reverse.begin(), cmp_diagonal_right_to_left_down_reverse.end());

        cmp_diagonal_right_to_left_down="";
    }

    // Lower half of matrix
    for(auto row_counter = 1; row_counter < ROW_SIZE; row_counter++)
    {
        auto current_column = COLUMN_SIZE -1; 
        auto current_row = row_counter;
        for(;current_column >= 0 && current_row < ROW_SIZE; current_column--, current_row++)
        {
            cmp_diagonal_right_to_left_down += puzzle[current_row][current_column]; 
        }

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_diagonal_right_to_left_down.find(words[k]);
            if (found != std::string::npos)
            {
                auto current_column = COLUMN_SIZE -1 -found;
                auto current_row = row_counter + found;
                for(auto l = 0; l < strlen(words[k]); current_column--, current_row++, l++)
                {
                    puzzle[current_row][current_column] = std::toupper(puzzle[current_row][current_column]);
                }
            }
        }

        cmp_diagonal_right_to_left_down="";
    }
}

void update_left_to_right_diagonal()
{
    std::string cmp_diagonal_left_to_right_up;

    // Upper half of matrix
    for(auto column_counter = COLUMN_SIZE - 1; column_counter >= 0; column_counter--)
    {
        auto current_column = column_counter; 
        auto current_row = 0;
        for(;current_column < COLUMN_SIZE && current_row < ROW_SIZE; current_column++, current_row++)
        {
            cmp_diagonal_left_to_right_up += puzzle[current_row][current_column];
        }

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_diagonal_left_to_right_up.find(words[k]);
            if (found != std::string::npos)
            {
                auto current_column = column_counter+found;
                auto current_row = found;
                for(auto l = 0; l < strlen(words[k]); current_column++, current_row++, l++)
                {
                    puzzle[current_row][current_column] = std::toupper(puzzle[current_row][current_column]);
                }
            }
        }

        cmp_diagonal_left_to_right_up="";
    }

    // Lower half of matrix
    for(auto row_counter = 1; row_counter < ROW_SIZE; row_counter++)
    {
        auto current_column = 0; 
        auto current_row = row_counter;
        for(;current_column <= COLUMN_SIZE -1 && current_row < ROW_SIZE; current_column++, current_row++)
        {
            cmp_diagonal_left_to_right_up += puzzle[current_row][current_column]; 
        }

        for (auto k=0; k<WORDS_SIZE; k++)
        {
            auto found = cmp_diagonal_left_to_right_up.find(words[k]);
            if (found != std::string::npos)
            {
                auto current_column = found;
                auto current_row = row_counter + found;
                for(auto l = 0; l < strlen(words[k]); current_column++, current_row++, l++)
                {
                    puzzle[current_row][current_column] = std::toupper(puzzle[current_row][current_column]);
                }
            }
        }

        cmp_diagonal_left_to_right_up="";
    }
}

int main (void)
{
    print_puzzle_matrix();

    update_horizontal_patterns();
    update_vertical_patterns();
    update_right_to_left_diagonal();
    update_left_to_right_diagonal();

    print_puzzle_matrix();

    return 0;
}
