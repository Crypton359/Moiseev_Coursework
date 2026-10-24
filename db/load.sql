BEGIN;
DELETE FROM readings;
DELETE FROM events;
DELETE FROM sqlite_sequence WHERE name IN ('readings','events');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(1,5,'s1',30,'TEST');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(1,5,'s2',0,'TEST');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(1,5,'s3',1,'TEST');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(2,10,'s1',30,'TEST');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(2,10,'s2',0,'TEST');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(2,10,'s3',1,'TEST');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(3,15,'s1',265.98,'AUTO');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(3,15,'s2',0,'AUTO');
INSERT INTO readings(n,t_s,sensor,value,mode) VALUES(3,15,'s3',1,'AUTO');
INSERT INTO events(n,t_s,type,message,mode) VALUES(3,15,'THRESHOLD',NULL,'AUTO');
COMMIT;

