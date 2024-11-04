# Blockchain (V0.1)
## Aprašas
Realizuota pati paprasčiausia blokų grandinės versija, naudojanti visų bloko transakcijų ID maišos reikšmę ir neoficialią sha256 maišos funkciją. Pateikiamos trys funkcijos: kasyba, iškastų blokų paieška, transakcijų paieška.

## Naudojimas
1. Parsisiųsti bc aplanką
2. Atsidarius aplanką bet kokioje integruotoje kūrimo aplinkoje į konsolę (CMD) suvesti šias komandas:
```
g++ -o blockchain blockchain.cpp hashFunc.cpp sha256.c
./blockchain
```
# Blockchain (V0.2)
## Aprašas
Realizuota pažangesnė blokų grandinės versija, naudojanti Merkle tree ir neoficialią sha256 maišos funkciją. Pateikiamos 4 funkcijos: kasyba, iškastų blokų paieška, transakcijų paieška, "decentralizuotų" blokų kasimo imitacija (kasami 5 blokai vienu metu).

## Naudojimas
1. Parsisiųsti bc aplanką
2. Atsidarius aplanką bet kokioje integruotoje kūrimo aplinkoje į konsolę (CMD) suvesti šias komandas:
```
g++ -o blockchain blockchain.cpp hashFunc.cpp sha256.c
./blockchain
```


