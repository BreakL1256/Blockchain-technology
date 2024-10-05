# Blockchain-technology
## 1 - 2 užduotys
##### V0.1
|Failai|Hash'ai|
|----|----|
| input.txt (0 simbolių)| |
| 1_simbolis.txt (1 simbolis):                              | 861da773615a97d7e4d4f881617a25d2fb335db419350337893f6c2d8fdb1d94
| 1.2_simbolis.txt (1 simbolis):                            | 861da773615a97d7e4d4f881617a25d2fb335da235622b058900d6c348132a92
| 1SeparateSymbol.txt (2000 simbolių, vienas skirtingas):   | a1cccf34bc5789d6ea282997f24abe93eb30e9bf7b1bcd6aa79c82bfed5be26b
| 1SeparateSymbol1.txt (2000 simbolių, vienas skirtingas):  | a0cdabfaac7eab96dcccc42a04c15b14f7173f5addc018feba82eb42d1812216
| Symbols.txt (2000 simbolių):                              | a6f98085796a8b4b80a1a0c4eae4e55af590f5f4e84af72dd1667d44d87a8e9e
| Symbols1.txt (2000 simbolių):                             | 80fdff76142d69099960b1fbd1b70b16e87f5d7c6b9cb5a3b57eb80782d386c9

##### V0.2
|Failai|Hash'ai|
|----|----|
| input.txt (0 simbolių)| |
| 1_simbolis.txt (1 simbolis):                              | cd13b7fe1829e73a81a7045d11dd8d00806a2c41debc0128eb342aeaf26c1566
| 1.2_simbolis.txt (1 simbolis):                            | cd972577ffe226b2c0ec440496f90d6dc186cc8d5d49e2efddea9c0d9b7e06d8
| 1SeparateSymbol.txt (2000 simbolių, vienas skirtingas):   | ce0c07ecd4746723888bbcc6e9d1689b9728a075caa398ba9b12d22f5d197d1f
| 1SeparateSymbol1.txt (2000 simbolių, vienas skirtingas):  | 9642da5efc4b43eed83da3929f622ff9d420c52c6225a37fb8843e96ef4049ab
| Symbols.txt (2000 simbolių):                              | dd23194a9f6d32e5cbb7d10a8d82b1f3ca1caaad46349cb6d9afb05bca669c0d
| Symbols1.txt (2000 simbolių):                             | 824e4af3b13f1bd696670a1ce6b4801d9dcefd6730e805cd84a77558873d0bc4

#### Deterministiškumas
##### V0.1
![Screenshot 2024-09-27 155936](https://github.com/user-attachments/assets/bfef378f-4681-4201-8081-8c23693e5ce8)

##### V0.2
![deterministiskumas_2](https://github.com/user-attachments/assets/c6740cc7-e937-452b-a92a-bb96d5e89625)

#### Išvados: 
##### V0.1
Visi hash'ai vienodo ilgio (64 simbolių)

##### V0.2
Visi hash'ai vienodo ilgio (64 simbolių)

## 3 - 4 užduotys
#### Lentelė:
##### V0.1

| Eilutės | Laikas (Vid.)|
|----|----|
|  1 eilutė    | 0.0001595 s |
|  8 eilutės   | 0.0002026 s |
|  32 eilutės  | 0.0002128 s |
|  128 eilutės | 0.0002584 s |
|  300 eilučių | 0.000324 s  |

##### V0.2

| Eilutės | Laikas (Vid.)|
|----|----|
|  1 eilutė    | 0.0001666 s |
|  8 eilutės   | 0.0001868 s |
|  32 eilutės  | 0.000191 s |
|  128 eilutės | 0.0002921 s |
|  300 eilučių | 0.0004367 s  |

#### Grafas:
##### V0.1
![Screenshot 2024-09-27 172924](https://github.com/user-attachments/assets/fb9eafe8-1887-4893-af5c-19607af8a5bf)

##### V0.2
![image](https://github.com/user-attachments/assets/c5f2dcc0-96ce-451a-b76c-96d02061aac8)

## 5 užduotis
##### V0.1
- Kolizijos: 47

##### V0.2
- Kolizijos: 0
  
## 6 užduotis
##### V0.1
|Kintamųjų tipai|Nesutapimo indeksas (Vid.)|
|----|----|
| Hex | 85.65% |
| Bit | 30.145% |

##### V0.2
|Kintamųjų tipai|Nesutapimo indeksas (Vid.)|
|----|----|
| Hex | 93.185% |
| Bit | 32.878% |

**Hex:**
- Maximum: 93.21%
- Minimum: 93.15%

**Bit:**
- Maximum: 32.89%
- Minimum: 32.87%

## Išvados:
Šio hash'o pagrindinė stiprybė yra aukštas šešioliktainio hash'o simbolių nesutapimo indeksas. Pagrindiniai trūkumai buvo didelis skaičius kolizijų, kurį pavyko sutvarkyti V0.2 versijoje

