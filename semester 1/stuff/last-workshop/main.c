#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer
{
  char id[10];
  char store[100];
  double debt;
};

int insert_customer();
int search_customer();
int list_customers();

int main(void)
{
  char answer;
  int code;

  do
  {
    // Clear the screen
    system("cls"); // Use "clear" for Unix-like systems

    // Display menu options
    printf("1. Add customer\n");
    printf("2. Search customer\n");
    printf("3. List customers\n");
    printf("4. Exit\n");

    // Get user choice
    printf("Enter your choice: ");
    answer = getchar();
    getchar(); // Consume the newline character

    switch (answer)
    {
    case '1':
      code = insert_customer();
      if (code == 0)
        printf("Customer added successfully!\n");
      else
        fprintf(stderr, "Error adding customer!\n");
      break;

    case '2':
      code = search_customer();
      if (code == 1)
        printf("Customer not found!\n");
      else if (code == -1)
        fprintf(stderr, "Error opening file!\n");
      break;

    case '3':
      code = list_customers();
      if (code == 0)
        printf("Customers listed successfully!\n");
      else
        printf("No customers found!\n");
      break;

    default:
      break;
    }

    // Wait for user input before continuing
    if (answer >= '1' && answer <= '3')
    {
      printf("Press any key to continue...");
      getchar();
    }

  } while (answer != '4');
  printf("Goodbye!\n");

  return 0;
}

int insert_customer()
{
  struct Customer customer;
  FILE *file;

  printf("Enter customer ID: ");
  fgets(customer.id, 10, stdin);
  getchar();
  printf("Enter customer store: ");
  fgets(customer.store, 100, stdin);
  customer.store[strlen(customer.store) - 1] = '\0';
  printf("Enter customer debt: ");
  scanf("%lf", &customer.debt);
  getchar();

  file = fopen("customers.dat", "a");

  if (file == NULL)
  {
    return -1;
  }

  fwrite(&customer, sizeof(struct Customer), 1, file);
  fclose(file);

  return 0;
}

int search_customer()
{
  struct Customer customer;
  char id[10];
  FILE *file;
  int found = 0;

  printf("Enter customer ID: ");
  fgets(id, sizeof(id), stdin);
  id[strcspn(id, "\n")] = '\0'; // Remove the newline character

  file = fopen("customers.dat", "r");

  if (file == NULL)
  {
    return -1;
  }

  while (fread(&customer, sizeof(struct Customer), 1, file) > 0)
  {
    // Compare the customer ID without the newline character
    if (strcmp(customer.id, id) == 0)
    {
      printf("--------------------\n");
      printf("Customer found:\n");
      printf("Id: %s\n", customer.id);
      printf("Store: %s\n", customer.store);
      printf("Debt: %.2lf\n", customer.debt);
      getchar(); // Still don't know why this is needed but it's needed anyway
      found = 1;
      break; // Exit the loop once the customer is found
    }
  }

  fclose(file);

  return !found;
}

int list_customers()
{
  struct Customer customer;
  FILE *file;
  int i = 0;

  file = fopen("customers.dat", "r");

  if (file == NULL)
  {
    return -1;
  }

  while (fread(&customer, sizeof(struct Customer), 1, file) > 0)
  {
    printf("--------------------\n");
    printf("Customer %d:\n", ++i);
    printf("Id: %s\n", customer.id);
    printf("Store: %s\n", customer.store);
    printf("Debt: %.2lf\n", customer.debt);
  }

  fclose(file);

  if (i == 0)
    return 1; // Return 1 if no customers were found

  printf("--------------------\n");
  return 0; // Return 0 if customers were listed successfully
}
