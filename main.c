#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define WORDLENGTH 30
#define MAX 10000
 
struct stock
{
    int stockNr;
    char itemName[WORDLENGTH];
    int balance;
};
typedef struct stock StockItem;
StockItem createItem(int stockNr, char itemName[], int balance, int* pNrInStock)
{
    StockItem item;
    if(*pNrInStock<MAX)
    {
        item.stockNr=stockNr;
        strcpy(item.itemName, itemName);
        item.balance=balance;
    }
    else
    {
        printf("Max value reached!\n");
        
    }

    return item; 

}
void checkStockNr(StockItem items[], int i, int pNrInStock) //kallas på ett antal gånger, rensar upp koden lite
{
            if(items[i].stockNr==0)
                printf("000");
            if(items[i].stockNr>0 && items[i].stockNr<=9)
                printf("00%d",items[i].stockNr);
            if(items[i].stockNr>=10 && items[i].stockNr<=99)
                printf("0%d",items[i].stockNr);
            if(items[i].stockNr>=100 && items[i].stockNr<=999)
                printf("%d",items[i].stockNr);
}
void printItems(StockItem items[],int pNrInStock)
{
    int i;
    
    if(pNrInStock<=0)
    {
        printf("\nItems list is empty\n");
    }
    else
    {
        printf("\nItem number\t\tName\t\tBalance\n");
        printf("--------------------------------------------------\n");
        
        for(i=0;i<pNrInStock;i++)
        {
            checkStockNr(items, i, pNrInStock);
            printf("%30s\t\t%d\n",items[i].itemName,items[i].balance);
        }
    }
}
int searchItemNumber(StockItem items[],int itemNr,int pNrInStock)
{
    int i;
    if(pNrInStock==0)
        return -1; //indikerar 'error'
    for(i=0;i<pNrInStock;i++)
    {
        if(items[i].stockNr==itemNr)
            return i;
    }
    return -1;
}
void registerItems(StockItem items[], int* pNrInStock) //R
{
    int itemNr,balance;
    char itemName[WORDLENGTH], more;

        do
        {
            if(*pNrInStock<MAX)
            {
                do
                {
            
                    printf("Enter an item number: ");
                    scanf("%d",&itemNr);
                    if(searchItemNumber(items,itemNr,*pNrInStock)!=-1)
                    {
                        printf("Item number should be unique! Please try again\n");
                    }
                }while(searchItemNumber(items,itemNr,*pNrInStock)!=-1);
        
                getchar();
        
                printf("Enter the item name: ");
                gets(itemName);
        
                printf("Enter how many items are left: ");
                scanf("%d",&balance);
       

                //if(*pNrInStock <MAX)
                //{
                    items[*pNrInStock]=createItem(itemNr,itemName,balance,pNrInStock);
                    (*pNrInStock)++;
                    printf("Do you want to register more items? (Y/N) ");
                    scanf(" %c",&more);
                //}
        }
        else
        {
            more='N';
            printf("Limit has been reached!");
        }
    }while(toupper(more)=='Y');
    
    printItems(items,*pNrInStock);
}
void openFile(StockItem items[], int* pNrInStock,char* fileName)
{
    
    FILE *fp;
   
    printf("Please enter file name: ");
    gets(fileName); 
   
    fp = fopen(fileName, "r"); 
    if (fp!=NULL)
    {
 
        char itemName[WORDLENGTH]="";
        int i=0;
        char ch;
        int stockNr, balance;
        char balanceArray[10];
        

        while(!feof(fp)) //kör koden tills den når slutet av filen (feof)
        {
            fscanf(fp,"%d",&stockNr);
            
            fscanf(fp,"%c",&ch);
            itemName[0]='\0';
            i=0;

            while(fscanf(fp,"%c",&ch) && (isalpha(ch) || isspace(ch))) //skannar karaktärer
            {
                itemName[i]=ch;
                i++;
            }
            
            i--;
            
            while(itemName[i]==' ')
            {
                itemName[i]='\0';
                i--;
            }
            
            balanceArray[0]=ch;
            i=1;
            
            while(!feof(fp) && (fscanf(fp,"%c",&ch) && ch!='\n'))
            {
                balanceArray[i]=ch;
                i++;
            }
            if(feof(fp))
            balanceArray[i-1]='\0';
            balance=atoi(balanceArray);
            items[(*pNrInStock)++]=createItem(stockNr,itemName,balance,pNrInStock);
        }
       
        fclose(fp);     
        printItems(items,*pNrInStock);
    }
    else
    {
        printf("Entered file cannot be found. Please register new items\n");
        registerItems(items,pNrInStock);
    }
}
void printMenu()
{
    printf("\n\n--------------------------------------------------------------------------------\n");
    printf("r (Register item)         //   p (Print out all items)  //   s (Search item)\n");
    printf("c (Change stock of item) //    o (Sort all items)      //    u (Unregister items)\n");
    printf("                        //     q (Save & Quit)        // \n");
    printf("--------------------------------------------------------------------------------\n");
   
}
int searchItems(StockItem items[],int pNrInStock) //S
{
    int selection,itemNum,balance,i,index, itemCount, selectFlag=0;
    char itemName[WORDLENGTH], more;
    
    do
    {
        printf("\nEnter your choice of search \n1->Search by item number\n2->Search by item name\n3->Search by balance ");
        scanf("%d",&selection);
        switch(selection)
        {
            case 1:
            selectFlag=0;
                printf("\nEnter item number to search ");
                scanf("%d",&itemNum);
                index=0;
                itemCount=0;
                if(pNrInStock==0)
                    return -1; //indikerar 'error'
                for(i=0;i<pNrInStock;i++)
                {
                    if(items[i].stockNr==itemNum)
                    {
                        checkStockNr(items, i, pNrInStock);
                        printf("%30s\t\t%d\n",items[i].itemName,items[i].balance);
                        index=i;
                        itemCount++;
                    }
                }
                if(itemCount==0)
                    printf("\nItem not found!");
    
                break;
                
            case 2:
            selectFlag=1;
                printf("\nEnter item name to search ");
                getchar();
                gets(itemName);
                index=0;
                itemCount=0;
                for(i=0;i<pNrInStock;i++)
                {
                    if(strcmp(items[i].itemName,itemName)==0 || strstr(items[i].itemName,itemName)!=NULL)
                    {
                        checkStockNr(items, i, pNrInStock);
                        printf("%30s\t\t%d\n",items[i].itemName,items[i].balance);
                        itemCount++;
                        index=i;
                    }
                }
                if(itemCount==0) printf("\nItems with given name not found! ");
                else if(itemCount>1)
                {
                    index=-1;
                    printf("More than 1 item with given search category found. Please select item number");
                    selection=1;
                }
                break;
            case 3:
            selectFlag=1;
                printf("\nEnter balance to search ");
                scanf("%d",&balance);
                index=0;
                itemCount=0;
                for(i=0;i<pNrInStock;i++)
                {
                    if(items[i].balance==balance)
                    {
                        checkStockNr(items, i, pNrInStock);
                        printf("%30s\t\t%d\n",items[i].itemName,items[i].balance);
                        itemCount++;
                        index=i;
                    }
                }
                if(itemCount==0) printf("\nNo items found with given balance ");
                else if(itemCount>1)
                {
                    index=-1;
                    printf("More than 1 item with given search category found. Please select item number");
                    selection=1;
                }
                break;
            default:
            selectFlag=1;
                printf("\nInvalid menu selection");
                 printf("\nEnter your choice of search \n1->Search by item number\n2->Search by item name\n3->Search by balance ");
                scanf("%d",&selection);
                break;
        }
        
    }while(selectFlag);
    

    return index;
}
void changeItemStock(StockItem items[],int pNrInStock)
{
    int index;
    int itemNum;
    char choice;
    int num;
    index=searchItems(items,pNrInStock);
    if(index==-1)
    {
        printf("\nItem not found");
    }
    else
    {
        printf("\nThere are %d items in stock",items[index].balance);
        do
        {
            printf("\nEnter your choice \nA->add to stock \nW->Withdraw from stock\nS->stop ");
            scanf(" %c",&choice);
            if(toupper(choice)=='A')
            {
                printf("\nHow many items do you want to add to balance? ");
                scanf("%d",&num);
                items[index].balance+=num;
            }
            else if(toupper(choice)=='W')
            {
                printf("\nHow many items do you want to withdraw? ");
                scanf("%d",&num);
                if(items[index].balance-num >=0)
                {
                    items[index].balance-=num;
                }
                else
                {
                    printf("\nNot enough stock to withdraw ");
                }
            }
            else if(toupper(choice)!='S')
            {
                printf("\n Invalid menu entry ");
            }
        }while(toupper(choice)!='S');
        
    }
}
void sortItems(StockItem items[],int pNrInStocks) //O
{
   int i,j;
   char choice;
   
   do
   {
       printf("\nPlease enter the order you want to sort\nA->Sort by item number \nB->Sort by item name\nC->Sort by balance\nS->Stop ");
       scanf(" %c",&choice);
       if(toupper(choice)=='A')
        {
           for(i=0;i<pNrInStocks;i++)
           {
               for(j=0;j<(pNrInStocks-i-1);j++)
               {
                   if(items[j].stockNr>items[j+1].stockNr)
                   {
                       StockItem temp=items[j];
                       items[j]=items[j+1];
                       items[j+1]=temp;
                   }
                   
               }
           }
           choice = 'S';
       }
       else if(toupper(choice)=='B')
        {
           for(i=0;i<pNrInStocks;i++)
           {
               for(j=0;j<(pNrInStocks-i-1);j++)
               {
                   if(strcmp(items[j].itemName,items[j+1].itemName)>0)
                   {
                       StockItem temp=items[j];
                       items[j]=items[j+1];
                       items[j+1]=temp;
                   }
               }
           }
           choice = 'S';
       }
       else if(toupper(choice)=='C')
        {
           for(i=0;i<pNrInStocks;i++)
           {
               for(j=0;j<(pNrInStocks-i-1);j++)
               {
                   if(items[j].balance>items[j+1].balance)
                   {
                       StockItem temp=items[j];
                       items[j]=items[j+1];
                       items[j+1]=temp;
                   }
                   
               }
           }
           choice = 'S';
       }
       else if(toupper(choice)!='S')
        {
            printf("\nInvalid menu entry");
        }
   }while(toupper(choice)!='S');
}
void unregItems(StockItem items[],int* pNrInStock) //U
{
    int index, i;

    index=searchItems(items,*pNrInStock);
    if(index == -1)
    {
        printf("\nSorry item was not found to remove");
    }
	else
	{
       for(i=index;i<*pNrInStock-1;i++)
       {
           items[i]=items[i+1];
       }
       (*pNrInStock)--;
       printf("The item has been removed!");
	}
}
void saveAndQuit(StockItem items[],int pNrInStock,char* fileName) //Q
{
   int i;
    FILE *fp;
    fp=fopen(fileName,"w");
    if(fp!=NULL)
    {
        for(i=0;i<pNrInStock;i++)
        {
            if(items[i].stockNr>0 && items[i].stockNr<=9)
                fprintf(fp,"\n00%d",items[i].stockNr);
            if(items[i].stockNr>=10 && items[i].stockNr<=99)
                fprintf(fp,"\n0%d",items[i].stockNr);
            if(items[i].stockNr>=100 && items[i].stockNr<=999)
                fprintf(fp,"\n%d",items[i].stockNr);
            fprintf(fp," %s %d",items[i].itemName,items[i].balance);
        }
        fclose(fp);
    }
    else
    {
        printf("File creation failed\n");
    }
}
int main()
{
 
    char input, fileName[MAX];
    int quitProgram = 0;
    int nrOfItems=0;
    int *pNrInStock=&nrOfItems;
    StockItem items[MAX];
    openFile(items, pNrInStock,fileName);
   
    do
    {
        printMenu();
        printf("r / p / s / c / o / u / q? ");
        scanf(" %c", &input);
       
            switch(toupper(input))
            {
                case 'R': registerItems(items,pNrInStock);
                    break;
                case 'P': printItems(items,*pNrInStock);
                    break;
                case 'S': searchItems(items,*pNrInStock);
                    break;
                case 'C': changeItemStock(items,*pNrInStock);
                    break;
                case 'O': sortItems(items,*pNrInStock);
                    printItems(items,*pNrInStock);
                    break;
                case 'U': unregItems(items,pNrInStock);
                    break;
                case 'Q': saveAndQuit(items,*pNrInStock,fileName);
                    quitProgram=1;
                    break;
                default: printf("Please Enter an accepted letter:");
                    break;
            }
    }while(quitProgram == 0);
    return 0;
}