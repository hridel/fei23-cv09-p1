# Cvičení 9
## Zpracování CSV souboru

Mějme datový CSV _(comma separated values)_ soubor [data/stats.csv](data%2Fstats.csv) obsahující statistiky hráčů zámořské NHL.


**Hlavička a první záznam souboru**

| Player Name | Team | Pos | Games | G | A | Pts | +/- | PIM | SOG | GWG | PPG | PPA | SHG | SHA | Hits | BS |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Connor McDavid | EDM | C | 80 | 64 | 87 | 151 | 22 | 36 | 340 | 11 | 21 | 48 | 4 | 3 | 89 | 39 |

---

Nadefinujte vlastní datový typ `Player` postavený na struktuře reprezentující záznam odpovídající jednomu řádku dat ze zmiňovaného CSV soubor.
Tedy následující hodnoty:
* **Player Name** – jméno hráče
* **Team** – zkratka klubu, za který hráč hraje
* **Pos** – zkratka pozice, na které hráč hraje
  * **C** – center
  * **LW** – levé křídlo
  * **RW** – pravé křídlo
  * **D** – obránce
* **Games** – počet odehraných zápasů
* **G** – počet vstřelených branek
* **A** – počet gólových nahrávek
* **Pts** – celkový počet bodů
* **+/-** – plus-minus hodnocení
* **PIM** – počet trestných minut
* **SOG** – počet střel na bránu
* **GWG** – počet vítězných branek
* **PPG** – počet vstřelených branek v přesilovkách
* **PPA** – počet gólových nahrávek v přesilovkách
* **SHG** – počet vstřelených branek v oslabeních
* **SHA** – počet gólových nahrávek v oslabeních
* **Hits** – počet "hitů"
* **BS** – počet blokovaných střel

Načtěte data do dynamicky alokované (realokované) paměti.

Nabízejte uživateli textové menu (dokud nezvolí volbu "Ukončit program")
s těmito položkami:
```text
1 – TOP 5 (nejproduktivnějších hráčů kanadského bodování)
2 – Nejlepší střelec
3 – Nejtretanější hráč
4 – Obránce s nejvyšším počtem asistencí

0 – Ukončit program
```

Na základě uživatelovy volby proveďte požadovanou akci.

V případě potřeby třídit pole, použijte "bubble sort" algoritmus.

---

**Užitečné funkce**

```c
char *strtok(char *__str, const char *__sep) 

long strtol(const char *__str, char **__endptr, int __base)

void *realloc(void *__ptr, size_t __size)
```


