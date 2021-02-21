#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // int head = 0;
    // int tail = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][0] == j)
            {
                if (!candidates[j].eliminated)
                {
                    candidates[j].votes++;
                }
                else
                {
                    int gone = 1;
                    while (candidates[preferences[i][gone]].eliminated == true)
                    {
                        gone++;

                    }
                    candidates[preferences[i][gone]].votes++;
                }
            }

        }
    }
    return;
}

// Print the winner of the election, if there is one

bool print_winner(void) // i.e. find_max()
{
    // TODO

    int head = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (head < candidates[i].votes && !candidates[i].eliminated)
        {
            head = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (head > 0.5 * voter_count && candidates[i].votes == head && !candidates[i].eliminated)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int tail = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (tail > candidates[i].votes && !candidates[i].eliminated)
        {
            tail = candidates[i].votes;
        }
    }
    return tail;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // tie :: EACH candidate still standing has same votes
    // min :: the smallest votes any candidate currently has
    
    int counter1 = 0;
    int counter2 = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min) 
        {
            counter1++;
        }
    }
    
    for (int i = 0; i < candidate_count; i++) 
    {
        if (candidates[i].eliminated == true)
        {
            counter2++;
        }
    }
    
    int counter_sum = counter1 + counter2;
    
    if (counter_sum == candidate_count)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
