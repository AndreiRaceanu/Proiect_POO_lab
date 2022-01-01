# Proiect_POO_lab

Am atasat 2 videouri cu 2 rulari diferite:o data cu user input, o data cu user input hardcodat;
Am atasat codul proect.cpp
Fara  sa fi hardcodat ceva, am primit de 2 ori acelasi rezultat(dupa cum o sa fie vazut si din cele 3 screenshot-uri cu rulari diferite). Rand() din c++ merge oricum f prost, initial am dorit sa fac o mapa intre supraveghetori si un team de concurenti
iar prima problema care a venit a fost criteriul de ordonare, asa ca ma decisesem sa dau override la operator ca sa ordoneze si sa nu imi dea eroare de template in felul urm:
bool operator < (const User& oth) const
        {
            return Debt < oth.Debt;
        }
 
in clasa User, si asta am si facut.
Urmatoarea eroare? ca erau mai multi cu acelasi debt desi range-ul pt rand() era f mare si am primit eroare de tamplate la stl, (rand() avand drept range de la 10.000 la 100000), m-am luat cu mainile de cap.)
Ce vreau sa spun este ca fara sa fi hardocat ceva am primit acelasi rezultat care e cel mai probabil datorat metodei Genken ptc rand() e doar de la 1 la 3 si da aceleasi valori care in final se anuleaza reciproc.
Am atasat si screnshot-urile.
