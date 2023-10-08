#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/**
 * Function to handle Menu "Hitung Gaji"
 */
void menuSalary();
/**
 * Function to handle Menu "Hitung Gaji dan Lembur"
 */
void menuOvertime();
/**
 * Name must contains letters and spaces only
 * {char[]} name - String that u wanna check is it valid name or not
 * returns {bool} - True if valid and False if not valid
 */
bool isValidName(char str[]);
/**
 * Check is string is a string of number (positive / negative & integer / decimal)
 * {char[]} strNumber - String that u wanna check
 * returns {bool}
 */
bool isValidNumber(char str[], bool acceptNegative, bool acceptFloat);
/**
 * Check is valid phone number. Phone number must starts with 0 and minimum length is 11
 * {char[]} number = string that u wanna check
 * returns {bool}
 */
bool isValidPhoneNumber(char number[]);
/**
 * Function to clear the screen
 */
void clearscr()
{
#ifdef _WIN32
  system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || \
    (defined(__APPLE__) && defined(__MACH__))
  system("clear");
#else
#error "OS not supported."
#endif
}

typedef enum Group
{
  D1 = 1,
  D2,
  D3
} GROUP;

typedef struct Employee
{
  char nip[50];
  char name[50];
  char address[100];
  char phone[30];
  char position[50];
  GROUP group;
  char groupName[30];
  unsigned int salary;
  float overtimeHours;
  int overtimeFeePerHour;
  float totalOvertimeFee;

} EMPLOYEE;
int main()
{

  bool stillPlay = true;
  int menu = 0;
  while (stillPlay)
  {
    clearscr();
    printf("========================================\n");
    printf("PROGRAM HITUNG GAJI KARYAWAN\n");
    printf("========================================\n");

    printf("\nMenu:\n");
    printf("1. Hitung Gaji\n");
    printf("2. Hitung Gaji dan Lembur\n");
    printf("3. Keluar\n");

    while (true)
    {
      char input[20];
      printf("\nSilahkan pilih menu:");
      scanf("%s", input);
      getchar();

      // Check user input valid number
      if (isValidNumber(input, false, false))
      {
        // Convert input from string to integer
        menu = atoi(input);
        if (menu >= 1 && menu <= 3)
        {
          break;
        }
      }
      printf("Invalid input.\n");
    }

    switch (menu)
    {
    case 1:
      menuSalary();
      break;
    case 2:
      menuOvertime();
      break;
    case 3:
      stillPlay = false;
      printf("\nTerima kasih telah menggunakan program kami.\n");
      break;
    default:
      stillPlay = false;
      break;
    }
  }

  return 0;
}
void menuSalary()
{
  clearscr();
  printf("----------------------------------------\n");
  printf("Menu Hitung Gaji Karyawan\n");
  printf("----------------------------------------\n");

  EMPLOYEE employee;
  // Input nip
  while (true)
  {
    char input[50];
    printf("\nNip = ");
    scanf("%[^\n]s", input);
    getchar();
    // Check is user input is a valid number
    if (isValidNumber(input, false, false))
    {
      strcpy(employee.nip, input);
      break;
    }
    printf("Nip harus berisi angka yang valid\n");
  }

  // Input Name
  while (true)
  {
    char input[50];
    printf("Nama = ");
    scanf("%[^\n]s", input);
    getchar();
    // Check is user input is a valid name
    if (isValidName(input))
    {
      strcpy(employee.name, input);
      break;
    }
    printf("Nama hanya boleh berisi huruf dan spasi\n");
  }

  // Input address
  while (true)
  {

    char address[100] = "";
    printf("Alamat = ");
    scanf("%[^\n]s", address);
    getchar();

    // Address cannot be empty
    if (strlen(address) > 0)
    {

      strcpy(employee.address, address);
      break;
    }
    printf("Alamat tidak boleh kosong.\n");
  }

  // input phone number
  while (true)
  {
    char input[30];
    printf("No HP = ");
    scanf("%[^\n]s", input);
    getchar();
    // Check is user input is a valid phone number
    if (isValidPhoneNumber(input))
    {
      strcpy(employee.phone, input);
      break;
    }
    printf("No HP harus diawali dengan angka 0 dan minimal 11 karakter.\n");
  }

  // Input position
  while (true)
  {

    char position[50] = "";
    printf("Jabatan = ");
    scanf("%[^\n]s", position);
    getchar();
    if (strlen(position) > 0)
    {

      strcpy(employee.position, position);
      break;
    }
    printf("Jabatan tidak boleh kosong.\n");
  }

  // Input Group
  printf("\nDaftar golongan:\n");
  printf("1. Golongan D1\n");
  printf("2. Golongan D2\n");
  printf("3. Golongan D3\n");
  while (true)
  {
    char input[20] = "";
    printf("Golongan = ");
    scanf("%[^\n]s", input);
    getchar();
    if (isValidNumber(input, false, false))
    {
      int numberInput = atoi(input);
      if (numberInput >= D1 && numberInput <= D3)
      {
        employee.group = (GROUP)numberInput;
        switch (numberInput)
        {
        case D1:
          employee.salary = 2500000;
          strcpy(employee.groupName, "Golongan D1");
          break;
        case D2:
          strcpy(employee.groupName, "Golongan D2");
          employee.salary = 2000000;
          break;
        case 3:
          strcpy(employee.groupName, "Golongan D3");
          employee.salary = 1500000;
          break;
        }
        break;
      }
    }
    printf("Golongan harus 1, 2, atau 3 sesuai dengan list diatas\n");
  }

  printf("\nHasil perhitungan gaji:\n");
  printf("%-40s : %s\n", "NIP ( Nomor Induk Pegawai )", employee.nip);
  printf("%-40s : %s\n", "Nama", employee.name);
  printf("%-40s : %s\n", "Alamat", employee.address);
  printf("%-40s : %s\n", "Nomor Handphone", employee.phone);
  printf("%-40s : %s\n", "Jabatan", employee.position);
  printf("%-40s : %s\n", "Golongan", employee.groupName);
  printf("%-40s : Rp %d\n", "Gaji Pokok", employee.salary);

  printf("\nTekan enter untuk kembali ke menu utama...\n");
  while (getchar() != '\n')
  {
  }
}
void menuOvertime()
{
  clearscr();
  printf("----------------------------------------\n");
  printf("Menu Hitung Gaji dan Lembur Karyawan\n");
  printf("----------------------------------------\n");

  EMPLOYEE employee;
  // Input nip
  while (true)
  {
    char input[50];
    printf("\nNip = ");
    scanf("%[^\n]s", input);
    getchar();
    // Check is user input is a valid number
    if (isValidNumber(input, false, false))
    {
      strcpy(employee.nip, input);
      break;
    }
    printf("Nip harus berisi angka yang valid\n");
  }

  // Input Group
  printf("\nDaftar golongan:\n");
  printf("1. Golongan D1\n");
  printf("2. Golongan D2\n");
  printf("3. Golongan D3\n");
  while (true)
  {
    char input[20] = "";
    printf("Golongan = ");
    scanf("%[^\n]s", input);
    getchar();
    if (isValidNumber(input, false, false))
    {
      // Convert string to integer
      int numberInput = atoi(input);
      if (numberInput >= D1 && numberInput <= D3)
      {
        employee.group = (GROUP)numberInput;
        switch (numberInput)
        {
        case D1:
          employee.salary = 2500000;
          employee.overtimeFeePerHour = 10000;
          strcpy(employee.groupName, "Golongan D1");
          break;
        case D2:
          strcpy(employee.groupName, "Golongan D2");
          employee.overtimeFeePerHour = 5000;
          employee.salary = 2000000;
          break;
        case 3:
          strcpy(employee.groupName, "Golongan D3");
          employee.overtimeFeePerHour = 2500;
          employee.salary = 1500000;
          break;
        }
        break;
      }
    }
    printf("Golongan harus 1, 2, atau 3 sesuai dengan list diatas\n");
  }

  // Input Overtime
  while (true)
  {
    char input[20];
    printf("Lembur = ");
    scanf("%[^\n]s", input);
    getchar();
    // Check is user input is a valid number
    if (isValidNumber(input, false, true))
    {
      // Convert string to double/float
      float hours = atof(input);
      if (hours >= 0)
      {
        employee.overtimeHours = hours;
        employee.totalOvertimeFee = employee.overtimeFeePerHour * hours;
        break;
      }
    }
    printf("Total jam lembur harus angka dan lebih besar atau sama dengan 0.\n");
  }
  printf("\nHasil perhitungan gaji dan lembur:\n");
  printf("%-40s : %s\n", "NIP ( Nomor Induk Pegawai )", employee.nip);
  printf("%-40s : %s\n", "Golongan", employee.groupName);
  printf("%-40s : Rp %d\n", "Gaji Pokok", employee.salary);
  printf("%-40s : %.2f Jam\n", "Total Jam Lembur", employee.overtimeHours);
  printf("%-40s : Rp %d\n", "Upah Lembur per Jam", employee.overtimeFeePerHour);
  printf("%-40s : Rp %.2f\n", "Total Upah Lembur", employee.totalOvertimeFee);
  printf("%-40s : Rp %.2f\n", "Total Gaji + Upah Lembur", employee.totalOvertimeFee + employee.salary);

  printf("\nTekan enter untuk kembali ke menu utama...\n");
  while (getchar() != '\n')
  {
  }
}
bool isValidName(char str[])
{
  int len = strlen(str);

  // Index of characters 'A' at ASCII table
  int startIndexUpperCase = 65;
  // Index of characters 'Z' at ASCII table
  int endIndexUpperCase = 90;

  // Index of characters 'a' at ASCII table
  int startIndexLowerCase = 97;
  // Index of characters 'z' at ASCII table
  int endIndexLowerCase = 122;

  // Index of characters ' ' at ASCII table
  int indexSpace = 32;

  bool isValid = true;

  for (int i = 0; i < len; i++)
  {
    // Check is an uppercase letter
    bool isValidUpperCase = false;
    if (str[i] >= startIndexUpperCase && str[i] <= endIndexUpperCase)
    {
      isValidUpperCase = true;
    }
    // Check is an lowercase letter
    bool isValidLowerCase = false;
    if (str[i] >= startIndexLowerCase && str[i] <= endIndexLowerCase)
    {
      isValidLowerCase = true;
    }

    // Check is a space
    bool isABlankSpace = false;
    if (str[i] == indexSpace)
    {
      isABlankSpace = true;
    }

    if (!isValidUpperCase && !isValidLowerCase && !isABlankSpace)
    {
      isValid = false;
      break;
    }
  }
  return isValid;
}

bool isValidNumber(char str[], bool acceptNegative, bool acceptFloat)
{

  bool isValid = true;

  // index of character 0 in ASCII Table
  int startIndex = 48;
  // index of character 9 in ASCII Table
  int endIndex = 57;
  // index of character "-" in ASCII Table

  int indexDash = 45;
  // index of character "." in ASCII Table
  int indexDot = 46;

  int len = strlen(str);
  if (len == 0)
  {
    return false;
  }
  int totalDot = 0;
  for (int i = 0; i < len; i++)
  {
    if (acceptNegative)
    {
      // Only accept dash as the first character
      if (str[i] == indexDash && i == 0)
      {
        continue;
      }
    }
    if (acceptFloat)
    {
      // Only accept one dot and not at the last character
      if (str[i] == indexDot && i != 0 && i != len - 1 && totalDot == 0)
      {
        totalDot += 1;
        continue;
      }
    }
    // Only accept numbers
    if (!(str[i] >= startIndex && str[i] <= endIndex))
    {
      isValid = false;
      break;
    }
  }

  return isValid;
}

bool isValidPhoneNumber(char number[])
{
  bool isValidDigit = isValidNumber(number, false, false);
  bool isStartsWithZero = number[0] == '0' ? true : false;
  bool hasValidLength = false;

  int len = strlen(number);
  if (len >= 11)
  {
    hasValidLength = true;
  }

  // check is starts with zero and has length minimum 11 digits
  if (isValidDigit && isStartsWithZero && hasValidLength)
  {
    return true;
  }
  else
  {
    return false;
  }
}
