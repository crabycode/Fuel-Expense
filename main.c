#include <stdio.h>
#include <stdlib.h>
typedef struct Car
{
    char brand[21];
    char model[21];
    float fuelExpense;
}Car;
void findCar(Car *car)
{
    FILE *file = fopen("cars.bin", "rb");
    if(!file)
    {
        printf("File could not be opened.");
        exit(1);
    }
    printf("Please enter car brand: ");
    scanf("%20s", car->brand);
    printf("Please enter car model: ");
    scanf("%20s", car->model);
    Car car2;
    int found = 0;
    while (fread(&car2, sizeof(Car), 1, file) == 1)
    {
        if (strcmp(car2.brand, car->brand) == 0 && strcmp(car2.model, car->model) == 0)
        {
            found =1;
            car->fuelExpense = car2.fuelExpense;
            printf("Brand: %s\n", car->brand);
            printf("Model: %s\n", car->model);
            printf("Fuel Expense: %.2f\n", car->fuelExpense);
        }
    }
    if(!found)
    {
        printf("Car not found.");
        exit(1);
    }
    fclose(file);
}
void addCar(Car *car)
{
    FILE *file = fopen("cars.bin", "ab");
    if(!file)
    {
        printf("File could not be opened.");
        exit(1);
    }
    printf("Please enter car brand: ");
    scanf("%20s", car->brand);
    printf("Please enter car model: ");
    scanf("%20s", car->model);
    printf("Please enter car fuel expense: ");
    scanf("%f", &car->fuelExpense);
    fwrite(car, sizeof(Car), 1, file);
    printf("Car successfully added!\n");
    fclose(file);
}
int main()
{
    printf("Hello and welcome to the fuel calculator!");
    printf("Have you logged in your car yet?\n1)yes  2)no\n");
    Car car;
    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            findCar(&car);
            break;
        case 2:
            addCar(&car);
            break;
    }
    printf("Ok! How many kilometers are you going to pass?\n");
    float kilometres = 0;
    scanf("%f", &kilometres);
    float calculation = car.fuelExpense/100 * kilometres;
    printf("For those kilometers you are going to burn %.2f fuel\n", calculation);
    printf("What is the price of your fuel? \n");
    float price = 0;
    scanf("%f", &price);
    printf("Then it's going to cost you %.2f lv.", price*calculation);
    return 0;
}
