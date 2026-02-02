#include <locale.h>	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void Bisection();
void Regula_falsi();
void Newton_raphson();
void Inverse_matrix();
void Gauss_seidel();
void Sayisal_turev();
void Trapez();
void Cholesky_yontemi();
void Simpson();
void Gregory_newton_enterpolasyon();

double turev(char *str, double x);
double determinant(double **matrix, int n);
void inverse(double **matrix, double **inverse, int n);
double rakam(char *str, int *index);
double parantez(char *str, int *index);
double trig_log(char *str, int *index);
double kuvvet(char *str, int *index);
double carpma_bolme(char *str, int *index);
double toplama_cikarma(char *str, int *index);
void bosluk_sil(char *str);
double solution(char *str, double *x);
char *x_yerlestir(char *str, double *x);

typedef struct {
    double lowerlimit;
    double upperlimit;
    double mid;
    double lowersolution;
    double uppersolution;
    double midsolution;
    double epsilon;
} Data;

typedef struct {
    double lowerLimit;
    double xValue;
    double upperLimit;
    double lowerSolution;
    double upperSolution;
    double xSolution;
    double epsilon;
    double ileriFARK;
    double geriFARK;
    double merkeziFARK;
} dataSayisal;

typedef struct {
    double initialGuess;
    double previousGuess;
    double epsilon;
    double fx;
    double dfx;
} NewtonRaphsonData;

typedef struct {
    double lowerlimit;
    double upperlimit;
    double lowersolution;
    double uppersolution;
    double n;
    double h;
    double i;
    double total;
} SimpsonsData;

int main() {	
	setlocale(LC_ALL, "Turkish");
    int secim;
    printf("H O Þ  G E L D Ý N Ý Z\n");
    do {
        printf("\nLutfen bir yontem seciniz:\n\n");
        printf("1. Bisection \n");
        printf("2. Regula-Falsi\n");
        printf("3. Newton-Raphson\n");
        printf("4. Matrisin Tersini Al\n");
        printf("5. Cholesky (ALU ) Yöntemi\n");
        printf("6. Gauss-Seidel Yöntemi\n");
        printf("7. Sayýsal Türev\n");
        printf("8. Simpson Kuralý\n");
        printf("9. Trapez Yöntemi\n");
        printf("10. Gregory-Newton Enterpolasyonu\n");
        printf("0. çýkýç\nSeçiminiz: ");
        scanf("%d", &secim);
        getchar();
        switch (secim) {
            case 1:
                system("cls");
                Bisection();
                break;
            case 2:
                system("cls");
                Regula_falsi();
                break;
            case 3:
                system("cls");
                Newton_raphson();
                break;
            case 4:
                system("cls");
                Inverse_matrix();
                break;
            case 5:
                system("cls");
                Cholesky_yontemi();;
                break;
            case 6:
                system("cls");
                Gauss_seidel();
                break;
            case 7:
                system("cls");
                Sayisal_turev();
                break;
            case 8:
                system("cls");
                Simpson();
                break;
            case 9:
                system("cls");
                Trapez();
                break;
            case 10:
                system("cls");
                Gregory_newton_enterpolasyon();
                break;
            case 11:
                system("cls");
                Cholesky_yontemi();
                break;
            case 0:
                break;
            default:
                system("cls");
                printf("Geçersiz seçim! Lütfen tekrar deneyin.\n");
        }
    } while (secim != 0);
    return 0;
}

void Bisection() {
    char expr[300];
    Data *dat = (Data *)malloc(sizeof(Data));
    if (!dat) { printf("Bellek ayrýlamadý\n"); return; }
    printf("BISEKSIYON YONTEMI\n");
    printf("Bir fonksiyon giriniz (orn: x^6-7x+9, sin(x), log(x) vs.)\n");
    fgets(expr, sizeof(expr), stdin);
    printf("Alt siniri girin: ");
    scanf("%lf", &dat->lowerlimit);
    while(getchar() != '\n');
    printf("Ust siniri girin: ");
    scanf("%lf", &dat->upperlimit);
    while(getchar() != '\n');
    dat->lowersolution = solution(expr, &dat->lowerlimit);
    dat->uppersolution = solution(expr, &dat->upperlimit);
    while ((dat->lowerlimit >= dat->upperlimit) || (dat->uppersolution * dat->lowersolution > 0)) {
        if (dat->lowerlimit > dat->upperlimit) { printf("Alt sinir ust sinirdan buyuk olamaz.\n"); }
        else if (dat->lowerlimit == dat->upperlimit) { printf("Sinirlar birbirine esit olamaz.\n"); }
        else if (dat->uppersolution * dat->lowersolution > 0) { printf("Bu aralikta kok bulunmuyor.\n"); }
        printf("Alt siniri tekrar giriniz: ");
        scanf("%lf", &dat->lowerlimit);
        while(getchar() != '\n');
        printf("Ust siniri tekrar giriniz: ");
        scanf("%lf", &dat->upperlimit);
        while(getchar() != '\n');
        dat->lowersolution = solution(expr, &dat->lowerlimit);
        dat->uppersolution = solution(expr, &dat->upperlimit);
    }
    if (dat->uppersolution == 0 && dat->lowersolution == 0) {
        printf("%lf ve %lf fonksiyonun kokudur.\n", dat->upperlimit, dat->lowerlimit);
    } else if (dat->uppersolution == 0) {
        printf("%lf fonksiyonun kokudur.\n", dat->upperlimit);
    } else if (dat->lowersolution == 0) {
        printf("%lf fonksiyonun kokudur.\n", dat->lowerlimit);
    } else {
        printf("Bu aralikta bir kok mevcut.\n");
        printf("epsilon giriniz: ");
        scanf("%lf", &dat->epsilon);
        while(getchar() != '\n');
        int iter = 0;
        do {
            dat->mid = (dat->lowerlimit + dat->upperlimit) / 2.0;
            dat->midsolution = solution(expr, &dat->mid);
            iter++;
            printf("\n--- %d. Adim ---", iter);
            printf("\nAlt Sinir: %lf, f(alt): %lf", dat->lowerlimit, dat->lowersolution);
            printf("\nUst Sinir: %lf, f(ust): %lf", dat->upperlimit, dat->uppersolution);
            printf("\nOrta Nokta: %lf, f(orta): %lf\n", dat->mid, dat->midsolution);
            fflush(stdout);
            if (dat->midsolution * dat->lowersolution <= 0) {
                dat->upperlimit = dat->mid;
                dat->uppersolution = dat->midsolution;
            } else {
                dat->lowerlimit = dat->mid;
                dat->lowersolution = dat->midsolution;
            }
        } while (fabs(dat->midsolution) > dat->epsilon && iter < 10000);
        printf("\n Sonuc: %lf fonksiyonun kokudur.\n", dat->mid);
        fflush(stdout);
    }
    free(dat);
    printf("\nCikmak icin Enter'a basin...\n");
    getchar();
}

void Regula_falsi() {
    char expr[300];
    Data *dataPtr = (Data *)malloc(sizeof(Data));
    if (dataPtr == NULL) {
        printf("Hafýza ayrýlýrken hata oluþtu!\n");
        return;
    }
    printf("REGULA-FALSI (Doðrunun Kestiði Yöntem)\n");
    printf("Fonksiyonu giriniz (örn: x^3-2x+1, sin(x), log(x) vs.):\n");
    fgets(expr, sizeof(expr), stdin);
    printf("Alt sýnýrý girin: ");
    scanf("%lf", &dataPtr->lowerlimit);
    printf("Üst sýnýrý girin: ");
    scanf("%lf", &dataPtr->upperlimit);
    dataPtr->lowersolution = solution(expr, &dataPtr->lowerlimit);
    dataPtr->uppersolution = solution(expr, &dataPtr->upperlimit);
    while ((dataPtr->lowerlimit >= dataPtr->upperlimit) || (dataPtr->uppersolution * dataPtr->lowersolution > 0)) {
        if (dataPtr->lowerlimit > dataPtr->upperlimit) {
            printf("Alt sýnýr üst sýnýrdan büyük olamaz.\n");
        } else if (dataPtr->lowerlimit == dataPtr->upperlimit) {
            printf("Sýnýrlar eþit olamaz.\n");
        } else if (dataPtr->uppersolution * dataPtr->lowersolution > 0) {
            printf("Bu aralýkta kök yok.\n");
        }
        printf("Alt sýnýrý tekrar giriniz: ");
        scanf("%lf", &dataPtr->lowerlimit);
        printf("Üst sýnýrý tekrar giriniz: ");
        scanf("%lf", &dataPtr->upperlimit);
        dataPtr->lowersolution = solution(expr, &dataPtr->lowerlimit);
        dataPtr->uppersolution = solution(expr, &dataPtr->upperlimit);
    }
    if (dataPtr->uppersolution == 0 && dataPtr->lowersolution == 0) {
        printf("%lf ve %lf köktür.\n", dataPtr->upperlimit, dataPtr->lowerlimit);
    } else if (dataPtr->uppersolution == 0) {
        printf("%lf fonksiyonun köküdür.\n", dataPtr->upperlimit);
    } else if (dataPtr->lowersolution == 0) {
        printf("%lf fonksiyonun köküdür.\n", dataPtr->lowerlimit);
    } else {
        printf("Aralýkta bir kök var.\n");
        printf("Hassasiyet (epsilon) deðerini giriniz: ");
        scanf("%lf", &dataPtr->epsilon);
        int iter = 0;
        do {
            dataPtr->mid = ((dataPtr->lowersolution * dataPtr->upperlimit) - (dataPtr->uppersolution * dataPtr->lowerlimit))
                         / (dataPtr->lowersolution - dataPtr->uppersolution);
            dataPtr->midsolution = solution(expr, &dataPtr->mid);
            iter++;
            printf("\n%d. Adým:", iter);
            printf("\nAlt Sýnýr: %lf, f(alt): %lf", dataPtr->lowerlimit, dataPtr->lowersolution);
            printf("\nÜst Sýnýr: %lf, f(üst): %lf", dataPtr->upperlimit, dataPtr->uppersolution);
            printf("\nYeni Tahmin: %lf, f(yeni): %lf\n", dataPtr->mid, dataPtr->midsolution);
            if (dataPtr->midsolution * dataPtr->lowersolution <= 0) {
                dataPtr->upperlimit = dataPtr->mid;
                dataPtr->uppersolution = dataPtr->midsolution;
            } else {
                dataPtr->lowerlimit = dataPtr->mid;
                dataPtr->lowersolution = dataPtr->midsolution;
            }
        } while (fabs(dataPtr->midsolution) > dataPtr->epsilon && iter < 10000);
        printf("\nSonuç: %lf fonksiyonun köküdür.\n", dataPtr->mid);
    }
    free(dataPtr);
    getchar();
}

void Sayisal_turev() {
    char fonk[230];
    dataSayisal* diffData = (dataSayisal*)malloc(sizeof(dataSayisal));
    printf("SAYISAL TÜREV HESAPLAMA\n");
    printf("Fonksiyonu giriniz (örn: 2*x+5, x^3-2*x^2-3*x-15, sin(x), log(x), vs.):\n");
    fgets(fonk, sizeof(fonk), stdin);
    printf("Türev alýnacak x deðerini giriniz: ");
    scanf("%lf", &diffData->xValue);
    printf("Epsilon (adým) deðeri giriniz: ");
    scanf("%lf", &diffData->epsilon);
    diffData->lowerLimit  = diffData->xValue - diffData->epsilon;
    diffData->upperLimit  = diffData->xValue + diffData->epsilon;
    diffData->xSolution      = solution(fonk, &diffData->xValue);
    diffData->lowerSolution  = solution(fonk, &diffData->lowerLimit);
    diffData->upperSolution  = solution(fonk, &diffData->upperLimit);
    
    printf("\nEpsilon (adým) = %.8lf\n", diffData->epsilon);
    diffData->ileriFARK    = (diffData->upperSolution - diffData->xSolution) / diffData->epsilon;
    diffData->geriFARK     = (diffData->xSolution - diffData->lowerSolution) / diffData->epsilon;
    
    diffData->merkeziFARK  = (diffData->upperSolution - diffData->lowerSolution) / (2 * diffData->epsilon);
    printf("Merkezi Fark (Ortalama Türev): %.7lf\n", diffData->merkeziFARK);
    printf("Geri Fark  (Soldan Yaklaþým) : %.7lf\n", diffData->geriFARK);
    printf("Ýleri Fark (Saðdan Yaklaþým) : %.7lf\n", diffData->ileriFARK);
    free(diffData);
    getchar();
}

void Trapez() {
    char ifade[230];
    double altSinir, ustSinir, n, h, toplam, x;
    printf("TRAPEZ YÖNTEMÝ (Yaklaþýk Ýntegral Hesabý)\n");
    printf("Fonksiyon giriniz (örn: x^2+3, sin(x), log(x), vs.):\n");
    fgets(ifade, sizeof(ifade), stdin);
    printf("Alt sýnýr deðerini giriniz: ");
    scanf("%lf", &altSinir);
    printf("Üst sýnýr deðerini giriniz: ");
    scanf("%lf", &ustSinir);
    int ters = 1;
    if (ustSinir < altSinir) {
        double gecici = ustSinir;
        ustSinir = altSinir;
        altSinir = gecici;
        ters = -1;
    }
    double fAlt = solution(ifade, &altSinir);
    double fUst = solution(ifade, &ustSinir);
    printf("Bölme sayýsýný (n) giriniz: ");
    scanf("%lf", &n);
    h = (ustSinir - altSinir) / n;
    toplam = 0.0;
    x = altSinir + h;
    while (x < ustSinir) {
        toplam += solution(ifade, &x);
        x += h;
    }
    toplam += (fAlt + fUst) / 2.0;
    toplam *= h * ters;
    printf("Yaklaþýk integral sonucu: %.7lf\n", toplam);
    getchar();
}

double turev(char *fonk, double xDegeri) {
    double x1 = xDegeri;
    double x2 = xDegeri + 0.001;
    double fx1 = solution(fonk, &x1);
    double fx2 = solution(fonk, &x2);
    double sonuc = (fx2 - fx1) / 0.001;
    return sonuc;
}

void Newton_raphson() {
    NewtonRaphsonData *veri = (NewtonRaphsonData *)malloc(sizeof(NewtonRaphsonData));
    char fonk[230];
    printf("NEWTON-RAPHSON YÖNTEMÝ\n");
    printf("Kök aranan fonksiyonu giriniz (örn: x^3-3x+2, sin(x), log(x)):\n");
    fgets(fonk, sizeof(fonk), stdin);
    printf("Kök için baþlangýç tahminini giriniz: ");
    scanf("%lf", &veri->initialGuess);
    printf("Hassasiyet (epsilon) giriniz: ");
    scanf("%lf", &veri->epsilon);
    int adim = 0;
    do {
        veri->previousGuess = veri->initialGuess;
        veri->fx = solution(fonk, &veri->initialGuess);
        veri->dfx = turev(fonk, veri->initialGuess);
        if (veri->dfx != 0) {
            veri->initialGuess = veri->previousGuess - veri->fx / veri->dfx;
        }
        
        adim++;
        printf("%d. Adým:\n", adim);
        printf("Önceki tahmin: %.8lf\n", veri->previousGuess);
        printf("f(x): %.8lf\n", veri->fx);
        printf("f'(x): %.8lf\n", veri->dfx);
        printf("Yeni tahmin: %.8lf\n\n", veri->initialGuess);
    } while (fabs(veri->initialGuess - veri->previousGuess) > veri->epsilon && veri->dfx != 0);
    if (veri->dfx == 0) {
        printf("Türev sýfýrlandý, kök bulunamadý.\n");
    } else {
        printf("Bulunan kök: %.8lf\n", veri->initialGuess);
    }
    free(veri);
}

void Simpson() {
    char fonk[230];
    SimpsonsData *simpson = malloc(sizeof(SimpsonsData));
    int ters = 1;
    int i;
    int method;
    printf("SIMPSON YÖNTEMÝ (Yaklaþýk Ýntegral)\n");
    printf("Hangi yöntemi kullanmak istiyorsunuz?\n");
    printf("1. Simpson 1/3 Kuralý\n");
    printf("2. Simpson 3/8 Kuralý\n");
    printf("Seçiminiz (1 veya 2): ");
    scanf("%d", &method);
    getchar();
    printf("Fonksiyon giriniz (örn: x^2+5, sin(x), log(x)):\n");
    fgets(fonk, sizeof(fonk), stdin);
    printf("Alt sýnýrý giriniz: ");
    scanf("%lf", &simpson->lowerlimit);
    printf("Üst sýnýrý giriniz: ");
    scanf("%lf", &simpson->upperlimit);
    if (simpson->upperlimit < simpson->lowerlimit) {
        double gecici = simpson->upperlimit;
        simpson->upperlimit = simpson->lowerlimit;
        simpson->lowerlimit = gecici;
        ters = -1;
    }
    simpson->lowersolution = solution(fonk, &simpson->lowerlimit);
    simpson->uppersolution = solution(fonk, &simpson->upperlimit);
    if (method == 1) {
        printf("n deðerini giriniz (çift olmalý!): ");
        scanf("%lf", &simpson->n);
        if (((int)simpson->n) % 2 != 0) {
            printf("n çift olmalý!\n");
            free(simpson);
            return;
        }
        simpson->h = (simpson->upperlimit - simpson->lowerlimit) / simpson->n;
        simpson->total = simpson->lowersolution + simpson->uppersolution;
        for (i = 1; i < (int)simpson->n; i++) {
            simpson->i = simpson->lowerlimit + i * simpson->h;
            if (i % 2 == 0)
                simpson->total += 2.0 * solution(fonk, &simpson->i);
            else
                simpson->total += 4.0 * solution(fonk, &simpson->i);
        }
        simpson->total = (simpson->total * (simpson->h / 3.0)) * ters;
        printf("Simpson 1/3 ile yaklaþýk integral sonucu: %.8lf\n", simpson->total);
    } else if (method == 2) {
        printf("n deðerini giriniz (3'ün katý olmalý!): ");
        scanf("%lf", &simpson->n);
        if (((int)simpson->n) % 3 != 0) {
            printf("n 3'ün katý olmalý!\n");
            free(simpson);
            return;
        }
        simpson->h = (simpson->upperlimit - simpson->lowerlimit) / simpson->n;
        simpson->total = simpson->lowersolution + simpson->uppersolution;
        for (i = 1; i < (int)simpson->n; i++) {
            simpson->i = simpson->lowerlimit + i * simpson->h;
            if (i % 3 == 0)
                simpson->total += 2.0 * solution(fonk, &simpson->i);
            else
                simpson->total += 3.0 * solution(fonk, &simpson->i);
        }
        simpson->total = (simpson->total * (3.0 * simpson->h / 8.0)) * ters;
        printf("Simpson 3/8 ile yaklaþýk integral sonucu: %.8lf\n", simpson->total);
    } else {
        printf("Geçersiz seçim!\n");
    }
    getchar();
    free(simpson);
}

void Gregory_newton_enterpolasyon() {
    int n, i, j;
    double *X, *Y, arananX, toplam, h, carpim;
    double **farkTablosu;
    printf("GREGORY-NEWTON ENTERPOLASYON\n");
    printf("Kaç tane (x, y) çifti gireceksiniz?\n");
    scanf("%d", &n);
    X = (double *)malloc(n * sizeof(double));
    Y = (double *)malloc(n * sizeof(double));
    farkTablosu = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        farkTablosu[i] = (double *)malloc(n * sizeof(double));
    }
    printf("Sýrayla x ve y deðerlerini girin:\n");
    for (i = 0; i < n; i++) {
        printf("%d. (x, y): ", i + 1);
        scanf("%lf %lf", &X[i], &Y[i]);
    }
    printf("f(x) deðerini bulmak istediðiniz x deðerini girin: ");
    scanf("%lf", &arananX);
    for (i = 0; i < n; i++) {
        farkTablosu[i][0] = Y[i];
    }
    for (j = 1; j < n; j++) {
        for (i = 0; i < n - j; i++) {
            farkTablosu[i][j] = farkTablosu[i + 1][j - 1] - farkTablosu[i][j - 1];
        }
    }
    printf("\nFark Tablosu:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            printf("%.6lf\t", farkTablosu[i][j]);
        }
        printf("\n");
    }
    h = X[1] - X[0];
    printf("\nh = %.6lf\n", h);
    toplam = Y[0];
    carpim = 1.0;
    for (i = 1; i < n; i++) {
        carpim *= (arananX - X[i - 1]) / (h * i);
        toplam += carpim * farkTablosu[0][i];
    }
    printf("Sonuç: f(%.3lf) = %.8lf\n", arananX, toplam);
    free(X);
    free(Y);
    for (i = 0; i < n; i++) {
        free(farkTablosu[i]);
    }
    free(farkTablosu);
    getchar();
}

void Inverse_matrix() {
    int boyut, satir, sutun;
    double **matris, **tersMatris, det;
    printf("MATRÝSÝN TERSÝNÝ BULMA\n");
    printf("Matrisin boyutunu giriniz: ");
    scanf("%d", &boyut);
    matris = (double **)malloc(boyut * sizeof(double *));
    tersMatris = (double **)malloc(boyut * sizeof(double *));
    for (satir = 0; satir < boyut; satir++) {
        matris[satir] = (double *)malloc(boyut * sizeof(double));
        tersMatris[satir] = (double *)malloc(boyut * sizeof(double));
    }
    for (satir = 0; satir < boyut; satir++) {
        for (sutun = 0; sutun < boyut; sutun++) {
            printf("%d. satýr, %d. sütun elemanýný giriniz: ", satir + 1, sutun + 1);
            scanf("%lf", &matris[satir][sutun]);
        }
    }
    printf("Girdiðiniz Matris:\n");
    for (satir = 0; satir < boyut; satir++) {
        for (sutun = 0; sutun < boyut; sutun++) {
            printf("%.5lf ", matris[satir][sutun]);
        }
        printf("\n");
    }
    det = determinant(matris, boyut);
    printf("Determinant: %.8lf\n", det);
    if (det != 0.0) {
        inverse(matris, tersMatris, boyut);
        printf("Matrisin Tersi:\n");
        for (satir = 0; satir < boyut; satir++) {
            for (sutun = 0; sutun < boyut; sutun++) {
                printf("%.8lf ", tersMatris[satir][sutun]);
            }
            printf("\n");
        }
    } else {
        printf("Girilen matrisin tersi yoktur (determinant sýfýr).\n");
    }
    for (satir = 0; satir < boyut; satir++) {
        free(matris[satir]);
        free(tersMatris[satir]);
    }
    free(matris);
    free(tersMatris);
}

double determinant(double **matris, int boyut) {
    double detSonuc = 0.0;
    int i, j, x;
    if (boyut == 1) {
        return matris[0][0];
    } else if (boyut == 2) {
        return matris[0][0] * matris[1][1] - matris[0][1] * matris[1][0];
    } else {
        double **altMatris = (double **)malloc((boyut - 1) * sizeof(double *));
        for (i = 0; i < boyut - 1; i++)
            altMatris[i] = (double *)malloc((boyut - 1) * sizeof(double));
        for (x = 0; x < boyut; x++) {
            int altSatir = 0;
            for (i = 1; i < boyut; i++) {
                int altSutun = 0;
                for (j = 0; j < boyut; j++) {
                    if (j != x) {
                        altMatris[altSatir][altSutun] = matris[i][j];
                        altSutun++;
                    }
                }
                altSatir++;
            }
            detSonuc += pow(-1, x) * matris[0][x] * determinant(altMatris, boyut - 1);
        }
        for (i = 0; i < boyut - 1; i++)
            free(altMatris[i]);
        free(altMatris);
    }
    return detSonuc;
}

void inverse(double **matris, double **ters, int boyut) {
    double det = determinant(matris, boyut);
    if (boyut == 1) {
        ters[0][0] = 1.0 / matris[0][0];
        return;
    }
    double **kofak = (double **)malloc(boyut * sizeof(double *));
    int i, j, k, x, y;
    for (i = 0; i < boyut; i++)
        kofak[i] = (double *)malloc(boyut * sizeof(double));
    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            double **altMatris = (double **)malloc((boyut - 1) * sizeof(double *));
            for (k = 0; k < boyut - 1; k++)
                altMatris[k] = (double *)malloc((boyut - 1) * sizeof(double));
            int altSatir = 0;
            for (x = 0; x < boyut; x++) {
                if (x != i) {
                    int altSutun = 0;
                    for (y = 0; y < boyut; y++) {
                        if (y != j) {
                            altMatris[altSatir][altSutun] = matris[x][y];
                            altSutun++;
                        }
                    }
                    altSatir++;
                }
            }
            kofak[i][j] = pow(-1, i + j) * determinant(altMatris, boyut - 1);
            for (k = 0; k < boyut - 1; k++)
                free(altMatris[k]);
            free(altMatris);
        }
    }
    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            ters[j][i] = kofak[i][j] / det;
        }
    }
    for (i = 0; i < boyut; i++)
        free(kofak[i]);
    free(kofak);
}

void Cholesky_yontemi() {
    int n, i, j, k;
    printf("CHOLESKY (ALU) YÖNTEMÝ\n");
    printf("Denklem sisteminin boyutunu giriniz (n x n): ");
    scanf("%d", &n);
    double **A = (double **)malloc(n * sizeof(double *));
    double *b = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));
    double **L = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)calloc(n, sizeof(double));
    }
    printf("Matris A'nýn elemanlarýný satýr satýr giriniz:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &A[i][j]);
        }
    }
    printf("Sað taraf vektörü b'nin elemanlarýný giriniz:\n");
    for (i = 0; i < n; i++) {
        printf("b[%d]: ", i + 1);
        scanf("%lf", &b[i]);
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            double toplam = 0.0;
            for (k = 0; k < j; k++)
                toplam += L[i][k] * L[j][k];
            if (i == j)
                L[i][j] = sqrt(A[i][i] - toplam);
            else
                L[i][j] = (A[i][j] - toplam) / L[j][j];
        }
    }
    for (i = 0; i < n; i++) {
        double toplam = 0.0;
        for (k = 0; k < i; k++)
            toplam += L[i][k] * y[k];
        y[i] = (b[i] - toplam) / L[i][i];
    }
    for (i = n - 1; i >= 0; i--) {
        double toplam = 0.0;
        for (k = i + 1; k < n; k++)
            toplam += L[k][i] * x[k];
        x[i] = (y[i] - toplam) / L[i][i];
    }
    printf("\nÇözüm vektörü x:\n");
    for (i = 0; i < n; i++)
        printf("x%d = %.8lf\n", i + 1, x[i]);
    for (i = 0; i < n; i++) {
        free(A[i]);
        free(L[i]);
    }
    free(A);
    free(L);
    free(b);
    free(y);
    free(x);
}

void Gauss_seidel() {
    int i, j, k, n, iterasyon = 0;
    double **A, *x_guncel, *x_onceki, hata, toplam, fark;
    int kullaniciGirisi = 0;
    printf("GAUSS-SEIDEL YÖNTEMÝ\n");
    printf("Kaç bilinmeyenli denklem sistemi çözeceksiniz? ");
    scanf("%d", &n);
    A = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
        A[i] = (double *)malloc((n + 1) * sizeof(double));
    x_guncel = (double *)malloc(n * sizeof(double));
    x_onceki = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++) {
        printf("%d. denklemin katsayýlarýný ve sonucu giriniz:\n", i + 1);
        for (j = 0; j < n; j++) {
            printf("x%d katsayýsý: ", j + 1);
            scanf("%lf", &A[i][j]);
        }
        printf("Sonuç: ");
        scanf("%lf", &A[i][n]);
    }
    printf("Hata (epsilon) deðerini giriniz: ");
    scanf("%lf", &hata);
    printf("Baþlangýç deðerlerini elle girmek için 1 yazýn, otomatik sýfýrdan baþlamak için baþka bir deðer girin: ");
    scanf("%d", &kullaniciGirisi);
    if (kullaniciGirisi == 1) {
        for (i = 0; i < n; i++) {
            printf("x%d için baþlangýç deðeri: ", i + 1);
            scanf("%lf", &x_guncel[i]);
        }
    } else {
        for (i = 0; i < n; i++)
            x_guncel[i] = 0.0;
    }
    for (i = 0; i < n; i++)
        x_onceki[i] = x_guncel[i];
    do {
        for (i = 0; i < n; i++) {
            toplam = A[i][n];
            for (j = 0; j < n; j++) {
                if (j != i) {
                    toplam -= A[i][j] * x_guncel[j];
                }
            }
            x_onceki[i] = x_guncel[i];
            x_guncel[i] = toplam / A[i][i];
        }
        iterasyon++;
        printf("---- %d. iterasyon sonuçlarý ----\n", iterasyon);
        for (i = 0; i < n; i++) {
            printf("x%d = %.8lf\n", i + 1, x_guncel[i]);
        }
        fark = 0.0;
        for (i = 0; i < n; i++) {
            if (fabs(x_guncel[i] - x_onceki[i]) > fark)
                fark = fabs(x_guncel[i] - x_onceki[i]);
        }
    } while (fark > hata);
    printf("\nSon çözüm:\n");
    for (i = 0; i < n; i++) {
        printf("x%d = %.8lf\n", i + 1, x_guncel[i]);
    }
    for (i = 0; i < n; i++) free(A[i]);
    free(A);
    free(x_guncel);
    free(x_onceki);
}

double solution(char *ifade, double *xDeger) {
    int pos = 0;
    int i = 0;
    bosluk_sil(ifade);
    char *duzenli = x_yerlestir(ifade, xDeger);
    bosluk_sil(duzenli);
    double sonuc = 0.0;
    char sonucBuf[100];
    char oncekiBuf[100];
    char *tempStr = (char *)malloc(strlen(duzenli) + 1);
    strcpy(tempStr, duzenli);
    while ((int)strlen(duzenli) > i) {
        pos = 0;
        sonuc = toplama_cikarma(tempStr, &pos);
        gcvt(sonuc, 6, sonucBuf);
        if (i <= 0) {
            i += pos;
        } else {
            i += pos - (int)strlen(oncekiBuf);
        }
        char *kisaTemp = tempStr + pos;
        strcat(sonucBuf, kisaTemp);
        strcpy(tempStr, sonucBuf);
        gcvt(sonuc, 6, oncekiBuf);
    }
    free(tempStr);
    free(duzenli);
    return sonuc;
}

void bosluk_sil(char* str) {
    char* ok = str;
    char* yaz = str;
    while (*ok != '\0') {
        if (!isspace(*ok)) {
            *yaz = *ok;
            yaz++;
        }
        ok++;
    }
    *yaz = '\0';
}

char *x_yerlestir(char *giris, double *xDeger) {
    char *cikis = (char*)malloc(250 * sizeof(char));
    char *oku = giris;
    char *yaz = cikis;
    while (*oku != '\0') {
        if (*oku == 'x' || *oku == 'X') {
            if (oku != giris && isdigit(*(oku - 1))) {
                yaz += sprintf(yaz, "*%.15lf", *xDeger);
            } else {
                yaz += sprintf(yaz, "%.15lf", *xDeger);
            }
            oku++;
        } else {
            *yaz++ = *oku++;
        }
    }
    *yaz = '\0';
    return cikis;
}

double rakam(char *str, int *pos) {
    char *ptr = str + *pos;
    double sayi = strtof(ptr, &ptr);
    int ilerleme = ptr - (str + *pos);
    if (ptr[0] == 'd' && ptr[1] == 'e' && ptr[2] == 'g') {
        sayi = round(sayi * M_PI / 180.0 * 1000000) / 1000000;
        ilerleme += 3;
    }
    else if (!isdigit(ptr[0]) && ptr[0] != '^' && ptr[0] != '*' && ptr[0] != '/' &&
             ptr[0] != '+' && ptr[0] != '-' && ptr[0] != ')' && ptr[0] != '}' &&
             ptr[0] != ']' && ptr[0] != '(' && ptr[0] != '{' && ptr[0] != '[' &&
             ptr[0] != '\0') {
        int ileri = 0;
        while (!isdigit(ptr[ileri]) && ptr[ileri] != '^' && ptr[ileri] != '*' && ptr[ileri] != '/' &&
               ptr[ileri] != '+' && ptr[ileri] != '-' && ptr[ileri] != ')' && ptr[ileri] != '}' &&
               ptr[ileri] != ']' && ptr[ileri] != '(' && ptr[ileri] != '{' && ptr[ileri] != '[' &&
               ptr[ileri] != '\0') {
            ileri++;
        }
        sayi = 0;
        printf("\nBilinmeyen ifade!\n");
        ilerleme += ileri;
    }
    *pos += ilerleme;
    return sayi;
}

double toplama_cikarma(char *str, int *pos) {
    double sonuc = carpma_bolme(str, pos);
    while (str[*pos] == '+' || str[*pos] == '-') {
        char islem = str[*pos];
        (*pos)++;
        double terim = carpma_bolme(str, pos);
        if (islem == '-') {
            sonuc -= terim;
        } else {
            sonuc += terim;
        }
    }
    return sonuc;
}

double carpma_bolme(char *str, int *pos) {
    double sonuc = kuvvet(str, pos);
    while (str[*pos] == '*' || str[*pos] == '/') {
        char islem = str[*pos];
        (*pos)++;
        double terim = kuvvet(str, pos);
        if (islem == '*') {
            sonuc *= terim;
        } else {
            sonuc /= terim;
        }
    }
    return sonuc;
}

double kuvvet(char *str, int *pos) {
    double taban = trig_log(str, pos);
    while (str[*pos] == '^') {
        (*pos)++;
        double us = trig_log(str, pos);
        if (taban < 0 && ((int)us) % 2 == 0) {
            taban = -pow(taban, us);
        } else {
            taban = pow(taban, us);
        }
    }
    return taban;
}

double parantez(char *str, int *pos) {
    int par_say = 0;
    char altStr[300];
    strcpy(altStr, str + *pos);
    int i, bitis = 0;
    for (i = 0; altStr[i] != '\0'; i++) {
        if (altStr[i] == '(' || altStr[i] == '[' || altStr[i] == '{') par_say++;
        if ((altStr[i] == ')' || altStr[i] == ']' || altStr[i] == '}') && par_say > 0) par_say--;
        else if ((altStr[i] == ')' || altStr[i] == ']' || altStr[i] == '}') && par_say == 0) {
            altStr[i] = '\0';
        }
    }
    double sonuc = toplama_cikarma(altStr, &bitis);
    *pos += bitis;
    return sonuc;
}

double trig_log(char *str, int *pos) {
    if (str[*pos] == '(' || str[*pos] == '[' || str[*pos] == '{') {
        (*pos)++;
        double s = parantez(str, pos);
        (*pos)++;
        return s;
    }
    if ((str[*pos] == 'p' || str[*pos] == 'P') && (str[*pos+1] == 'i' || str[*pos+1] == 'I')) {
        *pos += 2;
        return M_PI;
    }
    if (str[*pos] == 'e') {
        (*pos)++;
        return M_E;
    }
    char *p = str + *pos;
    double icDeger = 0.0;
    if (!strncmp(p, "cos", 3) && p[3] == '(') {
        *pos += 4;
        icDeger = parantez(str, pos); (*pos)++;
        return cos(icDeger);
    }
    if (!strncmp(p, "sin", 3) && p[3] == '(') {
        *pos += 4;
        icDeger = parantez(str, pos); (*pos)++;
        return sin(icDeger);
    }
    if (!strncmp(p, "cot", 3) && p[3] == '(') {
        *pos += 4;
        icDeger = parantez(str, pos); (*pos)++;
        return 1.0 / tan(icDeger);
    }
    if (!strncmp(p, "tan", 3) && p[3] == '(') {
        *pos += 4;
        icDeger = parantez(str, pos); (*pos)++;
        return tan(icDeger);
    }
    if (!strncmp(p, "arccos", 6) && p[6] == '(') {
        *pos += 7;
        icDeger = parantez(str, pos); (*pos)++;
        return acos(icDeger);
    }
    if (!strncmp(p, "arcsin", 6) && p[6] == '(') {
        *pos += 7;
        icDeger = parantez(str, pos); (*pos)++;
        return asin(icDeger);
    }
    if (!strncmp(p, "arccot", 6) && p[6] == '(') {
        *pos += 7;
        icDeger = parantez(str, pos); (*pos)++;
        return atan(icDeger) / icDeger;
    }
    if (!strncmp(p, "arctan", 6) && p[6] == '(') {
        *pos += 7;
        icDeger = parantez(str, pos); (*pos)++;
        return atan(icDeger);
    }
    if (!strncmp(p, "log", 3)) {
        *pos += 3;
        if (p[3] == '(') {
            (*pos)++;
            icDeger = parantez(str, pos); (*pos)++;
            return log10(icDeger);
        } else {
            double taban = toplama_cikarma(str, pos);
            if ((int)taban != 0 && str[*pos] == '(') {
                (*pos)++;
                icDeger = parantez(str, pos); (*pos)++;
                return log(icDeger) / log(taban);
            } else if (str[*pos] == '(') {
                (*pos)++;
                icDeger = parantez(str, pos); (*pos)++;
                return log10(icDeger);
            }
        }
    }
    if (!strncmp(p, "ln", 2) && p[2] == '(') {
        *pos += 3;
        icDeger = parantez(str, pos); (*pos)++;
        return log(icDeger);
    }
    return rakam(str, pos);
}
