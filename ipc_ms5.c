#include <stdio.h>
#include <string.h>

struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};




/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
const double TAX = 0.13;
#define MAX_ITEM_NO 555 
#define MAX_QTY     999
#define SKU_MAX     999
#define SKU_MIN     100 
#define DATAFILE "items.txt"

void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n");
}
void prnTitle(void) {
	printf("Row |SKU| Name                | Price   |Taxed| Qty | Min |   Total   |Atn\n");
	
printf("----+---+---------------------+---------+-----+-----+-----+-----------|---\n");       
}
void prnFooter(double gTotal) {
	
printf("----------------------------------------------------------+---------------\n");
	if (gTotal > 0) {
	printf("					     Grand Total: |     %12.2lf\n", gTotal); 
	}
}
void clrKyb(void) {
	while(getchar() != '\n');	
}
void pause(void) {
	printf("Press <ENTER> to continue...");
	clrKyb();
}
int getInt(void){
	int Value;
	char NL = 'x';
	while (NL != '\n') {
		scanf("%d%c", &Value, &NL);
		if (NL != '\n') {
			clrKyb(); 
			printf("Invalid integer, please try again: ");	
			scanf("%d%c", &Value, &NL);	
		}
	}
	return Value;
}
double getDbl(void) {
	double Value;
        char NL = 'x';
        while (NL != '\n') {
		scanf("%lf%c", &Value, &NL);
		if (NL != '\n') {
                	clrKyb();
                	printf("Invalid integer, please try again: ");
			scanf("%lf%c", &Value, &NL);
		}                
        }
	return Value;
}
int getIntLimited(int lowerLimit, int upperLimit) {
	int Value;
	do {
		Value = getInt();
		if (Value < lowerLimit || Value > upperLimit) {
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		}
	} while (Value < lowerLimit || Value > upperLimit);
	return Value;
}
double getDblLimited(double lowerLimit, double upperLimit) {
	double Value;
        do {
                Value = getDbl();
                if (Value < lowerLimit || Value > upperLimit) {
                        printf("Invalid value, %lf < value < %lf: ", lowerLimit, upperLimit);
                }
        } while (Value < lowerLimit || Value > upperLimit);
	return Value;
}

int yes(void) {
	char CH;
	int RET = 0;
	do {
		scanf("%c", &CH);
		clrKyb();
		if (CH != 'y' && CH != 'Y' && CH != 'N' && CH != 'n'){
			printf("Only (Y)es or (N)o are acceptable: ");
		}
	} while (CH != 'y'  && CH != 'Y' && CH != 'N' && CH != 'n');
	
	if (CH == 'y' || CH == 'Y') {
		RET = 1;
	} 
	return RET;
}

int menu(void) {
	int num = 0;
	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- delete item\n");
	printf("7- Search by name\n");
	printf("0- Exit program\n");
	printf("> ");
	num = getIntLimited(0,7);
	return num;
}



double totalAfterTax(struct Item item){
	double total;
		if (item.isTaxed == 1) {
			total = item.price * (double)item.quantity * (TAX + 1);
		}	
		else {
			total = item.price * (double)item.quantity;
		}
	return total;
}
int isLowQty(struct Item item){
	int isTrue;
		if (item.quantity < item.minQuantity) {
			isTrue = 1;
		}
		else {
			isTrue = 0;
		}
	return isTrue;
}
struct Item itemEntry(int sku){
	int i = 0;
	struct Item itemEntry;
	itemEntry.sku = sku;
	printf("        SKU: %d\n", itemEntry.sku);
	printf("       Name: ");
	scanf("%21[^\n]", itemEntry.name);
	clrKyb();
	printf("      Price: ");
	itemEntry.price = getDblLimited(0.01, 1000.00);
	printf("   Quantity: ");
	itemEntry.quantity = getIntLimited(1, MAX_QTY);
	printf("Minimum Qty: ");
	itemEntry.minQuantity = getIntLimited(0, 100);
	printf("   Is Taxed: ");
	itemEntry.isTaxed = yes();
	return itemEntry;
}
void dspItem(struct Item item, int linear){ 
	double total = totalAfterTax(item);
	int isLow = isLowQty(item);
	while (linear == 1) {
		if ((isLow == 0) && (item.isTaxed == 1)) {
			printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, total);
			break;  
		}
		else if ((isLow == 0) && (item.isTaxed == 0)) {
                        printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, total);
                        break;
                }

		if ((isLow == 1) && (item.isTaxed == 1)) {
			printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|***\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, total);
			break;
		}
		else if ((isLow == 1) && (item.isTaxed == 0)) {
                        printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|***\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, total);
                        break;
                }

	}	
	while (linear == 0) {
		if ((isLow == 0) && (item.isTaxed == 1)) {
			printf("        SKU: %d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %.2lf\n", item.price);
			printf("   Quantity: %d\n", item.quantity);
			printf("Minimum Qty: %d\n", item.minQuantity);
			printf("   Is Taxed: Yes\n");
			break;
		}
		if ((isLow == 0) && (item.isTaxed == 0)) {
			printf("        SKU: %d\n", item.sku);
                        printf("       Name: %s\n", item.name);
                        printf("      Price: %.2lf\n", item.price);
                        printf("   Quantity: %d\n", item.quantity);
                        printf("Minimum Qty: %d\n", item.minQuantity);
                        printf("   Is Taxed: No\n");
                        break;
		}
		if ((isLow == 1) && (item.isTaxed == 1)) {
			printf("        SKU: %d\n", item.sku);
                        printf("       Name: %s\n", item.name);
                        printf("      Price: %.2lf\n", item.price);
                        printf("   Quantity: %d\n", item.quantity);
                        printf("Minimum Qty: %d\n", item.minQuantity);
                        printf("   Is Taxed: Yes\n");
                        printf("WARNING: Quantity low, please order ASAP!!!\n");
                        break;
		}
		if ((isLow == 1) && (item.isTaxed == 0)) {          
                        printf("        SKU: %d\n", item.sku);
                        printf("       Name: %s\n", item.name);
                        printf("      Price: %.2lf\n", item.price);
                        printf("   Quantity: %d\n", item.quantity);
                        printf("Minimum Qty: %d\n", item.minQuantity);
                        printf("   Is Taxed: No\n");
			printf("WARNING: Quantity low, please order ASAP!!!\n");
			break;
                }

	}
}
void listItems(const struct Item item[], int NoOfItems){
	int i = 0;
	int row = 0;
	int total = 0;
	int linear = 1;
	double totalPrice = 0;
	prnTitle();
	for (i = 0; i < NoOfItems; i++) {
		row = i + 1;
		printf("%-4d", row);
		dspItem(item[i], linear);
		total = totalAfterTax(item[i]);
		totalPrice = totalPrice + total;
	}	
	prnFooter(totalPrice);
}
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* 
index){
	int i = 0;
	int value = 0;
	for (i = 0; i < NoOfRecs; i++) {
		if (sku == item[i].sku){
			value = 1;
			break;	
		}
	}
	
	*index = i;
	return value;	
}

void search(const struct Item item[], int NoOfRecs){
	int sku, value, index;
        printf("Please enter the SKU: ");
        sku = getIntLimited(SKU_MIN, SKU_MAX);
        value = locateItem(item, NoOfRecs, sku, &index);

        if (value == 1) {
                dspItem(item[index], 0);
        }	
        else {
                printf("Item not found!\n");
        }
}
void updateItem(struct Item* itemptr){
	struct Item item;
        int i, value, sku;
	int answer = 0;
	sku = (*itemptr).sku;
        printf("Enter new data: \n");
        item = itemEntry(sku);
        printf("Overwrite old data? (Y)es/(N)o: ");
        answer = yes();
        if (answer == 1) {
		*itemptr = item;
                printf("--== Updated! ==--\n");
        }
        else {
                printf("--== Aborted! ==--\n");
        }
}

void addItem(struct Item item[], int *NoOfRecs, int sku){
	struct Item newItem;
	int answer = 0;
	int total;
	if (*NoOfRecs == MAX_ITEM_NO) {
		printf("Can not add new item; Storage FULL!\n");
	}
	else {
		newItem = itemEntry(sku);
		printf("Add Item? (Y)es/(N)o: ");
		answer = yes();
		if (answer == 1) {
			printf("--== Added! ==--\n");
			item[*NoOfRecs] = newItem;
			total = *NoOfRecs;
			total = total + 1;
			*NoOfRecs = total;	
		}		
		else {
			printf("--== Aborted! ==--\n");
		}		
	}
}
void addOrUpdateItem(struct Item item[], int* NoOfRecs){
	int sku, i, answer;
	int found = 0;
	printf("Please enter the SKU: ");
	sku = getIntLimited(SKU_MIN, SKU_MAX);
	for (i = 0; i < *NoOfRecs; i++) {
		if (sku == item[i].sku) {
			found = 1;
			break;
		}		
	}
	if (found == 1) {
		dspItem(item[i], 0);
		printf("Item already exists, Update? (Y)es/(N)o: ");
		answer = yes();
			if (answer == 1) {
				updateItem(&item[i]);
			}		
			else {
				printf("--== Aborted! ==--\n");
			}
	}
	if (found == 0) {
		addItem(item, &(*NoOfRecs), sku);
	}	
}
void adjustQty(struct Item item[], int NoOfRecs, int stock){
	int sku, value, i;
	char toStock[20] = "to stock";
	char toCheckout[20] = "to checkout";
	int found = 0;
	printf("Please enter the SKU: ");
	sku = getIntLimited(SKU_MIN, SKU_MAX);
        for (i = 0; i < NoOfRecs; i++) {
                if (sku == item[i].sku) {
                        found = 1;
                        break;
                }               
        }
	if (found == 0) {
		printf("SKU not found in storage!\n");
	}
	if (found == 1) {
		dspItem(item[i], 0);
		if (stock == 1) {
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", toStock, (MAX_QTY - item[i].quantity));
			scanf("%d", &value);
			if (value == 0) {
				printf("--== Aborted ==--\n");
			}
			else {
				item[i].quantity = item[i].quantity + value;
				printf("--== Stocked! ==--\n");
			}
		}
		if (stock == 0) {
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", toCheckout, item[i].quantity);
			scanf("%d", &value);
			if (value == 0) {
                                printf("--== Aborted ==--\n");
                        }
                        else {
                                item[i].quantity = item[i].quantity - value;
				printf("--== Checked Out! ==--\n");
                        }
		}
	}
	if (item[i].quantity <= item[i].minQuantity) {
		printf("Quantity is low, please reorder ASAP!!!\n");
	}
}

void GrocInvSys(void){
        struct Item items[MAX_ITEM_NO];
        int noOfRecs;
        int DONE = 0;
        if (loadItems(items, DATAFILE, &noOfRecs) == 0) {
                printf("Could not read from %s.\n", DATAFILE);
        }
        int SEL;
        welcome();
        while (!DONE) {
        SEL = menu();
        if (SEL == 1) {
                printf("List items!\n");
                listItems(items, noOfRecs);
		clrKyb();
                pause();
        }
        if (SEL == 2) {
                printf("Search items!\n");
                search(items, noOfRecs);
		clrKyb();
                pause();
        }
        if (SEL == 3) {
                printf("Checkout Item!\n");
                adjustQty(items, noOfRecs, CHECKOUT);
                if (saveItems(items, DATAFILE, noOfRecs) == 0) {
                        printf("could not update file %s\n", DATAFILE);
                }
		clrKyb();
                pause();
	}
	if (SEL == 4) {
                printf("Stock Item!\n");
                adjustQty(items, noOfRecs, STOCK);
                if (saveItems(items, DATAFILE, noOfRecs) == 0) {
                        printf("could not update file %s\n", DATAFILE);
                }
		clrKyb();
                pause();
        }
        if (SEL == 5) {
                printf("Add/Update Item!\n");
                addOrUpdateItem(items, &noOfRecs);
                if (saveItems(items, DATAFILE, noOfRecs) == 0) {
                        printf("could not update file %s\n", DATAFILE);
                }
		clrKyb();
                pause();
        }
        if (SEL == 6) {
                printf("Delete Item!\n");
                printf("Not implemented!\n");
                pause();
        }
        if (SEL == 7) {
                printf("Search by name!\n");
                printf("Not implemented!\n");
                pause();
        }
        if (SEL == 0) {
                printf("Exit the program? (Y)es/(N)o: ");
                DONE = yes();
        }
        }
}




/*End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/

void saveItem(struct Item item, FILE* dataFile) {
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}
int loadItem(struct Item* item, FILE* dataFile){
	int true = 0;
	struct Item newItem;
	newItem = *item;
	if (fscanf(dataFile, "%d,%d,%d,%lf,%d,%21[^\n]", &newItem.sku,  &newItem.quantity, &newItem.minQuantity, &newItem.price, &newItem.isTaxed, newItem.name) == 6) {
		true = 1;
		*item = newItem;
	}
	return true;

}
int saveItems(struct Item* item, char fileName[], int NoOfRecs){
	int true = 0;
	int i;
	FILE *fp = NULL;

	fp = fopen(fileName, "w");

	if (fp != NULL) {
		for (i = 0; i < NoOfRecs; i++) {
			saveItem(item[i], fp);
		}
		true = 1;
		fclose(fp);
	}
	return true;
}
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr){
	int true = 0;
	int i = 0;;
	FILE *fp = NULL;
	
	fp = fopen(fileName, "r");
	
	if (fp != NULL) {
		while (loadItem(&item[i], fp) != 0) {
			i++;
		}
		true = 1;
		*NoOfRecsPtr = i;
		fclose(fp);
	}
	return true;
}

/*End of milestone 5 prototypes
*********************************************************************/




/**************************************************************************
    TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR                                                      
       TT       EE         SS             TT       EE          RR     RR          
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
       TT       EE               SS       TT       EE          RR  RR
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here:



void prnFile() {
   FILE* tp = fopen("test.txt", "r");
   char ch;
   if (tp) {
      for (; fscanf(tp,"%c", &ch) == 1; putchar(ch));
      fclose(tp);
   }
   else {
      printf("text.txt not found\n");
   }
}


int main(void) {
   int i, n;
   struct Item GI[3] = {
      { 4.4,275,0,10,2,"Royal Gala Apples" },
      { 5.99,386,0,20,4,"Honeydew Melon" },
      { 3.99,240,0,30,5,"Blueberries" },
   };
   struct Item I;
   struct Item IN[3];
   printf("***********Testing saveItem:\n");
   printf("Your saveItem saved the following in test.txt: \n");
   FILE* tp = fopen("test.txt", "w");
   if (tp) {
      for (i = 0; i < 3; i++) saveItem(GI[i], tp);
      fclose(tp);
      prnFile();
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItem!\n\n\n");
   pause();
   printf("***********Testing loadItem:\n");
   printf("Your loadItem loaded the following from test.txt: \n");
   tp = fopen("test.txt", "r");
   if (tp) {
      for (i = 0; i < 3; i++) {
         loadItem(&I, tp);
         dspItem(I, LINEAR);
      }
      fclose(tp);
      tp = fopen("test.txt", "w");
      fclose(tp);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItem!\n\n\n");
   pause();
   printf("***********Testing saveItems:\n");
   printf("Your saveItems saved the following in test.txt: \n");
   saveItems(GI, "test.txt", 3);
   prnFile();
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItems!\n\n\n");
   pause();
   printf("***********Testing loadItems:\n");
   printf("Your loadItems loaded the following from test.txt: \n");
   loadItems(IN, "test.txt", &n);
   for (i = 0; i < n; i++) {
      dspItem(IN[i], LINEAR);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItems!\n\n\n");
   pause();
   printf("Done!\n");
   return 0;
}

/* End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/********************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here: */ 
int main(void) {
GrocInvSys();
return 0;
}

/* End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/

/*End of milestone 5 functions
*********************************************************************/

/********************************************************************
Milestones 1  to 4 functions*/



/*End of milestone 1 to 4 functions
*********************************************************************/








/* ms5 Tester output

***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!


Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!


Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!


Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!


Press <ENTER> to continue...
Done!


*/
