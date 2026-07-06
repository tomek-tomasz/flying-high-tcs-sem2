--ZAD1
CREATE OR REPLACE FUNCTION abstrakcja()
RETURNS TRIGGER AS $$
DECLARE
    czy_lodowka BOOLEAN;
    czy_pralka BOOLEAN;
BEGIN
    SELECT EXISTS(SELECT 1 FROM lodowki WHERE id_produktu = NEW.id) INTO czy_lodowka;
    SELECT EXISTS(SELECT 1 FROM pralki WHERE id_produktu = NEW.id) INTO czy_pralka;

    IF NOT czy_lodowka AND NOT czy_pralka THEN
        RAISE NOTICE 'BLAD';
    END IF;

    IF czy_lodowka AND czy_pralka THEN
        RAISE NOTICE 'BLAD';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE CONSTRAINT TRIGGER trg_produkt_po_insercie
AFTER INSERT ON produkty
DEFERRABLE INITIALLY DEFERRED
FOR EACH ROW EXECUTE PROCEDURE abstrakcja();


CREATE OR REPLACE FUNCTION pralka()
RETURNS TRIGGER AS $$
BEGIN
    IF EXISTS (SELECT 1 FROM pralki WHERE id_produktu = NEW.id_produktu) THEN
        RAISE NOTICE 'BLAD';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_lodowki
BEFORE INSERT ON lodowki
FOR EACH ROW EXECUTE PROCEDURE pralka();

CREATE OR REPLACE FUNCTION lodowka()
RETURNS TRIGGER AS $$
BEGIN
    IF EXISTS (SELECT 1 FROM lodowki WHERE id_produktu = NEW.id_produktu) THEN
        RAISE NOTICE 'BLAD';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_pralki
BEFORE INSERT ON pralki
FOR EACH ROW EXECUTE PROCEDURE lodowka();
----