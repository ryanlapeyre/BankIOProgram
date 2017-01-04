/**********************
 *  Ryan Lapeyre 
 *  file reading / writing
 *********************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int load_data(char* argv , char** name , int *account , float *balance , int clients);
void print_data(char** name , int *account , float *balance , int clients);
int check_account(char** name, int *account , char *name_entered , int account_entered , int clients);
int string_compare(char *name , char *name_entered);
int highest_amount(float *balance , int clients);
int lowest_amount(float *balance , int clients);
float average_amount(float *balance , int clients);
void write_data (char* argv , char** name ,int *account, float *balance, int clients, 
        int high_index, int low_index, float average);
void sort_account(char** name, int *account , float *balance, int clients );

int main (int argc , char** argv)
{
    char** name;
    float *balance;
    int *account; 
    char *name_entered;
    int account_entered;
    int high_index = 0;
    int low_index = 0;
    int choice = 0;
    float average = 0;
    float withdraw_amount = 0;
    float deposit_amount = 0;
    int index_account = 0;





    if ( argc != 4)
    {
        printf("\nInsufficient arguments!!\n");
        puts("");
    }
    else
    {

        int clients = atoi(argv[2]); 
        balance = malloc(sizeof(float)*clients);
        account = malloc(sizeof(int)*clients);
        name = malloc(sizeof(char*)*clients);
        name_entered = malloc(sizeof(char)*50);

        load_data( argv[1],  name , account , balance , clients );




        print_data(name , account , balance , clients);

        puts("");

        printf("Enter a name:");
        scanf("%s" , name_entered);
        printf("Enter an account number:");
        scanf("%d" , &account_entered);

        puts("");

        index_account = (check_account(name , account , name_entered , account_entered , clients));	

        if( check_account(name , account , name_entered , account_entered , clients) == -1)
        {   
            printf("Error! Account does not exist!!\n");

            puts("");


            high_index = highest_amount(balance , clients);
            low_index = lowest_amount(balance , clients);
            average = average_amount(balance , clients);




            printf("%s has the highest amount $%.2f in account number %d\n"  , *(name + high_index) , *(balance + high_index) , *(account + high_index)); 

            printf("%s has the lowest amount $%.2f in account number %d\n"  , *(name + low_index) , *(balance + low_index) , *(account + low_index)); 

            printf("The average balance is $%.2f\n" , average);

            sort_account(name, account ,  balance,  clients );

            high_index = highest_amount(balance , clients);
            low_index = lowest_amount(balance , clients);
            average = average_amount(balance , clients);



            print_data(name , account , balance , clients);



            write_data( argv[3] ,  name , account, balance, clients, 
                    high_index,  low_index, average);


        }
        else
        {
            printf("Do you want to\n");
            puts("1.Withdraw");
            puts("2.Deposit");
            scanf("%d" , &choice);
            if(choice == 1)
            {
                printf("\nPlease enter amount to withdraw:");
                scanf("%f" , &withdraw_amount);
                if(*(balance + index_account) < withdraw_amount)
                {
                    printf("\nInsufficient funds!!\n");

                    sort_account( name, account , balance, clients );

                    high_index = highest_amount(balance , clients);
                    low_index = lowest_amount(balance , clients);
                    average = average_amount(balance , clients);


                    write_data(argv[3] , name , account, balance,  clients, 
                            high_index, low_index, average);



                }
                else
                    *(balance + index_account) -= withdraw_amount;

            }
            if(choice == 2)
            {

                printf("\nPlease enter amount to deposit:");
                scanf("%f" , &deposit_amount);
                *(balance + index_account) += deposit_amount;

            }

            high_index = highest_amount(balance , clients);
            low_index = lowest_amount(balance , clients);
            average = average_amount(balance , clients);


            puts("");
            printf("%s has the highest amount $%.2f in account number %d\n"  , *(name + high_index) , *(balance + high_index) , *(account + high_index)); 

            printf("%s has the lowest amount $%.2f in account number %d\n"  , *(name + low_index) , *(balance + low_index) , *(account + low_index)); 
            printf("The average is $%.2f\n" , average);

            sort_account(name, account ,  balance,  clients );

            print_data(name , account , balance , clients);

            high_index = highest_amount(balance , clients);
            low_index = lowest_amount(balance , clients);
            average = average_amount(balance , clients);	

            write_data( argv[3] ,  name , account, balance, clients, 
                    high_index,  low_index, average);


            int z = 0;
            for(z = 0; z < clients; ++z)
                free(*(name + z));

            free(balance);
            free(account);
            free(name);
            free(name_entered);
        }
    }




    return 0;
}


int load_data(char* file_name, char** name , int *account , float *balance , int clients )
{
    FILE* cfPtr = fopen( file_name , "r");

    if((cfPtr) == NULL)
    {
        return 0;
    }
    int i;


    for(i = 0; i < clients; i++  )
    {

        *(name+i) = malloc(sizeof(char)*30);

        fscanf(cfPtr, "%s %d %f\n" , *(name+i) , (account + i) , (balance + i));



    }
    fclose(cfPtr);
    return 1;

}

void print_data(char** name ,  int *account , float *balance , int clients)

{
    int i;

    puts("");
    printf("%-10s%-14s%s\n" , "Name" , "Account No." , "Amount");

    for( i = 0; i < clients; i++)
    {

        printf("%-13s%-10d%7.2f\n" , *(name + i) , *(account + i) , *(balance + i)); 

    }
}

int check_account(char** name, int *account , char *name_entered , int account_entered , int clients)

{
    int i;

    for(i = 0; i < clients; i++)
    {
        if(string_compare(*(name + i) , name_entered) == 1)
            if(*(account + i) == account_entered)
                return i;


    }
    return -1;
}
int highest_amount(float *balance , int clients)

{
    int i=0;
    int highest_index=0;
    float highestAccount=*(balance +i);
    for(i = 1; i < clients; i++)
    {
        if(*(balance + i) > highestAccount)
        {
            highestAccount=*(balance+i);
            highest_index=i;
        }


    }

    return highest_index;

}
int string_compare(char *name , char *name_entered) 
{
    while (*name == *name_entered)
    {
        if (*name == '\0' || *name_entered == '\0')
            break;

        name++;
        name_entered++;
    }

    if (*name == '\0' && *name_entered == '\0')
        return 1;
    else
        return 0;
}
int lowest_amount(float *balance , int clients)
{
    int i=0;
    int highest_index=0;
    float highestAccount=*(balance +i);
    for(i = 1; i < clients; i++)
    {
        if(*(balance + i) < highestAccount)
        {
            highestAccount=*(balance+i);
            highest_index=i;
        }


    }

    return highest_index;

}
float average_amount(float *balance , int clients)
{
    float sum = 0;
    float average = 0;
    int i;
    for(i = 0; i < clients; i++)
    {
        sum += *(balance + i); 
    }
    average = sum / clients;
    return average;
}
void write_data (char* file_name , char** name ,int *account, float *balance, int clients, 
        int high_index, int low_index, float average)
{
    FILE* cfPtr = fopen( file_name , "w");

    if((cfPtr) == NULL)
    {
        printf("Error file could not be opened");
    }
    int i;


    fprintf( cfPtr , "%-10s%-14s%s\n" , "Name" , "Account No." , "Amount");


    for(i = 0; i < clients; i++  )
    {

        fprintf(cfPtr , "%-13s%-10d%7.2f\n" , *(name + i) , *(account + i) , *(balance + i)); 




    }

    fprintf(cfPtr , "%s has the highest amount $%.2f in account number %d\n"  , *(name + high_index) , *(balance + high_index) , *(account + high_index)); 

    fprintf( cfPtr, "%s has the lowest amount $%.2f in account number %d\n"  , *(name + low_index) , *(balance + low_index) , *(account + low_index)); 

    fprintf(cfPtr ,"The average is $%.2f\n" , average);




    fclose(cfPtr);

}
void sort_account(char** name, int *account , float *balance, int clients )

{
    int c;
    int d;
    int test = 0;
    char *extra;
    int spare;
    float clone;

    for ( c = 1; c < clients; c++)
    {

        for (d = 0; d < clients - 1; d++)
        {
            test = strcmp(*(name + 1 + d) , *(name + d));
            if(test < 0)
            {

                extra = *(name + d);
                *(name + d) = *(name + d + 1);
                *(name + d + 1) = extra;

                spare = *(account + d);
                *(account + d) = *(account + d + 1); 
                *(account + d + 1)= spare;

                clone = *(balance + d);
                *(balance + d)= *(balance + d + 1);
                *(balance + d + 1)= clone;



            }
        }


    }

}
