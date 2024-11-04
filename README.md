# Blockchain (V0.1)
## Aprašas
Realizuota pati paprasčiausia blokų grandinės versija, naudojanti visų bloko transakcijų ID maišos reikšmę ir neoficialią sha256 maišos funkciją. Pateikiamos trys funkcijos: kasybos,  iškastų blokų suradimas pagal id, transakcijų paieškų

## Naudojimas
1. Parsisiųsti bc aplanką
2. Atsidarius aplanką bet kokioje integruotoje kūrimo aplinkoje į konsolę (CMD) suvesti šias komandas:
```
g++ -o blockchain blockchain.cpp hashFunc.cpp sha256.c
./blockchain
```



