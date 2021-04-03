# Pažymiu skaičiuoklė
Programa skirta apskaičiuoti vieno ar kelių moksleivių pažymių galutinį balą.

# Programos veikimas
Atsidarius programą yra prašoma įvesti duomenis:
* Studento vardas pavardė
* Namų darbų pažymiai
* Egzamino rezultatas

Taip pat yra galimybe, kad pažymiai būtų sugeneruojami atsitiktiniu būdu

Galutiniam balui atspausdinti galima pasirinkti naudoti visų balų vidurkį arba medianą.

# Programos testavimas

Testavimas buvo atliktas naudojant 238GB Hitachi SATA SSD, 8.00GB Dual-Channel RAM 2133MHz (Unknown brand), Intel i3 7100U @ 2.40GHz
 
    Ar norite sugeneruoti studentu sarasu failus? (T/N): N
    Ar norite atlikti testavima? (T/N): T
    --------------------------------------------------
    Pradedamas testavimas su 1000 duomenu:
    - Naudojant vector:
    Irasu nuskaitymo laikas: 0.009975
    Irasu surusiavimo laikas: 0.003681
    - Naudojant list: 
    Irasu nuskaitymo laikas: 0.009432
    Irasu surusiavimo laikas: 0.001995
    - Naudojant deque: 
    Irasu nuskaitymo laikas: 0.01228
    Irasu surusiavimo laikas: 0.008226
    --------------------------------------------------
    Pradedamas testavimas su 10000 duomenu:
    - Naudojant vector:
    Irasu nuskaitymo laikas: 0.080543
    Irasu surusiavimo laikas: 0.053663
    - Naudojant list: 
    Irasu nuskaitymo laikas: 0.068606
    Irasu surusiavimo laikas: 0.014319
    - Naudojant deque: 
    Irasu nuskaitymo laikas: 0.064062
    Irasu surusiavimo laikas: 0.06252
    --------------------------------------------------
    Pradedamas testavimas su 100000 duomenu:
    - Naudojant vector:
    Irasu nuskaitymo laikas: 0.707505
    Irasu surusiavimo laikas: 0.449731
    - Naudojant list: 
    Irasu nuskaitymo laikas: 0.658147
    Irasu surusiavimo laikas: 0.219713
    - Naudojant deque: 
    Irasu nuskaitymo laikas: 0.67883
    Irasu surusiavimo laikas: 0.876861
    --------------------------------------------------
    Pradedamas testavimas su 1000000 duomenu:
    - Naudojant vector:
    Irasu nuskaitymo laikas: 6.42586
    Irasu surusiavimo laikas: 5.62348
    - Naudojant list: 
    Irasu nuskaitymo laikas: 7.36148
    Irasu surusiavimo laikas: 2.4272
    - Naudojant deque: 
    Irasu nuskaitymo laikas: 7.37906
    Irasu surusiavimo laikas: 11.8036
    --------------------------------------------------
    Pradedamas testavimas su 10000000 duomenu:
    - Naudojant vector:
    Irasu nuskaitymo laikas: 63.6472
    Irasu surusiavimo laikas: 67.5484
    - Naudojant list: 
    Irasu nuskaitymo laikas: 63.3495
    Irasu surusiavimo laikas: 21.0415
    - Naudojant deque: 
    Irasu nuskaitymo laikas: 60.88
    Irasu surusiavimo laikas: 121.129

# Releases #

* [v0.1](https://github.com/Benjaminas1/Pazymiu-skaiciuokle-VU/releases/tag/v0.1) : pirminė programos versija.

* [v0.2](https://github.com/Benjaminas1/Pazymiu-skaiciuokle-VU/releases/tag/v0.2) :
  * Pridėta galimybė nuskaityti duomenis iš failo.
  * Studentai yra automatiškai išrūšiuojami pagal jų vardus.

* [v0.3](https://github.com/Benjaminas1/Pazymiu-skaiciuokle-VU/releases/tag/v0.3) :
  * Sukurtas `functions.cpp` failas, kuriame yra sudėtos visos programoje naudojamos funkcijos.
  * Sukurtas `functions.h` header failas, kuriame yra saugoma studentų struct.

* [v0.4](https://github.com/Benjaminas1/Pazymiu-skaiciuokle-VU/releases/tag/v0.4) :
  * Sukurta funkcija leidžianti atlikti programos veikimo greičio (spartos) analizę.
  * Sukurta funkcija leidžianti sugeneruoti atsitiktinius studentų sarašų failus (1'000, 10'000, 100'000, 1'000'000, 10'000'000 įrašų).
  * Sukurtas studentų rūšiavimas į dvi grupes pagal galutinį balą.
  * Sugrupuoti studentai yra atitinkamai išvedami į du skirtingus failus.

* [v0.5](https://github.com/Benjaminas1/Pazymiu-skaiciuokle-VU/releases/tag/v0.5) :
  * Testavimas atliekamas naudojant tris skirtingus konteinerius: vector, list, deque.


# V0.5 versijos kompiliavimas:
      g++ -c main.cpp includes/functions.cpp includes/students.cpp
      g++ -o main main.o functions.o students.o

