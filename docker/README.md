
# Docker Installation

1. First you have to install the _Docker Engine_, which is available on Linux, macOS, and Windows 10.
  For instructions, checkout: https://docs.docker.com/engine/install/
  For macOS, and Windows 10, install the Docker Desktop App.

2. Install Docker-Compose
  If you are Linux based, you have to install Docker-Compose separately.
  Instructions can be found here: https://docs.docker.com/compose/install/

3. Check your installation.
  
  Once you have completed the installation steps, open a terminal session and make sure that your installation of docker works:

  ~~~none
  ❯ docker --version
  Docker version 19.03.8, build afacb8b

  ❯ docker-compose --version
  docker-compose version 1.25.4, build 8d51620a
  ~~~

# Setup Postgres

If everything is installed correctly, open a terminal session and change directory to where the docker-compose.yml file is located.

To start the database systems PostgreSQL12 and MonetDB use `docker-compose up -d`. This command will download all docker images from http://dockerhub.com and run everything deamonised (which means, that it will run in the background until you stop it!).

⚠ To stop the services use `docker-compose down` or `docker-compose down -v` IFF you want to delete all database files as well.

## Create a new user

To get things started, create a new user and a database. Make sure the PostgreSQL server is running before you start. Use `docker-compose ps -a` to do so.

In order to connect to the database system we do not have to install any packages locally, everything required comes bundled with the docker image.

Running `docker exec -it pg12 psql -U postgres -d postgres` opens a psql session inside the docker container.

To create a new user insert: 
~~~
CREATE ROLE root SUPERUSER CREATEDB INHERIT LOGIN;
CREATE DATABASE root;
\q
~~~

You can now use `docker exec -it pg12 psql` without the `-U` and `-d` flags.

# Howto use MonetDB

To enter the docker container, use `docker exec -it monetdb bash`

## Create a Database

Create a new database `db2` (and release it to "operational mode") with the following commands:

```
$ monetdb create db2
$ monetdb release db2
```

## Start the _MonetDB Client_

Connect as user `monetdb` to the database `db2` using the `mclient` tool (the default password is `monetdb`):
```
$ mclient -u monetdb -d db2
password: monetdb
```

### Language: _SQL_
From within the client, run some first _SQL_ queries to create and show table `test`:
```sql
sql>CREATE TABLE test (x int);
sql>INSERT INTO test VALUES (1),(10);
sql>SELECT * FROM test;
```

### Language: _MAL_
To start a client session accepting _MAL_ code instead of _SQL_ use the argument `-l mal`:
```bash
$ mclient -u monetdb -d db2 -l mal
password: monetdb
```
and enter the following _MAL_ program to print the _BAT_ of column `x` of table `test`:
```
sql.init();
c := sql.mvc();
x:bat[:int] := sql.bind(c, "sys", "test", "x", 0);
io.print(x);
```

