#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// additional func
bool is_cycle(int head, int tail, int iterator);
// bool was_winner(int n, int iterator);
// bool was_loser(int n, int iterator);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // eliminate all losing pairs
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    // printf("%d", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    int gapi;
    int gapy;

    pair temp;
    // pair temp[pair_count];
    // int n = 0;

    int counter = -1;   // A C H I E V E M E N T

    while (counter != 0)
    {
        counter = 0; // fail when placing counter inside if

        for (int i = 0; i < pair_count; i++) // bubble foreach adjacent pair can't use j
        {
            gapi = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            gapy = preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner];

            if (gapi < gapy)
            {
                temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                // n++;
                counter++;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (is_cycle(pairs[i].winner, pairs[i].loser, i) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}

bool is_cycle(int head, int tail, int iterator)
{
    for (int i = iterator - 1; i >= 0; i--)
    {
        if (tail == pairs[i].winner)
        {
            // check legal pairs only
            if (locked[pairs[i].winner][pairs[i].loser] == true)
            {
                if (pairs[i].loser != head)
                {
                    for (int j = i - 1; j >= 0; j--)
                    {
                        if (tail == pairs[j].winner)
                        {
                            if (locked[pairs[j].winner][pairs[j].loser] == true)
                            {
                                if (pairs[j].loser != head)
                                {
                                    tail = pairs[j].loser;
                                    // return is_cycle(head, tail, iterator);
                                    // lock check turn all green if above line commented
                                }
                                else
                                {
                                    return true;
                                }
                            }
                        }
                    }
                    tail = pairs[i].loser;
                    return is_cycle(head, tail, iterator);
                }
                else
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    // find source
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[k][i] == true)
                    {
                        break; // break only breaks inner loop
                    }
                    // print name not num
                    printf("%s\n", candidates[i]);
                }
            }

        }
    }
    return;
}