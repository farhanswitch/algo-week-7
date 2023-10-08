#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * Fungsi untuk membersihkan layar konsol berdasarkan sistem operasi.
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

/**
 * Fungsi untuk memeriksa apakah sebuah string adalah angka (positif/negatif & integer/decimal).
 * @param str - String yang ingin diperiksa.
 * @param acceptNegative - Apakah menerima angka negatif atau tidak.
 * @param acceptFloat - Apakah menerima angka desimal atau tidak.
 * @return true jika string adalah angka yang valid, false sebaliknya.
 */
bool isValidNumber(char str[], bool acceptNegative, bool acceptFloat);

/**
 * Fungsi untuk menghitung discount dan kupon undian belanja.
 */
void menuHitungBelanja();

int main()
{
    clearscr();
    bool programActive = true;
    int menu = 0;
    while (programActive)
    {
        clearscr();
        printf("========================================\n");
        printf("PROGRAM HITUNG DISCOUNT DAN UNDIAN BELANJA\n");
        printf("========================================\n");

        printf("\nMenu:\n");
        printf("1. Belanja\n");
        printf("2. Keluar\n");
        while (true)
        {
            char input[100];
            printf("\nSilahkan pilih menu:");
            scanf("%s", input);
            getchar();
            // Memeriksa apakah input pengguna adalah angka yang valid
            if (isValidNumber(input, false, false))
            {
                // Mengonversi input dari string ke integer
                menu = atoi(input);
                if (menu >= 1 && menu <= 2)
                {
                    break;
                }
            }
            printf("Input tidak valid.\n");
        }
        switch (menu)
        {
        case 1:
            menuHitungBelanja();
            getchar();
            break;

        case 2:
            programActive = false;
            printf("\nTerima kasih telah menggunakan program kami.\n");
            break;
        default:
            programActive = false;
            break;
        }
    }

    return 0;
}

void menuHitungBelanja()
{
    clearscr();

    double totalPembelian, totalBayar;
    int jumlahKupon = 0;

    printf("Selamat datang di Supermarket!\n");

    // Meminta pengguna memasukkan total pembelian dan memvalidasi input
    char input[100];
    while (true)
    {
        printf("Masukkan total pembelian Anda (Rp): ");
        scanf("%s", input);
        getchar();

        if (isValidNumber(input, false, true))
        {
            // Mengonversi input dari string ke double
            totalPembelian = atof(input);
            break;
        }
        printf("Input tidak valid. Masukkan angka yang benar.\n");
    }

    if (totalPembelian >= 100000.00)
    {
        // Menghitung diskon 10%
        totalBayar = totalPembelian * 0.90;
        // Menghitung jumlah kupon undian berdasarkan total pembelian setelah diskon
        jumlahKupon = (int)(totalBayar / 100000.00);

        // Menghitung potongan dalam bentuk rupiah
        double potongan = totalPembelian - totalBayar;

        printf("\nAnda mendapatkan diskon sebesar 10%% \n");
        printf("Potongan yang didapatkan: Rp %.2lf\n", potongan);
        printf("Total pembelian sebelum diskon: Rp %.2lf\n", totalPembelian);
        printf("Total pembelian setelah diskon: Rp %.2lf\n", totalBayar);
        printf("Anda mendapatkan %d kupon undian!\n", jumlahKupon);
    }
    else
    {
        totalBayar = totalPembelian;
        printf("Total pembelian Anda tidak memenuhi syarat untuk kupon undian.\n");
        printf("Total pembelian: Rp %.2lf\n", totalBayar);
    }

    printf("Terima kasih telah berbelanja di Supermarket kami!\n");
    printf("\nTekan enter untuk kembali ke menu awal..\n");
    while (getchar() != '\n')
    {
    }
}

bool isValidNumber(char str[], bool acceptNegative, bool acceptFloat)
{
    bool isValid = true;
    int startIndex = 0;
    int endIndex = strlen(str) - 1;
    int dotCount = 0;

    if (acceptNegative && str[startIndex] == '-')
    {
        startIndex = 1; // Mengabaikan tanda negatif jika diterima
    }

    for (int i = startIndex; i <= endIndex; i++)
    {
        if (str[i] == '.')
        {
            dotCount++;
            if (dotCount > 1 || !acceptFloat)
            {
                isValid = false;
                break;
            }
        }
        else if (str[i] < '0' || str[i] > '9')
        {
            isValid = false;
            break;
        }
    }

    return isValid;
}
