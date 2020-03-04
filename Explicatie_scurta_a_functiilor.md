
# Proiect Programare Procedurala

Partea de criptare/decriptare:

•	Functia xorshift32: genereaza numere pseudo-aleatoare pornind de la seed, care primeste numarul de la care incepe generarea, numarul de elemente, si vectorul R in care se pun elementele;

•	Structura pixel: ce contine cele 3 culorii posibile R(red),G(green),B(blue);

•	Functia liniarizare_intern: pune intr-un vector de tip struct pixel valorile pixelilor din imagine, care primeste calea imaginii;

•	 Functia liniarizare_extern: pune intr-o imagine valorile pixelilor din vector, care primeste calea imaginii, calea imaginii care trebuie afisate si vectorul de pixeli;

•	Functia XOR: xoreaza un pixel cu o valoare I, primeste pixelul si valoarea;

•	Functia criptare: unde vom cripta imaginea primita cu ajutorul R0 si SV care se afla intr-un fisier txt. Mai intai vom genera numerele pseudo-aleatoare , vom face permutarea si vom xor elementele, functia primeste imaginea care trebuie criptate, imaginea criptata, fisierul txt care contine R0 si SV;

•	Functia decriptare: unde vom decripta imaginea criptata, calculam numerele pseudo-aleatoare, permutarea inversa, xorarea inversa, dupa xor vom aplica permutarea inversa, functia primeste imaginea care trebuie decriptata, imaginea criptata, fisierul txt care contine R0 si SV;

•	Functia chi_patrat are ca parametru imaginea pentru care vom calcula frecventa fiecarui canal, prima data calculam frecventa teoretica, dupa frecventa pe fiecare canal, iar la final aplicam suma pentru fiecare canal si le afisam;

Modulul de recunoastere de pattern-uri intr-o imagine:

•	Stuctura detectii care contine coordonatele x si y de unde incepe un sablon, val in care punem 0 de fiecare date cand corr este peste pragul ps , corelatia si un pixel de tipul struct pixel;

•	Functia salvam_img_intern pune imaginea intr-o matrice de tip struct pixel, are ca parametru imaginea;

•	Functia salvam_img_extern formeaza o imagine parcurgand matricea de tip struct pixel, are ca parametrii imaginea, imaginea care trebuie afisata si matricea;

•	Functia liniarizare_grayscale formeaza o matrice unde R=G=B are ca paramertru imaginea;

•	Fuctia color coloreaza marginile sablonului, are ca parametrii inaltimea imaginii, latimea imaginii, coordonatele i si j , inaltimea sablonului, latimea sablonului , matricea care contine pixelii si culoare;

•	Functia maxim care returneaza maximul dintre cei 2 parametrii a si b;

•	Functia minim care returneaza minimul dintre cei 2 parametrii a si b;

•	Functia cmp care o utilizam pentru qsort comparand elementele vectorului;

•	Functia eliminare_nonmaximelor are ca parametrii vectorul si numarul de elemente, in functie vom ordona crescator vectorul,dupa ne vom plimba prin vector cu 2 for vom calcula maximul dintre 0 si minimul dintre prima coordonata +inaltimea si al doua coordonata +inaltime – maximul dintre prima coordonata si a doua, daca aria_intersectie este egala cu 0 suprapunerea este 0, altfel  suprapunera devine arie_intersectie/(arie_sablon+arie_sablon-arie_intersectie), daca suprapunere este mai mare ca 0.2 vector.val=1 insemnand ca este eliminat;

•	Functia templatematching are ca parametrii imaginea originala, imaginea fara eliminarea suprapunerilor, imaginea dupa eliminarea suprapunerilor si pragul ps, in functie vom citi cele 10 sabloane si culoarea pentru fiecare sablon, vom calcula media sablon, derivatia sablon , dupa aceea vom calcula pentru fiecare fereastra media si derivatia, daca corr mai mare ca ps, vom pune fereastra in  vectorul D si vom colora fereastra, dupa care vom elimina suprapunerile;

In int main() vom citi numele imaginilor si vom apela criptarea, decriptare, chi_patrat si templatemaching
