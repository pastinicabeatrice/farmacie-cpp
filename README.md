# Farmacie (C++)

Exemplu de programare orientată pe obiecte în C++ cu clasele `Farmacie` și `DistribuitorMedicamente`.

## Ce conține

- constructori, constructor de copiere, operator de atribuire și destructor (vector de salarii alocat dinamic)
- clasa imbricată `Farmacist`
- membru static (`salariuMinim`) cu metode statice
- supraîncărcarea operatorilor `[]`, `+=`, `==`, `>` și `<<`
- clasă prietenă (`DistribuitorMedicamente`)
- enum pentru modul de eliberare a medicamentelor

## Rulare

```
g++ farmacie.cpp -o farmacie
./farmacie
```

Sau se adaugă fișierul într-un proiect Visual Studio.
