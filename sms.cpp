#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <alloc.h>
#include <process.h>

#define Up_arrow     72
#define Down_arrow   80
#define Left_arrow   75
#define Right_arrow  77
#define Page_up      73
#define Pg_down      81
#define Delete	      83
#define End          79
#define Home         71
#define ins	         82
#define Enter        13
#define Esc          27

#define TRUE     1
#define FALSE    0
enum state   {send = '0', received = '1'};
enum search  {found , notfound};
enum execute {succeed, unsucceed};

struct _payamak
{
   _payamak *back;
   char owner[15];
   char text[64];
   state status;
   _payamak *branch;
   _payamak *next;

} *start = NULL,
  *curr_node = NULL,
   *new_node = NULL,
   *temp = NULL,
   payamak,
   *first_page,
   *end_page,
   *current;

enum exeute insert_node();
enum execute delete_node();
enum search search_node();
void goto_home_of_list();
void goto_end_of_list();
void goto_nextpayamak();
void goto_backpayamak();
void goto_nextpage_of_list();
void goto_backpage_of_list();
void rewrite_file();
void get_newpayamak();
void delete_payamak();
void display_branch();
void display_menu();
void organize_payamak_list();
void free_list();

void main()
{
   int repeat = TRUE;
   char input;

    clrscr();
    display_menu();
    input = getch();
    input = getch();
    exit(1);
    organize_payamak_list();
    do
    {
       input=getch();
       if (input == 0)
          {
             input=getch();
             switch(input)
             {
                case Up_arrow :
                        goto_backpayamak();
                        break;
                case Down_arrow:
                        goto_nextpayamak();
                        break;
                case Left_arrow :
                case Right_arrow:
                case Page_up:
                        goto_nextpage_of_list();
                        break;
                case Pg_down:
                        goto_backpage_of_list();
                        break;
                case Delete:
                        delete_payamak();
                        organize_payamak_list();
                        break;
                case End:
                        goto_end_of_list();
                        break;
                case Home:
                        goto_home_of_list();
                        break;
                case ins:
                    get_newpayamak();
                    organize_payamak_list();
                    break;
                default:
                   break;
             }
          }
       else
          {
             switch(input)
             {
                case Enter:
                    display_branch();
                    break;
                case Esc:
                    repeat= FALSE;
                    break;
             }
          }
    }while(repeat);
    free_list();
}

enum exeute insert_node()
{
   return(succeed);
}

enum execute delete_node()
{
   return(succeed);
}

enum search search_node()
{
   return(succeed);
}

void goto_home_of_list()
{
}

void goto_end_of_list()
{
}

void goto_nextpayamak()
{
}

void goto_backpayamak()
{
}

void goto_nextpage_of_list()
{
}

void goto_backpage_of_list()
{
}

void rewrite_file()
{
}

void get_newpayamak()
{
    rewrite_file();
}

void delete_payamak()
{
    rewrite_file();
}

void display_branch()
{
}

void display_menu()
{
 clrscr();
   textcolor(LIGHTGREEN);
   gotoxy(2,23); cprintf("PgDn:");
   gotoxy(2,24); cprintf("PgUp:");
   gotoxy(25,23); cprintf("Ins:");
   gotoxy(25,24); cprintf("Del:");
   gotoxy(45,23); cprintf("Home:");
   gotoxy(45,24); cprintf("End:");
   gotoxy(60,23); cprintf("Enter:");
   textcolor(YELLOW);
   gotoxy(7,23); cprintf("Next-Page");
   gotoxy(7,24); cprintf("Previuse-Page");
   gotoxy(29,23); cprintf("New-Sms");
   gotoxy(29,24); cprintf("Delete-Sms");
   gotoxy(66,23); cprintf("Detail");
   window(5,2,24,22); textbackground(WHITE);clrscr();
   window(6,3,23,21); textbackground(BLUE); clrscr();
   getch();
}

void organize_payamak_list()
{
   FILE *file_payamak;
   int i;
   char s[80];
   file_payamak = fopen("payamak.txt","r");
   if ( file_payamak == NULL )
      {
         puts ( "Cannot open payamak file" ) ;
         exit(1);  /*  End Of Program  */
      }
   else
      {
         while(1)
           {
              fgets(s, 80,file_payamak);
              if( feof(file_payamak) )
                 break ;
              else
                 {
                    strncpy(payamak.owner, s,15);
                    i=15;while(i<=78) { payamak.text[i-15]=s[i]; i++;}
                    payamak.status=s[80];
                    printf("%s%s%c",payamak.owner, payamak.text,payamak.status);
                    new_node = (_payamak *)malloc(sizeof(payamak));
                    if ( new_node == NULL)
                       {
                         printf(" Not enough memory \n");
                         printf("press any key to stop program");
                         getch();
                         exit(1);
                       }
                    else
                       {
                           strncpy(new_node -> owner, payamak.owner,15);
                           strncpy(new_node -> text, payamak.text,15);
                           new_node -> status = payamak.status;
                       }
                 }
           }
         fclose(file_payamak);
      }
}

void write_to_file()
{
   if (start != NULL)
   {
      FILE *file_payamak;
      file_payamak = fopen("payamak.txt","w");
      if ( file_payamak == NULL )
         {
            puts ( "Cannot open payamak file" ) ;
         }
      else
         {
            curr_node = start;
            while(curr_node != NULL)
               {
                   fputs(payamak.owner,file_payamak);
                   fputs(payamak.text, file_payamak);
                   fputc(payamak.status, file_payamak);
                   if ( curr_node-> branch!= NULL)
                      {
                         temp=curr_node;
                         curr_node = curr_node -> branch;
                         while(curr_node != NULL)
                            {
                               fputs(payamak.owner,file_payamak);
                               fputs(payamak.text, file_payamak);
                               fputc(payamak.status, file_payamak);
                               curr_node = curr_node -> branch;
                            }
                         curr_node = temp;
                      }
                   else
                      curr_node=curr_node -> next;
               }
            fclose(file_payamak);
         }
   }
}

void free_list()
{
   if (start != NULL)
   {
      curr_node = start;
      while(curr_node != NULL)
         {
             if ( curr_node-> branch!= NULL)
                {
                   while(curr_node-> branch != NULL)
                      {
                         temp=curr_node->branch;
                         free(curr_node);
                         curr_node = temp;
                      }
                }
             else
                {
                    temp=curr_node->next;
                    free(curr_node);
                    curr_node= temp;
                }
         }
   }
}
