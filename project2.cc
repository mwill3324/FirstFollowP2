
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "lexer.h"
//#include "lexer.cc"// may need to be included to run properly on some compilers...
#define MAX_TEXT_LINE_LENGTH 128
using namespace std;

int main (int argc, char* argv[])
{
    int task;
    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }
    LexicalAnalyzer lexer;
    ///////////Holds first two lines////////
    Token terminals[255];
    Token NonTerms[255];
    ////////////////////////////////////////
    Token lines[255][255];
    ////////////////////////Task 1///////////////////
    string Tnames[255];
    string Terms[255];
    int occ[255];
    memset (occ,-1,255);
    ////////////////////////////////////////////////
    int nolines= 0;

    int termIt = 0,b = 0, c = 0;
    Terms[c]="!";
    //cout<<Terms[c]<<" ";
    c++;

    while(terminals[b].token_type != HASH){
        terminals[termIt] = lexer.GetToken();
        //terminals[a].Print();
        ////task 1/////////////
        if(terminals[termIt].token_type == ID){

            Tnames[c] = terminals[termIt].lexeme;
            Terms[c] = terminals[termIt].lexeme;
            occ[c]= 0;
            //cout<<Terms[c]<<" ";
            c++;
        }
        ////////////////////
        termIt++;
        b = termIt - 1;
    }
    int numTerms = c;
    //cout<<termIt<<" "<<c<<endl;
    //cout<<endl;
     b = 0;
    int numNons = 0;
    while(NonTerms[b].lexeme != "#"){
        NonTerms[numNons] = lexer.GetToken();
        //NonTerms[a].Print();
      /////task 1//////////
       // if(terminals[b].token_type == ID && NonTerms[numNons].lexeme.length() > 0){
            Tnames[c] = NonTerms[numNons].lexeme;
            occ[c] = 0;
            //cout<<Tnames[c]<<" ";
            c++;
       // }
        /////////////////////
        if(NonTerms[numNons].token_type == HASH)
        {
            break;
        }
        numNons++;
        b = numNons - 1;
    }
    //cout<<endl;


    //cout<<"--Lines--"<<endl;
    int a = 0;
    b = 0;
    int row = 0, pos = 0;
    bool disc[c];
    while(lines[row][pos].token_type != DOUBLEHASH){
        memset(disc,false,c);
        pos = 0;
        while(1)
        {
            lines[row][pos] = lexer.GetToken();
            //lines[row][pos].Print();
            if(lines[row][pos].token_type == HASH){
               if(pos == 2)
               {
                lines[row][pos].lexeme = "!";
                lines[row][pos].token_type = ID;
                lines[row][pos+1].lexeme = "#";
                lines[row][pos+1].token_type = HASH;
                //cout<<lines[row][pos].lexeme<<" ";
                break;
               }
               else
               {
                 break;
               }
            }
             //cout<<lines[row][pos].lexeme<<" ";

            /////////////////task 1///////////////////////
                int found = 0;
                while(found < c)
                {
                    if(lines[row][pos].lexeme.compare(Tnames[found]) == 0)
                        {
                            disc[found] = true;
                            break;
                        }
                    found++;
                }
            ////////////////////////////////////
            pos++;
        }
        //cout<<endl;
        int z = 0;
        while(z<=c){
            if(disc[z] == true){
                    occ[z]++;
                }
            z++;
            }
            z=0;
        row++;
        nolines++;
        lines[row][pos] = lexer.GetToken();
        if(lines[row][pos].token_type == DOUBLEHASH){
            break;
        }
        else
        {
            lexer.UngetToken(lines[row][pos]);
        }
        //cout<<endl;
    }




    int numRows = row;
    bool reachable[c];
    memset(reachable,false,c);

   //string first[numNons][255];
   //string follow[numNons][255];
    bool first[numNons][numTerms];
    bool follow[numNons][numTerms];
    int fillr = 0;
    while(fillr<numNons){
        int fillc = 0;
        while(fillc<numTerms){
                  first[fillr][fillc] = false; //Easy delim to set for this proj
                  follow[fillr][fillc] = false;
                  fillc++;
              }
              fillr++;
    }



    bool changed = true;

    //cout<<lines[0][0].lexeme<<endl;
    //cout<<lines[0][1].lexeme<<endl;
    //cout<<lines[0][2].lexeme<<endl;
    //cout<<lines[0][3].lexeme<<endl;

    ///////////First///////////////////
    //////////////
    string Nons[numNons];
    int nn = 0;
    int loc = 0;
    //////////////////////////////////
    while(nn<numNons)
    {
        Nons[nn] = Tnames[numTerms+nn];
        nn++;
    }
    //cout<<strlen(lines[0][0].lexeme.c_str())<<endl;
    /////////////

    int curr = 0;
    int ran  = 0;
    //////////////START OF FIRST/////////////////
    /////////////////////////////////////////////
    /////////////////////////////////////////////
    while(changed == true)
    {
        ran++;
        curr = 0;
        changed = false;
        while(curr < numRows){
            //changed = false;
            ///////////////////find location//////////////////
            int x=0;
            /////////////////////////////vvv takes care of multiple non term rules on diff lines
            while(x < numNons)
            {
                if(lines[curr][0].lexeme == Nons[x])
                {
                   loc = x;
                   break;
                }
                x++;
            }
            //////////////////////////////////////////////////////////////////
           // cout<<Nons[loc]<<" "<<lines[curr][0].lexeme<<endl;
            /////////////////////////////////////////////////
            bool eps = true;
            int epos = 0;

            while(eps == true)
            {
                eps = false;
                bool isterm = false;
                int tcheck;
                for(tcheck = 0; tcheck < numTerms;tcheck++) //Find terminal
                {
                    if(lines[curr][ 2 + epos].lexeme == Terms[tcheck])
                    {
                        //cout<<lines[curr][2+epos].lexeme<<" "<<Terms[tcheck]<<endl;
                        isterm = true;
                        break;
                    }
                }
                if(isterm == true) //////////////////CHECKS 4 TERMINAL
                {
                    //cout<<"IS TERM"<<endl;
                    if(first[loc][tcheck]!= true)
                    {
                        first[loc][tcheck] = true;
                        changed = true;
                    }
                }
                /////////////////////////////////////////////////////////////////
                ///////////////////NON NON NON NON NON NON////////////////////////
                else
                {
                    // cout<<"NON TERM"<<endl;
                    /////////////////find location of first letter
                    int xx = 0;
                    int loc2;
                        while(xx < numNons)
                        {
                            if(lines[curr][  2 + epos  ].lexeme == Nons[xx])
                            {
                               loc2 = xx;
                               break;
                            }
                            xx++;
                        }

                    ////////////////////////////////
///////////////////////////////////////////////////////////////////
                    for(int y = 1; y < numTerms; y++){
                        if(first[loc2][y]== true){

                            if(first[loc][y]!= true){
                                first[loc][y]=true;
                                changed = true;
                            }

                        }
                    }
                     ///////////////////////////
                    if(first[loc2][0] == true){ //if there is epsilon
                        if(lines[curr][  2 + epos + 1  ].token_type != ID ){ //check next empty
                           // cout<<"eend: "<<lines[curr][  2 + epos + 1  ].lexeme << endl;
                            if(first[loc][0] != true){
                                    first[loc][0] = true;
                                    changed = true;
                            }
                        }
                        else{ //if not empty move on
                                epos++;
                                eps = true;
                                //cout<<"epstrue: "<< epos << lines[curr][  2 + epos + 1  ].lexeme <<endl;
                            }
                            /////////////////
                    }
                }
            }//EPS
            curr++;
        }
        //break;
        if(ran>0)
            {
            //break;
            }
    }
    //cout<<"ran: "<<ran<<endl;
    /////////////////////////////////////////
    /////////////////FOLLOW//////////////////

    follow[0][0] = true; // sets S follow to $ for beginning
    bool changef = true;
    while(changef == true)
        {
            int curf = 0;
            changef = false;
            while(curf < numNons){ //GO through all the Non terminals ie/ SABC
                /////////////////////////find curf(current) letter
                //cout<<endl;
                for(int i = 0;i < numRows;i++) // goes through lines
                {
                    for(int j = 2; lines[i][j].token_type != HASH;j++) // searches line
                    {
                        //cout<<"NON Term: "<<Nons[curf]<<" Line:"<<lines[i][j].lexeme;
                        if(Nons[curf] == lines[i][j].lexeme)
                        {
                            //cout<<" match ";
                            bool epsf = true;
                            int eposf = 0;

                            while (epsf == true){
                                epsf = false;
                                bool ist = false;
                                int pp = 0, locf;

                               // while(pp < numNons) ////check if the follow is a Non terminal
                               while(pp < numTerms)
                                {
                                    //if(lines[i][j+1].lexeme == Nons[pp])
                                    //cout<<lines[i][j+1+eposf].lexeme << Terms[pp]<< " ";
                                    if(lines[i][j+1+eposf].lexeme == Terms[pp])
                                    {
                                        //cout<<"found: "<<lines[i][j+1+eposf].lexeme<<endl;
                                        ist = true;
                                        locf = pp;
                                        break;
                                    }
                                    pp++;
                                }

                                if(ist == true)
                                {
                                    //////////add Terminal to follow/////////////
                                    if(follow[curf][locf] != true)
                                    {
                                        //cout<<"adding: "<<Terms[locf]<<endl;
                                        follow[curf][locf] = true;
                                        changef = true;

                                    }

                                }
                                else // check NON TERMINAL
                                {
                                    ///////////add first to follow///////////////////////
                                    ///////////then check for epsilon////////////////////
                                    //////////finds letters position in first array
                                        bool isNonf = false;
                                        int xy = 0;
                                        int locf2;

                                        while(xy < numNons)
                                        {
                                            //if(lines[curf][  2 + eposf  ].lexeme == Nons[xy])
                                            if(lines[i][j+1+eposf].lexeme == Nons[xy])//if the one after the match is a non
                                                {
                                                   locf2 = xy; //gives location of non
                                                   isNonf = true;
                                                   break;
                                                }
                                            xy++;
                                        }

                                        if(isNonf == true)
                                        {
                                            //cout<<"NON ADD FIRST"<<endl;
                                            ////////////////////////////////
                                            //////adds to follow array//////
                                        for(int y = 1; y < numTerms; y++){ // starts at y=1 because of epsilon
                                                if(first[locf2][y] == true){
                                                    if(follow[curf][y]!= true){
                                                        //cout<<"true"<<endl;
                                                        follow[curf][y]=true;
                                                        changef = true;
                                                    }
                                                }
                                            }
                                            /////////////////////////////////////////////////////////////////
                                            if(first[locf2 + eposf][0] == true)
                                            {
                                                epsf = true;
                                                eposf++;
                                            }
                                        }
                                        else
                                        {
                                            int folLoc;
                                           // cout<<"add follow to follow"<<endl;
                                           for(int y = 0; y < numNons; y++){// for finding location of the NOn term letter
                                                if(lines[i][0].lexeme == Nons[y])//because it was the eol, add follow to follow
                                                        {
                                                           folLoc = y; //gives location of
                                                           break;
                                                        }
                                                }
                                           // cout<<folLoc;
                                            for(int y = 0; y < numTerms; y++){ // starts at y=1 because of epsilon
                                                if(follow[folLoc][y] == true){
                                                    if(follow[curf][y]!= true){
                                                        //cout<<"true"<<endl;
                                                        follow[curf][y]=true;
                                                        changef = true;
                                                    }
                                                }
                                            }
                                        }
                                }

                            }////whjle eps == true
                        }
                        //cout<<endl;

                        }
                    }
                    curf++;
                }
        }

        //////////////////////////////useless gramar
    bool used[numRows];
    bool changedU = true;
    bool nonsU[numNons];
    bool startU = false;
    bool usedinS[numNons];
    while (changedU == true)
    {
        changedU = false;
        int curU = 0;
        changedU = false;

                string start = lines[0][0].lexeme;
                for(int i = 0;i < numRows;i++) // goes through lines
                {
                    //cout<<"loop"<<endl;
                    if(lines[i][0].lexeme==start)
                    {

                    }
                    for(int j = 2; lines[i][j].token_type != HASH && lines[i][j].token_type == ID; j++) // searches line
                    {///////checks each indv line
                        bool isterm = false, isNon = false;
                        for(int a = 0; a<numTerms; a++)// check Term
                        {
                            if(lines[i][j].lexeme == Terms[a])
                            {
                                isterm = true;
                                if(lines[i][j+1].token_type == HASH &&used[i]!= true ) //check if its a one line term
                                {
                                    used[i] = true; //line is accepted
                                    changedU = true;
                                    if(lines[i][j].lexeme==start)
                                    {
                                        startU = true;
                                    }
                                }
                                //continue; //passed test
                            }
                        }
                        for(int a = 0; a<numNons; a++)// check NON
                        {
                            if(lines[i][j].lexeme == Nons[a])
                            {
                                if(nonsU[a] == true)
                                { //checked if the Non terminates
                                    isNon = true;//nonsU has to be true, otherwise NON can be useless...
                                    if(lines[i][j+1].token_type == HASH && used[i]!= true)
                                    {//and if its the end of the line accept it
                                        used[i] = true; //line is accepted
                                        changedU = true;
                                        if(lines[i][j].lexeme==start)
                                    {
                                        startU = true;
                                    }
                                    }
                                }
                            }
                        }
                        if(isNon == false && isterm == false)
                        {
                            break; //end the line
                        }
                    }
                }
              //  curU++;
            //}





        ///////////ADD USELESS GRAMAR
    }


    ////////////////////////////////////////
    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);
    // TODO: Read the input grammar at this point from standard input

    /*
       Hint: You can modify and use the lexer from previous project
       to read the input. Note that there are only 4 token types needed
       for reading the input in this project.

       WARNING: You will need to modify lexer.cc and lexer.h to only
       support the tokens needed for this project if you are going to
       use the lexer.
     */
    int f = 1;
    switch (task) {
        case 1:
            // TODO: perform task 1.
            while(f<c-1)
            {
                cout<< Tnames[f] << ": "<< occ[f]<<endl;
                f++;
            }
            break;

        case 2:
            // TODO: perform task 2.
            if(startU = true)
            {
            for(int i = 1;i < numRows;i++)
                {
                    bool space = false;
                    for(int j = 0; lines[i][j].token_type != HASH;j++)
                    {
                        if(lines[i][j].token_type)
                        if(used[i] == true)
                        {
                            space = true;
                             if(j==0)
                            {
                                cout<<lines[i][j].lexeme;
                                cout<<" ->";
                            }
                            else if(j>1)
                            {
                                cout<<" "<<lines[i][j].lexeme;
                            }
                            else
                            {
                                cout<<lines[i][j].lexeme;
                            }

                        }
                    }
                    if(space == true)
                    {
                        cout<<endl;
                    }

                }
            }

            break;
        case 3:
            // TODO: perform task 3.
             for(int x = 0;x<numNons;x++)
                {
                bool comma = false;
                cout<<"FIRST("<<Nons[x]<<") = { ";
                for(int y = 0;y<numTerms;y++)
                {
                    if(first[x][y]==true)
                    {
                        if(comma == true)
                            {
                                cout<<", ";
                            }
                        comma = true;
                        if(y==0)
                        {
                            cout<<"#";
                        }
                        else{cout<<Terms[y];}
                    }
                }
                cout<<" }"<<endl;
            }
            break;

        case 4:
            // TODO: perform task 4.
             for(int x = 0;x<numNons;x++)
            {
                bool comma = false;
                cout<<"FOLLOW("<<Nons[x]<<") = { ";
                for(int y = 0;y<numTerms;y++)
                {
                    if(follow[x][y]==true)
                    {
                        if(comma == true)
                            {
                                cout<<", ";
                            }
                        comma = true;
                        if(y==0)
                        {
                            cout<<"$";
                        }
                        else{cout<<Terms[y];}
                    }
                }
                cout<<" }"<<endl;
            }
            break;

        case 5:
            // TODO: perform task 5.
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}

