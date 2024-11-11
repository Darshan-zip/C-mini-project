#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//creating a structure for a player
typedef struct
{
    char name[25], how_out[100];
    int team,
       total_runs, fours, sixes, 
       overs, runs_given, extras, wickets;
} 
Player;

//creating a structure for a match/scoreboard with total statistics
typedef struct
{
    int runs[4], wickets[4];
}
Match;

//teams is an array of the 2 teams with 11 players each
//teams keeps track of statistics for an innings
//total_teams keeps track for the entire match
Player teams[2][11], total_teams[2][11];

//test_match is a Match struct that acts a scorecard
//it has two arrays with 4 elements each that
//keep track of runs and wickets in each innings
Match test_match;

//in is a function that checks the membership of num
//in array arr of size n
int in(int num, int arr[], int n)
{
    for(int i=0;i<n;i++)
        if(arr[i]==num) 
            return 1;
    return 0;
}

//max returns the maximum of two values
int max(int x, int y)
{
    if(x>y) 
        return x;
    return y;
}

//generates players for both teams, consisting of 6 batsmen and 5 bowlers
void gen_teams()
{
    char namelist[60][25] = {"James\0","Robert\0","John\0","Michael\0","David\0","William\0","Richard\0",
    "Joseph\0","Thomas\0","Christopher\0","Charles\0","Daniel\0","Matthew\0","Anthony\0","Mark\0","Donald\0",
    "Steven\0","Andrew\0","Paul\0","Joshua\0","Kenneth\0","Kevin\0","Brian\0","George\0","Timothy\0","Ronald\0",
    "Jason\0","Edward\0","Jeffrey\0","Ryan\0","Jacob\0","Gary\0","Nicholas\0","Eric\0","Jonathan\0","Stephen\0",
    "Larry\0","Justin\0","Scott\0","Brandon\0","Benjamin\0","Samuel\0","Gregory\0","Alexander\0","Patrick\0",
    "Frank\0","Raymond\0","Jack\0","Dennis\0","Jerry\0","Tyler\0","Aaron\0","Jose\0","Adam\0","Nathan\0","Henry\0",
    "Zachary\0","Douglas\0","Peter\0","Kyle\0"};
    int repeats[22], element, i, j=0, k;
    
    test_match.runs[0]=0,test_match.runs[1]=0,test_match.runs[2]=0,test_match.runs[3]=0; 
    test_match.wickets[0]=0,test_match.wickets[1]=0,test_match.wickets[2]=0,test_match.wickets[3]=0;
    
    for(i=0;i<11;i++)
    {
        for(k=0;k<=1;k++)
        {
            teams[k][i].team = k;
            teams[k][i].total_runs=0,teams[k][i].fours=0;
            teams[k][i].sixes=0,teams[k][i].overs=0;
            teams[k][i].runs_given=0,teams[k][i].extras=0;
            teams[k][i].wickets=0;
            
            total_teams[k][i].team = k;
            total_teams[k][i].total_runs=0,total_teams[k][i].fours=0;
            total_teams[k][i].sixes=0,total_teams[k][i].overs=0;
            total_teams[k][i].runs_given=0,total_teams[k][i].extras=0;
            total_teams[k][i].wickets=0;
            
            do
                element = rand()%60+1;
            while(in(element,repeats,22));
            repeats[j++] = element;
            strcpy(teams[k][i].name,namelist[element-1]);
            strcpy(total_teams[k][i].name,namelist[element-1]);
        }
    }
}

//simulates a delivery/ball
void simulate(int *bat1, int *bat2, int *bow, int batting_team, int innings)
{
    printf("\n");
    int roll = rand()%100 + 1, wroll = rand()%100 + 1, exroll = rand()%100 + 1;
    
    if(exroll<=9)//no ball or wide ball
    {
        teams[!batting_team][bow[0]].extras+=1;
        test_match.runs[innings]+=1;
        if(exroll>4)//wide ball
        {
            printf("WIDE ball bowled! ");
            if(roll==2) roll++; //six not possible in a wide ball
            if(6<=wroll && wroll<=85) wroll=0; //these modes of wickets not possible in wide ball
        }
        else //no ball
        {
            printf("NO ball bowled! ");
            if(4<=wroll && wroll<=85 || wroll>=96) wroll=0; //these modes of wickets not possible in wide ball
        }
    }
    
    if(roll<=5)//wicket (not considering time out, mankading, retired hurt, as they complicate the code a lot)
    {
        if(wroll==1)//obstructing the field
        {
            printf("%s has OBSTRUCTED THE FIELD in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][bow[0]].name);
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"obstructing the field\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll==2)//handling the ball
        {
            printf("%s has HANDLED THE BALL in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][bow[0]].name);
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"handling the ball\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll==3)//hit the ball twice
        {
            printf("%s has HIT THE BALL TWICE in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][bow[0]].name);
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"hit the ball twice\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll<=5)//hit wicket
        {
            printf("%s has HIT THE WICKET in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][bow[0]].name);
            teams[!batting_team][bow[0]].wickets+=1;
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"hit wicket\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll<=20)//bowled
        {
            printf("%s has been BOWLED out in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][bow[0]].name);
            teams[!batting_team][bow[0]].wickets+=1;
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"bowled out\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll<=60)//caught
        {
            printf("%s has been CAUGHT out by %s in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][rand()%11].name,teams[!batting_team][bow[0]].name);
            teams[!batting_team][bow[0]].wickets+=1;
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"caught out\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll<=85)//lbw
        {
            printf("%s has been LBW-ed in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][bow[0]].name);
            teams[!batting_team][bow[0]].wickets+=1;
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"LBW\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll<=95)//run out
        {
            printf("%s has been RUN out by %s in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][rand()%11].name,teams[!batting_team][bow[0]].name);
            teams[!batting_team][bow[0]].wickets+=1;
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"run out\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        else if(wroll<=100)//stumping
        {
            printf("%s has been STUMPED out by %s in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][5].name,teams[!batting_team][bow[0]].name);
            teams[!batting_team][bow[0]].wickets+=1;
            test_match.wickets[innings]+=1;
            strcpy(teams[batting_team][bat1[0]].how_out,"stumping\0");
            bat1[0]=max(bat1[0],bat2[0]) + 1; //new batsman coming in
        }
        printf("%s : %d, %s : %d\n",teams[batting_team][bat1[0]].name,teams[batting_team][bat1[0]].total_runs,
            teams[batting_team][bat2[0]].name,teams[batting_team][bat2[0]].total_runs);
        printf("%s : %d overs, %d wickets\n",teams[!batting_team][bow[0]].name,
            teams[!batting_team][bow[0]].overs,teams[!batting_team][bow[0]].wickets);
    }
    else if(roll==6)//six
    {
        printf("%s has hit a SIX in %s's delivery!\n",teams[batting_team][bat1[0]].name,
            teams[!batting_team][bow[0]].name);
        teams[batting_team][bat1[0]].total_runs+=6;
        teams[batting_team][bat1[0]].sixes+=1;
        teams[!batting_team][bow[0]].runs_given+=6;
        test_match.runs[innings]+=6;
        printf("%s : %d, %s : %d\n",teams[batting_team][bat1[0]].name,teams[batting_team][bat1[0]].total_runs,
            teams[batting_team][bat2[0]].name,teams[batting_team][bat2[0]].total_runs);
        printf("%s : %d overs, %d wickets\n",teams[!batting_team][bow[0]].name,
            teams[!batting_team][bow[0]].overs,teams[!batting_team][bow[0]].wickets);
    }
    else if(roll<=16)//four
    {
        if(4<exroll && exroll<=9) //wide ball
        {
            printf("The ball has gone for FOUR in %s's delivery!\n", teams[!batting_team][bow[0]].name);
            teams[!batting_team][bow[0]].extras+=4; 
        }
        else
        {
            printf("%s has hit a FOUR in %s's delivery!\n",teams[batting_team][bat1[0]].name,
                teams[!batting_team][bow[0]].name);
            teams[batting_team][bat1[0]].total_runs+=4;
            teams[batting_team][bat1[0]].fours+=1;
            teams[!batting_team][bow[0]].runs_given+=4;
        }
        test_match.runs[innings]+=4;
        printf("%s : %d, %s : %d\n",teams[batting_team][bat1[0]].name,teams[batting_team][bat1[0]].total_runs,
            teams[batting_team][bat2[0]].name,teams[batting_team][bat2[0]].total_runs);
        printf("%s : %d overs, %d wickets\n",teams[!batting_team][bow[0]].name,
            teams[!batting_team][bow[0]].overs,teams[!batting_team][bow[0]].wickets);
    }
    else if(roll<=19)//three runs
    {
        printf("%s has taken THREE runs in %s's delivery.\n",teams[batting_team][bat1[0]].name,
            teams[!batting_team][bow[0]].name);
        teams[batting_team][bat1[0]].total_runs+=3;
        teams[!batting_team][bow[0]].runs_given+=3;
        test_match.runs[innings]+=3;
        //swapping batsmen
        bat1[0] = bat1[0]^bat2[0];
        bat2[0] = bat1[0]^bat2[0];
        bat1[0] = bat1[0]^bat2[0];
        printf("%s : %d, %s : %d\n",teams[batting_team][bat1[0]].name,teams[batting_team][bat1[0]].total_runs,
            teams[batting_team][bat2[0]].name,teams[batting_team][bat2[0]].total_runs);
        printf("%s : %d overs, %d wickets\n",teams[!batting_team][bow[0]].name,
            teams[!batting_team][bow[0]].overs,teams[!batting_team][bow[0]].wickets);
    }
    else if(roll<=29)//double
    {
        printf("%s has taken TWO runs in %s's delivery.\n",teams[batting_team][bat1[0]].name,
            teams[!batting_team][bow[0]].name);
        teams[batting_team][bat1[0]].total_runs+=2;
        teams[!batting_team][bow[0]].runs_given+=2;
        test_match.runs[innings]+=2;
        printf("%s : %d, %s : %d\n",teams[batting_team][bat1[0]].name,teams[batting_team][bat1[0]].total_runs,
            teams[batting_team][bat2[0]].name,teams[batting_team][bat2[0]].total_runs);
        printf("%s : %d overs, %d wickets\n",teams[!batting_team][bow[0]].name,
            teams[!batting_team][bow[0]].overs,teams[!batting_team][bow[0]].wickets);
    }
    else if(roll<=62)//single
    {
        printf("%s has taken ONE run in %s's delivery.\n",teams[batting_team][bat1[0]].name,
            teams[!batting_team][bow[0]].name);
        teams[batting_team][bat1[0]].total_runs+=1;
        teams[!batting_team][bow[0]].runs_given+=1;
        test_match.runs[innings]+=1;
        //swapping batsmen
        bat1[0] = bat1[0]^bat2[0];
        bat2[0] = bat1[0]^bat2[0];
        bat1[0] = bat1[0]^bat2[0];
        printf("%s : %d, %s : %d\n",teams[batting_team][bat1[0]].name,teams[batting_team][bat1[0]].total_runs,
            teams[batting_team][bat2[0]].name,teams[batting_team][bat2[0]].total_runs);
        printf("%s : %d overs, %d wickets\n",teams[!batting_team][bow[0]].name,
            teams[!batting_team][bow[0]].overs,teams[!batting_team][bow[0]].wickets);
    }
    else //dot ball
    {
        printf("%s has played a DOT ball in %s's delivery.\n",teams[batting_team][bat1[0]].name,
            teams[!batting_team][bow[0]].name);
        printf("%s : %d, %s : %d\n",teams[batting_team][bat1[0]].name,teams[batting_team][bat1[0]].total_runs,
            teams[batting_team][bat2[0]].name,teams[batting_team][bat2[0]].total_runs);
        printf("%s : %d overs, %d wickets\n",teams[!batting_team][bow[0]].name,
            teams[!batting_team][bow[0]].overs,teams[!batting_team][bow[0]].wickets);
    }
    if(exroll<=9) simulate(bat1,bat2,bow,batting_team,innings);
}

//function that takes care of proceedings when an over ends
int endover(int *bat1, int *bat2, int *bow, int batting_team, int innings, int over)
{
    //swapping batsmen
    bat1[0] = bat1[0]^bat2[0];
    bat2[0] = bat1[0]^bat2[0];
    bat1[0] = bat1[0]^bat2[0];
    
    //changing bowler after updating overs bowled
    teams[!batting_team][bow[0]].overs += 1;
    int b, bias=rand()%100 + 1;
    if(bias==1)
    {
        do
            b=rand()%5;
        while(b==bow[0]);
    }
    else
    {
        do
            b=rand()%5 + 6;
        while(b==bow[0]);
    }
    bow[0]=b;
    
    //declare + follow-on(?)
    int dec=0, follow_on=0;
    if(over>45 && test_match.runs[innings]>300 && rand()%10 + 1!=10) dec = 1;
    if(dec && innings==1 && test_match.runs[1]*2<test_match.runs[0]) follow_on = 1;
    return follow_on*10+dec;
}

//function that takes care of proceedings when an innings ends
int endinnings(int innings, int *batting_team, int follow_on)
{
    printf("\n---------INNINGS %d OVER----------\n",innings+1);
    printf("----- %d/%d -------\n",test_match.runs[innings],test_match.wickets[innings]);
    for(int i=0; i<=1;i++)
    {
        for(int j=0;j<11;j++)
        {
            printf("%s:%s\n",teams[i][j].name , teams[i][j].how_out);
            printf("Total Runs:%d, Fours:%d, Sixes:%d\n",teams[i][j].total_runs , teams[i][j].fours, teams[i][j].sixes);
            printf("Overs Bowled:%d, Runs Given:%d, Extras:%d, Wickets:%d\n",teams[i][j].overs , 
                    teams[i][j].runs_given, teams[i][j].extras, teams[i][j].wickets);
            printf("\n");
            
            total_teams[i][j].total_runs+=teams[i][j].total_runs,total_teams[i][j].fours+=teams[i][j].fours;
            total_teams[i][j].sixes+=teams[i][j].sixes,total_teams[i][j].overs+=teams[i][j].overs;
            total_teams[i][j].runs_given+=teams[i][j].runs_given,total_teams[i][j].extras+=teams[i][j].extras;
            total_teams[i][j].wickets+=teams[i][j].wickets;
            
            teams[i][j].total_runs=0,teams[i][j].fours=0;
            teams[i][j].sixes=0,teams[i][j].overs=0;
            teams[i][j].runs_given=0,teams[i][j].extras=0;
            teams[i][j].wickets=0;
        }
        printf("\n");
    }
    if(innings==1 && test_match.runs[1]*2<test_match.runs[0]) follow_on = 1;
    if(!follow_on) 
    {
        if (innings==2 && test_match.runs[0]+test_match.runs[2]<test_match.runs[1])
            return !batting_team[0];
        else if (innings==3 && test_match.runs[0]+test_match.runs[2]<test_match.runs[1]+test_match.runs[3])
            return batting_team[0];
        else if(innings==3 && test_match.runs[0]+test_match.runs[2]>test_match.runs[1]+test_match.runs[3])
            return !batting_team[0];
        batting_team[0] = !batting_team[0] ;
    }
    else
    {
        printf("Follow on given\n");
        if (innings==2 && test_match.runs[1]+test_match.runs[2]<test_match.runs[0])
            return !batting_team[0];
        else if (innings==3 && test_match.runs[0]+test_match.runs[3]<test_match.runs[1]+test_match.runs[2])
            return !batting_team[0];
        else if(innings==3 && test_match.runs[0]+test_match.runs[3]>test_match.runs[1]+test_match.runs[2])
            return batting_team[0];
    }
    
    if(batting_team[0]) printf("Team Royals is batting now!\n");
    else printf("Team Titans is batting now!\n");
    
    return -1;
}

//function that chooses the man of the match
void man_of_match()
{
    int maxruns=0, maxwickets=0;
    char runname[25], wicketname[25];
    
    for(int i=0; i<=1;i++)
    {
        for(int j=0;j<11;j++)
        {
            if(total_teams[i][j].total_runs>maxruns)
            {
                maxruns = total_teams[i][j].total_runs;
                strcpy(runname, total_teams[i][j].name);
            }
            if(total_teams[i][j].wickets>maxwickets)
            {
                maxwickets = total_teams[i][j].wickets;
                strcpy(wicketname, total_teams[i][j].name);
            }
        }
    }
    
    if(20*maxwickets<maxruns) printf("Man of the Match is : %s with %d runs\n",runname,maxruns);
    else printf("Man of the Match is : %s with %d wickets\n",wicketname,maxwickets);
}

//absolute value function
int ABS(int x)
{
    if(x<0) return -x;
    return x;
}

//function that starts the match and uses loops to implement
//the match proceedings per ball, per over, per innings
int start_match()
{
    int overs=5, bat1=0, bat2=1, bow=rand()%5+6, batting_team=rand()%2, all_out, won, dec, follow_on=0;
    if (batting_team) printf("Team Royals is batting first!\n\n");
    else printf("Team Titans is batting first!\n\n");
    
    for(int i=0;i<4;i++)
    {
        test_match.runs[i]=0, test_match.wickets[i]=0;
        for(int j=1;j<=overs;j++)
        {
            for(int k=1;k<=6;k++)
            {
                simulate(&bat1,&bat2,&bow,batting_team,i);
                all_out = test_match.wickets[i]==10;
                if(all_out) break;
            }
            if(all_out) break;
            dec = endover(&bat1,&bat2,&bow,batting_team,i,j); //new bowler required, batsmen swap places, innings may be declared
            if(dec%10) 
            {
                if(dec/10) follow_on = dec/10;
                break; //dec is of the form (follow-on or not?)(declared or not?)
            }
        }
        if(i==2 && test_match.runs[1]*2<test_match.runs[0]) follow_on = 1;
        won = endinnings(i,&batting_team,dec/10); //displays statistics of the entire innings, bowling team and batting team swap
        if(won>-1) break;
        bat1=0, bat2=1;
    }
    if(won>-1) 
    {
        if(won==0)
            printf("Team Titans won the match");
        else
            printf("Team Royals won the match");
        int DIFF, XOR;
        XOR = ((!batting_team && won)||(batting_team && !won));
        if(follow_on)
        {
            if(XOR==0)
            {
                DIFF = ABS((test_match.wickets[0]+test_match.wickets[3]) - (test_match.wickets[1]+test_match.wickets[2]));
                printf(" by %d wickets\n",DIFF);
            }
            else
            {
                DIFF = ABS((test_match.runs[0]+test_match.runs[3]) - (test_match.runs[1]+test_match.runs[2]));
                printf(" by %d runs\n",DIFF);
            }
        }
        else
        {
            if(XOR==0)
            {
                DIFF = ABS((test_match.wickets[0]+test_match.wickets[2]) - (test_match.wickets[1]+test_match.wickets[3]));
                printf(" by %d wickets\n",DIFF);
            }
            else
            {
                DIFF = ABS((test_match.runs[0]+test_match.runs[2]) - (test_match.runs[1]+test_match.runs[3]));
                printf(" by %d runs\n",DIFF);
            }
        }
    }
    else printf("The match was a draw\n");
}

//main function that calls gen_teams, start_match, man_of_match
int main()
{
    srand(time(0));
    gen_teams();
    //printing info of teams
    printf("START\n");
    printf("\n    %-15s  %-15s\t\n\n","Titans","Royals");
    for(int i=0;i<11;i++)
    {
        printf("%-2d. %-15s  %-2d. %-15s\n",i+1,teams[0][i].name,i+1,teams[1][i].name);
    }
    printf("\n");
    
    start_match(); 
    man_of_match();
    return 0;
}
