#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string.h>
 using namespace std;

typedef struct date
    {
     char dtr[20];
     struct date *next;
    }dt;

void dateentry(dt **, dt **, const char *);
void datecount(dt *);

int flag=0, ca=0, cn=0, ct=0, cd=0, n=0, cp=1, ly=0, d=0, m=0;
void acount(const char*);
int checkday(const char*);
int checkmonth(const char*);
int checkyear(const char*);
int leap(int);
dt *r=NULL;
dt *f=NULL;

int main()
{
   int i=0, j=0, tmp=1;
   fstream fp;
   char p[50], str[20], ltr[20], ch;
   P:
     cout<<"\nEnter the number of paragraphs (not more than total number of paragraphs in file): ";
     cin>>n;
     cin.ignore();
     if(flag==0)
      {
       cout<<"\nEnter path of file: ";
   F:
       gets(p);
      }
     fp.open(p,ios::in);
     if(fp.fail())
      {
       cout<<"\nFile not found.";
       cout<<"\n\nERROR:Wrong path entered.\n\nHELP:\nSyntax- DRIVE:\\Directory\\Filename.extention";
       cout<<"\nPlease enter correct path: ";
       goto F;
      }
   else
      {
       while(!fp.eof())
           {
            fp.read((char*)&ch,sizeof(ch));
            if(ch=='\n')
              {
               tmp++;
              }
           }
       fp.close();
       if(n>tmp)
        {
         cout<<"\nError: The number of paragraph entered is less than the total number of paragraphs in file.\n";
         flag=1;
         goto P;
        }
       //cout<<"\nTOTAL number of paragraphs in file= "<<tmp<<endl;
       cout<<"\n\nOutput format: Number of 'a',Number of 'an',Number of 'the',Number of dates\n\n";
       fp.open(p,ios::in);
       while(!fp.eof())
           {
            fp.read((char*)&ch,sizeof(ch));
            ch=tolower(ch);
            if(ch=='\n')
             {
              datecount(f);
              cout<<endl<<ca<<",";
              cout<<cn<<",";
              cout<<ct<<",";
              cout<<cd;
              ca=0;
              cn=0;
              ct=0;
              cd=0;
              r=NULL;
              f=NULL;
              cp++;
              if(cp>n)
               {
                cout<<"\n\n\nEnd of Program";
                exit(0);
               }
             }
            if(ch!=' ' && ch!='.' && ch!=',' && ch!=';' && ch!=':' && ch!='?' && ch!='"' && ch!='/' && ch!='\\' && ch!='-' && ch!='\n' && ch!='(' && ch!=')' && ch!='\n')
             {
              str[i]=ch;
              i++;
             }
            else
             {
              str[i]='\0';
              acount(str);
              i=0;
             }
            if(ch!=' ' && ch!='.' && ch!=',' && ch!=';' && ch!=':' && ch!='?' && ch!='"' && ch!='/' && ch!='\\' && ch!='-' && ch!='\n' && ch!='(' && ch!=')' && ch!='\n' && ch!='t' && ch!='h')
             {
              ltr[j]=ch;
              j++;
             }
            else
             {
              if(j!=0)
               {
                ltr[j]='\0';
                if(strcmp(ltr,"ember")==0 || strcmp(ltr,"ober")==0)
                 {
                 }
                else
                 {
                  dateentry(&f,&r,ltr);
                 }
                j=0;
               }
             }
           }
       fp.close();
       if(cp==tmp && cp<=n)
        {
         datecount(f);
         cout<<endl<<ca<<",";
         cout<<cn<<",";
         cout<<ct<<",";
         cout<<cd;
         ca=0;
         cn=0;
         ct=0;
         cd=0;
         r=NULL;
         f=NULL;
         if(cp>n)
          {
           cout<<"\n\n\nEnd of Program\n\n";
           exit(0);
          }
        }
      }
   return 0;
}

void acount(const char* str)                                  //COUNTING OF 'a', 'an', 'the'.
{
 if(strcmp(str,"a")==0)
   {
    ca++;
   }
 else if(strcmp(str,"an")==0)
   {
    cn++;
   }
 else if(strcmp(str,"the")==0)
   {
    ct++;
   }
}

void dateentry(dt **f, dt **r, const char* ltr)
{
 dt *q=NULL;
 q=(dt*)malloc(sizeof(dt));
 strcpy(q->dtr,ltr);
 q->next=NULL;
 if((*r)==NULL)
  {
   *r=q;
   *f=q;
  }
 else
  {
   (*r)->next=q;
   (*r)=q;
   (*r)->next=NULL;
  }
}

int leap(int y)
{
 if(y%400==0)
  {
   return 1;
  }
 else if(y%100==0)
  {
   return 0;
  }
 else if(y%4==0)
  {
   return 1;
  }
 else
  {
   return 0;
  }
}

int checkday(const char* s)
{
 int i, a;
 a=atoi(s);
 for(i=1;i<=31;i++)
  {
   if(a==i)
    {
     d=i;
     return 1;
    }
  }
}

int checkmonth(const char* s)
{
 int i, a;
 a=atoi(s);
 for(i=1;i<=12;i++)
  {
   if(a==i)
    {
     m=i;
     return 1;
    }
  }
}

int checkyear(const char* s)
{
 int i, a;
 a=atoi(s);
 for(i=1;i<=9999;i++)
  {
   if(a==i)
    {
     ly=i;
     return 1;
    }
  }
}

void datecount(dt *f)                                     //COUNTING OF VALID DATES.
{
 if(f!=NULL)
  {
   while(f!=NULL)
       {
        if(f->next!=NULL && (f->next)->next!=NULL && ((f->next)->next)->next!=NULL)
         {
          if(checkday(f->dtr)==1)
           {
            if(strcmp(((f->next)->next)->dtr,"")!=0 && ((strcmp((f->next)->dtr,"january")==0) || (strcmp((f->next)->dtr,"february")==0) || (strcmp((f->next)->dtr,"marc")==0) || (strcmp((f->next)->dtr,"april")==0) || (strcmp((f->next)->dtr,"may")==0) || (strcmp((f->next)->dtr,"june")==0) || (strcmp((f->next)->dtr,"july")==0) || (strcmp((f->next)->dtr,"augus")==0) || (strcmp((f->next)->dtr,"sep")==0) || (strcmp((f->next)->dtr,"oc")==0) || (strcmp((f->next)->dtr,"november")==0) || (strcmp((f->next)->dtr,"december")==0) || (strcmp((f->next)->dtr,"jan")==0) || (strcmp((f->next)->dtr,"feb")==0) || (strcmp((f->next)->dtr,"mar")==0) || (strcmp((f->next)->dtr,"apr")==0) || (strcmp((f->next)->dtr,"jun")==0) || (strcmp((f->next)->dtr,"jul")==0) || (strcmp((f->next)->dtr,"aug")==0) || (strcmp((f->next)->dtr,"nov")==0) || (strcmp((f->next)->dtr,"dec")==0)))
             {
              if(checkyear(((f->next)->next)->dtr)==1)
               {
                if(leap(ly)==1)
                 {
                  if((strcmp((f->next)->dtr,"february")==0) || (strcmp((f->next)->dtr,"feb")==0))
                   {
                    if(d>=1 && d<=29)
                     {
                      cd++;
                     }
                   }
                  else
                   {
                    cd++;
                   }
                 }
                else
                 {
                  if((strcmp((f->next)->dtr,"february")==0) || (strcmp((f->next)->dtr,"feb")==0))
                   {
                    if(d>=1 && d<=28)
                     {
                      cd++;
                     }
                   }
                  else
                   {
                    cd++;
                   }
                 }
               }
             }
            if(checkyear((f->next)->dtr)==1)
             {
              if(strcmp(((f->next)->next)->dtr,"")!=0 && (strcmp(((f->next)->next)->dtr,"january")==0 || strcmp(((f->next)->next)->dtr,"february")==0 || strcmp(((f->next)->next)->dtr,"marc")==0 || strcmp(((f->next)->next)->dtr,"april")==0 || strcmp(((f->next)->next)->dtr,"may")==0 || strcmp(((f->next)->next)->dtr,"june")==0 || strcmp(((f->next)->next)->dtr,"july")==0 || strcmp(((f->next)->next)->dtr,"augus")==0 || strcmp(((f->next)->next)->dtr,"sep")==0 || strcmp(((f->next)->next)->dtr,"oc")==0 || strcmp(((f->next)->next)->dtr,"november")==0 || strcmp(((f->next)->next)->dtr,"december")==0) || (strcmp(((f->next)->next)->dtr,"jan")==0 || strcmp(((f->next)->next)->dtr,"feb")==0 || strcmp(((f->next)->next)->dtr,"mar")==0 || strcmp(((f->next)->next)->dtr,"apr")==0 || strcmp(((f->next)->next)->dtr,"jun")==0 || strcmp(((f->next)->next)->dtr,"jul")==0 || strcmp(((f->next)->next)->dtr,"aug")==0 || strcmp(((f->next)->next)->dtr,"nov")==0 || strcmp(((f->next)->next)->dtr,"dec")==0))
               {
                if(leap(ly)==1)
                 {
                  if((strcmp(((f->next)->next)->dtr,"february")==0) || (strcmp(((f->next)->next)->dtr,"feb")==0))
                   {
                    if(d>=1 && d<=29)
                     {
                      cd++;
                     }
                   }
                  else
                   {
                    cd++;
                   }
                 }
                else
                 {
                  if((strcmp(((f->next)->next)->dtr,"february")==0) || (strcmp(((f->next)->next)->dtr,"feb")==0))
                   {
                    if(d>=1 && d<=28)
                     {
                      cd++;
                     }
                   }
                  else
                   {
                    cd++;
                   }
                 }
             }
           }
         }
        if(checkday(f->dtr)==1)
         {
          if(strcmp(f->dtr,"")!=0 && strcmp((f->next)->dtr,"of")==0)
           {
            if((strcmp(((f->next)->next)->dtr,"january")==0) || (strcmp(((f->next)->next)->dtr,"february")==0) || (strcmp(((f->next)->next)->dtr,"marc")==0) || (strcmp(((f->next)->next)->dtr,"april")==0) || (strcmp(((f->next)->next)->dtr,"may")==0) || (strcmp(((f->next)->next)->dtr,"june")==0) || (strcmp(((f->next)->next)->dtr,"july")==0) || (strcmp(((f->next)->next)->dtr,"augus")==0) || (strcmp(((f->next)->next)->dtr,"sep")==0) || (strcmp(((f->next)->next)->dtr,"oc")==0) || (strcmp(((f->next)->next)->dtr,"november")==0) || (strcmp(((f->next)->next)->dtr,"december")==0) || (strcmp(((f->next)->next)->dtr,"jan")==0) || (strcmp(((f->next)->next)->dtr,"feb")==0) || (strcmp(((f->next)->next)->dtr,"mar")==0) || (strcmp(((f->next)->next)->dtr,"apr")==0) || (strcmp(((f->next)->next)->dtr,"jun")==0) || (strcmp(((f->next)->next)->dtr,"jul")==0) || (strcmp(((f->next)->next)->dtr,"aug")==0) || (strcmp(((f->next)->next)->dtr,"nov")==0) || (strcmp(((f->next)->next)->dtr,"dec")==0))
             {
              if(checkyear((((f->next)->next)->next)->dtr)==1)
               {
                if(leap(ly)==1)
                 {
                  if((strcmp(((f->next)->next)->dtr,"february")==0) || (strcmp(((f->next)->next)->dtr,"feb")==0))
                   {
                    if(d>=1 && d<=29)
                     {
                      cd++;
                     }
                   }
                  else
                   {
                    cd++;
                   }
                 }
                else
                 {
                  if((strcmp(((f->next)->next)->dtr,"february")==0) || (strcmp(((f->next)->next)->dtr,"feb")==0))
                   {
                    if(d>=1 && d<=28)
                     {
                      cd++;
                     }
                   }
                  else
                   {
                    cd++;
                   }
                 }
               }
             }
           }
         }
        if(strcmp(f->dtr,"")!=0 && (strcmp(f->dtr,"january")==0 || strcmp(f->dtr,"february")==0 ||  strcmp(f->dtr,"marc")==0 ||strcmp(f->dtr,"april")==0 || strcmp(f->dtr,"may")==0 || strcmp(f->dtr,"june")==0 || strcmp(f->dtr,"july")==0 || strcmp(f->dtr,"augus")==0 || strcmp(f->dtr,"sep")==0 || strcmp(f->dtr,"oc")==0 || strcmp(f->dtr,"november")==0 || strcmp(f->dtr,"december")==0) || (strcmp(f->dtr,"jan")==0 || strcmp(f->dtr,"feb")==0 ||  strcmp(f->dtr,"mar")==0 ||strcmp(f->dtr,"apr")==0 || strcmp(f->dtr,"jun")==0 || strcmp(f->dtr,"jul")==0 || strcmp(f->dtr,"aug")==0 || strcmp(f->dtr,"nov")==0 || strcmp(f->dtr,"dec")==0))
         {
          if(checkday((f->next)->dtr)==1)
           {
            if(checkyear(((f->next)->next)->dtr)==1)
             {
              if(leap(ly)==1)
               {
                if((strcmp(f->dtr,"february")==0) || (strcmp(f->dtr,"feb")==0))
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if((strcmp(f->dtr,"february")==0) || (strcmp(f->dtr,"feb")==0))
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
          if(checkyear((f->next)->dtr)==1)
           {
            if(checkday(((f->next)->next)->dtr)==1)
             {
              if(leap(ly)==1)
               {
                if((strcmp(f->dtr,"february")==0) || (strcmp(f->dtr,"feb")==0))
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if((strcmp(f->dtr,"february")==0) || (strcmp(f->dtr,"feb")==0))
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
         }
        if(checkyear(f->dtr)==1)
         {
          if(strcmp((f->next)->dtr,"")!=0 && (strcmp((f->next)->dtr,"january")==0 || strcmp((f->next)->dtr,"february")==0 || strcmp((f->next)->dtr,"marc")==0 || strcmp((f->next)->dtr,"april")==0 || strcmp((f->next)->dtr,"may")==0 || strcmp((f->next)->dtr,"june")==0 || strcmp((f->next)->dtr,"july")==0 || strcmp((f->next)->dtr,"augus")==0 || strcmp((f->next)->dtr,"sep")==0 || strcmp((f->next)->dtr,"oc")==0 || strcmp((f->next)->dtr,"november")==0 || strcmp((f->next)->dtr,"december")==0) || (strcmp((f->next)->dtr,"jan")==0 || strcmp((f->next)->dtr,"feb")==0 || strcmp((f->next)->dtr,"mar")==0 || strcmp((f->next)->dtr,"apr")==0 || strcmp((f->next)->dtr,"jun")==0 || strcmp((f->next)->dtr,"jul")==0 || strcmp((f->next)->dtr,"aug")==0 || strcmp((f->next)->dtr,"nov")==0 || strcmp((f->next)->dtr,"dec")==0 ))
           {
            if(checkday(((f->next)->next)->dtr)==1)
            {
             if(leap(ly)==1)
              {
               if((strcmp((f->next)->dtr,"february")==0) || (strcmp((f->next)->dtr,"feb")==0))
                {
                 if(d>=1 && d<=29)
                  {
                   cd++;
                  }
                }
               else
                {
                 cd++;
                }
              }
             else
              {
               if((strcmp((f->next)->dtr,"february")==0) || (strcmp((f->next)->dtr,"feb")==0))
                {
                 if(d>=1 && d<=28)
                  {
                   cd++;
                  }
                }
               else
                {
                 cd++;
                }
              }
            }
           }
          if(checkday((f->next)->dtr)==1)
           {
           if(strcmp(((f->next)->next)->dtr,"")!=0 && (strcmp(((f->next)->next)->dtr,"january")==0 || strcmp(((f->next)->next)->dtr,"february")==0 || strcmp(((f->next)->next)->dtr,"marc")==0 || strcmp(((f->next)->next)->dtr,"april")==0 || strcmp(((f->next)->next)->dtr,"may")==0 || strcmp(((f->next)->next)->dtr,"june")==0 || strcmp(((f->next)->next)->dtr,"july")==0 || strcmp(((f->next)->next)->dtr,"augus")==0 || strcmp(((f->next)->next)->dtr,"sep")==0 || strcmp(((f->next)->next)->dtr,"oc")==0 || strcmp(((f->next)->next)->dtr,"november")==0 || strcmp(((f->next)->next)->dtr,"december")==0) || (strcmp(((f->next)->next)->dtr,"jan")==0 || strcmp(((f->next)->next)->dtr,"feb")==0 || strcmp(((f->next)->next)->dtr,"mar")==0 || strcmp(((f->next)->next)->dtr,"apr")==0 || strcmp(((f->next)->next)->dtr,"jun")==0 || strcmp(((f->next)->next)->dtr,"jul")==0 || strcmp(((f->next)->next)->dtr,"aug")==0 || strcmp(((f->next)->next)->dtr,"nov")==0 || strcmp(((f->next)->next)->dtr,"dec")==0))
            {
             if(leap(ly)==1)
               {
                if((strcmp(((f->next)->next)->dtr,"february")==0) || (strcmp(((f->next)->next)->dtr,"feb")==0))
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if((strcmp(((f->next)->next)->dtr,"february")==0) || (strcmp(((f->next)->next)->dtr,"feb")==0))
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
         }
        if(checkday(f->dtr)==1)
         {
          if(checkmonth((f->next)->dtr)==1)
           {
            if(checkyear(((f->next)->next)->dtr)==1)
             {
              if(leap(ly)==1)
               {
                if(m==2)
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if(m==2)
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
          if(checkyear((f->next)->dtr)==1)
           {
            if(checkmonth(((f->next)->next)->dtr)==1)
             {
              if(leap(ly)==1)
               {
                if(m==2)
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if(m==2)
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
         }
        if(checkmonth(f->dtr)==1)
         {
          if(checkday((f->next)->dtr)==1)
           {
            if(checkyear(((f->next)->next)->dtr)==1)
             {
              if(leap(ly)==1)
               {
                if(m==2)
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if(m==2)
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
          if(checkyear((f->next)->dtr)==1)
           {
            if(checkday(((f->next)->next)->dtr)==1)
             {
              if(leap(ly)==1)
               {
                if(m==2)
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if(m==2)
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
         }
        if(checkyear(f->dtr)==1)
         {
          if(checkmonth((f->next)->dtr)==1)
           {
            if(checkday(((f->next)->next)->dtr)==1)
            {
             if(leap(ly)==1)
              {
               if(m==2)
                {
                 if(d>=1 && d<=29)
                  {
                   cd++;
                  }
                }
               else
                {
                 cd++;
                }
              }
             else
              {
               if(m==2)
                {
                 if(d>=1 && d<=28)
                  {
                   cd++;
                  }
                }
               else
                {
                 cd++;
                }
              }
            }
           }
          if(checkday((f->next)->dtr)==1)
           {
            if(checkmonth(((f->next)->next)->dtr)==1)
             {
              if(leap(ly)==1)
               {
                if(m==2)
                 {
                  if(d>=1 && d<=29)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
              else
               {
                if(m==2)
                 {
                  if(d>=1 && d<=28)
                   {
                    cd++;
                   }
                 }
                else
                 {
                  cd++;
                 }
               }
             }
           }
         }
        }
        f=f->next;
    }
  }
}

//END OF PROGRAM