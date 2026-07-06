--ZAD1
SELECT NAZWA
FROM PRODUKTY P
WHERE P.ID_KATEGORIA = 
(SELECT ID_KATEGORIA
FROM PRODUKTY 
WHERE NAZWA = 'Piórnik duży');
----
--ZAD2
SELECT NAZWA
FROM PRODUKTY P 
WHERE ID_KATEGORIA = ANY 
(SELECT ID_KATEGORIA
FROM KATEGORIE 
WHERE NADKATEGORIA IS NOT NULL);
----
--ZAD3A
SELECT NAZWA 
FROM KATEGORIE K
WHERE 3 <= (
    SELECT COUNT(*)
    FROM PRODUKTY P
    WHERE P.ID_KATEGORIA = K.ID_KATEGORIA 
);
----
--ZAD3B
SELECT (
    SELECT DISTINCT NAZWA 
    FROM KATEGORIE K 
    WHERE K.ID_KATEGORIA = P.ID_KATEGORIA
)
FROM PRODUKTY P
GROUP BY id_kategoria
HAVING COUNT(*)>=3
;
----
--ZAD3C
SELECT K.NAZWA
FROM PRODUKTY P
JOIN kategorie k
ON p.id_kategoria = k.id_kategoria
GROUP BY p.id_kategoria, k.nazwa
HAVING COUNT(*)>=3
;
----
--ZAD4
SELECT *
FROM RABATY R 
WHERE AGE(DATA_DO, DATA_OD) = 
(SELECT
MAX(AGE(DATA_DO, DATA_OD))
FROM RABATY);
----
--ZAD5
SELECT *
FROM KATEGORIE K
WHERE VAT < ANY
(SELECT VAT
FROM KATEGORIE 
WHERE NADKATEGORIA = K.ID_KATEGORIA);
----
--ZAD6
SELECT ID_ZAMOWIENIA
FROM PRODUKTY_ZAMOWIENIA PZ
GROUP BY ID_ZAMOWIENIA
HAVING SUM(ILOSC) >= ALL
(SELECT SUM(ILOSC)
FROM PRODUKTY_ZAMOWIENIA
GROUP BY ID_ZAMOWIENIA);
----
--ZAD7
SELECT NAZWA , J.C
FROM PRODUKTY P
JOIN
(SELECT KOD_PRODUKTU, COUNT(DATA_WPROWADZENIA) C
FROM HISTORIA_CEN HC
WHERE EXTRACT(MONTH FROM DATA_WPROWADZENIA) = 4
GROUP BY KOD_PRODUKTU
HAVING COUNT(DATA_WPROWADZENIA)>=2
) J ON J.KOD_PRODUKTU = P.KOD_PRODUKTU;
----
--ZAD8
WITH RECURSIVE PRZODEK AS (

    SELECT ID_KATEGORIA, NAZWA
    FROM KATEGORIE
    WHERE NADKATEGORIA IS NULL

    UNION ALL

    SELECT K.ID_KATEGORIA, P.NAZWA
    FROM KATEGORIE K JOIN PRZODEK P ON K.NADKATEGORIA = P.ID_KATEGORIA
)
SELECT K.NAZWA, P.NAZWA
FROM PRZODEK P
JOIN KATEGORIE K 
ON P.ID_KATEGORIA = K.ID_KATEGORIA;
----
--ZAD9
SELECT P.NAZWA , ROUND(CENA_NETTO*(1 + VAT/100),2)
FROM PRODUKTY P
JOIN HISTORIA_CEN HC
ON P.KOD_PRODUKTU = HC.KOD_PRODUKTU
JOIN KATEGORIE K
ON P.ID_KATEGORIA = K.ID_KATEGORIA
WHERE DATA_WPROWADZENIA =
(SELECT MAX(DATA_WPROWADZENIA)
FROM PRODUKTY PW
JOIN HISTORIA_CEN HC
ON PW.KOD_PRODUKTU = HC.KOD_PRODUKTU
WHERE PW.KOD_PRODUKTU = P.KOD_PRODUKTU);
----
--ZAD10
SELECT P.NAZWA, ROUND((CENA_NETTO * (1 + K.VAT / 100)) - COALESCE(SUM(ZNIZKA), 0), 2)
FROM PRODUKTY P
JOIN KATEGORIE K ON P.ID_KATEGORIA = K.ID_KATEGORIA
JOIN HISTORIA_CEN HC ON P.KOD_PRODUKTU = HC.KOD_PRODUKTU
LEFT JOIN RABATY_PRODUKTY RP ON P.KOD_PRODUKTU = RP.ID_PRODUKTU
LEFT JOIN Rabaty R ON RP.ID_RABATU = R.ID_RABATU 
                   AND HC.DATA_WPROWADZENIA >= R.DATA_OD 
                   AND HC.DATA_WPROWADZENIA <= R.DATA_DO
WHERE HC.DATA_WPROWADZENIA = (
    SELECT MAX(DATA_WPROWADZENIA)
    FROM HISTORIA_CEN
    WHERE KOD_PRODUKTU = P.KOD_PRODUKTU
)
GROUP BY P.KOD_PRODUKTU, P.NAZWA, HC.CENA_NETTO, k.VAT;
----
--ZAD11
SELECT z.id_zamowienia, round(sum(pz.ilosc * hc.cena_netto*(1 + k.vat/100)),2)
FROM zamowienia z 
JOIN produkty_zamowienia pz
ON z.id_zamowienia = pz.id_zamowienia 
JOIN produkty p 
ON pz.produkt = p.kod_produktu
JOIN kategorie k
ON p.id_kategoria = k.id_kategoria
JOIN historia_cen hc
ON hc.kod_produktu = p.kod_produktu
WHERE hc.data_wprowadzenia = (
    SELECT max(data_wprowadzenia)
    FROM historia_cen hci
    WHERE hci.data_wprowadzenia <= z.data_zlozenia
    AND hc.kod_produktu = hci.kod_produktu
)
GROUP BY z.id_zamowienia;
----
--ZAD12
SELECT z.id_zamowienia,
ROUND(
    SUM(
        pz.ilosc * hc.cena_netto*(1 + k.vat/100)   
    ) -
    COALESCE((
        SELECT SUM(ri.znizka) znizka_produkt
        FROM produkty_zamowienia pzi
        JOIN rabaty_produkty rpi ON pzi.produkt = rpi.id_produktu
        JOIN rabaty ri ON rpi.id_rabatu = ri.id_rabatu
        WHERE z.data_zlozenia >= ri.data_od 
            AND (z.data_zlozenia <= ri.data_do OR ri.data_do IS NULL)
            AND pzi.ilosc >= rpi.min_ilosc
            AND pzi.id_zamowienia = z.id_zamowienia
    ),0) -
    COALESCE((
        SELECT SUM(ri.znizka) znizka_klient
        FROM rabaty_klienci rki
        JOIN rabaty ri ON rki.id_rabatu = ri.id_rabatu
        WHERE z.data_zlozenia >= ri.data_od 
            AND (z.data_zlozenia <= ri.data_do OR ri.data_do IS NULL)
            AND rki.id_zamowienia = z.id_zamowienia
    ),0) 
    ,2
)
FROM zamowienia z 
JOIN produkty_zamowienia pz ON z.id_zamowienia = pz.id_zamowienia 
JOIN produkty p ON pz.produkt = p.kod_produktu
JOIN kategorie k ON p.id_kategoria = k.id_kategoria
JOIN historia_cen hc ON hc.kod_produktu = p.kod_produktu
WHERE hc.data_wprowadzenia = (
    SELECT max(hci.data_wprowadzenia)
    FROM historia_cen hci
    WHERE hci.data_wprowadzenia <= z.data_zlozenia
        AND hc.kod_produktu = hci.kod_produktu
)
GROUP BY z.id_zamowienia, z.data_zlozenia;
----