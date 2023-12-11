#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Material {
    char name[50];
    int quantity;
    char unit[20];
    float cost;
    struct Material* next;
};

struct Material* createMaterialNode(char name[], int quantity, char unit[], float cost) {
    struct Material* newNode = (struct Material*)malloc(sizeof(struct Material));
    strcpy(newNode->name, name);
    newNode->quantity = quantity;
    strcpy(newNode->unit, unit);
    newNode->cost = cost;
    newNode->next = NULL;
    return newNode;
}

struct Material* insertMaterial(struct Material* head, char name[], int quantity, char unit[], float cost) {
    struct Material* newNode = createMaterialNode(name, quantity, unit, cost);

    if (head == NULL) {
        return newNode;
    }

    struct Material* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

void freeList(struct Material* head) {
    struct Material* current = head;
    struct Material* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

float calculateCost(struct Material* head) {
    float totalCost = 0.0;
    struct Material* current = head;

    while (current != NULL) {
        totalCost += current->cost * current->quantity;
        current = current->next;
    }

    return totalCost;
}

int calculateTotalMaterials(struct Material* head) {
    int totalMaterials = 0;
    struct Material* current = head;

    while (current != NULL) {
        totalMaterials += current->quantity;
        current = current->next;
    }

    return totalMaterials;
}

void promptUser(struct Material* head) {
    struct Material* current = head;

    while (current != NULL) {
        printf("Enter the quantity of %s (%s): ", current->name, current->unit);
        scanf("%d", &(current->quantity));
        current = current->next;
    }
}

int main() {
    struct Material* head = NULL;

    
    head = insertMaterial(head, "Aluminum", 0, "kg", 2.5);
    head = insertMaterial(head, "Steel", 0, "kg", 3.0);
    head = insertMaterial(head, "Carbon Fiber", 0, "kg", 10.0);
    head = insertMaterial(head, "Plastic", 0, "kg", 1.5);
    head = insertMaterial(head, "Rubber", 0, "kg", 0.8);
    head = insertMaterial(head, "Circuit Boards", 0, "pieces", 15.0);
    head = insertMaterial(head, "Wires", 0, "meters", 2.0);
    head = insertMaterial(head, "Sensors", 0, "pieces", 25.0);
    head = insertMaterial(head, "Motors", 0, "pieces", 8.0);

    
    promptUser(head);

    
    int totalMaterials = calculateTotalMaterials(head);
    printf("\n***-------------------------------------------------***");
    printf("\nThe total materials used in one machine is: %d %s\n", totalMaterials, head->unit);
    printf("***-------------------------------------------------***\n");
    
    float totalInvestment = calculateCost(head);
    printf("The total investment to produce one machine is: $%.2f\n", totalInvestment);
    printf("***-------------------------------------------------***\n");

    float profitMargin = 0.20;  
    float sellingPrice = totalInvestment * (1.0 + profitMargin);
    float revenue;
    float potentialLosses;

    if (sellingPrice - totalInvestment < 0) {
        potentialLosses = sellingPrice - totalInvestment;
        revenue = 0;
    } else {
        revenue = sellingPrice - totalInvestment;
        potentialLosses = 0;
    }

    printf("The selling price of one machine is: $%.2f\n", sellingPrice);
    printf("***-------------------------------------------------***\n");
    printf("The revenue from selling one machine is: $%.2f\n", revenue);
    printf("***-------------------------------------------------***");

    
    freeList(head);

    return 0;
}