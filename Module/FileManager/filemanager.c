#include "filemanager.h"
#include <stdio.h>

BinTree BacaPohonMakanan(char namaFile[100])
{
    STARTBARIS(namaFile);
    int pos = 0;
    return PreOrderToTree(CBaris.TabBaris, &pos);
}

TabKata BacaArray(char namaFile[100])
{
    TabKata T;
    MakeEmptyArray(&T);
    STARTBARIS(namaFile);
    int i = 0;
    while (!EndBaris)
    {
        i++;
        RESETKATAA();
        CKataA.Length = CBaris.Length;
        sprintf(CKataA.TabKata, "%s", CBaris.TabBaris);
        AddAsLastEl(&T, CKataA);
        ADVBARIS();
    }
    return T;
}

void TulisSaveGame(char namaFile[100], Queue ANS, Queue AS, long Uang, long Nyawa, JAM Waktu, POINT Posisi,
                   int Stage, TabKata Orderan, TabKata BOO, Queue PDM, MATRIKS P1, MATRIKS P2, MATRIKS P3,
                   MATRIKS P4, Graph Pintu, BinTree PohM, Stack Food, Stack Hand,TabKata NamaBahan,
                   TabKata XBahan, TabKata YBahan)
{
    FILE *fp = fopen(namaFile, "w");
    fprintf(fp, "-AntrianNonStar\n");
    fprintf(fp, "%d\n", NBElmt(ANS));
    while (!IsEmptyQueue(ANS))
    {
        PELANGGAN temp;
        Del(&ANS, &temp);
        fprintf(fp, "Pelanggan\n");
        fprintf(fp, "%d\n%ld\n", Banyak(temp), JAMToDetik(WaktuCabut(temp)));
    }
    fprintf(fp, "-AntrianStar\n");
    fprintf(fp, "%d\n", NBElmt(AS));
    while (!IsEmptyQueue(AS))
    {
        PELANGGAN temp;
        Del(&AS, &temp);
        fprintf(fp, "Pelanggan\n");
        fprintf(fp, "%d\n%ld\n", Banyak(temp), JAMToDetik(WaktuCabut(temp)));
    }
    fprintf(fp, "-Uang\n");
    fprintf(fp, "%ld\n", Uang);
    fprintf(fp, "-Nyawa\n");
    fprintf(fp, "%ld\n", Nyawa);
    fprintf(fp, "-Waktu\n");
    fprintf(fp, "%ld\n", JAMToDetik(Waktu));
    fprintf(fp, "-Posisi\n");
    fprintf(fp, "%d\n", Absis(Posisi));
    fprintf(fp, "%d\n", Ordinat(Posisi));
    fprintf(fp, "-Stage\n");
    fprintf(fp, "%d\n", Stage);
    fprintf(fp, "-Orderan\n");
    fprintf(fp, "%d\n", NbElmt(Orderan));
    for (int i = 1; i <= NbElmt(Orderan); i++)
    {
        fprintf(fp, "%s %s\n", Elmt(Orderan, i).TabKata,Elmt(BOO,i).TabKata);
    }
    fprintf(fp, "-PelangganDiMeja\n");
    fprintf(fp, "%d\n", NBElmt(PDM));
    while (!IsEmptyQueue(PDM))
    {
        PELANGGAN temp;
        Del(&PDM, &temp);
        fprintf(fp, "Pelanggan\n");
        fprintf(fp, "%d\n", Ruangan(temp));
        fprintf(fp, "%d\n", Absis(Pos(temp)));
        fprintf(fp, "%d\n", Ordinat(Pos(temp)));
        fprintf(fp, "%d\n", Banyak(temp));
        fprintf(fp, "%ld\n", JAMToDetik(WaktuCabut(temp)));
        fprintf(fp, "%s\n", Orderan(temp).TabKata);
        if (IsStar(temp))
        {
            fprintf(fp, "Yes\n");
        }
        else
        {
            fprintf(fp, "No\n");
        }
        if (SudahOrder(temp))
        {
            fprintf(fp, "Yes\n");
        }
        else
        {
            fprintf(fp, "No\n");
        }
    }
    fprintf(fp, "-Peta1\n");
    fprintf(fp, "%d\n%d\n", NBrsEff(P1), NKolEff(P1));
    for (int i = GetFirstIdxBrs(P1); i <= GetLastIdxBrs(P1); i++)
    {
        for (int j = GetFirstIdxKol(P1); j <= GetLastIdxKol(P1); j++)
        {
            fprintf(fp, "%c", ElmtMat(P1, i, j));
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-Peta2\n");
    fprintf(fp, "%d\n%d\n", NBrsEff(P2), NKolEff(P2));
    for (int i = GetFirstIdxBrs(P2); i <= GetLastIdxBrs(P2); i++)
    {
        for (int j = GetFirstIdxKol(P2); j <= GetLastIdxKol(P2); j++)
        {
            fprintf(fp, "%c", ElmtMat(P2, i, j));
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-Peta3\n");
    fprintf(fp, "%d\n%d\n", NBrsEff(P3), NKolEff(P3));
    for (int i = GetFirstIdxBrs(P3); i <= GetLastIdxBrs(P3); i++)
    {
        for (int j = GetFirstIdxKol(P3); j <= GetLastIdxKol(P3); j++)
        {
            fprintf(fp, "%c", ElmtMat(P3, i, j));
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-Peta4\n");
    fprintf(fp, "%d\n%d\n", NBrsEff(P4), NKolEff(P4));
    for (int i = GetFirstIdxBrs(P4); i <= GetLastIdxBrs(P4); i++)
    {
        for (int j = GetFirstIdxKol(P4); j <= GetLastIdxKol(P4); j++)
        {
            fprintf(fp, "%c", ElmtMat(P4, i, j));
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-Pintu\n");
    char sPintu[100] = "";
    int banyak = 0;
    adrNode P = First(Pintu);
    if (P != Nil)
    {
        adrNode PNext = Next(P);
        while (Next(P) != Nil)
        {
            while (PNext != Nil)
            {
                adrSuccNode tempSucc = SearchEdge(Pintu, Id(P), Id(PNext));
                if (tempSucc != Nil)
                {
                    banyak += 1;
                    sprintf(sPintu, "%s%d %d ", sPintu, Id(P), Id(PNext));
                    sprintf(sPintu, "%s%d %d %d %d\n", sPintu, Asal(tempSucc).X, Asal(tempSucc).Y,
                            Tujuan(tempSucc).X, Tujuan(tempSucc).Y);
                }
                PNext = Next(PNext);
            }
            P = Next(P);
            PNext = Next(P);
        }
    }
    fprintf(fp, "%d\n%s", banyak, sPintu);
    fprintf(fp, "-Food\n");
    char sFood[550] = "";
    int banyakFood = 0;
    while (!IsEmptyStack(Food))
    {
        Kata temp;
        Pop(&Food, &temp);
        char tempS[50];
        banyakFood += 1;
        sprintf(tempS, "%s", sFood);
        sprintf(sFood, "%s\n%s", temp.TabKata, tempS);
    }
    fprintf(fp, "%d\n%s", banyakFood, sFood);
    fprintf(fp, "-Hand\n");
    char sHand[550] = "";
    int banyakHand = 0;
    while (!IsEmptyStack(Hand))
    {
        Kata temp;
        Pop(&Hand, &temp);
        char tempS[50];
        banyakHand += 1;
        sprintf(tempS, "%s", sHand);
        sprintf(sHand, "%s\n%s", temp.TabKata, tempS);
    }
    fprintf(fp, "%d\n%s", banyakHand, sHand);
    fprintf(fp, "-BahanDapur\n");
    fprintf(fp, "%d\n", NbElmt(NamaBahan));
    for (int i = 1; i <= NbElmt(NamaBahan); i++)
    {
        fprintf(fp, "%s %s %s\n", Elmt(NamaBahan, i).TabKata,Elmt(XBahan,i).TabKata,Elmt(YBahan,i).TabKata);
    }
    fprintf(fp, ".");
    fclose(fp);
}
void BacaSaveGame(char namaFile[100], Queue *ANS, Queue *AS, long *Uang, long *Nyawa, JAM *Waktu,
                  POINT *Posisi, int *Stage, TabKata *Orderan, TabKata *BOO, Queue *PDM, MATRIKS *P1,
                  MATRIKS *P2, MATRIKS *P3, MATRIKS *P4, Graph *Pintu, BinTree *PohM, Stack *Food, 
                  Stack *Hand,TabKata* NamaBahan,TabKata* XBahan, TabKata* YBahan)
{
    TabKata T = BacaArray(namaFile);
    //Baca Antrian Non Star
    STARTKATAB("-AntrianNonStar");
    int IdxANS = Search1(T, CKataB);
    int banyakANS = StringToLongInt(Elmt(T, IdxANS + 1).TabKata);
    CreateEmptyQueue(ANS, 100);
    for (int i = 0; i < banyakANS; i++)
    {
        PELANGGAN temp;
        Banyak(temp) = StringToLongInt(Elmt(T, IdxANS + 3 + 3 * i).TabKata);
        WaktuCabut(temp) = DetikToJAM(StringToLongInt(Elmt(T, IdxANS + 4 + 3 * i).TabKata));
        IsStar(temp) = false;
        Pos(temp) = MakePOINT(-1, -1);
        SudahOrder(temp) = false;
        Ruangan(temp) = -1;
        Add(ANS, temp);
    }
    //Baca Antrian Star
    STARTKATAB("-AntrianStar");
    int IdxAS = Search1(T, CKataB);
    int banyakAS = StringToLongInt(Elmt(T, IdxAS + 1).TabKata);
    CreateEmptyQueue(AS, 100);
    for (int i = 0; i < banyakAS; i++)
    {
        PELANGGAN temp;
        Banyak(temp) = StringToLongInt(Elmt(T, IdxAS + 3 + 3 * i).TabKata);
        WaktuCabut(temp) = DetikToJAM(StringToLongInt(Elmt(T, IdxAS + 4 + 3 * i).TabKata));
        IsStar(temp) = true;
        Pos(temp) = MakePOINT(-1, -1);
        SudahOrder(temp) = false;
        Ruangan(temp) = -1;
        Add(AS, temp);
    }
    //Baca Config
    STARTKATAB("-Uang");
    int IdxUang = Search1(T, CKataB);
    *Uang = StringToLongInt(Elmt(T, IdxUang + 1).TabKata);
    STARTKATAB("-Nyawa");
    int IdxNyawa = Search1(T, CKataB);
    *Nyawa = StringToLongInt(Elmt(T, IdxNyawa + 1).TabKata);
    STARTKATAB("-Waktu");
    int IdxWaktu = Search1(T, CKataB);
    *Waktu = DetikToJAM(StringToLongInt(Elmt(T, IdxWaktu + 1).TabKata));
    STARTKATAB("-Posisi");
    int IdxPosisi = Search1(T, CKataB);
    int XP = StringToLongInt(Elmt(T, IdxPosisi + 1).TabKata);
    int YP = StringToLongInt(Elmt(T, IdxPosisi + 2).TabKata);
    *Posisi = MakePOINT(XP, YP);
    STARTKATAB("-Stage");
    int IdxStage = Search1(T, CKataB);
    *Stage = StringToLongInt(Elmt(T, IdxStage + 1).TabKata);
    //Baca Orderan
    STARTKATAB("-Orderan");
    int IdxOrd = Search1(T, CKataB);
    int banyakOrd = StringToLongInt(Elmt(T, IdxOrd + 1).TabKata);
    MakeEmptyArray(Orderan);
    MakeEmptyArray(BOO);
    for (int i = 0; i < banyakOrd; i++)
    {
        STARTKATAB(Elmt(T,IdxOrd+i+2).TabKata);
        AddAsLastEl(Orderan,CKataB);
        ADVKATAB();
        AddAsLastEl(BOO,CKataB);
    }
    //Baca Pelanggan di meja
    STARTKATAB("-PelangganDiMeja");
    int IdxPDM = Search1(T, CKataB);
    int banyakPDM = StringToLongInt(Elmt(T, IdxPDM + 1).TabKata);
    CreateEmptyQueue(PDM, 100);
    for (int i = 0; i < banyakPDM; i++)
    {
        PELANGGAN temp;
        Ruangan(temp) = StringToLongInt(Elmt(T, IdxPDM + 3 + 9 * i).TabKata);
        int XT = StringToLongInt(Elmt(T, IdxPDM + 4 + 9 * i).TabKata);
        int YT = StringToLongInt(Elmt(T, IdxPDM + 5 + 9 * i).TabKata);
        Pos(temp) = MakePOINT(XT, YT);
        Banyak(temp) = StringToLongInt(Elmt(T, IdxPDM + 6 + 9 * i).TabKata);
        WaktuCabut(temp) = DetikToJAM(StringToLongInt(Elmt(T, IdxPDM + 7 + 9 * i).TabKata));
        Orderan(temp) = Elmt(T, IdxPDM + 8 + 9 * i);
        IsStar(temp) = IsSameString(Elmt(T, IdxPDM + 9 + 9 * i).TabKata, "Yes");
        SudahOrder(temp) = IsSameString(Elmt(T, IdxPDM + 10 + 9 * i).TabKata, "Yes");
        Add(PDM, temp);
    }
    //Baca Peta 1
    STARTKATAB("-Peta1");
    int IdxP1 = Search1(T, CKataB);
    int barisPeta = StringToLongInt(Elmt(T, IdxP1 + 1).TabKata);
    int kolomPeta = StringToLongInt(Elmt(T, IdxP1 + 2).TabKata);
    MakeMATRIKS(barisPeta, kolomPeta, P1);
    for (int i = 0; i < barisPeta; i++)
    {
        for (int j = 0; j < kolomPeta; j++)
        {
            ElmtMat(*P1, i, j) = Elmt(T, IdxP1 + 3 + i).TabKata[j];
        }
    }
    //Baca Peta 2
    STARTKATAB("-Peta2");
    int IdxP2 = Search1(T, CKataB);
    barisPeta = StringToLongInt(Elmt(T, IdxP2 + 1).TabKata);
    kolomPeta = StringToLongInt(Elmt(T, IdxP2 + 2).TabKata);
    MakeMATRIKS(barisPeta, kolomPeta, P2);
    for (int i = 0; i < barisPeta; i++)
    {
        for (int j = 0; j < kolomPeta; j++)
        {
            ElmtMat(*P2, i, j) = Elmt(T, IdxP2 + 3 + i).TabKata[j];
        }
    }
    //Baca Peta 3
    STARTKATAB("-Peta3");
    int IdxP3 = Search1(T, CKataB);
    barisPeta = StringToLongInt(Elmt(T, IdxP3 + 1).TabKata);
    kolomPeta = StringToLongInt(Elmt(T, IdxP3 + 2).TabKata);
    MakeMATRIKS(barisPeta, kolomPeta, P3);
    for (int i = 0; i < barisPeta; i++)
    {
        for (int j = 0; j < kolomPeta; j++)
        {
            ElmtMat(*P3, i, j) = Elmt(T, IdxP3 + 3 + i).TabKata[j];
        }
    }
    //Baca Peta 4
    STARTKATAB("-Peta4");
    int IdxP4 = Search1(T, CKataB);
    barisPeta = StringToLongInt(Elmt(T, IdxP4 + 1).TabKata);
    kolomPeta = StringToLongInt(Elmt(T, IdxP4 + 2).TabKata);
    MakeMATRIKS(barisPeta, kolomPeta, P4);
    for (int i = 0; i < barisPeta; i++)
    {
        for (int j = 0; j < kolomPeta; j++)
        {
            ElmtMat(*P4, i, j) = Elmt(T, IdxP4 + 3 + i).TabKata[j];
        }
    }
    //Baca Pintu
    STARTKATAB("-Pintu");
    int IdxPin = Search1(T, CKataB);
    int banyakTransisi = StringToLongInt(Elmt(T, IdxPin + 1).TabKata);
    for (int i = 0; i < banyakTransisi; i++)
    {
        STARTKATAB(Elmt(T, IdxPin + 2 + i).TabKata);
        int roomA = StringToLongInt(CKataB.TabKata);
        ADVKATAB();
        int roomB = StringToLongInt(CKataB.TabKata);
        ADVKATAB();
        int XA = StringToLongInt(CKataB.TabKata);
        ADVKATAB();
        int YA = StringToLongInt(CKataB.TabKata);
        ADVKATAB();
        int XB = StringToLongInt(CKataB.TabKata);
        ADVKATAB();
        int YB = StringToLongInt(CKataB.TabKata);
        CreatePintu(Pintu, roomA, roomB, MakePOINT(XA, YA), MakePOINT(XB, YB));
    }
    //General Pohon Makanan
    *PohM = BacaPohonMakanan("../Default Save/Pohon.txt");
    //Baca Stack
    CreateEmptyStack(Food);
    STARTKATAB("-Food");
    int IdxFood = Search1(T, CKataB);
    int banyakFood = StringToLongInt(Elmt(T, IdxFood + 1).TabKata);
    for (int i = 0; i < banyakFood; i++)
    {
        Push(Food, Elmt(T, IdxFood + 2 + i));
    }
    CreateEmptyStack(Hand);
    STARTKATAB("-Hand");
    int IdxHand = Search1(T, CKataB);
    int banyakHand = StringToLongInt(Elmt(T, IdxHand + 1).TabKata);
    for (int i = 0; i < banyakHand; i++)
    {
        Push(Hand, Elmt(T, IdxHand + 2 + i));
    }
    //Baca NamaBahan
    STARTKATAB("-BahanDapur");
    int IdxBah = Search1(T, CKataB);
    int banyakBah = StringToLongInt(Elmt(T, IdxBah + 1).TabKata);
    MakeEmptyArray(NamaBahan);
    MakeEmptyArray(XBahan);
    MakeEmptyArray(YBahan);
    for (int i = 0; i < banyakBah; i++)
    {
        STARTKATAB(Elmt(T,IdxBah+i+2).TabKata);
        AddAsLastEl(NamaBahan,CKataB);
        ADVKATAB();
        AddAsLastEl(XBahan,CKataB);
        ADVKATAB();
        AddAsLastEl(YBahan,CKataB);
    }
}