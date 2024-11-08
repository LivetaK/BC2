# BC2

<h1>V0.2</h1>
<h2>Kaip veikia programa?</h2>
Programa leidžia pasirinkti - ar generuoti blokų grandinę, ar imituoti decentralizuotą blokų kasimą.
<br>
<br>
Pasirinkus blokų grandinės generavimą, programa paima 100 atsitiktinių transakcijų, jas prideda į naują bloką kartu su kitais bloko elementais. Bloko kasimo procese yra imami visi antraštės elementai kartu su nonce ir transakcijų merkle root hash ir generuojama maišos reikšmė su tam tikru kiekiu nulių priekyje. Kai blokų grandinė yra sugeneruojama, programa leidžia "ištraukti" informaciją iš jos su komandomis "outTransaction" ir "outBlock". Atitinkamai yra išvedama arba tam tikra transakcija, arba tam tikras blokas.
<br>
<br>
Pasirinkus decentralizuotą kasimą, programa suskaiciuoja pirmojo genesis bloko reikšmę ir ją prideda į visus 5 blokus kandidatus, kurie taip pat yra atsitiktinai sudaromi. Tada programa kasa blokus po vieną kas 5 sekundes tol, kol randa kažkurio iš jų maišos funkciją. visas kasimo procesas yra išvedamas į ekraną.


<h1>V0.1</h1>
<h2>Kaip veikia programa?</h2>

Šioje programoje yra realizuota labai supaprastinta blokų grandinė. Kol kas nėra realizuotas dvejetainis merkle medis, vietoj jo naudojama visų bloko transakcijų ID maišos reikšmė. Yra funkcija, kuri visus bloko duomenis išveda į konsolę. Programuojant buvo naudojamas enkapsuliavimas, buvo parašyti konstruktoriai.

<h2>Kas laukia kitoje versijoje:</h2>

1. Realizuotas arba iš libbitcoin-system integruotas Merkle tree algoritmas;
2. Pridėta daugiau funkcijų, leidžiančių analizuoti grandinę;
3. Patobulintas transakcijų tikrinimas, kad labiau atitiktų realiai naudojamas blokų grandines;
4. Patobulintas blokų kasimo procesas.
