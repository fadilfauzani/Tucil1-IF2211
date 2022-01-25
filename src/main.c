#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MaxChar 100
#define boardSize 100

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define Yellow "\033[0;33m"
#define Blue "\033[0;34m"
#define Purple "\033[0;35m"
#define Cyan "\033[0;36m"
#define reset "\033[0m"

typedef struct string
{
    char buff[MaxChar];
    int length;
} string;

#define Char(S, i) (S).buff[i]

void printString(string s){
    for (int i = 0; i < s.length; i++){
        printf("%c", Char(s, i));
    };
    printf("\n");
}
typedef struct colorChar{
    char c;
    int type;
} colorChar;
typedef struct board
{
    colorChar buff[boardSize][boardSize];
    int sizeRow,sizeCol;
} board;

int ansCount;
char fileName[22] = "../test/testcasex.txt";
int testCount = 0;

#define Board(S, i, j) (S).buff[i][j]

string takeStringfromBoard(board b, int fromRow, int fromCol, int size, unsigned int mode){
    string res;
    int count = 0;
    switch (mode)
    {
    case 1:
        /* Kekanan */
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow, fromCol + i).c;
        break;
    case 2:
        /* ke kiri */
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow, fromCol - i).c;
        break;
    case 3:
        /* kebawah */
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow + i, fromCol).c;
        break;
    case 4:
        /* ke atas*/
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow - i, fromCol).c;
        break;
    case 5:
        /* miring Tenggara (bawah kanan)*/
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow + i, fromCol + i).c;
        break;
    case 6:
        /* miring Barat daya (bawah kiri)*/
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow + i, fromCol - i).c;
        break;
    case 7:
        /* miring Barat laut (kiri atas)*/
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow - i, fromCol - i).c;
        break;
    case 8:
        /* miring Timur laut (kanan atas)*/
        for (int i = 0; i < size; i++) Char(res, i) = Board(b, fromRow - i, fromCol + i).c;
        break;
    default:
        break;
    }
    res.length = size;
    return res;
}
/* Jelek banget karena nimpah yang sudah ada males buat baru*/
void showFoundStr(board *b,int fromRow, int fromCol, int size, unsigned int mode, int type, unsigned int verbose){
    switch (mode)
    {
    case 1:
        /* Kekanan */
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j = 0; j <(*b).sizeCol; j++)
                if (j >= fromCol && j < fromCol + size && i ==fromRow){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
        printf("\n");
        
        break;
    case 2:
        /* ke kiri */
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j =0; j < (*b).sizeCol; j++)
                if (j <= fromCol && j > fromCol - size && i ==fromRow){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
        printf("\n");
        break;
    case 3:
        /* kebawah */
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j =0; j < (*b).sizeCol; j++)
                if (i >= fromRow && i < fromRow + size && j ==fromCol){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
        printf("\n");
        break;
    case 4:
        /* ke atas*/
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j =0; j < (*b).sizeCol; j++)
                if (i <= fromRow && i > fromRow - size && j ==fromCol){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
        printf("\n");
        break;
    case 5:
        /* miring Tenggara (bawah kanan)*/
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j =0; j < (*b).sizeCol; j++)
                if (j >= fromCol && j < fromCol + size && i == fromRow - fromCol + j ){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
        printf("\n");
        break;
    case 6:
        /* miring Barat daya (bawah kiri)*/
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j =0; j < (*b).sizeCol; j++)
                if (j <= fromCol && j > fromCol - size && i == fromRow + fromCol - j ){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
        printf("\n");
        break;
    case 7:
        /* miring Barat laut (kiri atas)*/
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j =0; j < (*b).sizeCol; j++)
                if (j <= fromCol && j > fromCol - size && i == fromRow - fromCol + j ){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
        printf("\n");
        break;
    case 8:
        /* miring Timur laut (kanan atas)*/
        for (int i = 0; i < (*b).sizeRow; i++) {
            for (int j =0; j < (*b).sizeCol; j++)
                if (j >= fromCol && j < fromCol + size && i == fromRow + fromCol - j ){
                    if (verbose) printf("%c ",Board((*b), i, j).c);
                    else Board((*b),i,j).type = type;
                }
                else if (verbose)
                    printf("- ");
            if (verbose)
            printf("\n");
            }
        if (verbose)
            printf("\n");
        break;
    default:
        break;
    }
}

void makeBoard(board * b, FILE * stream){
    char cc = getc(stream);
    int i = 0;
    int j = 0;
    while (cc != EOF){
        if (cc == '\n') break;
        else if (cc == ' ') cc = getc(stream);
        Board(*b, i, j).c = cc;
        j++;
        cc = getc(stream);
        if (cc == '\n') {
            cc = getc(stream);
            i++;
            b->sizeCol = j;
            j = 0;    
        };
    }
    b->sizeRow = i;
}
void makesols(string sols[], FILE * stream){
    char cc = getc(stream);
    int i = 0;
    int j = 0;
    while (cc != EOF){
        while (cc != '\n' && cc != EOF){
            Char(sols[i], j) = cc;
            cc = getc(stream);
            // printf("%c", cc);
            j++;
        }
        sols[i].length = j;
        j = 0;
        printString(sols[i]);
        cc = getc(stream);
        i++;
    }
    ansCount = i;
}
unsigned int strcmpr(string A, string B){
    if (B.length < A.length) return 0;
    for (int i = 0; i < A.length; i++) {
        testCount++;
        if (Char(A, i) != Char(B, i)) return 0;
    };
    return 1;
}

int solve(board *b, string sols[], unsigned int verbose){
    int count = 0;
    int cType = 1;
    for (int i = 0; i < (*b).sizeRow;i++){
        for (int j = 0; j < (*b).sizeCol; j++){
                for (int k = 0; k < ansCount; k++){
                    if (cType > 6) cType = 1;
                    if (sols[k].length > 1){
                    for (int l = 1; l <= 8; l++) if (strcmpr(sols[k], takeStringfromBoard((*b), i, j, sols[k].length, l))){
                        count++;
                        if (verbose)
                        printf("\n%d. \n",count);
                        showFoundStr(b, i, j, sols[k].length, l, cType, verbose);
                        cType++;
                    }
                    }
                    else if (sols[k].length = 1){
                        if (strcmpr(sols[k], takeStringfromBoard((*b), i, j, sols[k].length, 1)))
                        {
                            count++;
                            if (verbose)
                            printf("\n%d. \n",count);
                            showFoundStr(b, i, j, sols[k].length, 1, cType, verbose);
                            cType++;
                        }
                    }
                    
                }
        }
    }
    return count;
}
char castInt(int in){
     switch (in)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    }
}
void showBoard(board b){
    for (int i = 0; i < b.sizeRow; i++){
        for (int j = 0; j< b.sizeCol; j++){
            // printf("%d\n",Board(b,i,j).type);
            switch (Board(b,i,j).type)
            {
            case 1:
                printf(RED);
                break;
            case 2:
                printf(Yellow);
                break;
            case 3:
                printf(Yellow);
                break;
            case 4:
                printf(Blue);
                break;
            case 5:
                printf(Purple);
                break;
            case 6:
                printf(Cyan);
                break;
            default:
                printf(reset);
                break;
            }
            printf("%c " reset, Board(b, i, j).c);
        }
        printf("\n");
    }
}
int main(){
    int x;
    board b;
    string sols[15];
    printf("Masukkan nomor testcase file(1-8): ");
    scanf("%d",&x);
    fileName[16] = castInt(x);
    FILE *txt = fopen(fileName, "r");
    makeBoard(&b, txt);
    showBoard(b);
    makesols(sols, txt);
    clock_t start,end;
    start = clock();
    int count = solve(&b, sols, 0);
    showBoard(b);
    end = clock();
    printf("melakukan total %d perbandingan huruf dan dibutuhkan %lf detik \n", testCount,(double)(end-start)/CLOCKS_PER_SEC);
    printf("terdapat %d kata yang ditemukan\n", count);
    fclose(txt);
}