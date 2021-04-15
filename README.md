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

* [v1.0](https://github.com/Benjaminas1/Pazymiu-skaiciuokle-VU/releases/tag/v1.0) :
  * Testavime implementuota galimybė pasirinkti tarp 3 skirtingų duomenų rūšiavimo strategijų.


# V1.0 versijos kompiliavimas:
Windows sistemai:

    g++ -c main.cpp includes/functions.cpp includes/students.cpp
    g++ -o main main.o functions.o students.o
      
Linux sistemai:

    make
    ./main

