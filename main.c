#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define CART_FILE "cart.txt"


typedef struct {
	char name[MAX_NAME_LENGTH];
	int price;	
} MenuItem;


typedef struct {
	MenuItem *items;
	int *quantities;
	int size;
	int capacity;
} Cart;


MenuItem menu[8][8] = {
    {{"English Breakfast", 12.00}, {"Continental Breakfast", 15.00}, {"French Toast", 8.00}, {"Eggs Benedict", 12.50}, {"Pancake Stack", 7.00}, {"Bagel with Cream Cheese", 6.00}, {"Greek Yogurt Bowl", 8.00}, {"Scrambled Eggs", 9.00}},
    {{"Beef Bourguignon", 20.00}, {"Chicken Tikka Masala", 17.50}, {"Lamb Rogan Josh", 19.00}, {"Beef Stroganoff", 18.00}, {"Ratatouille", 14.00}, {"Chicken Fajitas", 13.00}, {"Fish and Chips", 15.00}, {"Paella", 22.00}},
    {{"Miso Soup", 7.00}, {"Tom Yum Soup", 9.00}, {"French Onion Soup", 12.00}, {"Clam Chowder", 14.00}, {"Pho", 11.00}, {"Minestrone Soup", 10.00}, {"Gazpacho", 9.00}, {"Pumpkin Soup", 8.00}},
    {{"Bruschetta", 8.00}, {"Guacamole", 9.00}, {"Baba Ganoush", 10.00}, {"Stuffed Grape Leaves", 10.00}, {"Samosas", 7.00}, {"Olive Tapenade", 6.00}, {"Caprese Salad", 10.00}, {"Falafel", 7.00}},
    {{"Caesar Salad", 12.00}, {"Greek Salad", 11.00}, {"Cobb Salad", 13.00}, {"Caprese Salad", 10.00}, {"Waldorf Salad", 12.00}, {"Quinoa Salad", 11.00}, {"Nicoise Salad", 13.00}, {"Russian Salad", 10.00}},
    {{"Spring Rolls", 7.00}, {"Vegetable Samosas", 8.00}, {"Arancini", 10.00}, {"Stuffed Mushrooms", 9.00}, {"Zucchini Fritters", 8.00}, {"Mozzarella Sticks", 7.00}, {"Empanadas", 9.00}, {"Mini Tacos", 8.00}},
    {{"Tiramisu", 12.00}, {"Creme Brulee", 14.00}, {"Cheesecake", 9.00}, {"Baklava", 10.00}, {"Apple Pie", 9.00}, {"Chocolate Fondant", 11.00}, {"Pavlova", 12.00}, {"Mochi", 7.00}},
    {{"Coca Cola", 3.00}, {"Ice Tea", 3.00}, {"Sprite", 3.00}, {"Soda", 2.00}, {"Lemonade", 5.00}, {"Ayran", 4.00}, {"Salgam", 4.00}, {"Sira", 6.00}}
};

int stocks[8][8] = {
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45}
};

MenuItem veganMenu[8][8] = {
    {{"Scrambled Tofu", 12}, {"Avocado Toast", 10}, {"Vegan Pancakes", 15}, {"Granola Bowl", 12}, {"Chia Pudding", 8}, {"Smoothie Bowl", 14}, {"Vegan Cheese Platter", 16}, {"Hummus Breakfast Platter", 14}},
    {{"Black Bean Burger", 14}, {"Quinoa Burger", 16}, {"Mushroom Burger", 15}, {"Vegetable Falafel Burger", 13}, {"Tofu Burger", 15}, {"Bulgur Burger", 13}, {"Kidney Bean Burger", 12}, {"Quinoa and Veggie Burger", 15}},
    {{"Lentil Soup", 10}, {"Vegetable Miso Soup", 8}, {"Mushroom Soup", 9}, {"Pumpkin Soup", 11}, {"Noodle Soup", 10}, {"Cold Avocado Soup", 9}, {"Broccoli and Coconut Soup", 10}, {"Pea Soup", 8}},
    {{"Vegetable Pizza", 14}, {"Potato Gratin", 12}, {"Vegetable Pastry", 10}, {"Zucchini Fritters", 10}, {"Vegan Lasagna", 15}, {"Stuffed Peppers", 13}, {"French Fries", 6}, {"Vegan Kofte", 13}},
    {{"Mediterranean Salad", 11}, {"Chickpea Quinoa Salad", 12}, {"Crispy Tofu Salad", 10}, {"Mango and Avocado Salad", 14}, {"Kidney Bean and Corn Salad", 9}, {"Quinoa and Broccoli Salad", 13}, {"Green Lentil Salad", 10}},
    {{"Fried Potato Wedges", 8}, {"Bulgur Pilaf", 9}, {"Green Lentil Pilaf", 10}, {"Quinoa Pilaf", 11}, {"Roasted Sweet Potatoes", 10}, {"Chickpea Pilaf", 9}, {"Kidney Bean Puree", 9}, {"Cacik", 6}},
    {{"Vegan Chocolate Brownie", 5}, {"Coconut Pudding", 7}, {"Strawberry Chia Pudding", 8}, {"Vegan Fruit Tart", 6}, {"Lemon Coconut Cookies", 4}, {"Apple Cake", 5}, {"Hazelnut Energy Balls", 4}, {"Orange Snowball Cookies", 4}},
    {{"Fruit Smoothie", 7}, {"Vegan Cocoa", 5}, {"Iced Matcha Latte", 6}, {"Mint Lemonade", 5}, {"Ginger Apple Juice", 5}, {"Strawberry Banana Smoothie", 7}, {"Iced Rooibos Tea", 5}, {"Pineapple Mango Smoothie", 6}}
};

int veganStocks[8][8] = {
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45},
    {30, 55, 20, 25, 35, 35, 40, 45}
};


void initCart(Cart *cart) {
	cart ->size = 0;
	cart -> capacity = 2; 
	cart -> items = (MenuItem *)malloc(cart -> capacity * sizeof(MenuItem));
	cart -> quantities = (int *)malloc(cart -> capacity * sizeof(int));
	if (cart -> items == NULL || cart -> quantities == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	} 
}


void addProduct(Cart *cart, MenuItem item, int quantity) {
	if (cart -> size == cart -> capacity) {
		cart -> capacity *=2;
		cart -> items = (MenuItem *)realloc(cart -> items, cart -> capacity * sizeof(MenuItem));
		cart -> quantities = (int *)realloc(cart -> quantities, cart -> capacity * sizeof(int));
		if (cart -> items == NULL || cart -> quantities == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			exit(1);
		}
	}
	cart -> items[cart -> size] = item;
	cart -> quantities[cart -> size] = quantity;
	cart -> size++;
}	

void removeProduct(Cart *cart, int index) {
	for (int i = index; i < cart -> size -1; i++) {
		cart -> items[i] = cart -> items[i + 1];
		cart -> quantities[i] = cart -> quantities[i + 1];
	}
	cart -> size--;
}
	
void printCart(Cart *cart) {
	printf("\nCart:\n");
	int total = 0;
	for (int i = 0; i < cart ->size; i++) {
		printf("%s x%d - %d $\n", cart ->items[i].name, cart ->quantities[i], cart -> items[i].price * cart -> quantities[i]);
		total += cart -> items[i].price * cart -> quantities[i];
	}
	printf("Total: %d $\n", total);
}


void printCategories() {
	printf("Categories: \n");
	printf("1) Breakfast\n");
	printf("2) Steaks\n");
	printf("3) Soup\n");
	printf("4) Appetizer\n");
	printf("5) Salad\n");
	printf("6) Snack\n");
	printf("7) Dessert\n");
	printf("8) Beverage\n");
}

void printMenu(MenuItem men[8][8], int category) {
	for (int i = 0; i < 8; i++) {
		printf("%d. %s - %d $ (stock(s))\n", i + 1, menu[category][i].name, menu[category][i].price, stocks[category][i]);
	}
}

void printVeganMenu(MenuItem menu[8][8], int category) {
	for (int i = 0; i < 8; i++) {
		printf("%d. %s - %d $ (stock(s))\n", i + 1, menu[category][i].name, menu[category][i].price, veganStocks[category][i]);
	}
}

void saveCart(Cart *cart) {
    FILE *file = fopen(CART_FILE, "w");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing\n");
        return;
    }
    fprintf(file, "%d\n", cart->size);
    for (int i = 0; i < cart->size; i++) {
        fprintf(file, "%s %d %d\n", cart->items[i].name, cart->items[i].price, cart->quantities[i]);
    }
    fclose(file);
}


void loadCart(Cart *cart) {
	FILE *file = fopen(CART_FILE, "r");
	if (file == NULL) {
		printf("There is nothing :(");
		return;
	}
	fscanf(file, "%d", &cart -> size);
	cart -> capacity = cart -> size;
	cart -> items = (MenuItem *)realloc(cart -> items, cart -> capacity * sizeof(MenuItem));
	cart -> quantities = (int *)realloc(cart -> quantities, cart -> capacity * sizeof(int));
	for (int i = 0; i < cart -> size; i++) {
		fscanf(file, "%s %d %d", cart -> items[i].name, &cart -> items[i].price, &cart -> quantities[i]);
	}
	fclose(file);
}



int main(int argc, char *argv[]) {
	Cart cart;
	initCart(&cart);
	loadCart(&cart);
	int choice, category, item, quantity;
	
	while (1) {
		printf("\nMain Menu\n");
		printf("1) Normal Menu\n");
		printf("2) Vegan Menu\n");
		printf("3) Show Cart\n");
		printf("4) Exit\n");
		printf("Your Choice: ");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1:
				printCategories();
				printf("Please select a category(1-8): ");
				scanf("%d", &category);
				if (category < 1 || category > 8) {
					printf("Invalid category!\n");
					break;
				}
				printMenu(menu, category - 1);
				printf("Choose product (1-8): ");
				scanf("%d", &item);
				if (item < 1 || item > 8) {
					printf("Invalid product\n");
					break;
				}
				printf("Quantity: ");
				scanf("%d", &quantity);
				if (quantity > stocks[category - 1][item - 1]) {
					printf("There is no stock!\n");
					break;
				}
				stocks[category - 1][item - 1] -= quantity;
				addProduct(&cart, menu[category -1][item - 1], quantity);
				printf("Your produt(s) added to your cart\n");
				break;
		
			case 2:
				printCategories();
				printf("Please select a category(1-8): ");
				scanf("%d", &category);
				if (category < 1 || category > 8) {
					printf("Invalid category!\n");
					break;
				}
				printVeganMenu(veganMenu, category -1);
				printf("Choose product (1-8):");
				scanf("%d", &item);
				if (item < 1 || item > 8) {
					printf("Invalid product\n");
					break;
				}
				printf("Quantity: ");
				scanf("%d", &item);
				if (item < 1 || item > 8) {
					printf("There is no stock!\n");
					break;
				}
				veganStocks[category - 1][item - 1] -= quantity;
				addProduct(&cart, veganMenu[category -1 ][item - 1], quantity);
				printf("Your produt(s) added to your cart\n");
				break;
			case 3:
				printCart(&cart);
				break;
			case 4:
				saveCart(&cart);
				free(cart.items);
				free(cart.quantities);
				return 0;
			default:
				printf("Invalid selection!\n");
		}
			
	}
}
