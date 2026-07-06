--ZAD1
SELECT
CASE
    WHEN language = 1 THEN 'C++'
    WHEN language = 2 THEN 'C'
    WHEN language = 3 THEN 'Pascal'
    WHEN language = 4 THEN 'Scheme'
    WHEN language = 5 THEN 'Perl'
    WHEN language = 6 THEN 'Java'
    WHEN language = 7 THEN 'C#'
END "language"
, 
count(*) "submits"
FROM submits
GROUP BY language
ORDER BY 2 DESC;
----
--ZAD2
SELECT
shortname "name",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 8) "ok",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 7) "ans",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 5) "tle",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 4) "rte",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 14) "rte",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 3) "rte",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 2) "cmp",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 1) "rul",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 11) "hea",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id AND status = 6) "int",
(SELECT CASE WHEN COUNT(*) = 0 THEN NULL ELSE COUNT(*) END FROM submits WHERE problemsid = p.id) "all"
FROM problems p
ORDER BY 1;
----
--ZAD3
SELECT
    p.shortname "name",
    NULLIF(COUNT(CASE WHEN s.max_score = 1 THEN 1 END), 0) "100",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.9 AND s.max_score < 1 THEN 1 END), 0) "100-90",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.8 AND s.max_score < 0.9 THEN 1 END), 0) "90-80",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.7 AND s.max_score < 0.8 THEN 1 END), 0) "80-70",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.6 AND s.max_score < 0.7 THEN 1 END), 0) "70-60",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.5 AND s.max_score < 0.6 THEN 1 END), 0) "60-50",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.4 AND s.max_score < 0.5 THEN 1 END), 0) "50-40",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.3 AND s.max_score < 0.4 THEN 1 END), 0) "40-30",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.2 AND s.max_score < 0.3 THEN 1 END), 0) "30-20",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0.1 AND s.max_score < 0.2 THEN 1 END), 0) "20-10",
    NULLIF(COUNT(CASE WHEN s.max_score >= 0 AND s.max_score < 0.1 THEN 1 END), 0) "10-0",
    NULLIF(COUNT(s.usersid), 0) "all"
FROM problems p
LEFT JOIN (
    SELECT 
        problemsid, 
        usersid, 
        ROUND(CAST(MAX(COALESCE(ocena, 0)) AS NUMERIC), 4) as max_score
    FROM submits
    GROUP BY problemsid, usersid
) s ON s.problemsid = p.id
GROUP BY p.id, p.shortname
ORDER BY 1;
----