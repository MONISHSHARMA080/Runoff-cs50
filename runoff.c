#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

typedef struct
{
 int no;
 string name;
 int vote;
 bool eliminated;
}
candidate;
int preferences[100][9];
candidate candidates[9];
int nv;
int nc;
bool vote(int voter, int rank , string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main (int argc , string argv[])
{
if(argc == 1)
{
printf("USAGE: ./runoff and 'name of candidates'\n");
return 1;
}
 nc = argc - 1;
{
    if(nc != argc -1)
  {
    printf("NO OF CANDIDATES AND THEIR NAME ENTERED DON'T MATCH\n ");
    return 2;
  }
}
int k =0;
string t[nc*nv];
 nv = get_int("NO OF VOTERS: ");
 for(int i = 0 ; i < nv ; i++ )
  {
    for(int j = 0 ; j < nc; j++)
    {
      t[k] = get_string("%i-candidates' preference %i: " ,i + 1, j+1);
// convert string t into int by strcmp(argv[i] where i = 1), problem- manage t
       if(!vote(i,j,t[k]))
        {
         printf("INVALID VOTE\n");
         return 3;
        }
        for(int c=1 ;c<argc;c++)
        {
         if(strcmp(t[k],argv[c]) ==0)
          {
            preferences[i][j] = c;
          }
        }
         k+=1;
  }
  }

for(int i = 0 ; i < argc -1 ; i ++)
{
  // could use get int and assign no. (0,1,2,..nc for candidates by function )- check need for it
  int j=0;
   candidates[i].no = i;
  candidates[i].name = argv[i+1];
  candidates[i].eliminated = false;
}
}

bool vote(int voter, int rank , string name)
{
  for( int i=0; i< nc; i++)
  {
    if (strcmp( name , candidates[i].name)==0 && candidates[i].eliminated==false)
  {
     preferences[voter][rank]=i;
     return true;
  }
  }
return false;
}

void tabulate(void)
{
for(int i =0 ; i < nv ; i++)
{
for (int j=0; j< nc ; j++)
{
  if(candidates[preferences[i][j]].eliminated == false)
{
  candidates[preferences[i][j]].vote+=1;
}
 if(candidates[preferences[i][j]].eliminated == true)
{
   j+=1;
candidates[preferences[i][j]].vote+=1;
}
}
}
}

bool print_winner(void)
{
int majority = round((nv / 2));
for (int i=0; i<nc; i++)
 {
  if(candidates[i].vote > majority)
  {
   printf("WINNER IS %s", candidates[i].name);
   return true;
  }
 }
return false;
}
// can also use sorting linear or buble to push largest to edge and pick if 2 then eliminate min

int find_min(void)
{
  //mv is minimum votes
int mv=nv;
for(int i=0;i <nc; i++)
{
if(candidates[i].vote<mv &&candidates[i].eliminated== false)
{
  mv=candidates[i].vote;
}
}
return mv;
}

bool is_tie(int min)
{
  int m=0;
  int maxv = min;
  for(int i=0; i<nc;i++)
  {
     if(candidates[i].vote >min && candidates[i].vote> maxv)
      {
        maxv= candidates[i].vote;
      }
  }
 for(int i=0; i<nc; i++)
{
if(candidates[i].vote == maxv)
{
  for(int j= i+1;j<nc;j++)
  {
    if(candidates[j].vote == maxv)
    {
      m+=1;
    }
  }
}
}
if(m > 0)
{
  return true;
}
 return false;
}

void eliminate(int min)
{
  for(int i=0;i<nc;i++)
  {
    if(candidates[i].vote==min && candidates[i].eliminated== false)
  {
   candidates[i].eliminated = true;
  }
  }
}