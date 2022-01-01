/* ************************************************************************** */
/*                                                                            */
/*                            \\             /`/``                            */
/*                            ~\o o_       0 0\                               */
/*                            / \__)      (u  ); _  _                         */
/*                     / \/ \/  /           \  \/ \/ \                        */
/*                    /(   . . )            (         )\                      */
/*                   /  \_____/              \_______/  \                     */
/*                       []  []               [[] [[]    *.                   */
/*                       []] []]              [[] [[]                         */
/*                                                                            */
/* ****************************************************************** nuo *** */

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;
using vvi = vector<vector<int>>;

//      DRIVE

vector<string>  init_grid(unsigned int, unsigned int, char, char);
int             count_live_neighbors(vector<string>, vvi, int, int, char);
bool            game_of_life(vector<string>&, vvi, char, char);
void            print_grid(vector<string>);

int     main(void)
{
        vector<vector<int>>     neighbors;
        vector<string>          grid;
        unsigned int            W, H, count;
        char                    consent, live, die;
        char                    default_live = '~';
        char                    default_die = '_';
        int                     max_W = 199; // speed ? 200 x 33 : 199 x 59
        int                     max_H = 59;
        int                     max = 6;
        char                    s[max];

        neighbors = 
        {
            { 1,  1}, { 1, 0}, { 1, -1}, { 0, -1},
            {-1, -1}, {-1, 0}, {-1,  1}, { 0,  1}
        };
        
        //  Ask user for W, H and two single-char symbols

        cout << "Enter a width  : ";
        fgets(s, max, stdin);
        if (!isdigit(s[0])) W = max_W;
        stringstream(s) >> W;
        W = W < max_W ? W : max_W;
        fflush(stdin);
        s[0] = 0;

        cout << "Enter a height : ";
        fgets(s, max, stdin);
        if (!isdigit(s[0])) H = max_H;
        stringstream(s) >> H;
        H = H < max_H ? H : max_H; // H = max(55, H);
        fflush(stdin);
        s[0] = 0;
        
        cout << "Life symbol    : ";
        fgets(s, max, stdin);
        if (!isprint(s[0]) || s[0] == '\n') live = default_live;
        else                                live = s[0];
        fflush(stdin);
        s[0] = 0;

        cout << "Death symbol   : ";
        fgets(s, max, stdin);
        if (!isprint(s[0]) || s[0] == '\n') die = default_die;
        else                                die = s[0];
        fflush(stdin);
        s[0] = 0;

        if (live == die)
        {
            live = default_live;
            die = default_die;
        }

        cout << "live:"<< live << endl;
        cout << "die:"<< (int)die << endl;
        grid = init_grid(W, H, live, die);
        print_grid(grid);

        //  Ask for consent

        cout << "Start automata? (y/n)  : ";
        scanf("%c", &consent);
        if (consent != '\n' && consent != 'y')  return (1);

        //  The game starts here

        count = 1;
        while (1)
        {
            if (!game_of_life(grid, neighbors, live, die)) break;
            print_grid(grid);
            cout << "Generation " << count << endl;
            count++;
        }

        return (0);
}

//

vector<string>  init_grid(unsigned int W, unsigned int H, char o, char x)
{
        vector<string>  grid;
        size_t          n, i, j;
        string          s;

        srand((unsigned int) time(NULL));
        i = -1;
        while (++i < H)
        {
            s = "";
            j = -1;
            while (++j < W)
            {
                n = (unsigned int) rand() % 2;
                if (!n) s += x;
                else    s += o;
            }
            grid.push_back(s);
        }

        return (grid);
}

//      classic conway rules

//      condensed :
//      Any live cell with 2 or 3 live neighbours survives.
//      Any dead cell with 3 live neighbours becomes a live cell.
//      All other cells die (or stay dead) in the next generation.

//      verbose :
//      Any live cell with < 2 live neighbours dies, as if by underpopulation.
//      Any live cell with 2 or 3 live neighbours lives.
//      Any live cell with > 3 live neighbours dies, as if by overpopulation.
//      Any dead cell with 3 live neighbours gains life, as if by reproduction.

//      + 1 rule:
//      a cell might gain life should 1 or 2 neighbors are alive
//      ex nihilo happens at most once each generation


bool    game_of_life(vector<string> &grid, vvi n, char o, char x)
{
        vector<string>  state;
        bool            active, exnihilo;
        int             alive, r;

        state = grid;
        exnihilo = active = false;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].length(); j++)
            {
                alive = count_live_neighbors(grid, n, i, j, o);
                if (alive != 2 && alive != 3)
                {
                    if (state[i][j] != x)   active = true;
                    state[i][j] = x;
                }
                if (alive == 3)
                {
                    if (state[i][j] != o)   active = true;
                    state[i][j] = o;
                }
                if ((alive == 1 || alive == 2) && grid[i][j] == x && !exnihilo)
                {
                    srand((unsigned int) time(NULL));
                    r = (unsigned int) rand() % 3;
                    if (!r) state[i][j] = o, exnihilo = true;
                }
            }
        }
        grid = state;

        return (active);
}

int     count_live_neighbors(vector<string> s, vvi n, int p, int q, char o)
{
        int     x, y, total;

        total = 0;
        for (int i = 0; i < n.size(); i++)
        {
            x = p + n[i][0];
            y = q + n[i][1];
            if (y > s[0].length() - 1)  y -= s[0].length();
            if (y < 0)                  y += s[0].length();
            if (x < 0)                  x += s.size();
            if (x > s.size() - 1)       x -= s.size();
            if (x < s[0].length() && y < s[0].length() &&
                y > -1 && x > -1 && s[x][y] == o) total++;
        }

        return (total);
}

void    print_grid(vector<string> grid)
{
        //cout << endl;
        for (int i = 0; i < grid.size(); i++) cout << grid[i] << ' ' << i << endl;
        //cout << endl;
}
