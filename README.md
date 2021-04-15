# Pažymiu skaičiuoklė
Programa skirta apskaičiuoti vieno ar kelių moksleivių pažymių galutinį balą.

# Programos veikimas
Atsidarius programą galima pasirinkti tarp skirtingų opcijų:
* Sugeneruoti duomenų failus
* Atlikti testavimą
* Nuskaityti duomenis iš failo
* Įvesti duomenis rankiniu būdu

# Duomenų failų generavimas
Atsidarius programą iškart yra išmetama užklausa, ar norima sugeneruoti duomenų failus.

     Ar norite sugeneruoti studentu sarasu failus? (T/N): T
     Irasu sugeneravimo laikas: 160.16
     
Sugeneruojami 5 duomenų failai iš 6 atsitiktinai sugeneruotų namų darbų ir egzamino pažymių. Šie failai atitinkamai sugeneruojami iš 10000000, 1000000, 100000, 10000, 1000 studentų.

     Vardas              Pavarde             ND0            ND1            ND2            ND3            ND4            ND5            Egz.           
     Vardas1             Pavarde1            2              4              8              2              1              2              5              
     Vardas2             Pavarde2            3              1              2              5              3              4              1              
     Vardas3             Pavarde3            8              8              6              5              1              4              5              
     Vardas4             Pavarde4            3              6              1              9              3              3              9              
     Vardas5             Pavarde5            3              4              4              6              7              2              4              
     Vardas6             Pavarde6            7              6              1              8              6              6              1      

# Testavimas


# Duomenų įvedimas rankiniu būdu
* Studento vardas pavardė
* Namų darbų pažymiai
* Egzamino rezultatas

Taip pat yra galimybe, kad pažymiai būtų sugeneruojami atsitiktiniu būdu

Galutiniam balui atspausdinti galima pasirinkti naudoti visų balų vidurkį arba medianą.

     Iveskite studento varda ir pavarde: Vaidotas Girinis
     Ar zinomas namu darbu kiekis? (T/N): T
     Iveskite namu darbu kieki: ė
     Ivesti duomenys yra neteisingo formato, iveskite skaiciu (ne mazesni nei 1): 4
     Ar norite kad mokinio balai butu sugeneruojami atsitiktiniu budu? (T/N): N
     Iveskite namu darbu pazymius:
     5 8 10 7
     Iveskite egzamino rezultata: 10
     Ar norite prideti dar viena moksleivi? (T/N): T
     Iveskite studento varda ir pavarde: Benjaminas Racas
     Ar zinomas namu darbu kiekis? (T/N): N
     Ar norite kad mokinio balai butu sugeneruojami atsitiktiniu budu? (T/N): T
     Ar norite prideti dar viena moksleivi? (T/N): T
     Iveskite studento varda ir pavarde: Vytautas Miltinis
     Ar zinomas namu darbu kiekis? (T/N): N
     Ar norite kad mokinio balai butu sugeneruojami atsitiktiniu budu? (T/N): N
     Iveskite namu darbu pazymius:
     10
     8
     10
     6
     -1
     Iveskite egzamino rezultata: 9
     Ar norite prideti dar viena moksleivi? (T/N): N
     Pasirinkite atspausdinti galutinio balo Vidurki(1) arba Mediana(2): 1
     Vardas         Pavarde        Galutinis (Vid.)
     ----------------------------------------------
     Vaidotas       Girinis        9.07
     Benjaminas     Racas          7.71
     Vytautas       Miltinis       8.80


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

