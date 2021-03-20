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
 
      Ar norite sugeneruoti studentu sarasu failus? (T/N): N
      Ar norite atlikti testavima? (T/N): T
      Pradedamas testavimas su 1000 duomenu
      Irasu nuskaitymo laikas: 0.009288
      Irasu surusiavimo laikas: 0.003843
      Irasu padalinimo laikas: 0.000323
      Blogu studentu isvedimo laikas: 0.032874
      Geru studentu isvedimo laikas: 0.058284

      Pradedamas testavimas su 10000 duomenu
      Irasu nuskaitymo laikas: 0.066168
      Irasu surusiavimo laikas: 0.036811
      Irasu padalinimo laikas: 0.003388
      Blogu studentu isvedimo laikas: 0.056377
      Geru studentu isvedimo laikas: 0.079731

      Pradedamas testavimas su 100000 duomenu
      Irasu nuskaitymo laikas: 0.684028
      Irasu surusiavimo laikas: 0.442374
      Irasu padalinimo laikas: 0.019369
      Blogu studentu isvedimo laikas: 0.291874
      Geru studentu isvedimo laikas: 0.409058

      Pradedamas testavimas su 1000000 duomenu
      Irasu nuskaitymo laikas: 7.44474
      Irasu surusiavimo laikas: 5.52554
      Irasu padalinimo laikas: 0.201942
      Blogu studentu isvedimo laikas: 2.71565
      Geru studentu isvedimo laikas: 4.47632

      Pradedamas testavimas su 10000000 duomenu
      Irasu nuskaitymo laikas: 61.1624
      Irasu surusiavimo laikas: 63.3781
      Irasu padalinimo laikas: 1.74078
      Blogu studentu isvedimo laikas: 26.8846
      Geru studentu isvedimo laikas: 37.6614

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


# V0.4 versijos kompiliavimas:
      g++ -c main.cpp includes/functions.cpp includes/students.cpp
      g++ -o main main.o functions.o students.o

