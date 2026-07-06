-- Zadanie: Sklep-AGD - Spójność

select * from produkty order by id;
select * from pralki order by id_produktu;
select * from lodowki order by id_produktu;

start transaction;
    insert into produkty (id, cena, kolor, klasa_energetyczna)
        values (100, 800.00, 'biały', 'A');

    insert into pralki (id_produktu, pojemnosc_znamionowa, roczne_zuzycie_wody, klasa_prania)
        values (100, 5, 7500, 'A');
commit;

select * from produkty order by id;
select * from pralki order by id_produktu;
select * from lodowki order by id_produktu;