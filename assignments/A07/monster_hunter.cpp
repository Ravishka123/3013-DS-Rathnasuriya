/*************************************************************
Ravishka Rathnasuriya
Dr. Terry Griffin
12/02/2019
Monster Hunter Game 

Description

 implement the A-Star algorithm allowing a set of monsters to find some character and kill him. 
 This has 4 levels. But still working on level on.

 start by placing a "Monster" (🦖) randomly on the screen/game-board somewhere and make it stationary. Then after placing a "Hunter" (🤺) on the game-board it should start moving towards the Monster. You can simulate animation with console apps by using a "clear screen" then redrawing the board after updating the location of each entity. After the Hunter reaches your Monster, go to level two. 
**************************************************************/

#include "TermGame.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
using namespace std;
namespace TG = TermGame;
namespace TP = TermPrint;

int rows = 30;
int cols = 50;


//structure to get the points
//x and y

struct Point {
    int x;
    int y;
    Point(){
        x=0;
        y=0;
    }
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

//player structure will make players in the game 
//defining its properties foreground, background, ch
struct Player {
    string ch;
    unsigned short foreground;
    unsigned short background;
    Player() {
        foreground = 8;
        background = 1;
        ch = "  ";
    }
    //constructor
    Player(string c) {
        foreground = 8;
        background = 1;
        ch = c;
    }
    //parametrized constructor
    Player(string c, unsigned short fore, unsigned short back = 1) {
        foreground = fore;
        background = back;
        ch = c;
    }

    /// set players attributes like colors
    void SetColor(unsigned short fore, unsigned short back = 1) {
        foreground = fore;
        background = back;
    }
    // print it
    void Print() {
        TP::print(ch, foreground, background);
    }
};


//structure for cell
//consist of different properties
// row, col, instance of player pointer, wall. character
struct Cell {
    int row;
    int col;
    Player *pl;
    bool wall;
    string ch;
    //constructor
    Cell() {
        col = 0;
        row = 0;
        pl = NULL;
        ch = ". ";
        wall = false;
    }
    //parametrized constructor
    Cell(int r, int c) {
        col = c;
        row = r;
        pl = NULL;
        ch = ". ";
        wall = false;
    }
    //parametrized constructor
    Cell(int r, int c, Player *p) {
        col = c;
        row = r;
        pl = p;
        ch = ". ";
        wall = false;
    }
//print the cell function
//using conditions to if the player is there or not.
    void PrintCell() {
        if (pl) {
            pl->Print();
        } else {
            TP::print(ch, 8, 1, false);
        }
    }
//function get player will get the player using a pointer
//using a temp pointer pointed to player
    Player *GetPlayer() {
        Player *temp = pl;
        pl = NULL;
        return temp;
    }
//set function to set the player 
    void SetPlayer(Player *p) {
        pl = p;
    }
//void make wall function will create a wall
    void MakeWall() {
        wall = true;
        ch = "🔳";
    }
};


//printboard function that will print the board
// parameters triple pointer to an instance of cell, rows and cols
//it will print the location of the board by travesing the cell
void printBoard(Cell ***gb, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            gb[i][j]->PrintCell();
        }
        cout << endl;
    }
}


// pointer to cell structure that would return an cell
//we pass rows and colums
// this will create a board and then return it to cell structure

Cell ***BuildBoard(int rows, int cols) {
    Cell ***GameBoard;
    Player *temp;
    GameBoard = new Cell **[rows];
    for (int i = 0; i < rows; i++) {
        GameBoard[i] = new Cell *[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            GameBoard[i][j] = new Cell(i, j);
        }
    }
    return GameBoard;
}

//bool function will return yes or no based on the position of the point
bool OnBoard(Point p) {
    return p.x >= 0 && p.x < cols && p.y >= 0 && p.y < rows;
}

//move function
// point as a parameter
// this will move the objects based on the implementation
void Move(Point &p) {
    if (rand() % 2 == 0) {
        if (rand() % 2 == 0) {
            ++p.x;
        } else {
            --p.x;
        }

    } else {
        if (rand() % 2 == 1) {
            ++p.y;
        } else {
            --p.y;
        }
    }

    if (!OnBoard(p)) {
        p.y = rand() % rows;
        p.x = rand() % cols;
    }

}

//double function for distance 
//calculated using the points and return it.
double Distance(Point p1, Point p2) {
    int dx{p1.x - p2.x};
    int dy{p1.y - p2.y};
    return dx * dx + dy * dy;
}

//🧞 🧞‍♀️ 🧞‍♂️🔥


//my main function

int main() {
//random number generates for integers r1,c1,r2,c2 whcih are rows and colums
  srand(time(0));

    int r1 = rand() % rows;
    int c1 = rand() % cols;
    int r2 = rand() % rows;
    int c2 = rand() % cols;

//for points of p1 and p2 we create the random numbers 
    Point p1(rand()%cols,rand()%rows);
    Point p2(rand()%cols,rand()%rows);
    Point tp;
//pointer to instances of player
    Player *temp1;
    Player *temp2;

//mke the distance
    double dist_prev = 0.0;
    double dist_next = 0.0;

//cell will call the buildboard function which will build a board and then return 
//it back to cell
    Cell ***GameBoard = BuildBoard(rows, cols);

    for (int i = 5; i < 15; i++) {
        GameBoard[10][i]->MakeWall();
    }

//pasing argumentds
    GameBoard[p1.y][p1.x]->SetPlayer(new Player("🤺", 2, 1));

    GameBoard[p2.y][p2.x]->SetPlayer(new Player("🦖", 2, 1));

    dist_prev = Distance(p1,p2);


//work done here test for the gme
    while (true) {
        TP::clear();

        temp1 = GameBoard[p1.y][p1.x]->GetPlayer();

        dist_next = Distance(p1,p2);
        while(dist_next >= dist_prev){
            Move(p1);
            dist_next = Distance(p1,p2);
        }
        dist_prev = dist_next;

        GameBoard[p1.y][p1.x]->SetPlayer(temp1);

//we assign monstersand hunters for the game and and its positions 
        if(p1.x==p2.x && p1.y==p2.y){
            temp2 = GameBoard[p2.y][p2.x]->GetPlayer();
            temp2->ch = "🦖";
            p2.x = rand()%cols;
            p2.y = rand()%rows;
            GameBoard[p2.y][p2.x]->SetPlayer(temp2);
            temp1->ch = "🤺";
            dist_next = dist_prev =0;
        }
//print board
        printBoard(GameBoard, rows, cols);
        TG::sleep(100);
    }
    return 0;
}



/*Astar Algorithm pseudocode
Still in progress in understanding how to use it for this problem.

function reconstruct_path(cameFrom, current)
    total_path := {current}
    while current in cameFrom.Keys:
        current := cameFrom[current]
        total_path.prepend(current)
    return total_path

// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
function A_Star(start, goal, h)
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    openSet := {start}

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start to n currently known.
    cameFrom := an empty map

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    gScore := map with default value of Infinity
    gScore[start] := 0

    // For node n, fScore[n] := gScore[n] + h(n).
    fScore := map with default value of Infinity
    fScore[start] := h(start)

    while openSet is not empty
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := gScore[neighbor] + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)

    // Open set is empty but goal was never reached
    return failure
    */