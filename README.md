# E-shop

Semestrálny projekt z predmetu Programovanie (3) na tému "E-shop".

## Inštalácia

Pri tvorbe bol použitý nasledovný software:
- C++ 17
- cmake v3.6.2
- boost v1.78.0

## Funkcie

Produkt
- názov, kategória, cena, množstvo na sklade
- úprava, kopírovanie, presúvanie produktu

Inventár produktov
- zoznam produktov, mapa názvov produktov na produkty
- zoznam produktov je zoradený podľa ceny vzostupne
- pri vkladaní sa používa binárne vyhľadávanie na nájdenie pozície pre produkt
- pri filtrovaní podľa ceny sa taktiež použije binárne vyhľadávanie
- rýchle vyhľadanie produktu podľa názvy za pomoci mapy
- filtrovanie podľa ceny, cenového rozsahu, kategórie
- získanie iterátora všektých produktov

Položka objednávky
- produkt, množstvo

Objednávka
- zoznam položiek objednávky, stav objednávky, addresa
- vytvorenie objednávky zo stavom "Spracováva sa"
- nahádzanie položiek do objednávky
- nahradenie položiek objednávky ktoré nie sú na sklade položkami z rovnakej kategórie a najvyššou cenou
- odoslanie objednávky nahradí položky, odráta ich z inventára a nastaví stav na "Odoslaná"

## Zostáva naprogramovať

Inventár produktov
- načítanie zo súboru
- uloženie do súboru

Recenzia
- väzba na produkt a objednávku
- načítanie zo súboru
- uloženie do súboru

Iné.