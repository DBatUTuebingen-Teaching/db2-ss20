-- Enable buffer cache statistics view in this database
CREATE EXTENSION pg_buffercache;


-- Perform measurements, insert results into table 'results'.
-- IMPORTANT: insert filenodes of relation orders and index orders_key_idx.
CREATE OR REPLACE FUNCTION run(n int) RETURNS VOID 
AS $$
DECLARE
    key int;
BEGIN
    -- create a table to store the measurements.
    DROP TABLE IF EXISTS results;
    CREATE TEMP TABLE results(
        run_nr integer, 
        realtion_pages integer, 
        index_pages integer
    );

    FOR i in 1 .. n LOOP
        -- Look up a random key in attribute o_orderkey
        key := trunc(random() * (15000-1) + 1);
        PERFORM o_custkey FROM orders WHERE o_orderkey = key;

        -- Insert number of current index and realtion pages in the buffer to results
        INSERT INTO results(run_nr, realtion_pages, index_pages) 
            -- YOUR QUERY on pg_buffercache
    END LOOP;
END;
$$ language plpgsql;