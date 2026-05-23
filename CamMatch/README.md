RULARE CAMMATCH CU MYSQL

1) Porneste MySQL Server.

2) O singura data, ruleaza in MySQL Workbench fisierul mysql_setup.sql:

CREATE DATABASE IF NOT EXISTS cammatch_final CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS 'cammatch_user'@'localhost' IDENTIFIED BY 'cammatch123';
GRANT ALL PRIVILEGES ON cammatch_final.* TO 'cammatch_user'@'localhost';
FLUSH PRIVILEGES;

3) In terminal, in folderul unde este pom.xml:

mvn spring-boot:run

4) Deschide aplicatia:

http://localhost:8080

5) Baza de date se vede in MySQL Workbench:

USE cammatch_final;
SELECT * FROM cameras;
SELECT id, username, email, password, role FROM users;
SELECT * FROM camera_ratings;
SELECT * FROM user_cameras;

CONTURI DEMO NOI

Administrator:
Email: admin@cammatch.demo
Parola: Admin2026!

Utilizator 1:
Email: ana.popescu@cammatch.demo
Parola: Ana2026!

Utilizator 2:
Email: mihai.ionescu@cammatch.demo
Parola: Mihai2026!

Utilizator 3:
Email: maria.stan@cammatch.demo
Parola: Maria2026!

Utilizator 4:
Email: andrei.dumitru@cammatch.demo
Parola: Andrei2026!

Utilizator 5:
Email: vlad.marin@cammatch.demo
Parola: Vlad2026!

OBSERVATII

- La prima pornire a acestei variante, aplicatia elimina utilizatorii demo vechi si creeaza automat administratorul plus cei 5 utilizatori normali de mai sus.
- Parolele sunt salvate criptat cu BCrypt in tabelul users.
- In panoul Admin > Utilizatori se pot vedea emailurile si parolele criptate.
- In panoul Admin > Camere si Admin > Utilizatori poti sorta tabelul dand click pe antete precum ID, Camera, Tip, Rating, Pret, Username sau Email.
- In pagina Camere a fost scoasa sectiunea de cautare.
- Camera adaugata din profil se salveaza in tabelul user_cameras si apare si in lista generala din tabelul cameras.
- Formularul de la profil permite completarea campurilor: brand, model, tip, fotografie, rezolutie, autonomie, senzor, video, pret, imagine si descriere.
- Datele sunt salvate in MySQL in timp real. Cand adaugi camere, utilizatori, ratinguri sau postari din aplicatie, apar imediat in baza cammatch_final.

Daca vrei sa folosesti alt user/parola MySQL, modifica in src/main/resources/application.properties:
spring.datasource.username=...
spring.datasource.password=...

## Ratinguri demo variate
Versiunea aceasta adauga automat ratinguri demo variate pentru camere, folosind cei 5 utilizatori normali demo.
Unele camere raman intentionat `Not rated`, pentru a demonstra si cazul fara evaluari.
Pentru o baza existenta, poti rula manual si scriptul `seed_varied_demo_ratings.sql` in MySQL Workbench.

## Favorite si comentarii demo
Versiunea aceasta adauga automat camere favorite pentru fiecare dintre cei 5 utilizatori normali demo.
De asemenea, creeaza postari si comentarii demo in forumurile unor camere, astfel incat sectiunea de forum si panoul Admin > Forum sa aiba continut demonstrabil.
Pentru o baza existenta, poti rula manual scriptul `seed_demo_favorites_and_comments.sql` in MySQL Workbench.
