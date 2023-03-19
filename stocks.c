#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct stock
{
    char name[100];
    float price;
    int num_of_stocks;
} stock;

void display_stock(stock my_stock)
{
    printf("%s $%.2f\n", my_stock.name, my_stock.price);
}

void read_input(stock *my_stock, char *file_name)
{
    FILE *output = fopen(file_name, "r");
    fscanf(output, "%s %f\n", my_stock->name, &my_stock->price);
    my_stock->num_of_stocks = 0;
    fclose(output);
}

void display_inventory(stock inv_stock)
{
    float total_value = 0;
    total_value = inv_stock.price * inv_stock.num_of_stocks;
    printf("You own %d of %s at $%.2f worth $%.2f\n", inv_stock.num_of_stocks, inv_stock.name, inv_stock.price, total_value);
}

void buy_stock(stock *my_stock, float *cash)
{
    float total_value = 0;
    int point = 0;
    int amount_stocks = 0;
    display_stock(*my_stock);
    printf("You have $%.2f\n", *cash);
    do
    {
        printf("How many stocks would you like to buy? ");
        scanf("%d", &amount_stocks);
        if((amount_stocks > 0) && (my_stock->price * amount_stocks < *cash))
        {
            point = 1;
        }
            else
            {
                printf("Invalid Input!\n");
                point = 0;
            }     
    }while(point != 1);
    total_value = my_stock->price * amount_stocks;
    my_stock->num_of_stocks += amount_stocks;
    *cash -= total_value;
    printf("You bought %d of %s at %.2f for %.2f\n", my_stock->num_of_stocks, my_stock->name, my_stock->price, total_value);
    printf("You have $%.2f remaining\n", *cash);
    }
void sell_stock(stock *my_stock, float *cash)
{
    float total_value = 0;
    int amount_stocks = 0;
    int point = 0;
    display_inventory(*my_stock);
    printf("You have $%.2f available\n", *cash);
    do{
        printf("How many stocks would you like to sell? ");
        scanf("%d", &amount_stocks);
        if((amount_stocks >= 0) && (my_stock->num_of_stocks >= amount_stocks))
        {
            point = 1;
        }
        else
        {
            printf("Invalid Input\n");
            point = 0;
        }
    }while(point != 1);
    total_value = my_stock->price * amount_stocks;
    my_stock->num_of_stocks -= amount_stocks;
    *cash += total_value;
    printf("You sold %d of %s at $%.2f for $%.2f\n", amount_stocks, my_stock->name, my_stock->price, total_value);
    printf("You have $%.2f left\n", *cash);
}

void end_turn(stock *my_stock, int *turn_count)
{
    printf("Turn #%d is ending.\nStock prices are about to change!\n", *turn_count);
    int rand_num = (rand() % (125 - 75 + 1)) + 75;
    float change_price_stock = (float)rand_num/(float)100;
    my_stock->price = my_stock->price * change_price_stock;
    *turn_count += 1;
}

int main()
{
    srand(time(NULL));
    float cash = 100.00;
    int counter = 1;
    stock apple_stock;
    read_input(&apple_stock, "input.txt");
    while(counter != 11)
    {
        display_stock(apple_stock);
        display_inventory(apple_stock);
        char command[100];
        printf("Money Available = $%.2f\n", cash);
        printf("Please enter a command (BUY, SELL, END): ");
        scanf("%s", command);
        if(strcmp(command,"BUY") == 0)
        {
            buy_stock(&apple_stock, &cash);
        }
        else if(strcmp(command, "SELL") == 0)
        {
            sell_stock(&apple_stock, &cash);
        }
        else if(strcmp(command, "END") == 0)
        {
            end_turn(&apple_stock, &counter);
        }
        else{
            printf("Invalid Command!\n");
        }
    }
    float final_amount_stock = apple_stock.price * apple_stock.num_of_stocks;
    float final_score = cash + final_amount_stock;
    printf("GAME OVER\n");
    printf("You have $%.2f in cash\nYou have $%.2f in stock value\nFor a total valuation of $%.2f\n", cash, final_amount_stock, final_score);
}