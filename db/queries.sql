-- 1. Минимум, среднее и максимум по каждому датчику (таблица readings).
-- Отдельно от AUTO и TEST

SELECT
    sensor,
    mode,
    MIN(value) as min_value,
    ROUND(AVG(value), 2) AS avg_value,
    MAX(value) AS max_value
FROM readings
GROUP BY sensor, mode
ORDER BY sensor, mode;

-- 2. Все события по порядку времени (таблица events).

SELECT
    n,
    t_s,
    type,
    message,
    mode
FROM events
ORDER BY t_s, id;

-- 3. Количество записей в каждой таблице.

SELECT 'readings' AS table_name, COUNT(*) as total
FROM readings

UNION ALL

SELECT 'events', COUNT(*)
FROM events;

-- 4. Последние 10 показаний

SELECT
    n,
    t_s,
    sensor,
    value,
    mode
FROM readings
ORDER BY id DESC
LIMIT 10;