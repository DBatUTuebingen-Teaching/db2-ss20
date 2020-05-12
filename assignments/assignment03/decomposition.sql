DROP TABLE t CASCADE;
CREATE TABLE t (
  id INT,
  a INT,
  b CHAR(1),
  c INT,
  d CHAR(1)
);

INSERT INTO t VALUES 
(1,6,'a',1,'f'),
(2,7,'b',2,'g'),
(3,8,'c',1,'f'),
(4,9,'d',2,'g'),
(5,0,'e',1,'f');
