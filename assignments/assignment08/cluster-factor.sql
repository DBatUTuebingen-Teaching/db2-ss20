DROP TABLE indexed;
CREATE TABLE indexed (
    a   int PRIMARY KEY,
    b   text,
    c   numeric(3,2)
);

INSERT INTO indexed(a,b,c)
    SELECT i, md5(i::text), sin(i)
    FROM   generate_series(1,1000000) AS i;

ALTER INDEX indexed_pkey RENAME TO indexed_a;
CREATE INDEX indexed_c_a ON indexed USING btree (c,a);

CLUSTER indexed USING indexed_c_a;
ANALYZE indexed;