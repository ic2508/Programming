<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Adaugă judecător</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />

<body class="page-justice">

<div class="justice-card" style="width:480px;">

<%
    String nume = request.getParameter("Nume_Judecator");
    String prenume = request.getParameter("Prenume_Judecator");
    String cnp = request.getParameter("CNP");
    String data = request.getParameter("Data_Nasterii");
    String grad = request.getParameter("Grad");

    if (nume != null) {

        jb.connect();

        try {
            if (jb.existaCNP(cnp)) {
%>
                <h2 class="justice-title" style="color:#c0392b;">
                    ❌ CNP deja existent
                </h2>

                <p>
                    Există deja un judecător cu acest CNP!
                </p>

                <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='nou_judecator.jsp'">
    		⬅️ Înapoi
			</button>
<%
            } else {
                jb.adaugaJudecator(nume, prenume, cnp, data, grad);
%>
                <h2 class="justice-title" style="color:#27ae60;">
                    ✅ Judecător adăugat
                </h2>

                <p>
                    Judecătorul a fost adăugat cu succes!
                </p>

                <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='tabela_judecatori.jsp'">
    		⬅️ Înapoi la tabel
			</button>
<%
            }
        } catch (SQLException e) {
%>
            <h2 class="justice-title" style="color:#c0392b;">
                ❌ Eroare la adăugare
            </h2>

            <p>
                Datele introduse sunt invalide sau CNP-ul există deja!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="location.href='nou_judecator.jsp'">
    		⬅️ Înapoi
			</button>
<%
        }

        jb.disconnect();

    } else {
%>

        <h2 class="justice-title">⚖️ Adaugă judecător ⚖️</h2>

        <form action="nou_judecator.jsp" method="post">

            <label>Nume:</label>
            <input type="text" name="Nume_Judecator" class="justice-btn" required>

            <br><br>

            <label>Prenume:</label>
            <input type="text" name="Prenume_Judecator" class="justice-btn" required>

            <br><br>

            <label>CNP:</label>
            <input type="text" name="CNP" class="justice-btn"
                   pattern="[0-9]{13}" title="CNP trebuie să aibă 13 cifre" required>

            <br><br>

            <label>Data nașterii:</label>
            <input type="date" name="Data_Nasterii" class="justice-btn" required>

            <br><br>

            <label>Grad:</label>
            <input type="text" name="Grad" class="justice-btn" required>

            <br>

            <button type="submit" class="justice-btn success">
    			➕ Adaugă judecător
			</button>


        </form>

        <div class="justice-nav-row">
            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>

    		<button type="button"
            class="justice-btn secondary"
            onclick="location.href='index.html'">
        	🏠 Acasă
    		</button>
        </div>

<%
    }
%>

</div>

</body>
</html>
