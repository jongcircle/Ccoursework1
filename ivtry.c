#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void update(int numofgoods);
void printMenu();
void searchItem();
void loadFile();
int search(char* inputname, int numofgoods);
void buy();
void putGoods();
void deleteGoods();
void printReport(int numofgoods);
void viewGoods();
void putNew();

struct Goods{
    char name[30];
    int price;
    int stock; 
    char itemcode[30];
};

struct Goods g[30];
int numofgoods = 0;

int main(){
    loadFile(); 
    while(1){
        printf("========================\n");
        viewGoods();
        printMenu();
        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            searchItem();
            break;
        case 2:
            buy();
            break;
        case 3:
            putNew();
            break;
        case 4:
            putGoods();
            break;
        case 5:
            deleteGoods();
            break;
        case 6:
            printReport(numofgoods);
            break;
        case 7:
            update(numofgoods);
            break;
        case 8:
            return 0;
        default:
            printf("\nYou entered the wrong number.\nPlease press again\n\n");
        }
    }
    return 0;
}

void viewGoods(){
    printf("Purchaseable products : ");
    for (int i = 0; i < numofgoods; i++)
    {
        if (g[i].stock == 0) continue;
        printf("%s\t", g[i].name);
    }
    printf("\n");
}

void update(int numofgoods){
    FILE *fp;
    fp = fopen("stock.bin", "w");
    fwrite(g, sizeof(struct Goods), numofgoods, fp);     // put struct array in file
    fclose(fp);
    printf("\nUpdate Finished\n");
}

void printMenu(){
    printf("1. Search for goods\n");
    printf("2. Buy\n");
    printf("3. Put the new goods\n");
    printf("4. Replenish stock\n");
    printf("5. Delete the items\n");
    printf("6. Print\n");
    printf("7. Update stock file\n");
    printf("8. Quit\n");
    printf("press the Number : ");
}

void searchItem(){
    printf("Please enter the name of goods : ");
    char *nameofgoods = malloc(sizeof(char) * 30);
    scanf("%s", nameofgoods);
    int index = search(nameofgoods, numofgoods);
    if (g[index].stock == 0)
    {
        printf("Does not exist\n\n");
    } else if (index >= 0) {
        printf("\n\nName : %s\nPrice : £%d\nStock : %d\nItem Code : %s\n\n", g[index].name, g[index].price, g[index].stock, g[index].itemcode);
    } else printf("Does not exist\n\n");
    free(nameofgoods);
}

void buy(){
    printf("Please enter the name of goods what you want to buy : ");
    char *nameofgoods = malloc(sizeof(char) * 30);
    scanf("%s", nameofgoods);
    int index = search(nameofgoods, numofgoods);
    if (g[index].stock == 0){
        printf("\n---Sold Out----\n");
    } else {
        printf("Price : £%d", g[index].price);
        g[index].stock--;
        printf("\n\nPayment Complete\n\n");
    }
    free(nameofgoods);
}

void putNew(){
    printf("What kind of goods do you want to put in the inventory? : ");
    char *nameofgoods = malloc(sizeof(char) * 30);
    scanf("%s", nameofgoods);
    printf("How much is this per one? : ");
    int price;
    scanf("%d", &price);
    printf("How much stock will you fill? : ");
    int stock;
    scanf("%d", &stock);
    printf("What is the item of code of this goods? :");
    char *itemcode = malloc(sizeof(char) * 30);
    scanf("%s", itemcode);    
    strcpy(g[numofgoods].name, nameofgoods);
    g[numofgoods].price = price;
    g[numofgoods].stock = stock;
    strcpy(g[numofgoods].itemcode, itemcode);
    printf("\nPut a new %s in the inventory.\n\n", nameofgoods);
    free(nameofgoods);
    free(itemcode);
    numofgoods++;
}

void loadFile(){
    FILE *fp = fopen("stock.bin", "rb");   // load the file
    fread(&g, sizeof(g), 1, fp);         // save the data to the g
    for (int i = 0; i < 30; i++)
    {
        if (g[i].price == 0) break;
        numofgoods++;                       // find the number of goods
    }
    fclose(fp);
}

int search(char* inputname, int numofgoods){ 
    for (int i = 0; i < numofgoods; i++)
    {
        if (!strcmp(g[i].name, inputname))
        {
            return i;
        }
    }
    return -1;
}

void putGoods(){
    printf("Please enter a item name to fill in the inventory. : ");
    char *nameofgoods = malloc(sizeof(char) * 30);
    scanf("%s", nameofgoods);
    printf("How much stock will you fill? : ");
    int inputNum;
    scanf("%d", &inputNum);
    int index = search(nameofgoods, numofgoods);
    g[index].stock += inputNum;
    printf("Now stock of %s : %d\n\n", g[index].name, g[index].stock);
    free(nameofgoods);
}

void deleteGoods(){
    printf("Please enter a item name to delete. : ");
    char *nameofgoods = malloc(sizeof(char) * 30);
    scanf("%s", nameofgoods);
    int index = search(nameofgoods, numofgoods);
    if (g[index].stock == 0){
        printf("There are no %s already.\n", g[index].name);
    } else {
        g[index].price = 0;
        g[index].stock = 0;
        printf("Delete all %s\n\n", g[index].name);
    }
    free(nameofgoods);
}

void printReport(int numofgoods){
    printf("\n\n-----Inventory Report-----\n");
    for (int i = 0; i < numofgoods; i++)
    {
        if (g[i].price == 0) continue;  // Check if the item has been deleted or not
        printf("Name : %s\nPrice : £%d\nStock : %d\nItem Code : %s", g[i].name, g[i].price, g[i].stock, g[i].itemcode);
        printf("\n----------------------------------\n");
    }
    printf("\n\n");
}