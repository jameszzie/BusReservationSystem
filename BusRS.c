#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUSES 5
#define MAX_SEATS 20

// Structure Definition
typedef struct {
    int bus_id;
    char route[50];
    int seats[MAX_SEATS]; // 0 = Available, 1 = Booked
    float fare;
} Bus;

// Global Data
Bus buses[MAX_BUSES];

// --- FUNCTION PROTOTYPES ---
void initializeData();
void viewSchedules();
void viewStatusBoard();
void bookSeat();
void cancelSeat();
void clearBuffer();

// --- MAIN FUNCTION ---
int main() {
    int choice;
    initializeData();

    while (1) {
        printf("\n===== BUS RESERVATION SYSTEM =====\n");
        printf("1. View Schedules\n");
        printf("2. View Status Board\n");
        printf("3. Book a Seat\n");
        printf("4. Cancel a Seat\n");
        printf("5. Exit\n");
        printf("Choice: ");
        
        // Fixed Line 32 Logic
        if (scanf("%d", &choice) != 1) {
            printf("[!] Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        
        if (choice == 5) {
        	printf("Exiting system. Thank you!\n");
        	break;
		}
        
        switch(choice) {
            case 1: viewSchedules(); break;
            case 2: viewStatusBoard(); break;
            case 3: bookSeat(); break;
            case 4: cancelSeat(); break;
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// --- FUNCTION DEFINITIONS ---

void initializeData() {
    char *routes[] = {"Manila-Baguio", "Pasay-Bicol", "Cebu-Oslob", "Davao-Tagum", "Iloilo-Caticlan"};
    int i; // Declare the variable here first
    
    for (i = 0; i < MAX_BUSES; i++) { // Then just use it here
        buses[i].bus_id = i + 101;
        strcpy(buses[i].route, routes[i]);
        buses[i].fare = 500.00 + (i * 100);
        
        int j; // Declare j here as well
        for (j = 0; j < MAX_SEATS; j++) {
            buses[i].seats[j] = 0;
        }
    }
}

void viewSchedules() {
    printf("\n--- CURRENT BUS SCHEDULES ---\n");
    printf("%-10s %-20s %-10s\n", "ID", "Route", "Fare");
    
    int i; // Move declaration here
    for (i = 0; i < MAX_BUSES; i++) {
        printf("%-10d %-20s PHP %.2f\n", buses[i].bus_id, buses[i].route, buses[i].fare);
    }
}

void viewStatusBoard() {
	int i, j; // Declare both here
	int taken;
	
    printf("\n--- BUS STATUS BOARD ---\n");
    for (i = 0; i < MAX_BUSES; i++) {
        int taken = 0;
        for(j = 0; j < MAX_SEATS; j++) {
		   if(buses[i].seats[j] == 1) taken++;
    }
    
    printf("Bus %d [%s]: %d/%d Seats Filled\n", 
            buses[i].bus_id, buses[i].route, taken, MAX_SEATS);
        
        for(j = 0; j < MAX_SEATS; j++) {
            printf("%s ", buses[i].seats[j] ? "[X]" : "[ ]");
            if((j+1) % 4 == 0) printf("  "); // aisle gap
        }
        printf("\n\n"); // Add a newline after each bus seat map
    }
}

void bookSeat() {
    int id, sn, i, found = -1;
    printf("\nEnter Bus ID: ");
    if (scanf("%d", &id) != 1) { clearBuffer(); return; }
    
    for (i = 0; i < MAX_BUSES; i++) {
        if (buses[i].bus_id == id) found = i;
    }

    if (found == -1) { 
        printf("Bus not found!\n"); 
        return; 
    }

    printf("Enter Seat (1-20): ");
    if (scanf("%d", &sn) != 1) { clearBuffer(); return; }

    if (sn < 1 || sn > 20) {
        printf("? Invalid seat number!\n");
    } else if (buses[found].seats[sn-1] == 1) {
        printf("? Seat already taken!\n");
    } else {
        buses[found].seats[sn-1] = 1;
        printf("? Seat %d successfully booked for Bus %d!\n", sn, id);
    }
    clearBuffer(); 
}

void cancelSeat() {
    int id, sn, i, found = -1;
    printf("\nEnter Bus ID for Cancellation: ");
    if (scanf("%d", &id) != 1) { clearBuffer(); return; }

    for (i = 0; i < MAX_BUSES; i++) {
        if (buses[i].bus_id == id) found = i;
    }

    if (found == -1) { 
        printf("Bus not found!\n"); 
        return; 
    }

    printf("Enter Seat Number to Cancel (1-20): ");
    if (scanf("%d", &sn) != 1) { clearBuffer(); return; }

    if (sn < 1 || sn > 20 || buses[found].seats[sn-1] == 0) {
        printf("? Error: Seat was not booked or is invalid.\n");
    } else {
        buses[found].seats[sn-1] = 0;
        printf("? Seat %d has been cancelled.\n", sn);
    }
    clearBuffer();
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != -1);
}
