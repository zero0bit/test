#include <stdio.h> // standard library
#include <stdlib.h> // For rand() and srand()
#include <time.h> // For time() function (used as random seed)

#define MAX 20 // bishtarin meghdar row and column

int rows, cols, mines; // row = radif ha, cols = soton, mines = min ha
char board[MAX][MAX]; // mydan kol bazy 
char visible[MAX][MAX]; // chizy keh karbar mibineh

// meghdar dehy avaliyeh ha do arry
void initializeBoard()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = '0'; // dor takhteh ro shomareh gozary mi konad
            visible[i][j] = '*'; // tamam khaneh ha ra * mi zarad
        }
}

// min ha ra beh sorat tasadofy gharar my dahad
void placeMines() 
{
    int placed = 0; // shomarandeh min ha
    while (placed < mines) // agar tedad min hay gharar gerefteh shodeh kam tar az shomarandeh min ha bashad
    {
        int r = rand() % rows; // entekhab yek radif random
        int c = rand() % cols; // entekhab yek soton random
        if (board[r][c] != 'M') // agar makan random bomb nabod dakhelesh
        {
            board[r][c] = 'M'; // bomb ro gharaa bedeh
            placed++; // afzayesh shomarandeh
        }
    }
}

// shomaresh min hay atraf khaneh hay khaly
int countMines(int r, int c)
{
    int count = 0; // shomarandeh min ha
    for (int i = -1; i <= 1; i++) // baressy hamsayeh ha radif ha
        for (int j = -1; j <= 1; j++) // // baressy hamsayeh ha soton ha
        { 
            int nr = r + i;
            int nc = c + j;

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
                if (board[nr][nc] == 'M')
                    count++;
        }
    return count;
}

// 0 ro dakhel khone haei keh bomb atarfesh nist mizareh 
void calculateNumbers()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (board[i][j] != 'M')
                board[i][j] = countMines(i, j) + '0'; // ersal be tabe "countMines"
}

// print board
void printBoard()
{
    printf("\n   ");
    for (int i = 0; i < cols; i++)
        printf("%2d ", i); // chap shomareh hay soton
    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        printf("%2d ", i); // chap shomareh hay radif
        for (int j = 0; j < cols; j++)
            printf(" %c ", visible[i][j]); // print mohtava selol hay ghabel namayesh bara karbar
        printf("\n");
    }
}

/*
khaneh ha ra keh * hastand rad mi konad
khaneha keh 0 hastand ra ba estefade az tabe bazgashty dobareh khane hay atrafesh ro seda mizaneh
, barrey mikonek keh age ona ham 0 hastan baz beshan
*/
void reveal(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols) // kharej az mahdodeh
        return;

    if (visible[r][c] != '*') // agar khine * bashi basteh misheh
        return;

    visible[r][c] = board[r][c]; // barab kardan khorojy ha

    if (board[r][c] == '0') // barresy khoneh hay atraf khaneh 0
    {
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                reveal(r + i, c + j); // seda zadan dobareh khod tabe bazgashty
    }
}

 // barresy win shodan
int checkWin()
{
    int hidden = 0; // shamresh khaneh hay makhfy
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (visible[i][j] == '*')
                hidden++;

    return hidden == mines; // agar khaneh hay min barabar khaneh hay makhfy bashad win!
}

// print kamel (zaman payan)
void revealAll()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            visible[i][j] = board[i][j];
}

int main()
{
    srand(time(NULL)); // bray ejad yek adad random ba estefade az time
    // agar seed ro nazarim har bar adad random tekrary mide alan miyad bar assa time mideh 

    // daryaft soton, radif, teydad min ha
    printf("Rows (max 20): ");
    scanf("%d", &rows);
    printf("Cols (max 20): ");
    scanf("%d", &cols);
    printf("Mines: ");
    scanf("%d", &mines);

    // barresy kharej bodan az mahdodeh
    if (rows <= 0 || rows > MAX || cols <= 0 || cols > MAX)
    {
        printf("Invalid board size!\n");
        return 1;
    }

    // barresy bishtar nabodan min ha az teydad kol khaneh ha
    if (mines >= rows * cols)
    {
        printf("Too many mines!\n");
        return 1;
    }

    // call function
    initializeBoard();
    placeMines();
    calculateNumbers();

    // r = radif, c = soton // vorody karbar baray barresy khaneh ha
    int r, c;

    while (1)
    {
        printBoard(); // print jadval bazy 
        printf("Enter row and col: ");


        // ba in dastor barresy misheh ke karbar 2 adad vared kardeh ya na
        // in dastor migoyad keh ma do adad ra dorost zadim ya nah bar asas megdar return.
        if (scanf("%d %d", &r, &c) != 2)
        {
            printf("Invalid input!\n");
            break;
        }

        if (r < 0 || r >= rows || c < 0 || c >= cols)
        {
            printf("Out of range!\n");
            continue;
        }

        // agar khaneh ro baz karim , dobareh bezanim mige "Already opened!"
        if (visible[r][c] != '*')
        {
            printf("Already opened!\n");
            continue;
        }

        // agar khaneh min bashad game over
        if (board[r][c] == 'M')
        {
            revealAll();
            printBoard();
            printf("Game Over!\n");
            break;
        }

        // call function
        reveal(r, c);

        // barresy win or not win
        if (checkWin())
        {
            revealAll();
            printBoard();
            printf("You Win!\n");
            break;
        }
    }

    return 0;
}