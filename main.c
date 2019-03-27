#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct pixel {
    unsigned int R;
    unsigned int G;
    unsigned int B;
};


struct detectii {
    unsigned int x, y, val;
    float corelatie;
    struct pixel nrculoare;
};

void xorshift32(unsigned int seed, unsigned int n, unsigned int **R) {
    unsigned int r, i;
    r = seed;
    for (i = 1; i < n; i++) {
        r = r ^ r << 13;
        r = r ^ r >> 17;
        r = r ^ r << 5;
        (*R)[i] = r;
    }
}

struct pixel **salvam_img_intern(char *filename) {
    FILE *fin = fopen(filename, "rb");
    int i, j;
    if (!fin) {
        printf("eroare la deschidere");
        return 0;
    }
    unsigned int latime_img, inaltime_img;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    fseek(fin, 54, SEEK_SET);
    struct pixel **a = (struct pixel **) malloc(sizeof(struct pixel *) * inaltime_img);
    for (i = 0; i < inaltime_img; i++)
        a[i] = malloc(sizeof(struct pixel) * latime_img);
    int padding;
    if (latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;
    for (i = 0; i < inaltime_img; i++) {
        fseek(fin, 54 + (latime_img * 3 + padding) * (i), SEEK_SET);
        for (j = 0; j < latime_img; j++) {
            fread(&(a[i][j].B), 1, 1, fin);
            fread(&(a[i][j].G), 1, 1, fin);
            fread(&(a[i][j].R), 1, 1, fin);
        }
    }
    fclose(fin);
    return a;

}

struct pixel **salvam_img_extern(char *imagine, char *img_afisare, struct pixel **a) {
    FILE *fin = fopen(imagine, "rb");
    FILE *fout = fopen(img_afisare, "wb");
    int i, j;
    if (!fin) {
        printf("eroare la deschidere");
        return 0;
    }
    if (!fout) {
        printf("eroare la deschidere");
        return 0;
    }
    unsigned int latime_img, inaltime_img;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);

    int k = 0, x = 0;
    fseek(fin, 0, SEEK_SET);
    for (i = 0; i < 54; i++) {
        fread(&k, 1, 1, fin);
        fwrite(&k, 1, 1, fout);
    }

    int padding;
    k = 0;
    if (latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;

    for (i = 0; i < inaltime_img; i++) {
        for (j = 0; j < latime_img; j++) {
            fwrite(&(a[i][j].B), 1, 1, fout);
            fwrite(&(a[i][j].G), 1, 1, fout);
            fwrite(&(a[i][j].R), 1, 1, fout);
        }
        for (k = 0; k < padding; k++)
            fwrite(&x, 1, 1, fout);
    }
    fclose(fin);
    fclose(fout);
    free(a);
    for (i = 0; i < inaltime_img; i++)
        free(a[i]);
}


int **liniarizare_grayscale(char *filename) {
    FILE *fin = fopen(filename, "rb");
    int i, j;
    if (!fin) {
        printf("eroare");
        return 0;
    }
    unsigned int latime_img, inaltime_img;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    fseek(fin, 54, SEEK_SET);
    int **a = (int **) malloc(sizeof(int *) * inaltime_img);
    for (i = 0; i < inaltime_img; i++)
        a[i] = malloc(sizeof(int) * latime_img);
    int padding;
    if (latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;
    unsigned char x;
    for (i = 0; i < inaltime_img; i++) {
        fseek(fin, 54 + (latime_img * 3 + padding) * (i), SEEK_SET);
        for (j = 0; j < latime_img; j++) {
            fread(&(x), 1, 1, fin);
            fread(&(x), 1, 1, fin);
            fread(&(x), 1, 1, fin);
            a[i][j] = x;
        }
    }
    fclose(fin);
    return a;

}

struct pixel *liniarizare_intern(char *filename) {
    FILE *fin = fopen(filename, "rb");
    int i, j;
    if (!fin) {
        printf("eroare4");
        return 0;
    }
    unsigned int latime_img, inaltime_img;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    int padding;
    if (latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;
    struct pixel *linia = malloc(sizeof(struct pixel) * inaltime_img * latime_img);
    for (i = 0; i < inaltime_img; i++) {
        fseek(fin, 54 + (latime_img * 3 + padding) * (inaltime_img - 1 - i), SEEK_SET);
        for (j = 0; j < latime_img; j++) {
            fread(&(linia[i * latime_img + j].B), 1, 1, fin);
            fread(&(linia[i * latime_img + j].G), 1, 1, fin);
            fread(&(linia[i * latime_img + j].R), 1, 1, fin);
        }
    }

    fclose(fin);
    return linia;
}

struct pixel *liniarizare_extern(char *imagine, char *img_afisare, struct pixel *a) {
    FILE *fin = fopen(imagine, "rb");
    FILE *fout = fopen(img_afisare, "wb");
    int i, j, x = 0;
    if (!fin) {
        printf("eroare la deschidere");
        return 0;
    }
    if (!fout) {
        printf("eroare la deschidere");
        return 0;
    }
    unsigned int latime_img, inaltime_img;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);

    int k = 0;
    fseek(fin, 0, SEEK_SET);
    for (i = 0; i < 54; i++) {
        fread(&k, 1, 1, fin);
        fwrite(&k, 1, 1, fout);
    }

    int padding;
    k = 0;
    if (latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;

    for (i = 0; i < inaltime_img; i++) {
        for (j = 0; j < latime_img; j++) {
            fwrite(&(a[(inaltime_img - i - 1) * latime_img + j].B), 1, 1, fout);
            fwrite(&(a[(inaltime_img - i - 1) * latime_img + j].G), 1, 1, fout);
            fwrite(&(a[(inaltime_img - i - 1) * latime_img + j].R), 1, 1, fout);
        }
        for (k = 0; k < padding; k++)
            fwrite(&x, 1, 1, fout);
    }
    fclose(fin);
    fclose(fout);
    free(a);
}

struct pixel XOR(struct pixel x, unsigned int i) {
    struct pixel p;
    unsigned char *c;
    c = &i;
    p.B = (*c) ^ x.B;
    c++;
    p.G = (*c) ^ x.G;
    c++;
    p.R = (*c) ^ x.R;
    return p;
}

void criptare(char *filenamei, char *filenameo, char *secret) {
    FILE *fin, *fout, *key;
    fin = fopen(filenamei, "rb");
    fout = fopen(filenameo, "wb");
    key = fopen(secret, "r");
    if (!fin) {
        printf("eroare1");
        return NULL;
    }
    if (!fout) {
        printf("eroare2");
        return NULL;
    }
    if (!key) {
        printf("eroare3");
        return NULL;
    }
    unsigned int latime_img, inaltime_img, x;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    fscanf(key, "%u", &x);
    unsigned int i, j, k, r, sv;
    struct pixel *li, *lo;
    unsigned int *permutare = malloc(sizeof(unsigned int) * inaltime_img * latime_img);
    for (i = 0; i < latime_img * inaltime_img; i++)
        permutare[i] = i + 1;
    unsigned int *R = (unsigned int *) calloc(2 * latime_img * inaltime_img - 1, sizeof(unsigned int));
    R[0] = x;
    xorshift32(x, 2 * latime_img * inaltime_img - 1, &R);
    li = malloc(sizeof(struct pixel) * inaltime_img * latime_img);
    lo = malloc(sizeof(struct pixel) * inaltime_img * latime_img);
    li = liniarizare_intern(filenamei);
    unsigned int n = latime_img * inaltime_img;
    for (i = n - 1; i > 0; i--) {
        r = R[n - i] % (i + 1);
        k = permutare[r];
        permutare[r] = permutare[i];
        permutare[i] = k;
    }
    for (i = 0; i < inaltime_img; i++)
        for (j = 0; j < latime_img; j++) {
            lo[permutare[i * latime_img + j] - 1].B = li[i * latime_img + j].B;
            lo[permutare[i * latime_img + j] - 1].G = li[i * latime_img + j].G;
            lo[permutare[i * latime_img + j] - 1].R = li[i * latime_img + j].R;
        }

    fscanf(key, "%u", &sv);
    lo[0] = XOR(lo[0], sv);
    lo[0] = XOR(lo[0], R[n]);
    n++;
    for (i = 1; i < inaltime_img * latime_img; i++) {
        lo[i].B = lo[i - 1].B ^ lo[i].B;
        lo[i].G = lo[i - 1].G ^ lo[i].G;
        lo[i].R = lo[i - 1].R ^ lo[i].R;
        lo[i] = XOR(lo[i], R[n]);
        n++;
    }
    liniarizare_extern(filenamei, filenameo, lo);

}

void decriptare(char *filenamei, char *filenameo, char *secret) {
    FILE *fin, *fout, *key;
    fin = fopen(filenamei, "rb");
    fout = fopen(filenameo, "wb");
    key = fopen(secret, "r");
    if (!fin) {
        printf("eroare la deschidere");
        return NULL;
    }
    if (!fout) {
        printf("eroare la deschidere");
        return NULL;
    }
    if (!key) {
        printf("eroare la deschidere");
        return NULL;
    }
    unsigned int latime_img, inaltime_img, x, sv;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    fscanf(key, "%u", &x);
    unsigned int *R = (unsigned int *) calloc(2 * latime_img * inaltime_img - 1, sizeof(unsigned int));
    R[0] = x;
    xorshift32(x, 2 * latime_img * inaltime_img - 1, &R);
    unsigned int i, j, k, r;
    struct pixel *li, *lo;
    unsigned int *permutare = malloc(sizeof(unsigned int) * inaltime_img * latime_img);
    unsigned int *inversapermutare = malloc(sizeof(unsigned int) * inaltime_img * latime_img);
    for (i = 0; i < latime_img * inaltime_img; i++)
        permutare[i] = i + 1;
    li = malloc(sizeof(struct pixel) * inaltime_img * latime_img);
    lo = malloc(sizeof(struct pixel) * inaltime_img * latime_img);
    li = liniarizare_intern(filenamei);
    unsigned int n = latime_img * inaltime_img;
    for (i = n - 1; i > 0; i--) {
        r = R[n - i] % (i + 1);
        k = permutare[r];
        permutare[r] = permutare[i];
        permutare[i] = k;
    }
    for (i = 0; i < latime_img * inaltime_img; i++)
        inversapermutare[permutare[i] - 1] = i + 1;

    n = 2 * latime_img * inaltime_img - 1;


    for (i = latime_img * inaltime_img - 1; i >= 1; i--) {
        li[i].B = li[i - 1].B ^ li[i].B;
        li[i].G = li[i - 1].G ^ li[i].G;
        li[i].R = li[i - 1].R ^ li[i].R;
        li[i] = XOR(li[i], R[n]);
        n--;
    }

    fscanf(key, "%u", &sv);
    li[0] = XOR(li[0], sv);
    li[0] = XOR(li[0], R[n]);

    for (i = 0; i < inaltime_img; i++)
        for (j = 0; j < latime_img; j++) {
            lo[inversapermutare[i * latime_img + j] - 1].B = li[i * latime_img + j].B;
            lo[inversapermutare[i * latime_img + j] - 1].G = li[i * latime_img + j].G;
            lo[inversapermutare[i * latime_img + j] - 1].R = li[i * latime_img + j].R;
        }

    liniarizare_extern(filenamei, filenameo, lo);
}

void chi_patrat(char *filename) {
    FILE *fin;
    fin = fopen(filename, "rb");
    if (!fin) {
        printf("eroare la deschidere");
        return NULL;
    }
    unsigned int *frecventa_albastru = calloc(256, sizeof(unsigned int));
    unsigned int *frecventa_verde = calloc(256, sizeof(unsigned int));
    unsigned int *frecventa_rosu = calloc(256, sizeof(unsigned int));
    unsigned int latime_img, inaltime_img, i, j;
    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    struct pixel *imagine_liniarizata = malloc(sizeof(struct pixel) * latime_img * inaltime_img);
    imagine_liniarizata = liniarizare_intern(filename);
    double chi_albastru = 0, chi_verde = 0, chi_rosu = 0;
    double frecventa_teoretica = (latime_img * inaltime_img) / 256.0;
    fseek(fin, 0, SEEK_SET);
    for (i = 0; i < inaltime_img; i++) {
        for (j = 0; j < latime_img; j++) {
            frecventa_albastru[imagine_liniarizata[i * latime_img + j].B]++;
            frecventa_verde[imagine_liniarizata[i * latime_img + j].G]++;
            frecventa_rosu[imagine_liniarizata[i * latime_img + j].R]++;
        }
    }
    for (i = 0; i < 256; i++) {
        chi_albastru = chi_albastru +
                       ((frecventa_albastru[i] - frecventa_teoretica) * (frecventa_albastru[i] - frecventa_teoretica)) /
                       frecventa_teoretica;
        chi_verde = chi_verde +
                    ((frecventa_verde[i] - frecventa_teoretica) * (frecventa_verde[i] - frecventa_teoretica)) /
                    frecventa_teoretica;
        chi_rosu = chi_rosu + ((frecventa_rosu[i] - frecventa_teoretica) * (frecventa_rosu[i] - frecventa_teoretica)) /
                              frecventa_teoretica;
    }
    printf("cu valorile chi patrat:\n %0.2f %0.2f %0.2f", chi_albastru, chi_verde, chi_rosu);
    fclose(fin);
}

void grayscale(struct pixel ***img, struct pixel ***sb, unsigned int inaltime_img, unsigned int latime_img,
               unsigned int inaltime_sab, unsigned int latime_sab) {
    unsigned int i, j, aux;
    for (i = 0; i < inaltime_img; i++) {
        for (j = 0; j < latime_img; j++) {
            aux = 0.299 * (*img)[i][j].R + 0.587 * (*img)[i][j].G + 0.114 * (*img)[i][j].B;
            (*img)[i][j].B = (*img)[i][j].G = (*img)[i][j].R = aux;
        }
    }
    for (i = 0; i < inaltime_sab; i++) {
        for (j = 0; j < latime_sab; j++) {
            aux = 0.299 * (*sb)[i][j].R + 0.587 * (*sb)[i][j].G + 0.114 * (*sb)[i][j].B;
            (*sb)[i][j].B = (*sb)[i][j].G = (*sb)[i][j].R = aux;
        }
    }
}

void color(unsigned int inaltime_img, unsigned int latime_img, unsigned int i, unsigned int j, unsigned int n,
           unsigned int m, struct pixel ***a, struct pixel culori) {
    unsigned int x, y;
    if (i + n < inaltime_img && j + m < latime_img) {
        for (x = i; x < i + n; x++) {
            (*a)[x][j] = culori;
            (*a)[x][j + m - 1] = culori;
        }
        for (y = j; y < j + m; y++) {
            (*a)[i][y] = culori;
            (*a)[i + n - 1][y] = culori;
        }
    }
}

int maxim(int a, int b) {
    return a > b ? a : b;
}

int minim(int a, int b) {
    return a < b ? a : b;
}

int cmp(const void *a, const void *b) {
    if (((struct detectii *) a)->corelatie > ((struct detectii *) b)->corelatie)
        return -1;
    return 1;
}

void eliminare_nonmaximelor(struct detectii **D, unsigned int z) {
    int i, j, inaltime = 15, latime = 11;
    float a, b, arie_intersectie, arie_sablon = inaltime * latime, suprapunere;
    qsort((*D), z, sizeof(struct detectii), cmp);
    for (i = 0; i < z - 1; i++)
        for (j = i + 1; j < z; j++) {
            a = maxim(minim((*D)[i].x + inaltime, (*D)[j].x + inaltime) - maxim((*D)[i].x, (*D)[j].x), 0);
            b = maxim(minim((*D)[i].y + latime, (*D)[j].y + latime) - maxim((*D)[i].y, (*D)[j].y), 0);
            arie_intersectie = a * b;
            if (arie_intersectie == 0)
                suprapunere = 0;
            else
                suprapunere = arie_intersectie / (arie_sablon + arie_sablon - arie_intersectie);
            if (suprapunere > 0.2) {
                (*D)[j].val = 1;
            }
        }
}

void templatematching(char *imagine, float ps, char *afisare_toate, char *afisare_dupa_eliminare) {
    FILE *f_imagine, *f_sablon, *f_afisare, *f_afisare_dupa_eliminare_suprapuneri;
    f_imagine = fopen(imagine, "rb");
    f_afisare = fopen(afisare_toate, "wb");
    f_afisare_dupa_eliminare_suprapuneri = fopen(afisare_dupa_eliminare, "wb");
    char *s = calloc(20, sizeof(char));
    unsigned int n, latime_img, inaltime_img, latime_sab, inaltime_sab, i, j, x, y, k = 0, z = 0, h;
    struct pixel **img_toate = salvam_img_intern(imagine);
    struct pixel **img_eliminare = salvam_img_intern(imagine);
    if (!f_imagine)
        printf("eroare la deschidere");
    if (!f_afisare)
        printf("eroare la deschidere");
    if (!f_afisare_dupa_eliminare_suprapuneri)
        printf("eroare la deschidere");
    fseek(f_imagine, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, f_imagine);
    fread(&inaltime_img, sizeof(unsigned int), 1, f_imagine);
    int **l_imagine = liniarizare_grayscale(imagine);

    struct detectii *D = calloc(100000, sizeof(struct detectii));
    for (h = 0; h < 10; h++) {

        struct pixel culori;
        unsigned int red, green, blue;
        printf("\nnumele sablonului este:");
        scanf("%s", s);
        printf("\nintesitatile culorilor sunt:");
        scanf("%u%u%u", &red, &green, &blue);
        culori.R = red;
        culori.G = green;
        culori.B = blue;

        f_sablon = fopen(s, "rb");
        if (!f_sablon)
            printf("eroare la deschidere");
        float medie_fereastra = 0, medie_sablon = 0, deviatie_sablon = 0, deviatie_fereastra = 0, corr = 0;
        fseek(f_sablon, 18, SEEK_SET);
        fread(&latime_sab, sizeof(unsigned int), 1, f_sablon);
        fread(&inaltime_sab, sizeof(unsigned int), 1, f_sablon);
        int **l_sablon = liniarizare_grayscale(s);

        n = inaltime_sab * latime_sab;

        for (i = 0; i < inaltime_sab; i++)
            for (j = 0; j < latime_sab; j++)
                medie_sablon = medie_sablon + l_sablon[i][j];
        medie_sablon = medie_sablon / n;

        for (i = 0; i < inaltime_sab; i++)
            for (j = 0; j < latime_sab; j++)
                deviatie_sablon += (l_sablon[i][j] - medie_sablon) * (l_sablon[i][j] - medie_sablon);

        deviatie_sablon = sqrt(deviatie_sablon / (n - 1));

        for (i = 0; i <= inaltime_img - inaltime_sab; i++)
            for (j = 0; j <= latime_img - latime_sab; j++) {
                medie_fereastra = 0;
                deviatie_fereastra = 0;
                corr = 0.0;

                for (x = i; x < i + inaltime_sab; x++)
                    for (y = j; y < j + latime_sab; y++)

                        medie_fereastra = medie_fereastra + l_imagine[x][y];
                medie_fereastra = medie_fereastra / n;

                for (x = i; x < i + inaltime_sab; x++)
                    for (y = j; y < j + latime_sab; y++)

                        deviatie_fereastra += (l_imagine[x][y] - medie_fereastra) * (l_imagine[x][y] - medie_fereastra);
                deviatie_fereastra = sqrt(deviatie_fereastra / (n - 1));

                for (x = i; x < i + inaltime_sab; x++)
                    for (y = j; y < j + latime_sab; y++)
                        corr += (l_imagine[x][y] - medie_fereastra) * (l_sablon[x - i][y - j] - medie_sablon) /
                                (deviatie_fereastra * deviatie_sablon);
                corr = corr / n;
                if (corr > ps) {
                    D[z].corelatie = corr;
                    D[z].nrculoare = culori;
                    D[z].val = 0;
                    D[z].x = i;
                    D[z].y = j;
                    z++;
                    color(inaltime_img, latime_img, i, j, inaltime_sab, latime_sab, &img_toate, culori);

                }
            }
    }

    salvam_img_extern(imagine, afisare_toate, img_toate);
    eliminare_nonmaximelor(&D, z);
    for (i = 0; i < z; i++)
        if (D[i].val == 0) {
            color(inaltime_img, latime_img, D[i].x, D[i].y, inaltime_sab, latime_sab, &img_eliminare, D[i].nrculoare);
        }
    salvam_img_extern(imagine, afisare_dupa_eliminare, img_eliminare);
}

int main() {
    char *s1 = calloc(20, sizeof(char));
    char *s2 = calloc(20, sizeof(char));
    char *s3 = calloc(20, sizeof(char));
    char *s4 = calloc(20, sizeof(char));
    char *s5 = calloc(20, sizeof(char));
    char *s6 = calloc(20, sizeof(char));
    char *s7 = calloc(20, sizeof(char));
    printf("numele pozei care trebuie criptata:");
    scanf("%s", s1);
    printf("\n");
    printf("numele pozei criptate:");
    scanf("%s", s2);
    printf("\n");
    printf("numele fisierului cu cheia secreta:");
    scanf("%s", s3);
    printf("\n");
    printf("numele pozei decriptate:");
    scanf("%s", s4);
    printf("\n");
    criptare(s1, s2, s3);
    printf("imaginea criptata ");
    chi_patrat(s2);
    printf("\n");
    printf("imaginea decriptata ");
    decriptare(s2, s4, s3);
    chi_patrat(s4);
    printf("\n");
    printf("numelui tabloului cu cifre:");
    scanf("%s", s5);
    printf("\n");
    printf("numelui imaginii de afisat:");
    scanf("%s", s6);
    printf("\n");
    printf("numelui imaginii de afisat dupa eliminare suprapunerilor:");
    scanf("%s", s7);
    printf("\n");
    float ps;
    printf("pragul ps este:");
    scanf("%f", ps);
    printf("\n");
    templatematching(s5, ps, s6, s7);
    return 0;

}
