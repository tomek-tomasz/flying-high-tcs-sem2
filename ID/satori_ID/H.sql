--ZAD1
SELECT DISTINCT
    status,
    COUNT(problem_id)
FROM submits 
NATURAL JOIN checks
GROUP BY status;
----
--ZAD2
WITH RankedChecks AS (
    SELECT 
        task_id,
        cost,
        RANK() OVER (
            PARTITION BY task_id 
            ORDER BY 
                CAST(NULLIF(split_part(cost, '-', 1), '') AS numeric) DESC NULLS LAST, 
                CAST(NULLIF(split_part(cost, '-', 2), '') AS numeric) DESC NULLS LAST
        ) AS rnk
    FROM checks
    WHERE status = 'OK'
),
MaxCosts AS (
    SELECT 
        task_id,
        MAX(cost) AS max_cost,
        COUNT(*)::int AS liczba_rozwiazan
    FROM RankedChecks
    WHERE rnk = 1
    GROUP BY task_id
)
SELECT 
    p.short_name,
    t.task_name,
    m.max_cost,
    COALESCE(m.liczba_rozwiazan, 0) AS liczba_rozwiazan
FROM tasks t
JOIN problems p ON t.problem_id = p.problem_id
LEFT JOIN MaxCosts m ON t.task_id = m.task_id;
----
--ZAD3
SELECT name, COALESCE(SUM(sum_problem), 0)::NUMERIC(11,2)
FROM
(
    SELECT user_id, name, problem_id, COALESCE(SUM(score) / sum_max_score * 100, 0) sum_problem, sum_max_score , SUM(score) 
    FROM
    (
        SELECT u.user_id, name, p.problem_id, t.task_id, MAX(COALESCE(score,0))::NUMERIC score, x.sum_max_score::NUMERIC
        FROM users u
        LEFT JOIN submits s ON u.user_id = s.user_id
        LEFT JOIN checks c ON s.submit_id = c.submit_id
        LEFT JOIN tasks t ON c.task_id = t.task_id
        LEFT JOIN problems p ON t.problem_id = p.problem_id
        LEFT JOIN (
            SELECT problem_id, SUM(max_score) sum_max_score
            FROM tasks NATURAL JOIN problems
            GROUP BY problem_id
        ) x ON p.problem_id = x.problem_id
        GROUP BY u.user_id, name, p.problem_id, x.sum_max_score, t.task_id
    )
    GROUP BY user_id, name, problem_id, sum_max_score
)
GROUP BY user_id, name;
----
--ZAD4
CREATE OR REPLACE FUNCTION f(n BIGINT)
    RETURNS BIGINT AS
$$
BEGIN
    IF n % 2 = 0 THEN RETURN n/2;
    ELSE RETURN 3*n + 1;
    END IF;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION collatz(n BIGINT)
    RETURNS BIGINT AS
$$
DECLARE
    m BIGINT;
BEGIN

    m = 0;
    WHILE n != 1 LOOP
        m = m + 1;
        n = f(n);
    END LOOP;
    RETURN m;
END;
$$
LANGUAGE plpgsql;
----
--ZAD5
CREATE OR REPLACE FUNCTION wstrzymane_uprawnienia(zadana_data DATE)
    RETURNS TABLE(  pesel CHARACTER(11),
                    imie CHARACTER VARYING,
                    nazwisko CHARACTER VARYING,
                    last_data DATE) AS
$$
BEGIN
    RETURN QUERY
    SELECT 
        k.pesel,
        k.imie,
        k.nazwisko,
        ou.od
    FROM kierowcy k
    NATURAL JOIN ograniczenia_uprawnien ou
    WHERE od <= zadana_data
    AND zadana_data < "do"
    AND od = (  SELECT MAX(od)
                FROM ograniczenia_uprawnien u
                WHERE od <= zadana_data
                AND zadana_data < "do"
                AND u.pesel = k.pesel);
END;
$$
LANGUAGE plpgsql;
---- 
--ZAD6
CREATE OR REPLACE FUNCTION punkty_karne()
    RETURNS TRIGGER AS 
$punkty_karne$
DECLARE
    sum_until_now int;
    new_points int;
BEGIN
    sum_until_now = (   SELECT SUM(punkty)
                        FROM wykroczenia w
                        JOIN mandaty m ON w.id = m.id_wykroczenia 
                        WHERE NEW.pesel = m.pesel
                        and m.data > NEW.data - INTERVAL '1 year'
                        );
    IF sum_until_now > 24 THEN
        INSERT INTO ograniczenia_uprawnien VALUES (NEW.pesel, NEW.data, NEW.data + INTERVAL '3 months' - INTERVAL '1 day', NULL);
    END IF;
    RETURN NEW;
END;
$punkty_karne$
LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER punkty_karne AFTER INSERT ON mandaty
FOR EACH ROW EXECUTE PROCEDURE punkty_karne();
----